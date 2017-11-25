#pragma once
/**
@file IRenderer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/


#include "swGraphicAPI/Resources/MeshResources.h"
#include "RenderCommands.h"


/**@brief Spos�b u�ycia renderera.

Renderer mo�e wysy�a� polecenia na kart� graficzn� od razu lub
zamiast tego tworzyc kolejk� komunikat�w i wysy�a� dopiero kiedy wszystko b�dzie przygotowane.
Ta druga opcja umo�liwia renderowanie wielow�tkowe.*/
enum RendererUsage
{
	USE_AS_DEFERRED,			///<Renderowanie do kolejki rozkaz�w.
	USE_AS_IMMEDIATE			///<Renderowanie natychmiastowe
};



/**@brief Klasa interfejsu renderera.
@ingroup GraphicAPI
@ingroup RenderingCommands*/
class IRenderer
{
private:
public:
	IRenderer() = default;
	virtual ~IRenderer() = default;


	virtual bool SupportsDefferedContextRendering() = 0;		///< Informuje czy Renderer nadaje si� do renderowania w wielu w�tkach do op�nionego contextu.
	virtual bool IsValid() = 0;


	virtual void		Draw					( const DrawCommand& command )						= 0;
	virtual void		DrawInstanced			( const DrawInstancedCommand& command )				= 0;

	virtual void		SetRenderTarget			( const SetRenderTargetCommand& command )			= 0;
	virtual void		SetRenderTarget			( const SetRenderTargetExCommand& command )			= 0;
	virtual void		ClearRenderTarget		( const ClearRenderTargetCommand& command )			= 0;

	virtual void		UpdateBuffer			( const UpdateBufferCommand& command )				= 0;
	virtual void		BindBuffer				( const BindBufferCommand& command )				= 0;
	virtual void		UpdateAndBindBuffer		( const UpdateBindBuffer& command )					= 0;

	virtual void		SetDefaultBuffers		( const SetDefaultBuffersCommand& command )			= 0;
	
	virtual void		SetShaderState			( const SetShaderStateCommand& command )			= 0;
	virtual void		SetShaderState			( const SetShaderStateExCommand& command )			= 0;
	virtual void		SetShaderState			( const SetRenderStateCommand& command )			= 0;
	virtual void		SetShaderState			( const SetRenderStateExCommand& command )			= 0;

	virtual void		CopyTexture				( const CopyTextureCommand& command )				= 0;
};


