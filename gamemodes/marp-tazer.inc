#if defined _marp_tazer_included
	#endinput
#endif
#define _marp_tazer_included

//=============================SISTEMA DE TAZER=================================

//================================DEFINES=======================================

#define TAZER_TIME              10000
#define TAZER_MAX_DISTANCE      16.0

#define TAZER_NONE              0
#define TAZER_EQUIPPED          1
#define TAZER_USED              2
#define TAZER_EMPTY             3

//===============================VARIABLES======================================

new tazerAmmo[MAX_PLAYERS],
	tazerStatus[MAX_PLAYERS],
	tazerInUse[MAX_PLAYERS];
	
resetTazer(playerid)
{
	if(tazerInUse[playerid])
	{
	    if(GetHandItem(playerid, HAND_RIGHT) == WEAPON_SILENCED)
	        SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	}
	tazerInUse[playerid] = 0;
	tazerStatus[playerid] = TAZER_NONE;
	tazerAmmo[playerid] = 0;
}

//================================FUNCIONES=====================================

forward checkTazer(playerid, issuerid, Float:amount, weaponid);
public checkTazer(playerid, issuerid, Float:amount, weaponid)
{	
	if(weaponid == WEAPON_SILENCED && tazerInUse[issuerid])
	{
		if(!IsPlayerInAnyVehicle(issuerid))
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				if(ProxDetectorS(TAZER_MAX_DISTANCE, issuerid, playerid))
				{
					if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
						return SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto est� ocupado o actualmente inhabilitado.");
					SendFMessage(playerid, COLOR_YELLOW2, "�Has sido tazeado por %s!, el efecto dura %d segundos.", GetPlayerNameEx(issuerid), TAZER_TIME / 1000);
					SendFMessage(issuerid, COLOR_YELLOW2, "�Has tazeado a %s por %d segundos!", GetPlayerNameEx(playerid), TAZER_TIME / 1000);
					TogglePlayerControllable(playerid, false);
					SetPVarInt(playerid, "disabled", DISABLE_TAZER);
					ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
					SetTimerEx("FinishTazerEffect", TAZER_TIME, 0, "i", playerid);
					PlayerPlayerActionMessage(issuerid, playerid, 15.0, "dispara su tazer cargado y le acierta a");
				} else {
					 SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto estaba demasiado lejos.");
				}
			} else {
				SendClientMessage(issuerid, COLOR_YELLOW2, "Debes bajar al sujeto del veh�culo antes de tazearlo.");
			}
		} else {
			SendClientMessage(issuerid, COLOR_YELLOW2, "�No lo puedes usar desde adentro de un veh�culo!");
		}
		return 1;
	}
	return 0;
}

forward FinishTazerEffect(playerid);
public FinishTazerEffect(playerid)
{
    if(GetPVarInt(playerid, "disabled") == DISABLE_TAZER)
	{
	    SendClientMessage(playerid, COLOR_YELLOW2, "El efecto del tazer se ha ido.");
		TogglePlayerControllable(playerid, true);
    	ApplyAnimation(playerid, "PED", "getup_front", 4.1, 0, 1, 1, 0, 1, 1);
    	SetPVarInt(playerid, "disabled", DISABLE_NONE);
    }
    return 1;
}

stock isPlayerUsingTazer(playerid)
{
	return tazerInUse[playerid];
}

//================================COMANDOS======================================

CMD:tazer(playerid, params[])
{
	if(!isPlayerCopOnDuty(playerid) && !isPlayerSideOnDuty(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(tazerStatus[playerid] == TAZER_NONE)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar equipado con un tazer!");

    if(tazerInUse[playerid] == 0)
    {
		if(tazerStatus[playerid] == TAZER_EMPTY)
			return SendClientMessage(playerid, COLOR_YELLOW2, "�Tu tazer no tiene mas munici�n, vuelve a la comisar�a a recargarlo!");
		if(GetHandItem(playerid, HAND_RIGHT) != 0)
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Tienes la mano ocupada!");
    	if(tazerStatus[playerid] == TAZER_EQUIPPED)
   		SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_SILENCED, 10);
		if(tazerStatus[playerid] == TAZER_USED)
	    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_SILENCED, tazerAmmo[playerid]);
    	SendClientMessage(playerid, COLOR_WHITE, "Has tomado tu tazer. Para guardarlo usa /tazer.");
    	tazerInUse[playerid] = 1;
		return 1;
	}
	if(tazerInUse[playerid] == 1)
	{
    	if(GetHandItem(playerid, HAND_RIGHT) != WEAPON_SILENCED) // Si se le acab� el tazer y por quedarse sin balas se borr� de la mano
    	{
    	    tazerAmmo[playerid] = 0;
    	    tazerStatus[playerid] = TAZER_EMPTY;
		}
		else
		{
			new weapon, ammo;
	 		GetPlayerWeaponData(playerid, 2, weapon, ammo); // Silenced se guarda en slot 2 de weapondatas
			if(weapon == WEAPON_SILENCED)
			{
				if(tazerStatus[playerid] != TAZER_EMPTY)
				{
				    tazerAmmo[playerid] = ammo;
				    if(GetHandItem(playerid, HAND_RIGHT) == WEAPON_SILENCED)
				    	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
				    tazerStatus[playerid] = TAZER_USED;
				}
				if(tazerAmmo[playerid] == 0)
					tazerStatus[playerid] = TAZER_EMPTY;
			}
		}
		tazerInUse[playerid] = 0;
    	SendClientMessage(playerid, COLOR_WHITE, "Has guardado tu tazer. Para usarlo nuevamente usa /tazer o ve a recargarlo si se te ha acabado.");
		return 1;
	}
	return 1;
}
