/**
@file SWMaterialLaoder.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "SWMaterialLoader.h"

#include "swGraphicAPI/Resources/MeshResources.h"


namespace sw
{


//template< typename ShaderType >
//struct ShaderFunGetter
//{
//	typedef ShaderType* ( AssetsManager::*ShaderLoadFun )( const std::wstring&, const std::string& );
//
//
//	static ShaderLoadFun		ShaderLoadingFunction()
//	{
//		static_assert( false, "Specialize struct" );
//	};
//};
//
//template<>
//struct ShaderFunGetter< VertexShader >
//{
//	typedef VertexShader* ( AssetsManager::*ShaderLoadFun )( const std::wstring&, const std::string& );
//
//	static ShaderLoadFun		ShaderLoadingFunction()
//	{
//		return &AssetsManager::LoadVertexShader;
//	}
//};
//
//template<>
//struct ShaderFunGetter< PixelShader >
//{
//	typedef PixelShader* ( AssetsManager::*ShaderLoadFun )( const std::wstring&, const std::string& );
//
//	static ShaderLoadFun		ShaderLoadingFunction()
//	{
//		return &AssetsManager::LoadPixelShader;
//	}
//};
//
//template<>
//struct ShaderFunGetter< GeometryShader >
//{
//	typedef GeometryShader* ( AssetsManager::*ShaderLoadFun )( const std::wstring&, const std::string& );
//
//	static ShaderLoadFun		ShaderLoadingFunction()
//	{
//		return &AssetsManager::LoadGeometryShader;
//	}
//};
//
//template<>
//struct ShaderFunGetter< ControlShader >
//{
//	typedef ControlShader* ( AssetsManager::*ShaderLoadFun )( const std::wstring&, const std::string& );
//
//	static ShaderLoadFun		ShaderLoadingFunction()
//	{
//		return &AssetsManager::LoadControlShader;
//	}
//};
//
//template<>
//struct ShaderFunGetter< EvaluationShader >
//{
//	typedef EvaluationShader* ( AssetsManager::*ShaderLoadFun )( const std::wstring&, const std::string& );
//
//	static ShaderLoadFun		ShaderLoadingFunction()
//	{
//		return &AssetsManager::LoadEvaluationShader;
//	}
//};




template< typename ShaderType >
inline Nullable< ResourcePtr< ShaderType > >	SWMaterialLoader::LoadShader	( IDeserializer* deser, const std::string& shaderNameString )
{
	ShaderLoadInfo shader = DeserializeShader( deser, shaderNameString );

	if( !shader.first )
		return Nullable< ResourcePtr< ShaderType > >( shaderNameString + " path is not set." );

	if( !shader.second )
		return Nullable< ResourcePtr< ShaderType > >( shaderNameString + " entry function is not set." );


	typename ShaderFunGetter< ShaderType >::ShaderLoadFun LoadShaderFunPtr = ShaderFunGetter< ShaderType >::ShaderLoadingFunction();

	std::wstring filePath = Convert::FromString< std::wstring >( std::string( shader.first ), std::wstring() );
	std::string entryFunction = std::string( shader.second );

	ShaderType* shaderObject = ( m_modelsManager->*LoadShaderFunPtr )( filePath, entryFunction );
	if( !shaderObject )
		return Nullable< ResourcePtr< ShaderType > >( shaderNameString + " file could not be loaded." );

	return Nullable< ResourcePtr< ShaderType > >( ResourcePtr< ShaderType >( shaderObject ) );
}


}	// sw
