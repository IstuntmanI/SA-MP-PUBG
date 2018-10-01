/*
	War Of Banish
		gamemode by Aktah (เอกวิทย์ ตาแฮ)
	
	1 Kill = 20/15/10 point solo/duo/squard
	5 damage = 1 point
	1 Rank = 
	
	720
	
	Solo rank Time * 1.2
	Duo rank Time * 0.6
	Squad rank Time * 0.3
*/

//--------------------------------[LSRP.PWN]--------------------------------
#include <a_samp>


/*  ---------------- SCRIPT REVISION ----------------- */

#define SERVER_GM_TEXT "0.0.1"

#undef  MAX_PLAYERS
#define MAX_PLAYERS (100)

/*=======================================================================================================
										[Includes]
=======================================================================================================*/
#include <crashdetect>
#include <a_http>
#include <streamer>
#include <foreach>
#include <sscanf2>
#include <a_mysql>
#include <timerfix>
#include <zcmd>
#include <UIC>
#include <mapandreas>
#include <c_object>
#include <c_textdraw>
#include <fader>
#include <FCNPC>
#include <GZ_ShapesALS>
#include <YSI\y_hooks>
#include <YSI\y_timers>
//#include <nex-ac>
#include <memory>
#include <colandreas>
#include <easyDialog>
//#include <PreviewModelDialog>
/*=======================================================================================================
										[Modules]
=======================================================================================================*/

// General
#include "./includes/defines.pwn"
#include "./includes/enums.pwn"
#include "./includes/variables.pwn"
#include "./includes/wrappers.pwn"
#include "./includes/timers.pwn"
#include "./includes/functions.pwn"
#include "./includes/mysql.pwn"
#include "./includes/callbacks.pwn"
#include "./includes/textdraws.pwn"


//streamer includes

// Core
#include "./includes/core/initgamemode.pwn"
//#include "./includes/core/compass.pwn"

// Main
#include "./includes/main/party.pwn"
#include "./includes/main/lobby.pwn"
#include "./includes/main/matchmaking/main.pwn"
#include "./includes/main/gameplay.pwn"
#include "./includes/main/gameplay_ui.pwn"

#include "./includes/system/mapicon_direction.pwn"
/*
#include "./includes/main/matchmaking.pwn"
#include "./includes/main/inventory.pwn"
*/
/*======================================================================================================*/

main(){}

public OnGameModeInit()
{
	OnGameModeInitEx();

	#if defined WOB_OnGameModeInit
		return WOB_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit WOB_OnGameModeInit
#if defined WOB_OnGameModeInit
	forward WOB_OnGameModeInit();
#endif

OnGameModeInitEx()
{
	print("Preparing the gamemode, please wait...");
	InitiateGamemode();
	//g_mysql_Init(); // not need yet
}

public OnGameModeExit()
{
	print("Exiting the gamemode, please wait...");
    //g_mysql_Exit();// not need yet
	return 1;
}

AntiDeAMX()
{
    new b;
    #emit load.pri b
    #emit stor.pri b
}
