#if defined _marp_same_included
	#endinput
#endif
#define _marp_same_included

#define PRICE_HOSP_HEAL        	100

#define POS_MEDIC_DUTY_X      	1131.0615
#define POS_MEDIC_DUTY_Y      	-1321.6823
#define POS_MEDIC_DUTY_Z      	1019.7036

#define POS_HOSP_HEAL_X			1163.6618
#define POS_HOSP_HEAL_Y			-1308.4156
#define POS_HOSP_HEAL_Z			1018.5358

new HospHealing[MAX_PLAYERS];

//=============================COMANDOS DEL SAME================================

CMD:morir(playerid, params[])
{
	if(GetPVarInt(playerid, "disabled") == DISABLE_DEATHBED)
	{
		SetPVarInt(playerid, "disabled", DISABLE_NONE);
        SetPlayerHealthEx(playerid, 0);
    }
	else
	{
        SendClientMessage(playerid, COLOR_YELLOW2, "No puedes utilizarlo en este momento.");
    }
    return 1;
}

CountMedicsOnDuty()
{
	new aux = 0;
 	foreach(new i : Player)
 	{
        if(IsMedicOnDuty(i))
    	    aux ++;
 	}
 	return aux;
}

IsMedicOnDuty(playerid)
{
	return (PlayerInfo[playerid][pFaction] == FAC_HOSP && MedDuty[playerid]);
}

CMD:mservicio(playerid, params[])
{
	new string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_HOSP)
		return 1;
	if(!PlayerToPoint(5.0, playerid, POS_MEDIC_DUTY_X, POS_MEDIC_DUTY_Y, POS_MEDIC_DUTY_Z))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en el vestuario!");

	if(MedDuty[playerid] == 0)
	{
		PlayerInfo[playerid][pHealth] = 100;
		MedDuty[playerid] = 1;
		format(string, sizeof(string), "Anuncio: un param�dico se ha puesto en servicio.", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_LIGHTGREEN, string);
	}
	else
	{
		PlayerActionMessage(playerid,15.0,"se quita el uniforme de m�dico y guarda su morral en el armario.");
		ResetPlayerWeapons(playerid);
		PlayerInfo[playerid][pHealth] = 100;
		MedDuty[playerid] = 0;
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	}
	return 1;
}

forward HospHeal(playerid);
public HospHeal(playerid)
{
	if(HospHealing[playerid])
	{
		TogglePlayerControllable(playerid, 1);
		SetPlayerHealthEx(playerid, 100.0);
		HospHealing[playerid] = 0;
        PlayerDoMessage(playerid, 15.0, "El m�dico ha finalizado el tratamiento del paciente.");
        SetPVarInt(playerid, "disabled", DISABLE_NONE);
	}
    return 1;
}

