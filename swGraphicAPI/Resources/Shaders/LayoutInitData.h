#pragma once
/**
@file LayoutInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <string>
#include <vector>


#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"




namespace sw
{

/**@brief Posible semantics of vertex attributes in shaders.
@ingroup Shaders*/
enum class AttributeSemantic : uint8
{
	Position,
	PositionTransformed,
	Normal,
	Tangent,
	Binormal,
	Color,
	Texcoord,
	PointSize,
	BlendIndicies,
	BlendWeights
};


/**@brief Describes one attribute in vertex layout descriptor.
@ingroup Shaders*/
struct LayoutEntry
{
	AttributeSemantic	SemanticName;
	ResourceFormat		AttribFormat;
	uint16				InputSlot;
	uint16				ByteOffset;
	uint32				InstanceDataStep;		///< Number of instances which will be drawn with the same data (before stepping to next element).
	bool				PerInstance;			///< Set to true if this entry describes per instance attribute.
};


}	// sw



/**@brief Describes vertex shader layout.

@todo Move to sw namespace

@ingroup Buffers
@ingroup Shaders
@ingroup Resources*/
class InputLayoutDescriptor : public sw::IAssetCreateInfo
{
	RTTR_ENABLE( sw::IAssetCreateInfo );
private:

	std::wstring					m_inputLayoutName;
	std::vector< sw::LayoutEntry >	m_entries;

protected:
public:
	explicit InputLayoutDescriptor		( const std::wstring& layoutName )
		:	m_inputLayoutName( layoutName )
	{}

	virtual ~InputLayoutDescriptor		() = default;

	/**@brief Adds Input layout entry.
	@deprecated This function remained for compatibility with previous version of creatng input layouts.*/
	virtual void			AddRow		( const char* semanticName, ResourceFormat format, unsigned int inputSlot, unsigned int byteOffset, bool perInstance, unsigned int instanceDataStep ) = 0;

	/**@brief Adds shader input layout entry.
	This function will fill not specified data with apropriate values.*/
	void					AddEntry				( sw::AttributeSemantic semanticName, ResourceFormat format );
	void					AddEntry				( sw::AttributeSemantic semanticName, ResourceFormat format, uint16 inputSlot );
	void					AddEntryPerInstance		( sw::AttributeSemantic semanticName, ResourceFormat format, uint16 inputSlot, uint32 instanceDataStep );

	const std::wstring&		GetName		() { return m_inputLayoutName; }

	virtual TypeID			GetAssetType() const override;
};






