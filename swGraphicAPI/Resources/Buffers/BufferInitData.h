#pragma once
/**
@file BufferInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Buffers/BufferRange.h"
#include "swCommonLib/Common/RTTR.h"

#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/Resources/Buffers/IBuffer.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include <assert.h>




namespace sw
{

class Buffer;


/**@brief Buffer initialization data.

@attention This structure doesn't take ownership of Data. Use only in synchronous api.

@ingroup Buffers*/
struct BufferInitData : public sw::IAssetCreateInfo
{
	const uint8*	Data;			///< Pointer must be valid only in time of creation.
	uint32			NumElements;
	uint32			ElementSize;
	TypeID  		DataType;		///< [Optional] Type of single element in buffer.
	ResourceUsage	Usage;


// ================================ //
//
	BufferInitData()
		: DataType( rttr::type::get_by_name( "" ) )	// Set invalid type.
	{
		Usage = ResourceUsage::Default;
		NumElements = 1;
		ElementSize = 0;
		Data = nullptr;
	}

	virtual TypeID			GetAssetType	() const override;
	virtual std::string		ResourceKey		() const override { return ""; }

public:
	RTTR_ENABLE( sw::IAssetCreateInfo );
};


/**@brief Constant buffer initialization data.

@attention This structure doesn't take ownership of Data. Use only in synchronous api.

@ingroup Buffers*/
struct ConstantBufferInitData : public BufferInitData
{
	BufferInfo		CreateBufferInfo() const;

public:
	RTTR_ENABLE( BufferInitData );
};



/**@brief Vertex buffer initialization data.

@attention This structure doesn't take ownership of Data. Use only in synchronous api.

@ingroup Buffers*/
struct VertexBufferInitData : public BufferInitData
{
	ResourcePtr< ShaderInputLayout >	VertexLayout;		///< [Optional] Layout of single vertex in buffer. You can add this layout to enable additional information in editor. Otherwise set to nullptr.
	PrimitiveTopology					Topology;			///< [Optional] Topology of verticies. @note Vertex buffer not always have topology. If you use index buffer, vertex buffer topology has no meaning. In this case it is set to PointList.

	VertexBufferInitData()
	{
		Topology = PrimitiveTopology::Points;
	}

	BufferInfo		CreateBufferInfo() const;

public:
	RTTR_ENABLE( BufferInitData );
};

/**@brief  Index buffer initialization data.

@attention This structure doesn't take ownership of Data. Use only in synchronous api.

@ingroup Buffers*/
struct IndexBufferInitData : public BufferInitData
{
	PrimitiveTopology					Topology;			///< [Optional] Topology of verticies. @note Index buffer topology override vertex buffer topology.
	bool								Use4BytesIndex;		///< Index buffer consists of 4 bytes instead of 2 bytes indicies.

	IndexBufferInitData()
	{
		Topology = PrimitiveTopology::Points;
		Use4BytesIndex = false;
	}

	BufferInfo		CreateBufferInfo() const;

public:
	RTTR_ENABLE( BufferInitData );
};


// ================================ //
//
inline BufferInfo		ConstantBufferInitData::CreateBufferInfo() const
{
	BufferInfo info;
	info.BufferType = BufferType::ConstantBuffer;
	info.ElementSize = ElementSize;
	info.NumElements = NumElements;
	info.DataType = DataType;
	info.Topology = PrimitiveTopology::Points;
	info.Usage = Usage;
	info.Use4BytesIndex = false;

	// Constant buffers must be 16 bytes aligned.
	assert( ElementSize % 16 == 0 );

	return info;
}

// ================================ //
//
inline BufferInfo		VertexBufferInitData::CreateBufferInfo() const
{
	BufferInfo info;
	info.BufferType = BufferType::VertexBuffer;
	info.ElementSize = ElementSize;
	info.NumElements = NumElements;
	info.DataType = DataType;
	info.Topology = Topology;
	info.Usage = Usage;
	info.Use4BytesIndex = false;
	info.VertexLayout = VertexLayout;

	return info;
}

// ================================ //
//
inline BufferInfo		IndexBufferInitData::CreateBufferInfo() const
{
	BufferInfo info;
	info.BufferType = BufferType::IndexBuffer;
	info.ElementSize = ElementSize;
	info.NumElements = NumElements;
	info.DataType = DataType;
	info.Topology = Topology;
	info.Usage = Usage;
	info.Use4BytesIndex = Use4BytesIndex;

	return info;
}

}	// sw