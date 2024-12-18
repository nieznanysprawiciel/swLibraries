#pragma once
/**
@file ShadingModelData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"
#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"



namespace sw
{


/**@brief Base class for classes storing shading model parameters.

@ingroup Materials*/
class ShadingModelBase : public Object
{
	RTTR_ENABLE( Object )
private:
public:
	ShadingModelBase();
	virtual				~ShadingModelBase		() = 0 {};

	virtual Size		GetSize		            () = 0;
	virtual uint8*		GetData		            () = 0;
	virtual TypeID		GetShadingModelType		() = 0;
	virtual TypeID		GetShadingModelPtrType	() = 0;


	std::string			GetShadingModelTypeName ();
};


/**@brief Class wrapping shading model parameters and exposing raw buffer access
to them.

@ingroup Materials*/
template< typename ShadingModelStruct >
class ShadingModelData : public ShadingModelBase
{
	RTTR_ENABLE( ShadingModelBase )
private:
public:
	ShadingModelStruct		Data;

public:
	explicit			ShadingModelData		();
	explicit			ShadingModelData		( ShadingModelStruct model );
    virtual				~ShadingModelData		() = default;

	void				StaticValidate			();


	virtual Size		GetSize		            () override { return sizeof( ShadingModelStruct ); }
	virtual uint8*		GetData		            () override { return reinterpret_cast<uint8*>( &Data ); }
	virtual TypeID		GetShadingModelType		() override { return rttr::type::get< ShadingModelStruct >(); }
	virtual TypeID		GetShadingModelPtrType	() override { return rttr::type::get< ShadingModelStruct* >(); }

	ShadingModelStruct&	GetStruct	() { return Data; }
};


//====================================================================================//
//			Inline definitions	
//====================================================================================//

// ================================ //
//
template< typename ShadingModelStruct >
inline void			ShadingModelData< ShadingModelStruct >::StaticValidate		()
{
	static_assert( std::is_default_constructible< ShadingModelStruct >::value, "Material data must be default constructible." );

	// Constructor must be registered in rttr with AsRawPtr policy.
	assert( TypeID::get< ShadingModelData< ShadingModelStruct > >().get_constructor().is_valid() );
	assert( TypeID::get< ShadingModelData< ShadingModelStruct > >().get_constructor().get_instantiated_type().is_pointer() );
	assert( TypeID::get< ShadingModelData< ShadingModelStruct > >().get_property( "Data" ).is_valid() );
}

// ================================ //
//
template< typename ShadingModelStruct >
inline				ShadingModelData< ShadingModelStruct >::ShadingModelData	()
{
	StaticValidate();
}

// ================================ //
//
template< typename ShadingModelStruct >
inline				ShadingModelData< ShadingModelStruct >::ShadingModelData	( ShadingModelStruct model )
	: Data( model )
{
	StaticValidate();
}

}	// sw

