/**
@file GUISystem.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "GUISystem.h"

#include "swInputLibrary/InputCore/KeyboardState.h"
#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGraphicAPI/Loaders/SoilTextureLoader/SoilTextureLoader.h"

#include "swInputLibrary/InputCore/Debugging/EventCapture.h"

#include <map>
#include <string>



namespace sw {
namespace gui
{

/// @todo This should be moved somewhere else.
INativeGUI*			CreateNativeGUI();



GUISystem*			GUISystem::m_instance = nullptr;


// ================================ //
//
GUISystem::GUISystem		( int argc, char** argv, INativeGUI* gui )
	:	m_cmdArgs( argc, argv )
	,	m_nativeGUI( gui )
	,	m_focusedWindow( nullptr )
	,	m_resourceManager( nullptr )
	,	m_renderingSystem( nullptr )
{
	m_instance = this;
}

// ================================ //
//
GUISystem::GUISystem		( int argc, char** argv, INativeGUI* gui, SetTestMode testMode )
	:	m_cmdArgs( argc, argv )
	,	m_nativeGUI( gui )
	,	m_focusedWindow( nullptr )
	,	m_resourceManager( nullptr )
	,	m_renderingSystem( nullptr )
{
	m_instance = this;

	m_guiConfig.IsTestMode = testMode == SetTestMode::True ? true : false;
}

// ================================ //
//
GUISystem::~GUISystem()
{
	for( auto window : m_windows )
		delete window;

	m_graphicApi->ReleaseAPI();
	delete m_resourceManager;
	delete m_graphicApi;
	delete m_nativeGUI;
}

//====================================================================================//
//			Main loop	
//====================================================================================//


/**@brief Application main loop.

@see Application*/
int					GUISystem::MainLoop()
{
	while( true )
	{
		bool end = MainLoopCore();
		if( end ) break;
	}

	CloseLogic();

	return 0;
}

/**@brief One step of main loop.
@todo Consider making this function virtual in future.

@return Returns true if application should end. Otherwise returns false.*/
bool				GUISystem::MainLoopCore()
{
	// Process native events.
	bool end = m_nativeGUI->MainLoop( m_guiConfig.UseBlockingMode );
	if( end ) return true;

	auto frameTime = m_clock.AdvanceFrame();

	HandleEvents( frameTime );

	// @todo How should it be done ??
	OnIdle( frameTime );
	RenderGUI( frameTime );

	return false;
}

/**@brief Processes messages and passes them to focused window.*/
void				GUISystem::HandleEvents		( const FrameTime& frameTime )
{
	for( auto window : m_windows )
		window->HandleInput( frameTime );
}

// ================================ //
//
void				GUISystem::RenderGUI		( const FrameTime& frameTime )
{
	if( m_guiConfig.RedrawOnlyFocused && m_focusedWindow )
	{
		m_renderingSystem->RenderTree( m_focusedWindow );
		m_focusedWindow->GetSwapChain()->Present( GetSyncInterval() );
	}

	if( !m_guiConfig.RedrawOnlyFocused )
	{
		for( auto window : m_windows )
		{
			m_renderingSystem->RenderTree( window );
			window->GetSwapChain()->Present( GetSyncInterval() );
		}
	}
}

// ================================ //
//
void				GUISystem::CloseLogic		()
{
	OnClosing();
}


//====================================================================================//
//			Initialization	
//====================================================================================//

/**@brief Invoke this function in application entry point (main).*/
ReturnResult		GUISystem::Init()
{
    ReturnResult result = Result::Success;

	result = result && Initialize();		// Initialize subsystems.
	result = result && OnInitialized();		// User initialization.

	m_clock.Start();	// Start clock as last in initialization.

	return result;
}


/**@brief GUI subsystems initialization.

If you need specific gui initialization in your application override this function.
You can set different GraphicApi or input api.*/
ReturnResult		GUISystem::Initialize()
{
	return DefaultInit( 1024, 768, "Window Tittle" );
}

/**@brief Makes initialization but leaves window creation for user.*/
ReturnResult		GUISystem::DefaultInitWithoutWindow	()
{
	ReturnResult result = Result::Success;

	result = result && DefaultInitResourceManager();
	result = result && DefaultInitPathsManager();
	result = result && DefaultInitGraphicAPI( m_guiConfig.DebugGraphics, true );
	result = result && DefaultInitNativeGUI();
	result = result && DefaultInitRenderingSystem();

	return result;
}

