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






/**@brief Describes vertex shader layout.

@todo Move to sw namespace

@ingroup Buffers
@ingroup Shaders
@ingroup Resources*/
class InputLayoutDescriptor : public sw::IAssetCreateInfo
{
	RTTR_ENABLE( sw::IAssetCreateInfo );
	RTTR_REGISTRATION_FRIEND;
private:

	std::vector< sw::LayoutEntry >	m_entries;

protected:
public:
    explicit InputLayoutDescriptor		() = default;
	virtual ~InputLayoutDescriptor		() = default;


	/**@brief Adds shader input layout entry.
	This function will fill not specified data with apropriate values.*/
	void					AddEntry				( AttributeSemantic semanticName, ResourceFormat format, uint16 offset );
	void					AddEntry				( AttributeSemantic semanticName, ResourceFormat format, uint16 offset, uint16 inputSlot );
	void					AddEntryPerInstance		( AttributeSemantic semanticName, ResourceFormat format, uint16 offset, uint16 inputSlot, uint32 instanceDataStep );

	virtual TypeID			GetAssetType			() const override;

	const std::vector< LayoutEntry >&			    GetEntries		() const { return m_entries; }

protected:

	void					AddEntryImpl			( AttributeSemantic semanticName, ResourceFormat format, uint16 offset, uint16 inputSlot, bool perInstance, uint32 instanceDataStep );
};

}	// sw




