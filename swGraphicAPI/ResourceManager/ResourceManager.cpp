/**
@file ResourceManager.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "ResourceManager.h"

#include "swCommonLib/Common/ObjectDeleter.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/ResourcesFactory.h"



#include "swCommonLib/Common/MemoryLeaks.h"


using namespace DirectX;

//-------------------------------------------------------------------------------//
//							wersja DirectX11
//-------------------------------------------------------------------------------//

ResourceManager::ResourceManager()
{}



ResourceManager::~ResourceManager( )
{}




/** @brief Znajduje Loader pasuj�cy do pliku podanego w parametrze.
@param[in] path �cie�ka do pliku, dla kt�rej szukamy loadera.
@return Wska�nik na odpowiedni loader lub nullptr, je�eli nie znaleziono pasuj�cego.*/
//ILoader* ResourceManager::FindLoader( const std::wstring& path )
//{
//	for ( unsigned int i = 0; i <  m_loader.size( ); ++i )
//	if ( m_loader[i]->can_load( path ) )
//		return m_loader[i];
//	return nullptr;
//}




/**@brief Tworzy nowy render target.

Funkcja dodaje stworzony obiekt do tablicy m_renderTarget. Je�eli tekstury
bufora color�w, g��boko�ci i stencilu nie s� nullptrami, to i one s� dodawane do tablicy m_texture.

Tekstury te maj� nazwy jak render target + dodany jest cz�on
- ::color
- ::depth
- ::stencil

@todo Przy dodawaniu tekstur nie jest sprawdzane czy one ju� istniej�. Trzeba albo to sprawdza�, albo zapewni�
np. jak�� polityk� nazewnictwa, �e w ten spos�b nie nadpisujemy istniej�cej tekstury.

@param[in] name Nazwa identyfikuj�ca render target.
@param[in] renderTargetDescriptor Deskryptor opisuj�cy parametry render targetu.
@return Zwraca stworzony obiekt lub nullptr w przypadku niepowodzenia. Je�eli render target ju� istnia�, to zwracany jest istniej�cy obiekt.
*/
RenderTargetObject* ResourceManager::CreateRenderTarget( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	RenderTargetObject* newRenderTarget = m_renderTarget.get( name );
	if( !newRenderTarget )
	{
		newRenderTarget = ResourcesFactory::CreateRenderTarget( name, renderTargetDescriptor );
		if( !newRenderTarget )	return nullptr;

		m_renderTarget.UnsafeAdd( name, newRenderTarget );
		
		auto colorBuff = newRenderTarget->GetColorBuffer();
		if( colorBuff )
			m_texture.UnsafeAdd( Convert::FromString( colorBuff->GetFilePath().String(), std::wstring() ), colorBuff );

		auto depthBuffer = newRenderTarget->GetDepthBuffer();
		if( depthBuffer )
			m_texture.UnsafeAdd( Convert::FromString( depthBuffer->GetFilePath().String(), std::wstring() ), depthBuffer );

		auto stencilBuffer = newRenderTarget->GetStencilBuffer();
		if( stencilBuffer )
			m_texture.UnsafeAdd( Convert::FromString( stencilBuffer->GetFilePath().String(), std::wstring() ), stencilBuffer );
	}

	return newRenderTarget;
}



