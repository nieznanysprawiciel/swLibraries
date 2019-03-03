/**
@file DX11InputLayout.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11InputLayout.h"
#include "DX11Compiler.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< DX11InputLayout >( "DX11InputLayout" );
}



// ================================ //
//
DX11InputLayout::DX11InputLayout( ID3D11InputLayout* layout )
{
	m_vertexLayout = layout;
}

// ================================ //
//
DX11InputLayout::~DX11InputLayout()
{
	if( m_vertexLayout )
		m_vertexLayout->Release();
	m_vertexLayout = nullptr;
}



//====================================================================================//
//			Layout	
//====================================================================================//


// ================================ //
//
class DX11LayoutTranslator
{
	typedef std::vector< D3D11_INPUT_ELEMENT_DESC > LayoutVec;
private:

	LayoutVec		m_inputElement;

public:

	explicit			DX11LayoutTranslator		( const InputLayoutDescriptor& layoutDesc );

	LayoutVec			GetDX11LayoutDesc		() const { return m_inputElement; }
	std::string			GenerateShader			() const;

public:

	LayoutVec					Translate		( const InputLayoutDescriptor& layoutDesc ) const;
	D3D11_INPUT_ELEMENT_DESC	Translate		( const sw::LayoutEntry& entry ) const;
	const char*					Translate		( sw::AttributeSemantic semantic ) const;

private:
	D3D11_INPUT_ELEMENT_DESC	CreateRow		( const char* semanticName, ResourceFormat format, unsigned int inputSlot, 
												unsigned int byteOffset, bool perInstance, unsigned int instanceDataStep ) const;
	Size						CountSemantic	( const char* semanticName ) const;

private:

	std::string					GenerateMain			() const;
	std::string					GenerateInputStruct		( const LayoutVec& layout ) const;
	std::string					GenerateAttribute		( const D3D11_INPUT_ELEMENT_DESC& attribute ) const;
	std::string					InputStructName			() const { return "InputVS"; }
	std::string					MapSemanticToType		( DXGI_FORMAT format ) const;
};



// ================================ //
//
DX11LayoutTranslator::DX11LayoutTranslator			( const InputLayoutDescriptor& layoutDesc )
	:	m_inputElement( Translate( layoutDesc ) )
{}

// ================================ //
//
std::string						DX11LayoutTranslator::GenerateShader	() const
{
	std::string vertexLayout = GenerateInputStruct( m_inputElement );
	vertexLayout += GenerateMain();

	return vertexLayout;
}


// ================================ //
//
DX11LayoutTranslator::LayoutVec	DX11LayoutTranslator::Translate		( const InputLayoutDescriptor& layoutDesc ) const
{
	LayoutVec elements;

	for( auto& element : layoutDesc.GetEntries() )
		elements.push_back( Translate( element ) );

	return elements;
}

// ================================ //
//
D3D11_INPUT_ELEMENT_DESC		DX11LayoutTranslator::Translate		( const sw::LayoutEntry& entry ) const
{
	return CreateRow( Translate( entry.SemanticName ), entry.AttribFormat, entry.InputSlot, entry.ByteOffset, entry.PerInstance, entry.InstanceDataStep );
}

// ================================ //
//
const char*						DX11LayoutTranslator::Translate		( sw::AttributeSemantic semantic ) const
{

	static std::pair< sw::AttributeSemantic, const char* > SemanticsMap[] =
	{
		std::make_pair( sw::AttributeSemantic::Position, "POSITION" ),
		std::make_pair( sw::AttributeSemantic::Normal, "NORMAL" ),
		std::make_pair( sw::AttributeSemantic::Tangent, "TANGENT" ),
		std::make_pair( sw::AttributeSemantic::Binormal, "BINORMAL" ),
		std::make_pair( sw::AttributeSemantic::BlendIndicies, "BLENDINDICES" ),
		std::make_pair( sw::AttributeSemantic::BlendWeights, "BLENDWEIGHT" ),
		std::make_pair( sw::AttributeSemantic::Color, "COLOR" ),
		std::make_pair( sw::AttributeSemantic::Texcoord, "TEXCOORD" ),
		std::make_pair( sw::AttributeSemantic::PositionTransformed, "POSITIONT" ),
		std::make_pair( sw::AttributeSemantic::PointSize, "PSIZE" )
	};

	for( auto& pair : SemanticsMap )
		if( pair.first == semantic )
			return pair.second;

	return "";
}

// ================================ //
//
D3D11_INPUT_ELEMENT_DESC		DX11LayoutTranslator::CreateRow		( const char* semanticName, ResourceFormat format, unsigned int inputSlot, unsigned int byteOffset, bool perInstance, unsigned int instanceDataStep ) const
{
	D3D11_INPUT_ELEMENT_DESC inputElement;
	inputElement.SemanticName = semanticName;
	inputElement.Format = DX11ConstantsMapper::Get( format );
	inputElement.InputSlot = inputSlot;
	inputElement.AlignedByteOffset = byteOffset;
	inputElement.InstanceDataStepRate = instanceDataStep;
	if( perInstance )
		inputElement.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA;
	else
		inputElement.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	inputElement.SemanticIndex = (UINT)CountSemantic( semanticName );

	return inputElement;
}

// ================================ //
//
Size							DX11LayoutTranslator::CountSemantic	( const char* semanticName ) const
{
	return std::count_if( m_inputElement.begin(), m_inputElement.end(), [ semanticName ]( const D3D11_INPUT_ELEMENT_DESC& element )
	{ 
		return strcmp( element.SemanticName, semanticName ) == 0;
	} );
}

// ================================ //
//
std::string						DX11LayoutTranslator::GenerateMain	() const
{
	std::string main;
	main = "struct OutputVS {};\n";
	main += "OutputVS main()\n";
	main += "{\n";
	main += "return (OutputVS)0;\n";
	main += "}\n";

	return main;
}

// ================================ //
//
std::string						DX11LayoutTranslator::GenerateInputStruct	( const LayoutVec& layout ) const
{
	std::string layoutStruct = "struct " + InputStructName();
	layoutStruct += "\n{\n";

	for( auto& attrib : layout )
	{
		layoutStruct += GenerateAttribute( attrib );
		layoutStruct += "\n";
	}

	layoutStruct += "\n};\n";

	return layoutStruct;
}

// ================================ //
//
std::string						DX11LayoutTranslator::GenerateAttribute		( const D3D11_INPUT_ELEMENT_DESC& attribute ) const
{
	std::string fullSemanticStr = attribute.SemanticName + Convert::ToString( attribute.SemanticIndex );

	std::string attributeEntry;

	attributeEntry = MapSemanticToType( attribute.Format );
	attributeEntry += " m" + fullSemanticStr + " : " + fullSemanticStr + ";";

	return attributeEntry;
}

// ================================ //
//
std::string						DX11LayoutTranslator::MapSemanticToType		( DXGI_FORMAT format ) const
{
	switch( format )
	{
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT:
			return "uint4";
		case DXGI_FORMAT::DXGI_FORMAT_R8G8_UINT:
			return "uint2";
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT:
			return "float4";
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT:
			return "float3";
		case DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT:
			return "float2";
		case DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT:
			return "float";
	}
	return "float4";
}


// ================================ //
//
sw::Nullable< DX11InputLayout* >			DX11InputLayout::CreateLayout		( const InputLayoutDescriptor& layoutDesc )
{
	DX11LayoutTranslator layoutTranslator( layoutDesc );

	std::string shaderCode = layoutTranslator.GenerateShader();
	sw::CompilationConfig config( ShaderType::VertexShader );

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto compiledBlob = sw::DX11Compiler::CompileShader( shaderCode, "main", config );

	if( !compiledBlob.IsValid() )
	{
#ifdef _DEBUG
		OutputDebugStringA( compiledBlob.GetErrorReason().c_str() );
#endif
		return compiledBlob.GetError();
	}

	auto& compiledShader = compiledBlob.Get();
	auto DX11layout = layoutTranslator.GetDX11LayoutDesc();

	ID3D11InputLayout* DX11layoutInterface = nullptr;

	HRESULT result = device->CreateInputLayout( DX11layout.data(), (UINT)DX11layout.size(), compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &DX11layoutInterface );

	if( FAILED( result ) )
		return "[DX11InputLayout] Can't create layout.";

	return new DX11InputLayout( DX11layoutInterface );
}

