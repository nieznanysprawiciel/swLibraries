/**
@file Layouts.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "LayoutInitData.h"
#include "InputLayout.h"


RTTR_REGISTRATION
{

	rttr::registration::enumeration< sw::AttributeSemantic >( "sw::AttributeSemantic" )
	(
		rttr::value( "Position", sw::AttributeSemantic::Position ),
		rttr::value( "PositionTransformed", sw::AttributeSemantic::PositionTransformed ),
		rttr::value( "Normal", sw::AttributeSemantic::Normal ),
		rttr::value( "Tangent", sw::AttributeSemantic::Tangent ),
		rttr::value( "Binormal", sw::AttributeSemantic::Binormal ),
		rttr::value( "Color", sw::AttributeSemantic::Color ),
		rttr::value( "Texcoord", sw::AttributeSemantic::Texcoord ),
		rttr::value( "PointSize", sw::AttributeSemantic::PointSize ),
		rttr::value( "BlendIndicies", sw::AttributeSemantic::BlendIndicies ),
		rttr::value( "BlendWeights", sw::AttributeSemantic::BlendWeights )
	);

	rttr::registration::class_< sw::LayoutEntry >( "sw::LayoutEntry" )
		.property( "Semantic", &sw::LayoutEntry::SemanticName )
		.property( "Format", &sw::LayoutEntry::AttribFormat )
		.property( "InputSlot", &sw::LayoutEntry::InputSlot )
		.property( "ByteOffset", &sw::LayoutEntry::ByteOffset )
		.property( "IsPerInstance", &sw::LayoutEntry::PerInstance )
		.property( "InstanceDataStep", &sw::LayoutEntry::InstanceDataStep );

	rttr::registration::class_< sw::InputLayoutDescriptor >( "sw::InputLayoutDescriptor" )
		.property( "Entries", &sw::InputLayoutDescriptor::m_entries );

}


namespace sw
{


// ================================ //
//
void			InputLayoutDescriptor::AddEntry					( sw::AttributeSemantic semanticName, ResourceFormat format )
{
	AddEntryImpl( semanticName, format, 0, false, 0 );
}

// ================================ //
//
void			InputLayoutDescriptor::AddEntry					( sw::AttributeSemantic semanticName, ResourceFormat format, uint16 inputSlot )
{
	AddEntryImpl( semanticName, format, inputSlot, false, 0 );
}

// ================================ //
//
void			InputLayoutDescriptor::AddEntryPerInstance		( sw::AttributeSemantic semanticName, ResourceFormat format, uint16 inputSlot, uint32 instanceDataStep )
{
	AddEntryImpl( semanticName, format, inputSlot, true, instanceDataStep );
}


// ================================ //
//
TypeID			InputLayoutDescriptor::GetAssetType				() const
{
	return TypeID::get< ShaderInputLayout >();
}

// ================================ //
//
void			InputLayoutDescriptor::AddEntryImpl				( sw::AttributeSemantic semanticName, ResourceFormat format, uint16 inputSlot, bool perInstance, uint32 instanceDataStep )
{
	sw::LayoutEntry entry;
	entry.SemanticName = semanticName;
	entry.AttribFormat = format;
	entry.InputSlot = inputSlot;
	entry.PerInstance = perInstance;
	entry.InstanceDataStep = instanceDataStep;

	m_entries.push_back( entry );
}

}	// sw
