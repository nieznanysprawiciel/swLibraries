#pragma once


#include "swGraphicAPI/Resources/MeshResources.h"

#include <vector>


namespace sw
{

struct InputLayoutInfo
{
	const char*			SemanticName;
	ResourceFormat		Format;
	unsigned int		InputSlot;
	unsigned int		ByteOffset;
	bool				PerInstance;
	unsigned int		InstanceDataStep;
};


/**@brief
@ingroup MockAPI*/
class MockInputLayoutDescriptor : public InputLayoutDescriptor
{
private:
	std::vector< InputLayoutInfo >		m_inputElement;
public:
	MockInputLayoutDescriptor( const std::wstring& layoutName ) : InputLayoutDescriptor( layoutName ) {}
	~MockInputLayoutDescriptor() = default;

	Size							GetNumElements() { return m_inputElement.size(); }

	virtual void					AddRow( const char* semanticName,
											ResourceFormat format,
											unsigned int inputSlot,
											unsigned int byteOffset,
											bool perInstance,
											unsigned int instanceDataStep );

	unsigned int					CountSemantic( const char* semanticName );
};

}	// sw