/**@brief Dodaje renderTarget do ResourceManagera, je�eli jeszcze nie istnia�.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@note Je�eli renderTarget ju� istnia� (jego nazwa), to ten podany w parametrze nie zostanie dodany.
Oznacza to, �e za jego zwolnienie odpowiada ten, kto go stworzy�. Trzeba zawsze sprawdzi� czy
zwr�cona warto�� jest tym samym co podali�my.

@todo Nie mo�e tak zosta�, �e kto� dodaje renderTarget i musi sprawdzi� czy nie dosta� innego. Nie mo�na
te� zmusza� kogo� do zwalniania pami�ci po renderTargecie. Wog�le dodawanie renderTarget�w musi si� odbywa� jako� inaczej.
Najlepiej, �eby by�y one tworzone przez ResourceManager, ale wtedy trzeba wymy�le� spos�b dodawania renderTargetu zwi�zanego z buforem okna.

@param[in] renderTarget renderTarget, kt�ry ma zosta� dodany.
@param[in] name Nazwa renderTargetu. Do materia�u b�dzie mo�na si� odwo�a� podaj�c ci�g znak�w
@return Zwraca wska�nik na dodany renderTarget.*/
RenderTargetObject* ResourceManager::AddRenderTarget( RenderTargetObject* renderTarget, const std::wstring& name )
{
	RenderTargetObject* newRenderTarget = m_renderTarget.get( name );
	if ( !newRenderTarget )
		m_renderTarget.UnsafeAdd( name, renderTarget );	// Dodali�my materia�

	return newRenderTarget;
}

/**@brief Dodaje vertex shader do ResourceManagera. Je�eli obiekt ju� istnia�, to nie jest tworzony nowy.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] fileName Nazwa pliku, w kt�rym znajduje si� vertex shader.
@param[in] shaderEntry Nazwa funkcji od kt�rej ma si� zacz�� wykonywanie shadera.
@return Zwraca obiekt dodanego shadera. Zwraca nullptr, je�eli shadera nie uda�o si� skompilowa�.*/
VertexShader* ResourceManager::LoadVertexShader( const std::wstring& fileName, const std::string& shaderEntry )
{
	VertexShader* shader = m_vertexShader.get( fileName );
	if ( !shader )
	{
		// Nie by�o shadera, trzeba go stworzy� i doda�
		shader = ResourcesFactory::CreateVertexShaderFromFile( fileName, shaderEntry );
		if ( !shader )		// shader m�g� mie� z�y format, a nie chcemy dodawa� nullptra do ResourceManagera
			return nullptr;

		m_vertexShader.UnsafeAdd( fileName, shader );	// Dodali�my tekstur�
	}

	return shader;
}

