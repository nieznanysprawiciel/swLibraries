#pragma once
/**
@file PipelineState.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "swGraphicAPI/Resources/BlendingState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/Resources/RasterizerState.h"



namespace sw
{


/**@brief
@ingroup MockAPI*/
class MockRasterizerState : public RasterizerState
{
	RTTR_ENABLE( RasterizerState );
private:

	RasterizerStateInfo					m_info;

protected:
	~MockRasterizerState() = default;
public:
	explicit	MockRasterizerState	( const RasterizerStateInfo& info );


	// Inherited via RasterizerState
	virtual std::string					GetResourceName	() const override;
	virtual const RasterizerStateInfo&	GetDescriptor	() override;

	static MockRasterizerState*			Create			( const RasterizerStateInfo& info );
};


/**@brief
@ingroup MockAPI*/
class MockDepthStencilState : public DepthStencilState
{
	RTTR_ENABLE( DepthStencilState );
private:

	DepthStencilInfo					m_info;

protected:
	~MockDepthStencilState() = default;
public:
	explicit	MockDepthStencilState	( const DepthStencilInfo& info );


	// Inherited via DepthStencilState
	virtual std::string					GetResourceName	() const override;
	virtual const DepthStencilInfo&		GetDescriptor	() override;

	static MockDepthStencilState*		Create			( const DepthStencilInfo& info );
};



/**@brief
@ingroup MockAPI*/
class MockBlendingState : public BlendingState
{
	RTTR_ENABLE( BlendingState );
private:

	BlendingInfo				m_info;

protected:
	~MockBlendingState() = default;
public:
	explicit	MockBlendingState	( const BlendingInfo& info );


	// Inherited via BlendingState
	virtual std::string				GetResourceName	() const override;
	virtual const BlendingInfo&		GetDescriptor	() override;

	static MockBlendingState*		Create			( const BlendingInfo& info );
};

}	// sw
