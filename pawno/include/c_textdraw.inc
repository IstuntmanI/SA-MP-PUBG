/*  c_textdraw.inc
 *
 *  (c) Copyright 2016, Emilijo "Correlli" Lovrich
 *
 *  Credits: - Y_Less for foreach/iterator.
*/

//#define C_TD_DBG_MSG

enum Data_Circle_TD
{
	Count,
	PlayerText:cTextDraw[MAX_PLAYER_TEXT_DRAWS],
	Slot
}

new
		TD_Circle_Data[MAX_PLAYERS][Data_Circle_TD];

static
		bool:gFunc = false;

forward OnPlayerCircleFinish(playerid);

stock TD_CreateCircle(playerid, text[], color, color2, Float:x_pos, Float:y_pos, Float:radius, Float:diff, Float:x_pos2, Float:y_pos2, Float:radius2, Float:diff2)
{
	if(TD_Circle_Data[playerid][Count])
		return false;

	TD_CircleFixDiff(diff);

	y_pos -= 20.0;

	new
			count[2], Float:rot;

	for(new a = 0; a < 360; a++)
	{
		rot += diff;
		count[0]++;
		if(!(rot < 360.0))
			break;
	}

	rot = 0.0;
	for(new a = 0; a < 360; a++)
	{
		if(count[1] == MAX_PLAYER_TEXT_DRAWS)
		{
			printf("Error at \"TD_CreateCircle\" function for text \"%s\" (player ID: %i) - limit is reached (%i/%i).",
				text,
				playerid,
				count[0],
				MAX_PLAYER_TEXT_DRAWS
			);
			break;
		}

		if(!CreateTD(
			playerid,
			text,
			color,
			count[1],
			(x_pos + (radius * floatcos(rot + 270.0, degrees))),
			(y_pos + (radius * floatsin(rot + 270.0, degrees)))
		))
		{
			printf("Error at \"TD_CreateCircle\" function for text \"%s\" (player ID: %i) - limit is reached (%i/%i).",
				".",
				playerid,
				count[0],
				MAX_PLAYER_TEXT_DRAWS
			);
			break;
		}

		count[1]++;

		rot += diff;
		if(!(rot < 360.0))
			break;
	}

	if(radius2 != 200) {
		TD_CircleFixDiff(diff2);

		y_pos2 -= 20.0;
		
		count[0] = 0;
		rot = 0.0;

		
		for(new a = 0; a < 360; a++)
		{
			rot += diff2;
			count[0]++;
			if(!(rot < 360.0))
				break;
		}

		rot = 0.0;
		for(new a = 0; a < 360; a++)
		{
			if(count[1] == MAX_PLAYER_TEXT_DRAWS)
			{
				printf("Error at \"TD_CreateCircle\" function for text \"%s\" (player ID: %i) - limit is reached (%i/%i).",
					text,
					playerid,
					count[0],
					MAX_PLAYER_TEXT_DRAWS
				);
				break;
			}

			if(!CreateTD(
				playerid,
				text,
				color2,
				count[1],
				(x_pos2 + (radius2 * floatcos(rot + 270.0, degrees))),
				(y_pos2 + (radius2 * floatsin(rot + 270.0, degrees)))
			))
			{
				printf("Error at \"TD_CreateCircle\" function for text \"%s\" (player ID: %i) - limit is reached (%i/%i).",
					".",
					playerid,
					count[0],
					MAX_PLAYER_TEXT_DRAWS
				);
				break;
			}

			count[1]++;

			rot += diff2;
			if(!(rot < 360.0))
				break;
		}
	}

	TD_Circle_Data[playerid][Count]	 =	count[1];

	#if defined C_TD_DBG_MSG
		printf("TD_CreateCircle(playerid: %i, count: %i);", playerid, TD_Circle_Data[playerid][Count]);
	#endif
	return true;
}

stock CreateTD(playerid, text[], color, slot, Float:x_pos, Float:y_pos)
{
	TD_Circle_Data[playerid][cTextDraw][slot] = CreatePlayerTextDraw(playerid, x_pos, y_pos, text);
	if(TD_Circle_Data[playerid][cTextDraw][slot] == PlayerText:INVALID_TEXT_DRAW)
		return false;
	PlayerTextDrawFont(playerid,			TD_Circle_Data[playerid][cTextDraw][slot],			1);
	PlayerTextDrawLetterSize(playerid,		TD_Circle_Data[playerid][cTextDraw][slot],	 0.5, 1.0);
	PlayerTextDrawColor(playerid,			TD_Circle_Data[playerid][cTextDraw][slot],		color);
	PlayerTextDrawSetOutline(playerid,		TD_Circle_Data[playerid][cTextDraw][slot],			0);
	PlayerTextDrawSetProportional(playerid,	TD_Circle_Data[playerid][cTextDraw][slot],			1);
	PlayerTextDrawSetShadow(playerid,		TD_Circle_Data[playerid][cTextDraw][slot],			0);
	PlayerTextDrawShow(playerid,			TD_Circle_Data[playerid][cTextDraw][slot]			 );
	return true;
}

stock TD_DestroyCircle(playerid)
{
	if(!TD_Circle_Data[playerid][Count])
		return false;

	new
			a;

	for(a = 0; a < TD_Circle_Data[playerid][Count]; a++)
		PlayerTextDrawDestroy(playerid, TD_Circle_Data[playerid][cTextDraw][a]);

	TD_Circle_Data[playerid][Count]			=	0;
	TD_Circle_Data[playerid][Slot]			=	0;
	return true;
}

stock TD_IsCircleCreated(playerid)
	return TD_Circle_Data[playerid][Count];


stock TD_CircleFixDiff(&Float:diff)
{
	if(diff < 1.40625)
		diff = 1.40625;
}

public OnPlayerDisconnect(playerid, reason)
{
	TD_DestroyCircle(playerid);

	if(gFunc)
		CallLocalFunction("TD_Circle_OnPlayerDisconnect", "ii", playerid, reason);
	return true;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect TD_Circle_OnPlayerDisconnect

forward TD_Circle_OnPlayerDisconnect(playerid, reason);

public OnGameModeInit()
{
	gFunc = (funcidx("TD_Circle_OnPlayerDisconnect") != -1);
	CallLocalFunction("TD_Circle_OnGameModeInit", "");
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit TD_Circle_OnGameModeInit

forward TD_Circle_OnGameModeInit();
