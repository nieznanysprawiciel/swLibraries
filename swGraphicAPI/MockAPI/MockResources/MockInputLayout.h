#pragma once
/**
@file MockInputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{


/**@brief 
@ingroup MockAPI*/
class MockInputLayout : public ShaderInputLayout
{
	RTTR_ENABLE( ShaderInputLayout );
private:

    InputLayoutDescriptor       m_desc;

protected:

	virtual			~MockInputLayout		();

public:
	explicit		MockInputLayout			( const AssetPath& fileName, InputLayoutDescriptor desc );


	static sw::Nullable< MockInputLayout* >		CreateLayout		( const AssetPath& fileName, const InputLayoutDescriptor& layoutDesc );

    virtual const InputLayoutDescriptor&        GetDescriptor       () const override;
};

}	// sw