/**@brief Dodaje vertex shader do ResourceManagera. Je�eli obiekt ju� istnia�, to nie jest tworzony nowy.
Tworzy te� layout wierzcho�ka zwi�zany z tym shaderem i zwraca go w zmiennej layout.

Je�eli vertex shader wcze�niej istnia�, to stworzenie layoutu wymaga ponownego skompilowania shadera. Shader taki jest potem
kasowany i nie zostaje zdublowany w ResourceManagerze, ale niepotrzebna praca zostaje w�o�ona. Jest wi�c zadaniem programisty, �eby
do takich rzeczy dochodzi�o jak najrzadziej.

@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] fileName Nazwa pliku, w kt�rym znajduje si� vertex shader.
@param[in] shaderEntry Nazwa funkcji od kt�rej ma si� zacz�� wykonywanie shadera.
@param[out] layout W zmiennej umieszczany jest wska�nik na layout wierzcho�ka. Nawet je�eli shader si� nie skompilowa�, to pole mo�e mie� warto�� inn� ni� nullptr.
Dzieje si� tak wtedy, gdy layout istnia� ju� wcze�niej.
@attention Je�eli vertex shader wcze�niej istnia�, to stworzenie layoutu wymaga ponownego skompilowania shadera. Shader taki jest potem 
kasowany i nie zostaje zdublowany w ResourceManagerze, ale niepotrzebna praca zostaje w�o�ona. Jest wi�c zadaniem programisty, �eby
do takich rzeczy dochodzi�o jak najrzadziej.
@param[in] layoutDesc Deskryptor opisujacy tworzony layout.
@return Zwraca obiekt dodanego shadera. Zwraca nullptr, je�eli shadera nie uda�o si� skompilowa�.*/
VertexShader* ResourceManager::LoadVertexShader( const std::wstring& fileName,
													const std::string& shaderEntry,
													ShaderInputLayout** layout,
													InputLayoutDescriptor* layoutDesc )
{
	/// @todo Ten kod to jaki� totalny shit. Jak komu� si� b�dzie nudzi�o kiedy� (ha ha), to mo�e niech poprawi.
	*layout = nullptr;
	VertexShader* shader = m_vertexShader.get( fileName );
	VertexShader* newShader = nullptr;
	ShaderInputLayout* inputLayout = m_vertexLayout.get( layoutDesc->GetName() );


	// Tworzymy potrzebne obiekty
	if( !inputLayout )
	{
		// Tworzymy shader niezale�nie czy istnieje. Inaczej nie mogliby�my stworzy� layoutu.
		// Shader zostanie potem usuni�ty.
		newShader = ResourcesFactory::CreateVertexShaderFromFile( fileName, shaderEntry, layout, layoutDesc );
		if ( !newShader )		// shader m�g� mie� z�y format, a nie chcemy dodawa� nullptra do ResourceManagera
			return nullptr;		// layout te� jest nullptrem, nie trzeba si� martwi�.
	}
	else if( !shader )
	{
		// Layout istnieje, ale shader nie.
		newShader = ResourcesFactory::CreateVertexShaderFromFile( fileName, shaderEntry );
		*layout = inputLayout;	// Je�eli layout istnia�, to przepisujemy go na wyj�cie. Je�eli nie to i tak b�dzie nullptr.
		if ( !newShader )		// shader m�g� mie� z�y format, a nie chcemy dodawa� nullptra do ResourceManagera
			return nullptr;
	}
	else
	{// Wszystkie obiekty istania�y ju� wcze�niej.
		*layout = inputLayout;
		return shader;
	}

	// Nowo powsta�e obiekty musz� zosta� dodane do kontener�w.
	if ( !shader )
	{
		// Nie by�o shadera, trzeba go doda�
		m_vertexShader.UnsafeAdd( fileName, newShader );	// Dodali�my shader
		shader = newShader;
	}
	else
	{	// Shader ju� by�, wi�c kasujemy nowy
		// Destruktor jest prywatny, wi�c nie mo�emy kasowa� obiektu bezpo�rednio.
		ObjectDeleter< VertexShader>::delete_object( shader, ObjectDeleterKey< VertexShader>() );
	}

	if( !inputLayout )	// Layoutu nie by�o wcze�niej wi�c dodajemy.
		m_vertexLayout.UnsafeAdd( layoutDesc->GetName(), *layout );

	return shader;
}


/**@brief Dodaje pixel shader do ResourceManagera. Je�eli obiekt ju� istnia�, to nie jest tworzony nowy.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] fileName Nazwa pliku, w kt�rym znajduje si� pixel shader.
@param[in] shaderEntry Nazwa funkcji od kt�rej ma si� zacz�� wykonywanie shadera.
@return Zwraca obiekt dodanego shadera. Zwraca nullptr, je�eli shadera nie uda�o si� skompilowa�.*/
PixelShader* ResourceManager::LoadPixelShader				( const std::wstring& fileName, const std::string& shaderEntry )
{
	PixelShader* shader = m_pixelShader.get( fileName );
	if ( !shader )
	{
		// Nie by�o shadera, trzeba go stworzy� i doda�
		shader = ResourcesFactory::CreatePixelShaderFromFile( fileName, shaderEntry );
		if ( !shader )		// shader m�g� mie� z�y format, a nie chcemy dodawa� nullptra do ResourceManagera
			return nullptr;

		m_pixelShader.UnsafeAdd( fileName, shader );	// Dodali�my tekstur�
	}

	return shader;
}

GeometryShader*		ResourceManager::LoadGeometryShader	( const std::wstring& fileName, const std::string& shaderEntry )
{
	//GeometryShader* shader = m_geometryShader.get( fileName );
	//if ( !shader )
	//{
	//	// Nie by�o shadera, trzeba go stworzy� i doda�
	//	shader = ResourcesFactory::CreatePixelShaderFromFile( fileName, shaderEntry );
	//	if ( !shader )		// shader m�g� mie� z�y format, a nie chcemy dodawa� nullptra do ResourceManagera
	//		return nullptr;

	//	m_geometryShader.UnsafeAdd( fileName, shader );	// Dodali�my tekstur�
	//}

	//return shader;
	assert( !"Implements me" );
	return nullptr;
}