/**@brief Default GUI system initialization function.*/
ReturnResult    	GUISystem::DefaultInit				( uint16 width, uint16 height, const std::string& windowTitle )
{
    ReturnResult result = Result::Success;

	result = result && DefaultInitWithoutWindow();
	result = result && DefaultInitFirstWindow( width, height, windowTitle, true );

	return result;
}


/**@brief Default native GUI initialization.

Native GUI object is set in constructor. Here we initialize it.
Function creates native input object.*/
ReturnResult		GUISystem::DefaultInitNativeGUI		()
{
	NativeGUIInitData nativeGUIInit;
	nativeGUIInit.FocusChanged = fastdelegate::MakeDelegate( this, &GUISystem::OnFocusChanged );

	return m_nativeGUI->Init( nativeGUIInit );
}

/**@brief Default graphic api initialization.*/
ReturnResult		GUISystem::DefaultInitGraphicAPI	( bool debug, bool singleThreaded )
{
	// ResourceFactory creates api which is linked as library.
	m_graphicApi = ResourcesFactory::CreateAPIInitializer();

	GraphicAPIInitData graphicApiData;
	graphicApiData.CreateSwapChain = false;		// We will create swap chain and render target later with window.
	graphicApiData.SingleThreaded = singleThreaded;
	graphicApiData.UseDebugLayer = debug;

	auto result = m_graphicApi->InitAPI( graphicApiData );
	assert( result.IsValid() );

	return result;
}

/**@brief Initializes rendering system.

@note m_resourceManager and m_graphicApi must be already initialized;*/
ReturnResult    	GUISystem::DefaultInitRenderingSystem	()
{
	if( !m_graphicApi )
		return "RenderingSystem initialization: precondition failed: GraphicAPI is nullptr.";

	if( !m_resourceManager )
        return "RenderingSystem initialization: precondition failed: ResourceManager is nullptr.";

	IRendererOPtr renderer( m_graphicApi->CreateRenderer( RendererUsage::USE_AS_IMMEDIATE ) );
	m_renderingSystem = std::unique_ptr< RenderingSystem >( new RenderingSystem( m_resourceManager, m_pathsManager, std::move( renderer ) ) );

	return m_renderingSystem->InitializeRenderingSystem();
}

// ================================ //
//
ReturnResult    	GUISystem::DefaultInitFirstWindow		( uint16 width, uint16 height, const std::string& windowTitle, bool show )
{
	// Note: we must always initialize first focus window. This is probably hack, but OnFocusChanged delegate won't be invoked.
	auto windowResult = CreateNativeHostWindow( width, height, windowTitle );
    if( windowResult.IsValid() )
    {
        m_focusedWindow->GotFocus();

        if( show )
            m_focusedWindow->GetNativeWindow()->Show();
        else
            m_focusedWindow->GetNativeWindow()->Hide();

        return Result::Success;
    }

    return windowResult.GetError();
}

// ================================ //
//
ReturnResult		GUISystem::DefaultInitPathsManager		()
{
    ReturnResult result = Result::Success;

	result = result && DefaultInitCorePaths();
	result = result && DefaultInitDependentPaths();

	return result;
}

// ================================ //
//
ReturnResult		GUISystem::DefaultInitCorePaths			()
{
    ReturnResult result = Result::Success;

    result = result && m_pathsManager->RegisterAlias( "$(TMP)", m_nativeGUI->GetOS()->GetTempDir() );
    result = result && m_pathsManager->RegisterAlias( "$(CoreGUI-Dir)", m_nativeGUI->GetOS()->GetApplicationDir() );

	return result;
}

// ================================ //
//
ReturnResult		GUISystem::DefaultInitDependentPaths	()
{
	/// @todo This should set hlsl or glsl directory depending on used graphic API.
	return m_pathsManager->RegisterAlias( "$(CoreGUI-Shader-Dir)", "$(CoreGUI-Dir)/Shaders/hlsl" );
}

/**@brief Function creates ResourceManager and calls default initialization.*/
ReturnResult		GUISystem::DefaultInitResourceManager	()
{
	m_resourceManager = new ResourceManager();
	return ResourceManagerInitImpl( m_resourceManager );
}

