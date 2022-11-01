/*****************************************************************************
    MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic, 2003-2004 Lax

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/

static inline PCHARINFO GetCharInfo(VOID) {
 //   if (!ppCharData) return NULL;
    return (PCHARINFO)pCharData;
}

static inline EQPlayer *GetSpawnByID(DWORD dwSpawnID)
{
	if (dwSpawnID<5000)
		return ppEQP_IDArray[dwSpawnID];
	return 0;
}
static inline EQPlayer *GetSpawnByName(char *spawnName)
{
	//
	//EQPlayer *
	return pLocalPlayer->GetPlayerFromName(spawnName);
    //return EqPlayer GetSpawnByName(spawnName);
}
static inline PSPELL GetSpellByID(DWORD dwSpellID)
{
	if (dwSpellID==0 || dwSpellID >= TOTAL_SPELL_COUNT)
		return 0;
	return &(*((PSPELLMGR)pSpellMgr)->Spells[dwSpellID]);
}

static inline PCHAR GetBodyTypeDesc(DWORD BodyTypeID)
{
	if (BodyTypeID<70)
		return szBodyType[BodyTypeID];
	return "*UNKNOWN BODYTYPE";
}

static inline PCHAR GetClassDesc(DWORD ClassID)
{
	if (ClassID==60)
		return "LDoN Recruiter";
	if (ClassID==61)
		return "LDoN Merchant";
	return pEverQuest->GetClassDesc(ClassID);
}



#define GetMaxMana() pCharData->Max_Mana()
#define GetMaxHPS() pCharData->Max_HP(0)
#define GetCurHPS() pCharData->Cur_HP(0)
#define GetMaxEndurance() pCharData->Max_Endurance()

static inline eSpawnType GetSpawnType(PSPAWNINFO pSpawn)
{
	switch(pSpawn->Type)
	{
	case SPAWN_PLAYER:
		{
			return PC;
		}
	case SPAWN_NPC:
		if (strstr(pSpawn->Name,"s_Mount"))
		{
			return MOUNT;
		}
		switch(pSpawn->BodyType)
		{
		case 11:
			return UNTARGETABLE;
		case 33:
			return CHEST;
		case 65:
			return TRAP;
		case 66:
			return TIMER;
		case 67:
			return TRIGGER;
		default:
			if (pSpawn->MasterID)
				return PET;
			else
				return NPC;
		}
		return NPC;
	case SPAWN_CORPSE:
		return CORPSE;
	default:
		return ITEM;
	}
}

static inline FLOAT GetDistance(FLOAT X1,FLOAT Y1)
{
	FLOAT dX=X1-((PSPAWNINFO)pCharSpawn)->X;
	FLOAT dY=Y1-((PSPAWNINFO)pCharSpawn)->Y;
	return sqrtf(dX*dX + dY*dY);
}

static inline FLOAT GetDistance(FLOAT X1,FLOAT Y1,FLOAT X2,FLOAT Y2)
{
	FLOAT dX=X1-X2;
	FLOAT dY=Y1-Y2;
	return sqrtf(dX*dX + dY*dY);
}

static inline FLOAT GetDistance3D(FLOAT X1, FLOAT Y1, FLOAT Z1, FLOAT X2, FLOAT Y2, FLOAT Z2)
{
    FLOAT dX = X1 - X2;
    FLOAT dY = Y1 - Y2;
    FLOAT dZ = Z1 - Z2;
    return sqrtf(dX*dX + dY*dY + dZ*dZ);
}


// ***************************************************************************
// Function:    DistanceToSpawn
// Description: Return the distance between two spawns
// ***************************************************************************
static inline FLOAT GetDistance(PSPAWNINFO pChar, PSPAWNINFO pSpawn)
{
    FLOAT X = pChar->X - pSpawn->X;
    FLOAT Y = pChar->Y - pSpawn->Y;
    //FLOAT Z = pChar->Z - pSpawn->Z;
    return sqrtf(X*X + Y*Y);// + Z*Z);
}

#define DistanceToSpawn(pChar,pSpawn) GetDistance(pChar,pSpawn)

#define _FileExists(filename) ( (_access( filename, 0 )) != -1 )

// ***************************************************************************
// FindMount(PSPAWNINFO) - Used to find the mount of a spawn, if one
//                         exists. returns the spawn if one does not.
// ***************************************************************************
static inline PSPAWNINFO FindMount(PSPAWNINFO pSpawn)
{
   if (!pSpawn->pActorInfo || !pSpawn->pActorInfo->Mount) return pSpawn;
   return pSpawn->pActorInfo->Mount; 
}


// ***************************************************************************
// Function:    ConColorToRGB
// Description: Returns the RGB color for a con color
// ***************************************************************************
static inline DWORD ConColorToARGB(DWORD ConColor)
{
    switch (ConColor) {
        case CONCOLOR_GREEN:
            return 0xFF00FF00;
        case CONCOLOR_LIGHTBLUE:
            return 0xFF00FFFF;
        case CONCOLOR_BLUE:
            return 0xFF0000FF;
        case CONCOLOR_BLACK:
            return 0xFFFFFFFF;
        case CONCOLOR_YELLOW:
            return 0xFFFFFF00;
        case CONCOLOR_RED:
        default:
            return 0xFFFF0000;
    }
}

static inline BOOL IsRaidMember(PSPAWNINFO pSpawn)
{
	for (DWORD N = 0 ; N < 72 ; N++)
	{
		if (pRaid->RaidMemberUsed[N] && !stricmp(pSpawn->Name,pRaid->RaidMember[N].Name))
			return 1;
	}
	return 0;
}

static inline BOOL IsGroupMember(PSPAWNINFO pSpawn)
{
	for (DWORD N = 0 ; N < 6 ; N++)
	{
		if (pSpawn==(PSPAWNINFO)ppGroup[N])
			return 1;
	}
	return 0;
}

static inline BOOL IsNumber(PCHAR String)
{
	if (*String==0)
		return FALSE;
	while(*String)
	{
		if (!((*String>='0' && *String<='9') || *String=='.'))
			return FALSE;
		++String;
	}
	return TRUE;
}

static inline BOOL IsNumberToComma(PCHAR String)
{
	if (*String==0)
		return FALSE;
	PCHAR Temp=String;
	while(*String)
	{
		if (!((*String>='0' && *String<='9') || *String=='.'))
		{
			if (*String==',' && Temp!=String)
				return TRUE;
			return FALSE;
		}
		++String;
	}
	return TRUE;
}

static inline BOOL LineOfSight(PSPAWNINFO Origin, PSPAWNINFO CanISeeThis)
{
	return CastRay(Origin,CanISeeThis->Y,CanISeeThis->X,CanISeeThis->Z);
}

static inline BOOL IsMobFleeing(PSPAWNINFO pChar, PSPAWNINFO pSpawn)
{
    FLOAT HeadingTo = (FLOAT)(atan2f(pChar->Y - pSpawn->Y, pSpawn->X - pChar->X) * 180.0f / PI + 90.0f);
    FLOAT Heading   = pSpawn->Heading*0.703125f;

    if (HeadingTo<0.0f)
        HeadingTo += 360.0f;
    else if (HeadingTo>=360.0f)
        HeadingTo -= 360.0f;

    FLOAT UB = HeadingTo + 120.0f;
    FLOAT LB = HeadingTo - 120.0f;

    if (LB < UB) return ((Heading < UB) && (Heading > LB));
    else return ((Heading < LB) && (Heading > UB));
}
static inline DWORD FixOffset(DWORD nOffset)
{
	//hack for new plugins...
    return (nOffset);
}