ControlShader*		ResourceManager::LoadControlShader	( const std::wstring& fileName, const std::string& shaderEntry )
{
	assert( !"Implements me" );
	return nullptr;
}

EvaluationShader*	ResourceManager::LoadEvaluationShader	( const std::wstring& fileName, const std::string& shaderEntry )
{
	assert( !"Implements me" );
	return nullptr;
}

/**@brief Dodaje tekstur� do ModelManagera, je�eli jeszcze nie istnia�a.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] fileName �cie�ka do tekstury

@return Zwraca wska�nik na dodan� tekstur� lub nullptr, je�eli nie da�o si� wczyta�.*/
TextureObject* ResourceManager::LoadTexture( const std::wstring& fileName )
{
	TextureObject* tex = m_texture.get( fileName );
	if ( !tex )
	{
		// Nie by�o tekstury, trzeba j� stworzy� i doda�
		TextureInfo texInfo;
		texInfo.FilePath = filesystem::Path( fileName );
		texInfo.GenerateMipMaps = true;
		texInfo.MipMapFilter = MipMapFilter::Lanczos4;

		MemoryChunk texData = LoadTextureImpl( texInfo.FilePath, texInfo );

		tex = ResourcesFactory::CreateTextureFromMemory( texData, std::move( texInfo ) );
		if ( !tex )		// Tekstura mog�a mie� z�y format, a nie chcemy dodawa� nullptra do ResourceManagera
			return nullptr;

		m_texture.UnsafeAdd( fileName, tex );	// Dodali�my tekstur�
	}

	return tex;
}

/**@brief Dodaje do ResourceManagera bufor wierzcho�k�w.
Je�eli pod tak� nazw� istnieje jaki� bufor, to zostanie zwr�cony wska�nik na niego.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] name Nazwa bufora, po kt�rej mo�na si� b�dzie odwo�a�.
@param[in] buffer Wska�nik na bufor z danym, kt�re maj� by� przeniesione do bufora DirectXowego.
@param[in] elementSize Rozmiar pojedynczego elementu w buforze.
@param[in] vertCount Liczba wierzcho�k�w/indeks�w w buforze.
@return Dodany bufor wierzcho�k�w. Zwraca nullptr, je�eli nie uda�o si� stworzy� bufora.*/
ResourcePtr< BufferObject > ResourceManager::CreateVertexBuffer( const std::wstring& name, const void* buffer, unsigned int elementSize, unsigned int vertCount )
{
	VertexBufferInitData initData;
	initData.Data = (const uint8*)buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;
	
	return CreateVertexBuffer( name, initData );
}

/**@brief Creates vetex buffer.

@return Returns buffer or nullptr if name already exists or buffer creation failed.*/
ResourcePtr<BufferObject>	ResourceManager::CreateVertexBuffer		( const std::wstring& name, const VertexBufferInitData& data )
{
	BufferObject* vertexBuff = m_vertexBuffer.get( name );
	if ( vertexBuff )	// Je�eli znale�li�my bufor, to zwracamy nullptr
		return ResourcePtr<BufferObject>();
	
	
	vertexBuff = ResourcesFactory::CreateBufferFromMemory( name, data.Data, data.CreateBufferInfo() );
	if ( !vertexBuff )		// Bufor m�g� si� nie stworzy�, a nie chcemy dodawa� nullptra do ResourceManagera
		return nullptr;

	m_vertexBuffer.UnsafeAdd( name, vertexBuff );	// Dodali�my bufor
	return ResourcePtr<BufferObject>( vertexBuff );
}

