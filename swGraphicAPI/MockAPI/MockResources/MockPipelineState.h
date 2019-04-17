#pragma once
/**
@file PipelineState.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"



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
	explicit	MockRasterizerState	( const AssetPath& name, const RasterizerStateInfo& info );


	virtual const RasterizerStateInfo&	GetDescriptor	() const override;

	static MockRasterizerState*			Create			( const AssetPath& name, const RasterizerStateInfo& info );
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
	explicit	MockDepthStencilState	( const AssetPath& name, const DepthStencilInfo& info );


	virtual const DepthStencilInfo&		GetDescriptor	() const override;

	static MockDepthStencilState*		Create			( const AssetPath& name, const DepthStencilInfo& info );
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
	explicit	MockBlendingState	( const AssetPath& name, const BlendingInfo& info );


	virtual const BlendingInfo&		GetDescriptor	() const override;

	static MockBlendingState*		Create			( const AssetPath& name, const BlendingInfo& info );
};

}	// sw
