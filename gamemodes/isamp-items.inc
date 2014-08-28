#if defined _isamp_items_included
	#endinput
#endif
#define _isamp_items_included

//==============================ITEM SYSTEM=====================================

#define ITEM_NONE               -1
#define ITEM_WEAPON             1
#define ITEM_OTHER              2
#define ITEM_STORABLE           3

#define ITEM_ID_CAMARA		    43
#define ITEM_ID_MATERIALES      47
#define ITEM_ID_BIDON		    48
#define ITEM_ID_MATERIAPRIMA    49
#define ITEM_ID_PRODUCTOS	    50
#define ITEM_ID_DINERO    		51
#define ITEM_ID_SANDWICH	    52
#define ITEM_ID_ALFAJOR		    53
#define ITEM_ID_AGUAMINERAL     54
#define ITEM_ID_MALETIN		    55
#define ITEM_ID_CASCOCOMUN      56
#define ITEM_ID_CASCOMOTOCROSS  57
#define ITEM_ID_CASCOROJO       58
#define ITEM_ID_CASCOBLANCO     59
#define ITEM_ID_CASCOROSA       60

//==============================DATA STORAGE====================================

enum ItemInfo {
	Name[40],
	ParamName[20],
	Type,
	BasePrice,
	bool:InvAvailable
};

static const ServerItems[][ItemInfo] = {

/*0*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*1*/	{"Manopla", "Cantidad", ITEM_WEAPON, 190, true},
/*2*/	{"Palo de Golf", "Cantidad", ITEM_WEAPON, 220, false},
/*3*/	{"Macana", "Cantidad", ITEM_WEAPON, 300, true},
/*4*/	{"Navaja", "Cantidad", ITEM_WEAPON, 250, true},
/*5*/	{"Bate", "Cantidad", ITEM_WEAPON, 250, false},
/*6*/	{"Pala", "Cantidad", ITEM_WEAPON, 300, false},
/*7*/	{"Palo de pool", "Cantidad", ITEM_WEAPON, 300, false},
/*8*/	{"Katana", "Cantidad", ITEM_WEAPON, 6000, false},
/*9*/	{"Motosierra", "Cantidad", ITEM_WEAPON, 15000, false},
/*10*/	{"Consolador doble punta", "Cantidad", ITEM_WEAPON, 150, true},
/*11*/	{"Consolador", "Cantidad", ITEM_WEAPON, 120, true},
/*12*/	{"Vibrador", "Cantidad", ITEM_WEAPON, 140, true},
/*13*/	{"Vibrador plateado", "Cantidad", ITEM_WEAPON, 120, true},
/*14*/	{"Flores", "Cantidad", ITEM_WEAPON, 50, true},
/*15*/	{"Baston", "Cantidad", ITEM_WEAPON, 200, true},
/*16*/	{"Granada", "Cantidad", ITEM_WEAPON, 1000, true},
/*17*/	{"Granada de gas", "Cantidad", ITEM_WEAPON, 200, true},
/*18*/	{"Bomba molotov", "Cantidad", ITEM_WEAPON, 450, true},
/*19*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*20*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*21*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*22*/	{"Pistola 9mm", "Munici�n", ITEM_WEAPON, 35, true},
/*23*/	{"Pistola 9mm con silenciador", "Munici�n", ITEM_WEAPON, 75, true},
/*24*/	{"Pistola Desert Eagle", "Munici�n", ITEM_WEAPON, 150, true},
/*25*/	{"Escopeta", "Munici�n", ITEM_WEAPON, 70, false},
/*26*/	{"Escopeta recortada", "Munici�n", ITEM_WEAPON, 120, false},
/*27*/	{"Escopeta de combate", "Munici�n", ITEM_WEAPON, 200, false},
/*28*/	{"Uzi", "Munici�n", ITEM_WEAPON, 50, true},
/*29*/	{"Subfusil MP-5", "Munici�n", ITEM_WEAPON, 95, false},
/*30*/	{"Fusil AK-47", "Munici�n", ITEM_WEAPON, 170, false},
/*31*/	{"Fusil M4", "Munici�n", ITEM_WEAPON, 170, false},
/*32*/	{"Pistola semiautomatica TEC-9", "Munici�n", ITEM_WEAPON, 50, true},
/*33*/	{"Rifle de caza", "Munici�n", ITEM_WEAPON, 60, false},
/*34*/	{"Rifle de francotirador", "Munici�n", ITEM_WEAPON, 550, false},
/*35*/	{"RPG-7", "Munici�n", ITEM_WEAPON, 25000, false},
/*36*/	{"Lanzamisiles", "Munici�n", ITEM_WEAPON, 20000, false},
/*37*/	{"Lanzallamas", "Munici�n", ITEM_WEAPON, 15000, false},
/*38*/	{"Minigun", "Munici�n", ITEM_WEAPON, 0, false},
/*39*/	{"Carga C4", "Cantidad", ITEM_WEAPON, 15000, false},
/*40*/	{"Detonador", "Cantidad", ITEM_WEAPON, 1000, true},
/*41*/	{"Aerosol", "Contenido", ITEM_WEAPON, 50, true},
/*42*/	{"Matafuegos", "Contenido", ITEM_WEAPON, 250, false},
/*43*/	{"C�mara fotogr�fica", "Fotos", ITEM_WEAPON, 20, true},
/*44*/	{"Visi�n nocturna", "Cantidad", ITEM_WEAPON, 0, false},
/*45*/	{"Visi�n t�rmica", "Cantidad", ITEM_WEAPON, 0, false},
/*46*/	{"Paraca�das", "Cantidad", ITEM_WEAPON, 0, false},
/*47*/	{"Caja de materiales", "Cantidad", ITEM_OTHER, 45, false},
/*48*/	{"Bid�n de combustible", "Contenido", ITEM_OTHER, 120, true},
/*49*/	{"Bolsa de materia prima", "Cantidad", ITEM_OTHER, 10, false},
/*50*/	{"Productos", "Cantidad", ITEM_OTHER, 50, false},
/*51*/	{"Dinero", "Cantidad", ITEM_OTHER, 1, false},
/*52*/	{"Sandwich", "Cantidad", ITEM_OTHER, 60, true},
/*53*/	{"Alfajor", "Cantidad", ITEM_OTHER, 30, true},
/*54*/	{"Agua mineral", "Cantidad", ITEM_OTHER, 40, true},
/*55*/	{"Malet�n", "Dinero", ITEM_OTHER, 500, true},
/*56*/  {"Casco Com�n", "Cantidad", ITEM_OTHER, 650, true}, //objectid 18645
/*57*/  {"Casco de Motocross", "Cantidad", ITEM_OTHER, 1150, true}, //objectid 18976
/*58*/  {"Casco Rojo", "Cantidad", ITEM_OTHER, 560, true}, //objectid 18977
/*59*/  {"Casco Blanco", "Cantidad", ITEM_OTHER, 560, true}, //objectid 18978
/*60*/  {"Casco Rosa", "Cantidad", ITEM_OTHER, 700, true} //objectid 18979

};

