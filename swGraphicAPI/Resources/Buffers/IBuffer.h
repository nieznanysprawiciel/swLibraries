#pragma once
/**
@file IBuffer.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.
*/

#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"

#include "swCommonLib/Common/MemoryChunk.h"
#include "swCommonLib/Common/Buffers/BufferRange.h"
#include "swCommonLib/System/Path.h"


/**@defgroup Buffers Buffers

@brief GPU buffer objects.
@detail

Buffer initialization classes:
- @ref ConstantBufferInitData
- @ref IndexBufferInitData
- @ref VertexBufferInitData

@ingroup Resources*/



namespace sw
{


class ShaderInputLayout;


/**@brief Type of buffer.
@ingroup Buffers*/
enum class BufferType : uint8
{
	VertexBuffer,		///< Vertex buffer
	IndexBuffer,		///< Index buffer
	ConstantBuffer		///< Constant buffer
};


/**@brief Descriptor of buffer hold by @ref Buffer.
@ingroup Buffers*/
struct BufferInfo
{
	uint32				NumElements;	///< Number of elements of type BufferDescriptor::DataType.
	uint32				ElementSize;	///< Size of single element in buffer.
	rttr::type			DataType;		///< [Optional] Type of single element in buffer.
	ResourceUsage		Usage;			///< Usage of resource by graphic card.
	BufferType			BufferType;		///< Vertex, index or constant buffer.

	///@name Only for vertex or index buffer.
	///@{
	PrimitiveTopology					Topology;			///< [Optional] Topology of verticies. @note Vertex buffer not always have topology. If you use index buffer, vertex buffer topology has no meaning. In this case it is set to PointList.
	///@}

	///@name Vertex buffer only
	///@brief For other buffer types VertexLayout should be set to nullptr.
	///@{
	ResourcePtr< ShaderInputLayout >	VertexLayout;		///< [Optional] Layout of single vertex in buffer. You can add this layout to enable additional information in editor. Otherwise set to nullptr.
	///@}

	///@name Index buffer only
	///@{
	bool								Use4BytesIndex;		///< Index buffer consists of 4 bytes instead of 2 bytes indicies.
	///@}

	explicit BufferInfo()
		: DataType( rttr::type::get_by_name( "" ) )	// Set invalid type.
        , NumElements( 0 )
        , ElementSize( 0 )
        , Usage( ResourceUsage::Default )
        , BufferType( BufferType::ConstantBuffer )
	{}

};


/**@brief Base class for buffers.
@ingroup Buffers
@ingroup Resources*/
class IBuffer : public Resource
{
	RTTR_ENABLE( Resource )
private:

protected:
	explicit		IBuffer		( const AssetPath& assetPath ) : Resource( assetPath ) {}
	virtual			~IBuffer	() = default;
public:
	virtual MemoryChunk			CopyData		() = 0;				///< Copies data from GPU to MemoryChunk.
	virtual const BufferInfo&	GetDescriptor	() const = 0;		///< Returns buffer descriptor.

	/**@brief Updates part of the buffer at offset.
	For buffer to be updatable it must be created with @ref ResourceUsage::Default
	or @ref ResourceUsage::Dynamic.*/
    virtual ReturnResult		UpdateData		( BufferRange data, PtrOffset offset ) = 0;
    
	/**@brief Resizes buffer to fit the data pointed by newData parameter.
	No other parameters of the Buffer are changed. Buffer is updated with new content.
	
	This operation will most probably create new buffer and remove old one.
	Should be avoided for performance reasons.
	Currently Buffer can be only resized up. If Buffer is larger than expected data, it will be only updated.*/
    virtual ReturnResult		Resize			( BufferRange newData ) = 0;
};


}	// sw


