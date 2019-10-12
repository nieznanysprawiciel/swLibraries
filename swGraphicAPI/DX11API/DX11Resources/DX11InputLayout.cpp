/**
@file DX11InputLayout.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11InputLayout.h"
#include "DX11Compiler.h"

#include "swGraphicAPI/DX11API/DX11Initializer/DX11Utils.h"

#include <string.h>



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11InputLayout >( "sw::DX11InputLayout" );
}



namespace sw
{


// ================================ //
//
DX11InputLayout::DX11InputLayout		( const AssetPath& fileName, ID3D11InputLayout* layout, InputLayoutDescriptor desc )
	:	ShaderInputLayout( fileName )
	,	m_vertexLayout( layout )
    ,   m_descriptor( std::move( desc ) )
{}

// ================================ //
//
DX11InputLayout::~DX11InputLayout()
{
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
    std::string					GenerateSemanticName	( const D3D11_INPUT_ELEMENT_DESC& attribute ) const;
	std::string					InputStructName			() const { return "InputVS"; }
	std::string					MapSemanticToType		( const char* semantic ) const;
};



// ================================ //
//
DX11LayoutTranslator::DX11LayoutTranslator			( const InputLayoutDescriptor& layoutDesc )
	: m_inputElement( Translate( layoutDesc ) )
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
static std::tuple< sw::AttributeSemantic, const char*, const char* > SemanticsMap[] =
{
    std::make_tuple( sw::AttributeSemantic::Position, "POSITION", "float4" ),
    std::make_tuple( sw::AttributeSemantic::Normal, "NORMAL", "float3" ),
    std::make_tuple( sw::AttributeSemantic::Tangent, "TANGENT", "float3" ),
    std::make_tuple( sw::AttributeSemantic::Binormal, "BINORMAL", "float3" ),
    std::make_tuple( sw::AttributeSemantic::BlendIndicies, "BLENDINDICES", "uint" ),
    std::make_tuple( sw::AttributeSemantic::BlendWeights, "BLENDWEIGHT", "float" ),
    std::make_tuple( sw::AttributeSemantic::Color, "COLOR", "float4" ),
    std::make_tuple( sw::AttributeSemantic::Texcoord, "TEXCOORD", "float2" ),
    std::make_tuple( sw::AttributeSemantic::PositionTransformed, "POSITIONT", "float4" ),
    std::make_tuple( sw::AttributeSemantic::PointSize, "PSIZE", "float" )
};

// ================================ //
//
const char*						DX11LayoutTranslator::Translate		( sw::AttributeSemantic semantic ) const
{
	for( auto& tuple : SemanticsMap )
		if( std::get< 0 >( tuple ) == semantic )
			return std::get< 1 >( tuple );

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
	main = "struct OutputVS {};\n\n";
	main += "OutputVS main( " + InputStructName() + " input )\n";
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

	layoutStruct += "\n};\n\n";

	return layoutStruct;
}

// ================================ //
//
std::string						DX11LayoutTranslator::GenerateAttribute		( const D3D11_INPUT_ELEMENT_DESC& attribute ) const
{
    std::string fullSemanticStr = GenerateSemanticName( attribute );
	std::string attributeEntry = "\t";

	attributeEntry = MapSemanticToType( attribute.SemanticName );
	attributeEntry += " m" + fullSemanticStr + " : " + fullSemanticStr + ";";

	return attributeEntry;
}

// ================================ //
//
std::string                     DX11LayoutTranslator::GenerateSemanticName  ( const D3D11_INPUT_ELEMENT_DESC& attribute ) const
{
    return attribute.SemanticName + Convert::ToString( attribute.SemanticIndex );
}

// ================================ //
//
std::string						DX11LayoutTranslator::MapSemanticToType		( const char* semantic ) const
{
    for( auto& tuple : SemanticsMap )
        if( strcmp( std::get< 1 >( tuple ), semantic ) == 0 )
            return std::get< 2 >( tuple );

	return "float4";
}


// ================================ //
//
sw::Nullable< DX11InputLayout* >			DX11InputLayout::CreateLayout		( const AssetPath& fileName, const InputLayoutDescriptor& layoutDesc )
{
	DX11LayoutTranslator layoutTranslator( layoutDesc );

	std::string shaderCode = layoutTranslator.GenerateShader();
	sw::CompilationConfig config( ShaderType::VertexShader );

    if( IsDebugLayerEnabled() )
    {
        config.Debug = true;
    }

	auto compiledBlob = sw::DX11Compiler::CompileShader( shaderCode, "main", config );

	if( !compiledBlob.IsValid() )
	{
        if( IsDebugLayerEnabled() )
    		OutputDebugStringA( compiledBlob.GetErrorReason().c_str() );

		return compiledBlob.GetError();
	}

	auto& compiledShader = compiledBlob.Get();
	auto DX11layout = layoutTranslator.GetDX11LayoutDesc();

	ID3D11InputLayout* DX11layoutInterface = nullptr;
	HRESULT result = device->CreateInputLayout( DX11layout.data(), (UINT)DX11layout.size(), compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &DX11layoutInterface );

	if( FAILED( result ) )
		return fmt::format( "[DX11InputLayout] Can't create layout. {}", DX11Utils::ErrorString( result ) );

	return new DX11InputLayout( fileName, DX11layoutInterface, layoutDesc );
}

// ================================ //
//
const InputLayoutDescriptor&                DX11InputLayout::GetDescriptor      () const
{
    return m_descriptor;
}


}	// sw