//==============================FUNCIONES=======================================

forward bool:HasItemInvPermission(itemid); // Devuelve verdadero si el objeto entra en un inventario (si esta permitido). Falso si no lo est�.
forward GetItemType(itemid); // Devuelve el tipo del item.
forward GetItemName(itemid); // Devuelve un string con el nombre del item.
forward GetItemParamName(itemid); // Devuelve un string con el nombre del parametro que le sigue al nombre del item.
forward GetItemPrice(itemid); // Devuelve el precio base unitario del item.
forward DeleteVisibleItemForPlayer(playerid, itemid); // Si el item es visible, lo borra para ese jugador.
forward GiveVisibleItemPlayerToPlayer(playerid, targetid, itemid); // Si el item es visible, lo borra para el jugador X y lo crea para el jugador Y.

//=======================IMPLEMENTACI�N DE FUNCIONES============================

stock bool:HasItemInvPermission(itemid)
{
	return ServerItems[itemid][InvAvailable];
}

stock GetItemType(itemid)
{
	return ServerItems[itemid][Type];
}

stock GetItemName(itemid)
{
	new str[40];
	format(str, sizeof(str), "%s" , ServerItems[itemid][Name]);
	return str;
}

stock GetItemParamName(itemid)
{
    new str[20];
    format(str, sizeof(str), "%s" , ServerItems[itemid][ParamName]);
	return str;
}

stock GetItemPrice(itemid)
{
	return ServerItems[itemid][BasePrice];
}

stock DeleteVisibleItemForPlayer(playerid, itemid)
{
	switch(itemid)
	{
	    case ITEM_ID_CASCOCOMUN: DeleteHelmetForPlayer(playerid);
	    case ITEM_ID_CASCOMOTOCROSS: DeleteHelmetForPlayer(playerid);
	    case ITEM_ID_CASCOROJO: DeleteHelmetForPlayer(playerid);
	    case ITEM_ID_CASCOBLANCO: DeleteHelmetForPlayer(playerid);
	    case ITEM_ID_CASCOROSA: DeleteHelmetForPlayer(playerid);
	    case ITEM_ID_MALETIN: DeleteBriefCaseForPlayer(playerid);
	}
	return 1;
}

stock GiveVisibleItemPlayerToPlayer(playerid, targetid, itemid)
{
	switch(itemid)
	{
		case ITEM_ID_CASCOCOMUN: GiveHelmetPlayerToPlayer(playerid, targetid, ITEM_ID_CASCOCOMUN);
		case ITEM_ID_CASCOMOTOCROSS: GiveHelmetPlayerToPlayer(playerid, targetid, ITEM_ID_CASCOMOTOCROSS);
		case ITEM_ID_CASCOROJO: GiveHelmetPlayerToPlayer(playerid, targetid, ITEM_ID_CASCOROJO);
		case ITEM_ID_CASCOBLANCO: GiveHelmetPlayerToPlayer(playerid, targetid, ITEM_ID_CASCOBLANCO);
		case ITEM_ID_CASCOROSA: GiveHelmetPlayerToPlayer(playerid, targetid, ITEM_ID_CASCOROSA);
		case ITEM_ID_MALETIN: GiveBriefCasePlayerToPlayer(playerid, targetid);
	}
	return 1;
}