/**@brief This functions sets ResourceManager from parameter and calls default initialization.*/
ReturnResult		GUISystem::InitResourceManager			( ResourceManager* resourceManager )
{
	m_resourceManager = resourceManager;
	return ResourceManagerInitImpl( m_resourceManager );
}

// ================================ //
//
ReturnResult		GUISystem::ResourceManagerInitImpl		( ResourceManager* resourceManager )
{
    m_pathsManager = m_resourceManager->GetPathsManager();

    // GUI needs Textures loader to work.
    ///< @todo What to do if user adds his own Texture loader? We must avoid conflicts between them.
    resourceManager->RegisterLoader( std::make_shared< SoilTextureLoader >() );

	return Result::Success;
}

//====================================================================================//
//			Focus management	
//====================================================================================//

/**@brief Changes focused window.

Delegate for native GUI.*/
void				GUISystem::OnFocusChanged				( INativeWindow* window, bool value )
{
	if( !value )
	{
		// Only lost focus
		if( m_focusedWindow && m_focusedWindow->GetNativeWindow() == window )
		{
			m_focusedWindow->LostFocus();
			m_focusedWindow = nullptr;
		}
		//else
		// ReportError
	}
	else
	{
		// Previous window loses focus.
		if( m_focusedWindow && m_focusedWindow->GetNativeWindow() == window )
		{
			return;
		}
		else if( m_focusedWindow && m_focusedWindow->GetNativeWindow() != window )
		{
			m_focusedWindow->LostFocus();
			m_focusedWindow = nullptr;
		}

		// Find new window with focus.
		for( auto hostWindow : m_windows )
		{
			if( hostWindow->GetNativeWindow() == window )
			{
				m_focusedWindow = hostWindow;
				m_focusedWindow->GotFocus();
				break;
			}
		}

		//if( !m_focusedWindow )
		// ReportError
	}
}

//====================================================================================//
//			Windows creation	
//====================================================================================//


// ================================ //
//
Nullable< HostWindow* >     GUISystem::CreateNativeHostWindow	( uint16 width, uint16 height, const std::string& windowTitle )
{
	NativeWindowDescriptor init( windowTitle );
	init.Height = height;
	init.Width = width;

	return CreateNativeHostWindow( init );
}

// ================================ //
//
Nullable< HostWindow* >     GUISystem::CreateNativeHostWindow	( NativeWindowDescriptor& windowDesc )
{
	auto nativeWindow = m_nativeGUI->CreateWindow( windowDesc );
	
	assert( nativeWindow );
	if( !nativeWindow )
		return fmt::format( "Failed to create native window [{}].", windowDesc.WindowTitle );

	// In test mode we need to send event manually.
	input::InputInitInfo initInfo;
	if( m_guiConfig.IsTestMode )
		initInfo.EventCapturer = std::make_shared< input::EventCapture >();

	auto input = m_nativeGUI->UseNativeInput( nativeWindow, initInfo );

	// Create host window from underlying native window.
	HostWindow* hostWindow = new HostWindow( nativeWindow, input, m_resourceManager, m_graphicApi );
	m_windows.push_back( hostWindow );

	return hostWindow;
}

//====================================================================================//
//				Other functions
//====================================================================================//

/**@copydoc EngineObject::MemorySize*/
Size                GUISystem::GetMemorySize()
{
	Size size = sizeof( HostWindow );
	size += m_windows.capacity() * sizeof( HostWindow* );

	for( auto window : m_windows )
		size += window->GetMemorySize();

	return size;
}

/**@brief Gets number of commnad line arguments.

Function doesn't take program nameinto account .*/
int					GUISystem::NumCommandLineArgs()
{
	return m_cmdArgs.ArgsCount - 1;
}

/**@brief Returns command line argument. 0 is first argument
not program name.*/
const char*			GUISystem::CommandLineArg( int num )
{
	return m_cmdArgs.Arguments[ num - 1 ];
}

/**@brief Returns program name retrived from 0 command line argument.*/
const char*			GUISystem::ProgramPath()
{
	return m_cmdArgs.ProgramName();
}


//====================================================================================//
//			Internal implementation	
//====================================================================================//

// ================================ //
//
int					GUISystem::GetSyncInterval() const
{
	return m_guiConfig.UseVSync ? 1 : 0;
}

/**@brief */
GUISystem&			GUISystem::Get()
{
	return *m_instance;
}


}	// gui
}	// sw

