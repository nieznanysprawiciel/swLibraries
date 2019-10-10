#pragma once
/**
@file GUISystemConfig.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


namespace sw {
namespace gui
{


/**@brief Configuration flags.*/
class GUISystemConfig
{
private:

public:

	bool			UseBlockingMode		: 1;		///< GUI will always wait for native events. Set to false if you want maximum FPS.
	bool			UseVSync			: 1;		///< Synchronize swaping render targets with screen frequency. Set to false if you want maximum FPS.
	bool			RedrawOnlyFocused	: 1;		///< Only focused window will be redrawn.
	bool			IsTestMode			: 1;		///< Check this flag in initialization to add test features. Note that if we want testing to be reliable,
													///< the behaviour of the application should be the same. Use this flag only to add state capturing objects
													///< or other mock functionalities. Use wise.
	bool			DebugGraphics		: 1;		///< Set debug mode while initializing graphic API.

public:

	explicit		GUISystemConfig()
		:	UseBlockingMode( true )
		,	UseVSync( true )
		,	RedrawOnlyFocused( true )
		,	IsTestMode( false )
		,	DebugGraphics( false )
	{}

};

}	// gui
}	// sw

