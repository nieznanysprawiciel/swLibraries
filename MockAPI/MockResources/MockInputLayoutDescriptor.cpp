/**
@file MockInputLayoutDescriptor.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "MockInputLayoutDescriptor.h"

#include <cstring>



namespace sw
{


// ================================ //
//
void MockInputLayoutDescriptor::AddRow( const char* semanticName, ResourceFormat format, unsigned int inputSlot, unsigned int byteOffset, bool perInstance, unsigned int instanceDataStep )
{
	InputLayoutInfo inputElement;
	inputElement.SemanticName = semanticName;
	inputElement.Format = format;
	inputElement.InputSlot = inputSlot;
	inputElement.ByteOffset = byteOffset;
	inputElement.InstanceDataStep = instanceDataStep;
	inputElement.PerInstance = perInstance;
	inputElement.SemanticName = semanticName;

	m_inputElement.push_back( inputElement );
}

// ================================ //
//
unsigned int MockInputLayoutDescriptor::CountSemantic( const char* semanticName )
{
	unsigned int numSemantic = 0;

	for( auto element : m_inputElement )
		if( strcmp( element.SemanticName, semanticName ) == 0 )
			++numSemantic;

	return numSemantic;
}

}	// sw

