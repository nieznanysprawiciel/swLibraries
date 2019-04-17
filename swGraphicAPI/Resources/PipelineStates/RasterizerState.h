#pragma once
/**
@file RasterizerStateObject.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swCommonLib/Common/ObjectDeleter.h"
#include "swGraphicAPI/Resources/ResourceObject.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"


/**@defgroup PipelineState
@ingroup Resources
*/



namespace sw
{

class RasterizerState;


/**@brief
@ingroup PipelineState*/
struct RasterizerStateInfo : public sw::IAssetCreateInfo
{
	RTTR_ENABLE( sw::IAssetCreateInfo );
public:
	CullMode		CullMode;
	FillMode		FillMode;
	int				DepthBias;
	bool			IsClockwise;
	bool			EnableScissor;
	bool			EnableZClipping;			///< Clipping of far plane.
	bool			ConservativeRasterizer;		///< Since in DirectX 11.2


// ================================ //
//
	RasterizerStateInfo()
		: CullMode( CullMode::Back )
		, FillMode( FillMode::Solid )
		, DepthBias( 0 )
		, IsClockwise( false )
		, EnableScissor( false )
		, EnableZClipping( true )
		, ConservativeRasterizer( false )
	{}

#define Compare( x ) if( x != other.x ) return false;


	bool	operator==	( const RasterizerStateInfo& other ) const
	{
		Compare( CullMode );
		Compare( FillMode );
		Compare( DepthBias );
		Compare( IsClockwise );
		Compare( EnableScissor );
		Compare( EnableZClipping );
		Compare( ConservativeRasterizer );
		return true;
	}

#undef Compare

public:

	virtual TypeID			GetAssetType			() const override { return TypeID::get< RasterizerState >(); }
};




/**@brief Rasterizer state and depth stencil state.

@ingroup PipelineState*/
class RasterizerState : public Resource
{
	RTTR_ENABLE( Resource );
	friend ObjectDeleter< RasterizerState >;
private:
protected:

	virtual			~RasterizerState() = default;

public:

	explicit		RasterizerState		( const AssetPath& assetPath ) : Resource( assetPath ) {}

	virtual const RasterizerStateInfo&		GetDescriptor	() const = 0;
};

DEFINE_RESOURCE_PTR_TYPE( RasterizerState );


}	// sw

