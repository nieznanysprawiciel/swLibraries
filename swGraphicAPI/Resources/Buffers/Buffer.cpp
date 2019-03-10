/**
@file Buffer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "Buffer.h"


using namespace sw;

RTTR_REGISTRATION
{

	// Buffer
	rttr::registration::class_< Buffer >( "sw::Buffer" )
		.property_readonly( "Descriptor", &Buffer::GetDescriptor ) BIND_AS_PTR;

	rttr::registration::class_< BufferInfo >( "sw::BufferInfo" )
		.property_readonly( "BufferName", &BufferInfo::GetName )
		.property_readonly( "NumberElements", &BufferInfo::NumElements )
		.property_readonly( "ElementSize", &BufferInfo::ElementSize )
		.property_readonly( "Usage", &BufferInfo::Usage )
		.property_readonly( "BufferType", &BufferInfo::BufferType )
		.property_readonly( "Topology", &BufferInfo::Topology )
		.property_readonly( "4 Bytes Index Size", &BufferInfo::Use4BytesIndex )
		.property_readonly( "VertexLayout", &BufferInfo::VertexLayout );

	rttr::registration::class_< BufferInitData >( "sw::BufferInitData" );
	rttr::registration::class_< ConstantBufferInitData >( "sw::ConstantBufferInitData" );
	rttr::registration::class_< VertexBufferInitData >( "sw::VertexBufferInitData" );
	rttr::registration::class_< IndexBufferInitData >( "sw::IndexBufferInitData" );

}


namespace sw
{

// ================================ //
//
Buffer::Buffer( unsigned int elementSize, unsigned int elementCount )
	: m_elementSize( elementSize ),
	m_elementCount( elementCount )
{}

// ================================ //
//
TypeID		BufferInitData::GetAssetType	() const
{
	return TypeID::get< Buffer >();
}




}	// sw

