#pragma once
/**
@file PhongMaterial.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/



#include <DirectXMath.h>



namespace sw
{

/**@brief Phong material buffer layout in @ref MaterialAsset.

@ingroup Materials*/
struct PhongMaterial
{
	DirectX::XMFLOAT4		Diffuse;
	DirectX::XMFLOAT4		Ambient;
	DirectX::XMFLOAT4		Specular;
	DirectX::XMFLOAT3		Emissive;
	float					Power;

    // ================================ //
    //
    explicit PhongMaterial()
    {   SetNullMaterial();    }
	
    inline void SetNullMaterial();
};


/**@brief Sets the most neutral material values.*/
inline void         PhongMaterial::SetNullMaterial()
{
	Diffuse.x = 1.0f;
	Diffuse.y = 1.0f;
	Diffuse.z = 1.0f;
	Diffuse.w = 1.0f;

	Ambient.x = 1.0f;
	Ambient.y = 1.0f;
	Ambient.z = 1.0f;
	Ambient.w = 1.0f;

	Specular.x = 1.0f;
	Specular.y = 1.0f;
	Specular.z = 1.0f;
	Specular.w = 1.0f;

	Emissive.x = 0.0f;
	Emissive.y = 0.0f;
	Emissive.z = 0.0f;

	Power = 1.0f;
}


}	// sw