/**@brief Dodaje do ResourceManagera bufor indeks�w.
Je�eli pod tak� nazw� istnieje jaki� bufor, to zostanie zwr�cony wska�nik na niego.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] name Nazwa bufora, po kt�rej mo�na si� b�dzie odwo�a�.
@param[in] buffer Wska�nik na bufor z danym, kt�re maj� by� przeniesione do bufora DirectXowego.
@param[in] elementSize Rozmiar pojedynczego elementu w buforze.
@param[in] vertCount Liczba wierzcho�k�w/indeks�w w buforze.
@return Dodany bufor indeks�w. Zwraca nullptr, je�eli nie uda�o si� stworzy� bufora.*/
ResourcePtr< BufferObject > ResourceManager::CreateIndexBuffer( const std::wstring& name, const void* buffer, unsigned int elementSize, unsigned int vertCount )
{
	IndexBufferInitData initData;
	initData.Data = (const uint8*)buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;

	return CreateIndexBuffer( name, initData );
}

/**@brief Vreates index buffer.

@return Returns buffer or nullptr if name already exists or buffer creation failed.*/
ResourcePtr<BufferObject>	ResourceManager::CreateIndexBuffer		( const std::wstring& name, const IndexBufferInitData& data )
{
	BufferObject* indexBuff = m_indexBuffer.get( name );
	if ( indexBuff )	// Je�eli znale�li�my bufor, to zwracamy nullptr
		return ResourcePtr<BufferObject>();
	
	
	indexBuff = ResourcesFactory::CreateBufferFromMemory( name, data.Data, data.CreateBufferInfo() );
	if ( !indexBuff )		// Bufor m�g� si� nie stworzy�, a nie chcemy dodawa� nullptra do ResourceManagera
		return nullptr;

	m_indexBuffer.UnsafeAdd( name, indexBuff );	// Dodali�my bufor
	return ResourcePtr<BufferObject>( indexBuff );
}

/**@brief Dodaje do ResourceManagera bufor sta�ch dla shadera.
Je�eli pod tak� nazw� istnieje jaki� bufor, to zostanie zwr�cony wska�nik na niego.
@note Funkcja nie dodaje odwo�ania do obiektu, bo nie zak�ada, �e kto� go od razu u�yje.
W ka�dym miejscu, gdzie zostanie przypisany zwr�cony obiekt, nale�y pami�ta� o dodaniu odwo�ania oraz
skasowaniu go, gdy obiekt przestanie by� u�ywany.

@param[in] name Nazwa bufora, po kt�rej mo�na si� b�dzie odwo�a�.
@param[in] buffer Wska�nik na bufor z danym, kt�re maj� by� przeniesione do bufora DirectXowego.
@param[in] size Rozmiar bufora.
@return Dodany bufor indeks�w. Zwraca nullptr, je�eli nie uda�o si� stworzy� bufora.*/
ResourcePtr< BufferObject >	ResourceManager::CreateConstantsBuffer( const std::wstring& name, const void* buffer, unsigned int size )
{
	ConstantBufferInitData initData;
	initData.Data = (const uint8*)buffer;
	initData.ElementSize = size;
	initData.NumElements = 1;

	return CreateConstantsBuffer( name, initData );
}

/**@brief Creates constant buffer.

@return Returns buffer or nullptr if name already exists or buffer creation failed.*/
ResourcePtr<BufferObject>	ResourceManager::CreateConstantsBuffer		( const std::wstring& name, const ConstantBufferInitData& data )
{
	BufferObject* constBuff = m_constantBuffer.get( name );
	if ( constBuff )	// Je�eli znale�li�my bufor, to zwracamy nullptr
		return ResourcePtr<BufferObject>();
	
	
	constBuff = ResourcesFactory::CreateBufferFromMemory( name, data.Data, data.CreateBufferInfo() );
	if ( !constBuff )		// Bufor m�g� si� nie stworzy�, a nie chcemy dodawa� nullptra do ResourceManagera
		return nullptr;

	m_constantBuffer.UnsafeAdd( name, constBuff );	// Dodali�my bufor
	return ResourcePtr<BufferObject>( constBuff );
}

