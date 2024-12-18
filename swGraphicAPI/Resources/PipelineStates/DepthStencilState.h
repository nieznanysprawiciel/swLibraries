#pragma once
/**
@file DepthStencilState.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swGraphicAPI/Resources/ResourceObject.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"




namespace sw
{

class DepthStencilState;


/**@brief
@ingroup PipelineState*/
struct DepthStencilInfo : public sw::IAssetCreateInfo
{
	RTTR_ENABLE( sw::IAssetCreateInfo );
public:
	bool			EnableDepthTest;
	bool			EnableStencilTest;

// ================================ //
//
	DepthStencilInfo()
		: EnableDepthTest( true )
		, EnableStencilTest( false )
	{}

#define Compare( x ) if( x != other.x ) return false;

	bool	operator==	( const DepthStencilInfo& other ) const
	{
		Compare( EnableDepthTest );
		Compare( EnableStencilTest );
		return true;
	}

#undef Compare

public:

	virtual TypeID			GetAssetType			() const override { return TypeID::get< DepthStencilState >(); }
	virtual std::string		ResourceKey				() const override { return ""; }
};




/**@brief
@ingroup PipelineState*/
class DepthStencilState : public Resource
{
	RTTR_ENABLE( Resource );
private:
protected:

	virtual			~DepthStencilState() = default;

public:
	explicit		DepthStencilState		( const AssetPath& assetPath ) : Resource( assetPath ) {}

	virtual const DepthStencilInfo&			GetDescriptor	() const = 0;
};

DEFINE_RESOURCE_PTR_TYPE( DepthStencilState );


}	// sw