CMD:curarse(playerid, params[])
{
	new string[128];

    if(GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un hospital para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_HOSP_HEAL_X, POS_HOSP_HEAL_Y, POS_HOSP_HEAL_Z))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes registrarte en la sala de recuperaci�n.");
	if(CountMedicsOnDuty() > 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actualmente hay un m�dico en servicio, ponte en contacto con �l para que te atienda.");
	if(HospHealing[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya est�s siendo curado.");
	if(GetPlayerCash(playerid) < PRICE_HOSP_HEAL)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario para el tratamiento ($%d).", PRICE_HOSP_HEAL);
		return 1;
	}

	GivePlayerCash(playerid, -PRICE_HOSP_HEAL);
	GiveFactionMoney(FAC_HOSP, PRICE_HOSP_HEAL);
	PlayerDoMessage(playerid, 15.0, "Un m�dico examina al paciente y tras un diagn�stico inicial, comienza a curarlo.");
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("HospHeal", 30000, false, "i", playerid);
	format(string, sizeof(string), "[Hospital]: El paciente %s se ha registrado en el %s y est� siendo atendido.", GetPlayerNameEx(playerid), Building[GetPlayerBuilding(playerid)][blText]);
	SendFactionMessage(FAC_HOSP, COLOR_WHITE, string);
	HospHealing[playerid] = 1;
	/*TakeHeadShot[playerid] = 0;*/
	SetPVarInt(playerid, "disabled", DISABLE_HEALING);
	GameTextForPlayer(playerid, "Aguarda unos instantes mientras te atienden", 10000, 4);
	return 1;
}

CMD:curar(playerid,params[])
{
    new target, cost;

	if(PlayerInfo[playerid][pFaction] != FAC_HOSP)
	    return 1;
    if(!MedDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
    if(sscanf(params, "ud", target, cost))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /curar [ID/Jugador] [precio]");
	if(cost < 0 || cost > 500)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�El costo no puede ser menor a 0 o mayor a 500!");
    if(GetPVarInt(playerid, "isHealing") != 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�Ya est�s curando a una persona: debes esperar 15 segundos para usar nuevamente el comando!");
	if(target == INVALID_PLAYER_ID || target == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(!ProxDetectorS(2.0, playerid, target))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar cerca del herido!");
  	if(GetPVarInt(target, "disabled") == DISABLE_DEATHBED)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se encuentra en su lecho de muerte y no hay nada que puedas hacer por �l.");

	SendFMessage(target, COLOR_LIGHTBLUE, "El m�dico %s te ha ofrecido un tratamiento curativo por $%d. Escribe (/aceptar medico) para recibirlo.", GetPlayerNameEx(playerid), cost);
    SendClientMessage(target, COLOR_WHITE, "Si no tienes el dinero, se te cobrar� hasta lo que tengas, y el resto se descontar� de tu cuenta bancaria.");
 	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido a %s un tratamiento curativo por $%d.", GetPlayerNameEx(target), cost);
	SetPVarInt(playerid, "healTarget", target);
	SetPVarInt(playerid, "isHealing", 1);
	SetPVarInt(target, "healIssuer", playerid);
	SetPVarInt(target, "healCost", cost);
	SetTimerEx("healTimer", 15000, false, "i", playerid);
	return 1;
}

//===========================SISTEMA DE ADICCIONES==============================

AddPlayerAdiction(playerid, Float:drugAdiction)
{
	if(PlayerInfo[playerid][pAdictionPercent] + drugAdiction < 100.0)
		PlayerInfo[playerid][pAdictionPercent] += drugAdiction;
	else
	    PlayerInfo[playerid][pAdictionPercent] = 100.0;
	PlayerInfo[playerid][pAdictionAbstinence] = 30 * 60 + ADICTION_ABSTINENCE_MAX - floatround(PlayerInfo[playerid][pAdictionPercent] * (ADICTION_ABSTINENCE_MAX / 100), floatround_round);
}

Float:GetPlayerAdiction(playerid)
{
	return PlayerInfo[playerid][pAdictionPercent];
}

DeletePlayerAdiction(playerid, Float:drugAdiction)
{
	if(PlayerInfo[playerid][pAdictionPercent] - drugAdiction > 0.0)
    	PlayerInfo[playerid][pAdictionPercent] -= drugAdiction;
	else
	    PlayerInfo[playerid][pAdictionPercent] = 0.0;
    PlayerInfo[playerid][pAdictionAbstinence] = 30 * 60 + ADICTION_ABSTINENCE_MAX - floatround(PlayerInfo[playerid][pAdictionPercent] * (ADICTION_ABSTINENCE_MAX / 100), floatround_round);
}

forward UpdatePlayerAdiction();
public UpdatePlayerAdiction()
{
    foreach(new playerid : Player)
    {
    	if(!IsPlayerAfk(playerid) && PlayerInfo[playerid][pJailed] != JAIL_OOC && !AdminDuty[playerid]) // Si no est� AFK ni en Jail OOC
		{
			if(PlayerInfo[playerid][pAdictionPercent] > 0.0)
			{
			    if(PlayerInfo[playerid][pAdictionAbstinence] <= 30 * 60)
			    {
			    	if(PlayerInfo[playerid][pAdictionAbstinence] > 0)
					{
			        	PlayerInfo[playerid][pAdictionAbstinence] -= ADICTION_UPDATE_TIME;
			        	if(PlayerInfo[playerid][pAdictionAbstinence] <= 0.0)
			        	    SendClientMessage(playerid, COLOR_RED, "�ltima advertencia, consume alguna droga antes de los pr�ximos 5 minutos o tu estado ser� cr�tico");
			        	else
							SendFMessage(playerid, COLOR_RED, "Entras en abstinencia. Consume alguna droga dentro de %d minutos o entrar�s en estado cr�tico.", PlayerInfo[playerid][pAdictionAbstinence] / 60);
					} else
		   				{
							SendClientMessage(playerid, COLOR_RED, "Entras en un estado cr�tico causado por tu abstinencia. Unos param�dicos te socorren y te llevan al hospital.");
							SendClientMessage(playerid, COLOR_RED, "Luego de un tiempo logran salvarte, cobr�ndote $7.500. Si no lo tienes se descontar� de tu cuenta bancaria.");
	   						if(GetPlayerCash(playerid) > ADICTION_REHAB_PRICE)
								GivePlayerCash(playerid, -ADICTION_REHAB_PRICE); // se cobra 7 mil por el tratamiento + 500 normales por morir
							else
								if(GetPlayerCash(playerid) > 0)
								{
									PlayerInfo[playerid][pBank] -= ADICTION_REHAB_PRICE - GetPlayerCash(playerid);
							    	ResetPlayerCash(playerid);
								} else
							    	PlayerInfo[playerid][pBank] -= ADICTION_REHAB_PRICE;
							SetPlayerHealthEx(playerid, 0.0);
		                    PlayerInfo[playerid][pAdictionAbstinence] = 30 * 60 + ADICTION_ABSTINENCE_MAX - floatround(PlayerInfo[playerid][pAdictionPercent] * (ADICTION_ABSTINENCE_MAX / 100), floatround_round);
			    		}
				} else
			        PlayerInfo[playerid][pAdictionAbstinence] -= ADICTION_UPDATE_TIME;
			}
		}
	}
	return 1;
}

CMD:rehabilitar(playerid, params[])
{
	new targetid;

	if(PlayerInfo[playerid][pFaction] != FAC_HOSP)
	    return 1;
    if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /rehabilitar [IDJugador/ParteDelNombre]");
	if(GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en el hospital!");
 	if(!MedDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(targetid == INVALID_PLAYER_ID || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(RehabOffer[targetid] != 999)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya est� con otro tratamiento en curso.");
	if(GetPlayerAdiction(targetid) == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no parece tener problemas de adicci�n.");
	if(GetPlayerCash(targetid) < ADICTION_REHAB_PRICE)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "El sujeto no tiene el dinero necesario para la rehabilitaci�n. ($%d)", ADICTION_REHAB_PRICE);
		return 1;
	}

    SendFMessage(targetid, COLOR_LIGHTBLUE, "El m�dico %s te ofrece una rehabilitaci�n con $%d de costo. Tipea /rehabilitarse si quieres. La oferta acaba en 15 segundos.", GetPlayerNameEx(playerid), ADICTION_REHAB_PRICE);
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido a %s un tratamiento de rehabilitaci�n cuyo costo es de $%d. La oferta termina en 15 segundos.", GetPlayerNameEx(targetid), ADICTION_REHAB_PRICE);
	RehabOffer[targetid] = playerid;
	SetTimerEx("RehabOfferCancel", 15000, false, "i", targetid);
	return 1;
}

forward RehabOfferCancel(playerid);
public RehabOfferCancel(playerid)
{
    RehabOffer[playerid] = 999;
}

CMD:rehabilitarse(playerid, params[])
{
	new aleatorio = random(100);

	if(RehabOffer[playerid] == 999)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido un tratamiento de rehabilitaci�n.");
 	if(RehabOffer[playerid] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
 	if(GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "�Ambos, m�dico y paciente, deben estar en el hospital!");
  	if(GetPlayerCash(playerid) < ADICTION_REHAB_PRICE)
    {
	   	SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario para la rehabilitaci�n. ($%d.-)", ADICTION_REHAB_PRICE);
		return 1;
	}

	if(aleatorio < 55)
	    DeletePlayerAdiction(playerid, GetPlayerAdiction(playerid) / 2); // 50 porciento de que baje a la mitad
	else
		if(aleatorio < 75)
	        DeletePlayerAdiction(playerid, (GetPlayerAdiction(playerid) / 10) * 9); // 25 porciento que baje 90 porciento
		else
		    if(aleatorio < 85)
		        DeletePlayerAdiction(playerid, 100.0); // 10 porciento de eliminar la adiccion
   			else
			    DeletePlayerAdiction(playerid, 0.0); // 15 porciento de que no pase nada
	PlayerActionMessage(playerid, 15.0, "es sometido a un tratamiento de rehabilitaci�n en la cl�nica, veremos como responde ante este.");
    SendClientMessage(RehabOffer[playerid], COLOR_YELLOW2, "Una parte del dinero del paciente te ser� pagado en la siguiente hora, y otra parte ir� al fondo del hospital.");
	GivePlayerCash(playerid, -ADICTION_REHAB_PRICE);
 	PlayerInfo[RehabOffer[playerid]][pPayCheck] += ADICTION_REHAB_PRICE / 4;
 	GiveFactionMoney(FAC_HOSP, ADICTION_REHAB_PRICE / 4);
	return 1;
}