/**@brief Created BlendingState object.

@return If object named name exist, returns nullptr.*/
ResourcePtr< BlendingState >	ResourceManager::CreateBlendingState	( const std::wstring& name, const BlendingInfo& info )
{
	auto resource = m_blendingState.get( name );
	if ( resource )	// Je�eli znale�li�my bufor, to zwracamy nullptr
		return ResourcePtr< BlendingState >();

	resource = ResourcesFactory::CreateBlendingState( info );
	m_blendingState.UnsafeAdd( name, resource );

	return ResourcePtr< BlendingState >( resource );
}

/**@brief Created RasterizerState object.

@return If object named name exist, returns nullptr.*/
ResourcePtr< RasterizerState >	ResourceManager::CreateRasterizerState	( const std::wstring& name, const RasterizerStateInfo& info )
{
	auto resource = m_rasterizerState.get( name );
	if ( resource )	// Je�eli znale�li�my bufor, to zwracamy nullptr
		return ResourcePtr< RasterizerState >();

	resource = ResourcesFactory::CreateRasterizerState( info );
	m_rasterizerState.UnsafeAdd( name, resource );

	return ResourcePtr< RasterizerState >( resource );
}

/**@brief Created DepthStencilState object.

@return If object named name exist, returns nullptr.*/
ResourcePtr< DepthStencilState >	ResourceManager::CreateDepthStencilState	( const std::wstring& name, const DepthStencilInfo& info )
{
	auto resource = m_depthStencilState.get( name );
	if ( resource )	// Je�eli znale�li�my bufor, to zwracamy nullptr
		return ResourcePtr< DepthStencilState >();

	resource = ResourcesFactory::CreateDepthStencilState( info );
	m_depthStencilState.UnsafeAdd( name, resource );

	return ResourcePtr< DepthStencilState >( resource );
}

//====================================================================================//
//			Listowanie asset�w
//====================================================================================//


/**@brief Listowanie bufor�w wierzcho�k�w.*/
std::vector< ResourcePtr< BufferObject > >		ResourceManager::ListVertexBuffers()
{
	return m_vertexBuffer.List();
}

/**@brief Listowanie bufor�w indeks�w.*/
std::vector< ResourcePtr< BufferObject > >		ResourceManager::ListIndexBuffers()
{
	return m_indexBuffer.List();
}

/**@brief Listowanie bufor�w sta�ych.*/
std::vector< ResourcePtr< BufferObject > >		ResourceManager::ListConstantBuffers()
{
	return m_constantBuffer.List();
}

/**@brief Listowanie layout�w wierzcho�k�w.*/
std::vector< ResourcePtr< ShaderInputLayout > > ResourceManager::ListShaderLayouts()
{
	return m_vertexLayout.List();
}

/**@brief Listowanie tekstur.*/
std::vector< ResourcePtr< TextureObject > >		ResourceManager::ListTextures()
{
	return m_texture.List();
}

/**@brief Listowanie vertex shader�w.*/
std::vector< ResourcePtr< VertexShader > >		ResourceManager::ListVertexShaders()
{
	return m_vertexShader.List();
}

/**@brief Listowanie pixel shader�w.*/
std::vector< ResourcePtr< PixelShader > >		ResourceManager::ListPixelShaders()
{
	return m_pixelShader.List();
}

/**@brief Listowanie render target�w.*/
std::vector< ResourcePtr< RenderTargetObject > > ResourceManager::ListRenderTargets()
{
	return m_renderTarget.List();
}

/**@brief Implementation of texture loading.

This is hack function. Resource manager have no texture loading function beacause
it needs separate library for this. Derived classes will implement it, but in future
this must change. ResourceManager must be fully operational class. Otherwise GUI 
won't load textures.*/
MemoryChunk ResourceManager::LoadTextureImpl( const filesystem::Path& filePath, TextureInfo& texInfo )
{
	assert( !"Implement me" );
	return MemoryChunk();
}


