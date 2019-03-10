#pragma once
/**
@file BlendingState.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swCommonLib/Common/ObjectDeleter.h"

#include "ResourceObject.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include <DirectXMath.h>





namespace sw
{


class BlendingState;



/**@brief Initialization of BlendingState.

@ingroup PipelineState*/
struct BlendingInfo : public sw::IAssetCreateInfo
{
	RTTR_ENABLE( sw::IAssetCreateInfo );
public:
	DirectX::XMFLOAT4	CustomBlendFactor;		///< Custom blend factors.
	bool				EnableBlending;
	BlendOperation		ColorOperation;
	BlendOperation		AlphaOperation;
	BlendFactor			SrcColorBlend;
	BlendFactor			DstColorBlend;
	BlendFactor			SrcAlphaBlend;
	BlendFactor			DstAlphaBlend;

// ================================ //
//
	BlendingInfo()
		: CustomBlendFactor( DirectX::XMFLOAT4( 0.0f, 0.0f, 0.0f, 0.0f ) )
		, EnableBlending( false )
		, ColorOperation( BlendOperation::Add )
		, AlphaOperation( BlendOperation::Add )
		, SrcColorBlend( BlendFactor::One )
		, DstColorBlend( BlendFactor::One )
		, SrcAlphaBlend( BlendFactor::One )
		, DstAlphaBlend( BlendFactor::One )
	{}

#define Compare( x ) if( x != other.x ) return false;

	bool	operator==	( const BlendingInfo& other ) const
	{
		Compare( CustomBlendFactor.x );
		Compare( CustomBlendFactor.y );
		Compare( CustomBlendFactor.z );
		Compare( CustomBlendFactor.w );
		Compare( EnableBlending );
		Compare( ColorOperation );
		Compare( EnableBlending );
		Compare( AlphaOperation );
		Compare( SrcColorBlend );
		Compare( DstColorBlend );
		Compare( SrcAlphaBlend );
		Compare( DstAlphaBlend );
		return true;
	}

#undef Compare

public:

	virtual TypeID			GetAssetType			() const override { return TypeID::get< BlendingState >(); }
};




/**@brief

@ingroup PipelineState*/
class BlendingState : public Resource
{
	RTTR_ENABLE( Resource );
	friend ObjectDeleter< BlendingState >;
private:
protected:

	virtual			~BlendingState() = default;

public:
	explicit		BlendingState()
		: Resource( 0 )
	{}


	virtual const BlendingInfo&		GetDescriptor	() = 0;
};


}	// sw