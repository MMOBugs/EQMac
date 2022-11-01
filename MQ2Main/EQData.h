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
namespace EQData
{

// ***************************************************************************
// Defines
// ***************************************************************************

enum PlayerClass
{
	Unknown=							0,
	Warrior=							1,
	Cleric=								2,
	Paladin=							3,
	Ranger=								4,
	Shadowknight=						5,
	Druid=								6,
	Monk=								7,
	Bard=								8,
	Rogue=								9,
	Shaman=								10,
	Necromancer=						11,
	Wizard=								12,
	Mage=								13,
	Enchanter=							14,
	Beastlord=							15,
	Berserker=							16,
	TotalClasses=						16,
};
// class 20 through 35 are the NPC GMs (same class order as above)
// class 41   Merchant
// class 60   LDoN Recruiter
// class 61   LDoN Merchant
// class 63   Tribute Master

typedef struct _ClassInfo
{
	bool CanCast;
	bool PureCaster;
	bool PetClass;
	bool DruidType;
	bool NecroType;
	bool ClericType;
	bool ShamanType;
	char RaidColorOrder;
	PCHAR Name;
	PCHAR ShortName;
} CLASSINFO, *PCLASSINFO;

static _ClassInfo ClassInfo[]=
{
	{0,0,0,0,0,0,0,0,"",""},//unk
	{0,0,0,0,0,0,0,13,"Warrior","war"},//war
	{1,1,0,0,0,1,0,2,"Cleric","clr"},//clr
	{1,0,0,0,0,1,0,8,"Paladin","pal"},//pal
	{1,0,0,1,0,0,0,9,"Ranger","rng"},//rng
	{1,0,0,0,1,0,0,11,"Shadowknight","shd"},//shd
	{1,1,0,1,0,0,0,3,"Druid","dru"},//dru
	{0,0,0,0,0,0,0,6,"Monk","mnk"},//mnk
	{1,0,0,0,0,0,0,0,"Bard","brd"},//brd
	{0,0,0,0,0,0,0,10,"Rogue","rog"},//rog
	{1,1,1,0,0,0,1,12,"Shaman","shm"},//shm
	{1,1,1,0,1,0,0,7,"Necromancer","nec"},//nec
	{1,1,0,0,0,0,0,14,"Wizard","wiz"},//wiz
	{1,1,1,0,0,0,0,5,"Mage","mag"},//mag
	{1,1,0,0,0,0,0,4,"Enchanter","enc"},//enc
	{1,0,1,0,0,0,1,1,"Beastlord","bst"},//bst
	{0,0,0,0,0,0,0,15,"Berserker","ber"},//ber
};

#define BI_TARGETABLE					1
#define BI_TRIGGER						2 
#define BI_TRAP							4
#define BI_TIMER						8

typedef struct _BodyInfo
{
	PCHAR Name;
	DWORD Flags;
} BODYINFO, *PBODYINFO;

#define SPAWN_PLAYER                    0
#define SPAWN_NPC                       1
#define SPAWN_CORPSE                    2
//#define SPAWN_ANY                     3
//#define SPAWN_PET                     4

#define ITEM_NORMAL1                    0x0031
#define ITEM_NORMAL2                    0x0036
#define ITEM_NORMAL3                    0x315f
#define ITEM_NORMAL4                    0x3336
#define ITEM_NORMAL5                    0x0032
#define ITEM_NORMAL6                    0x0033
#define ITEM_NORMAL7                    0x0034
#define ITEM_NORMAL8                    0x0039
#define ITEM_CONTAINER                  0x7900
#define ITEM_CONTAINER_PLAIN            0x7953
#define ITEM_BOOK                       0x7379

#define ITEMITEMTYPE_FOOD				0x0e 
#define ITEMITEMTYPE_WATER				0x0f 
#define ITEMITEMTYPE_ALCOHOL			0x26 
#define ITEMITEMTYPE_POISON				0x2a 
#define ITEMITEMTYPE_AUGUMENT			0x36 

#define ITEMEFFECTTYPE_COMBAT			0x00 
#define ITEMEFFECTTYPE_INVENTORY1		0x01 // Bards need to stop sing to cast 
#define ITEMEFFECTTYPE_WORN				0x02 
#define ITEMEFFECTTYPE_INVENTORY2		0x03 
#define ITEMEFFECTTYPE_MUSTEQUIP		0x04 // Bards need to stop sing to cast 
#define ITEMEFFECTTYPE_INVENTORY3		0x05 

#define SKILLMINDAMAGEMOD_BASH			0x00 
#define SKILLMINDAMAGEMOD_BACKSTAB		0x01 
#define SKILLMINDAMAGEMOD_DRAGONPUNCH	0x02 
#define SKILLMINDAMAGEMOD_EAGLESTRIKE	0x03 
#define SKILLMINDAMAGEMOD_FLYINGKICK	0x04 
#define SKILLMINDAMAGEMOD_KICK			0x05 
#define SKILLMINDAMAGEMOD_ROUNDKICK		0x06 
#define SKILLMINDAMAGEMOD_TIGERCLAW		0x07 
#define SKILLMINDAMAGEMOD_FRENZY		0x08 

#define COLOR_DEFAULT                   0x00 +   0
#define COLOR_DARKGREY                  0x00 +   1
#define COLOR_DARKGREEN                 0x00 +   2
#define COLOR_DARKBLUE                  0x00 +   3
#define COLOR_PURPLE                    0x00 +   5
#define COLOR_LIGHTGREY                 0x00 +   6

#define CONCOLOR_GREEN                  0x00 +  14
#define CONCOLOR_LIGHTBLUE              0x00 +  18
#define CONCOLOR_BLUE                   0x00 +  16
#define CONCOLOR_BLACK                  0x00 +  20
#define CONCOLOR_YELLOW                 0x00 +  15
#define CONCOLOR_RED                    0x00 +  13

#define USERCOLOR_SAY                   0xFF +   1 //  1  - Say
#define USERCOLOR_TELL                  0xFF +   2 //  2  - Tell
#define USERCOLOR_GROUP                 0xFF +   3 //  3  - Group
#define USERCOLOR_GUILD                 0xFF +   4 //  4  - Guild
#define USERCOLOR_OOC                   0xFF +   5 //  5  - OOC
#define USERCOLOR_AUCTION               0xFF +   6 //  6  - Auction
#define USERCOLOR_SHOUT                 0xFF +   7 //  7  - Shout
#define USERCOLOR_EMOTE                 0xFF +   8 //  8  - Emote
#define USERCOLOR_SPELLS                0xFF +   9 //  9  - Spells (meming, scribing, casting, etc.)
#define USERCOLOR_YOU_HIT_OTHER         0xFF +  10 //  10 - You hit other
#define USERCOLOR_OTHER_HIT_YOU         0xFF +  11 //  11 - Other hits you
#define USERCOLOR_YOU_MISS_OTHER        0xFF +  12 //  12 - You miss other
#define USERCOLOR_OTHER_MISS_YOU        0xFF +  13 //  13 - Other misses you
#define USERCOLOR_DUELS                 0xFF +  14 //  14 - Some broadcasts (duels)
#define USERCOLOR_SKILLS                0xFF +  15 //  15 - Skills (ups, non-combat use, etc.)
#define USERCOLOR_DISCIPLINES           0xFF +  16 //  16 - Disciplines or special abilities
#define USERCOLOR_UNUSED001             0xFF +  17 //  17 - Unused at this time
#define USERCOLOR_DEFAULT               0xFF +  18 //  18 - Default text and stuff you type
#define USERCOLOR_UNUSED002             0xFF +  19 //  19 - Unused at this time
#define USERCOLOR_MERCHANT_OFFER        0xFF +  20 //  20 - Merchant Offer Price
#define USERCOLOR_MERCHANT_EXCHANGE     0xFF +  21 //  21 - Merchant Buy/Sell
#define USERCOLOR_YOUR_DEATH            0xFF +  22 //  22 - Your death message
#define USERCOLOR_OTHER_DEATH           0xFF +  23 //  23 - Others death message
#define USERCOLOR_OTHER_HIT_OTHER       0xFF +  24 //  24 - Other damage other
#define USERCOLOR_OTHER_MISS_OTHER      0xFF +  25 //  25 - Other miss other
#define USERCOLOR_WHO                   0xFF +  26 //  26 - /who command
#define USERCOLOR_YELL                  0xFF +  27 //  27 - yell for help
#define USERCOLOR_NON_MELEE             0xFF +  28 //  28 - Hit for non-melee
#define USERCOLOR_SPELL_WORN_OFF        0xFF +  29 //  29 - Spell worn off
#define USERCOLOR_MONEY_SPLIT           0xFF +  30 //  30 - Money splits
#define USERCOLOR_LOOT                  0xFF +  31 //  31 - Loot message
#define USERCOLOR_RANDOM                0xFF +  32 //  32 - Dice Roll (/random)
#define USERCOLOR_OTHERS_SPELLS         0xFF +  33 //  33 - Others spells
#define USERCOLOR_SPELL_FAILURE         0xFF +  34 //  34 - Spell Failures (resists, fizzles, missing component, bad target, etc.)
#define USERCOLOR_CHAT_CHANNEL          0xFF +  35 //  35 - Chat Channel Messages
#define USERCOLOR_CHAT_1                0xFF +  36 //  36 - Chat Channel 1
#define USERCOLOR_CHAT_2                0xFF +  37 //  37 - Chat Channel 2
#define USERCOLOR_CHAT_3                0xFF +  38 //  38 - Chat Channel 3
#define USERCOLOR_CHAT_4                0xFF +  39 //  39 - Chat Channel 4
#define USERCOLOR_CHAT_5                0xFF +  40 //  40 - Chat Channel 5
#define USERCOLOR_CHAT_6                0xFF +  41 //  41 - Chat Channel 6
#define USERCOLOR_CHAT_7                0xFF +  42 //  42 - Chat Channel 7
#define USERCOLOR_CHAT_8                0xFF +  43 //  43 - Chat Channel 8
#define USERCOLOR_CHAT_9                0xFF +  44 //  44 - Chat Channel 9
#define USERCOLOR_CHAT_10               0xFF +  45 //  45 - Chat Channel 10
#define USERCOLOR_MELEE_CRIT            0xFF +  46 //  46 - Melee Crits
#define USERCOLOR_SPELL_CRIT            0xFF +  47 //  47 - Spell Crits
#define USERCOLOR_TOO_FAR_AWAY          0xFF +  48 //  48 - Too far away (melee)
#define USERCOLOR_NPC_RAMAGE            0xFF +  49 //  49 - NPC Rampage
#define USERCOLOR_NPC_FURRY             0xFF +  50 //  50 - NPC Furry
#define USERCOLOR_NPC_ENRAGE            0xFF +  51 //  51 - NPC Enrage
#define USERCOLOR_ECHO_SAY              0xFF +  52 //  52 - say echo
#define USERCOLOR_ECHO_TELL             0xFF +  53 //  53 - tell echo
#define USERCOLOR_ECHO_GROUP            0xFF +  54 //  54 - group echo
#define USERCOLOR_ECHO_GUILD            0xFF +  55 //  55 - guild echo
#define USERCOLOR_ECHO_OOC              0xFF +  56 //  56 - group echo
#define USERCOLOR_ECHO_AUCTION          0xFF +  57 //  57 - auction echo
#define USERCOLOR_ECHO_SHOUT            0xFF +  58 //  58 - shout echo
#define USERCOLOR_ECHO_EMOTE            0xFF +  59 //  59 - emote echo
#define USERCOLOR_ECHO_CHAT_1           0xFF +  60 //  60 - chat 1 echo
#define USERCOLOR_ECHO_CHAT_2           0xFF +  61 //  61 - chat 2 echo
#define USERCOLOR_ECHO_CHAT_3           0xFF +  62 //  62 - chat 3 echo
#define USERCOLOR_ECHO_CHAT_4           0xFF +  63 //  63 - chat 4 echo
#define USERCOLOR_ECHO_CHAT_5           0xFF +  64 //  64 - chat 5 echo
#define USERCOLOR_ECHO_CHAT_6           0xFF +  65 //  65 - chat 6 echo
#define USERCOLOR_ECHO_CHAT_7           0xFF +  66 //  66 - chat 7 echo
#define USERCOLOR_ECHO_CHAT_8           0xFF +  67 //  67 - chat 8 echo
#define USERCOLOR_ECHO_CHAT_9           0xFF +  68 //  68 - chat 9 echo
#define USERCOLOR_ECHO_CHAT_10          0xFF +  69 //  69 - chat 10 echo

#define DEITY_Bertoxxulous				201
#define DEITY_BrellSerilis				202
#define DEITY_CazicThule				203
#define DEITY_ErollisiMarr				204
#define DEITY_Bristlebane				205
#define DEITY_Innoruuk					206
#define DEITY_Karana					207
#define DEITY_MithanielMarr				208
#define DEITY_Prexus					209
#define DEITY_Quellious					210
#define DEITY_RallosZek					211
#define DEITY_RodcetNife				212
#define DEITY_SolusekRo					213
#define DEITY_TheTribunal				214
#define DEITY_Tunare					215
#define DEITY_Veeshan					216

#define ITEMTYPE_NORMAL					0
#define ITEMTYPE_PACK					1
#define ITEMTYPE_BOOK					2

#define COMP_NONE						0
#define COMP_EQ							1
#define COMP_NE							2
#define COMP_GT							3
#define COMP_LT							4
#define COMP_GE							5
#define COMP_LE							6
#define COMP_CONT						7
#define COMP_NOTCONT					8
#define COMP_BITAND						9
#define COMP_BITOR						10

#define COMP_TYPE_STRING				0
#define COMP_TYPE_NUMERIC				1
#define COMP_TYPE_BIT					2

#define CMD_MQ							1
#define CMD_EQ							2		

#define LASTFIND_NOTFOUND				96
#define LASTFIND_PRIMARY				97

#define EVENT_CHAT						0
#define EVENT_TIMER						1
#define EVENT_CUSTOM					2
#define EVENT_EVAL						3
#define EVENT_EXEC						4
#define EVENT_PULSE						5
#define EVENT_SHUTDOWN					6
#define EVENT_BREAK						7
#define NUM_EVENTS						8

#define CHAT_SAY						1
#define CHAT_TELL						2
#define CHAT_OOC						4
#define CHAT_SHOUT						8
#define CHAT_AUC						16
#define CHAT_GUILD						32
#define CHAT_GROUP						64
#define CHAT_CHAT						128
#define CHATEVENT(x)					(gEventChat & x)

#define FILTERSKILL_ALL					0
#define FILTERSKILL_INCREASE			1
#define FILTERSKILL_NONE				2

#define FILTERMACRO_ALL					0
#define FILTERMACRO_ENHANCED			1
#define FILTERMACRO_NONE				2


#define MAX_STRING						2048
#define MAX_VARNAME						64

// Defines for CXWnd WindowStyle
#define CWS_VSCROLL						0x1
#define CWS_HSCROLL						0x2
#define CWS_TITLE						0x4
#define CWS_CLOSE						0x8
//#define CWS_UNKNOWN					0x10
#define CWS_MINIMIZE					0x20
#define CWS_BORDER						0x40
//#define CWS_UNKNOWN					0x80
//#define CWS_UNKNOWN					0x100
#define CWS_RESIZEALL					0x200
#define CWS_TRANSPARENT					0x400
//#define CWS_UNKNOWN					0x800
#define CWS_NOMOVE						0x8000
#define CWS_UNKNOWN						0x40000
#define ToggleBit(field,bit)			field^=bit;
#define BitOn(field,bit)				field|=bit;
#define BitOff(field,bit)				field&=~bit;
// End CXWnd WindowStyle Defines
//MenuStyles
#define MS_EXPANDABLE						0x80000000;
enum MOUSE_DATA_TYPES {
   MD_Unknown = -1,
   MD_Button0Click=0,
   MD_Button1Click,
   MD_Button0,
   MD_Button1
};

#define nEQMappableCommands				0x7e


// ***************************************************************************
// Structures
// ***************************************************************************

typedef struct _MOUSESPOOF {
   MOUSE_DATA_TYPES   mdType;
   DWORD            dwData;
   struct _MOUSESPOOF   *pNext;
} MOUSESPOOF, *PMOUSESPOOF;

typedef struct _MOUSECLICK {
   BYTE ConfirmLeftClick;// DO NOT WRITE TO THIS BYTE
   BYTE ConfirmRightClick;// DO NOT WRITE TO THIS BYTE
   BYTE RightClick;
   BYTE LeftClick;
} MOUSECLICK, *PMOUSECLICK;

typedef struct _UILOCATION {
   DWORD x;
   DWORD y;
   DWORD w;
   DWORD h;
   CHAR error[MAX_STRING];
} UILOCATION, *PUILOCATION;

#define ITEM_NAME_LEN         64
#define LORE_NAME_LEN         80

typedef struct _ITEMINFOOLD { 
/*0x00*/ CHAR Name[ITEM_NAME_LEN]; 
/*0x40*/ CHAR LoreName[LORE_NAME_LEN]; 
/*0x90*/ CHAR IDFile[0x20]; 
/*0xb0*/ DWORD ItemNumber; 
/*0xb4*/ DWORD EquipSlots; 
/*0xb8*/ DWORD Cost; 
/*0xbc*/ DWORD IconNumber; 
/*0xc0*/ BYTE Unknown0xc0[0x10]; 
/*0xd0*/ BYTE UnknownData0xd0; 
/*0xd1*/ BYTE Weight; 
/*0xd2*/ BYTE NoRent; 
/*0xd3*/ BYTE NoDrop; // 0=can drop (and place in bank), 1=no drop, (2=no bank) 
/*0xd4*/ BYTE Size; 
/*0xd5*/ BYTE Type; 
/*0xd6*/ BYTE TradeSkills; 
/*0x0d7*/ BYTE Lore; 
/*0x0d8*/ BYTE PendingLore; 
/*0x0d9*/ BYTE Artifact; 
/*0x0da*/ BYTE Summoned; 
/*0x0db*/ BYTE SvCold; 
/*0x0dc*/ BYTE SvFire; 
/*0x0dd*/ BYTE SvMagic; 
/*0x0de*/ BYTE SvDisease; 
/*0x0df*/ BYTE SvPoison; 
/*0x0e0*/ BYTE STR; 
/*0x0e1*/ BYTE STA; 
/*0x0e2*/ BYTE AGI; 
/*0x0e3*/ BYTE DEX; 
/*0x0e4*/ BYTE CHA; 
/*0x0e5*/ BYTE INT; 
/*0x0e6*/ BYTE WIS; 
/*0x0e7*/ BYTE Unknown0xe7; 
/*0x0e8*/ DWORD HP; 
/*0x0ec*/ DWORD Mana; 
/*0x0f0*/ DWORD AC; 
/*0x0f4*/ DWORD SkillModValue; 
/*0x0f8*/ DWORD BaneDMGRace; 
/*0x0fc*/ DWORD BaneDMGBodyType; 
/*0x100*/ DWORD RequiredLevel; 
/*0x104*/ DWORD InstrumentType; 
/*0x108*/ DWORD InstrumentMod; 
/*0x10c*/ DWORD Classes; 
/*0x110*/ DWORD Races; 
/*0x114*/ DWORD Diety; 
/*0x118*/ BYTE Unknown0x118[0x4]; 
/*0x11c*/ DWORD SpellId; 
/*0x120*/ DWORD Color; 
/*0x124*/ BYTE SkillModType; 
/*0x125*/ BYTE BaneDMGBodyTypeValue; 
/*0x126*/ BYTE BaneDMGRaceValue; 
/*0x127*/ BYTE Magic; 
/*0x128*/ BYTE Level; 
/*0x129*/ BYTE Light; 
/*0x12a*/ BYTE Delay; 
/*0x12b*/ BYTE RecommendedLevel; 
/*0x12c*/ BYTE RecommendedSkill; 
/*0x12d*/ BYTE DmgBonusType; 
/*0x12e*/ BYTE DmgBonusVal; 
/*0x12f*/ BYTE Range; 
/*0x130*/ BYTE Damage; 
/*0x131*/ BYTE ItemType; 
/*0x132*/ WORD Material; 
/*0x134*/ DWORD AugSlot1; 
/*0x138*/ DWORD AugSlot2; 
/*0x13c*/ DWORD AugSlot3; 
/*0x140*/ DWORD AugSlot4; 
/*0x144*/ DWORD AugSlot5; 
/*0x148*/ DWORD AugType; 
/*0x14c*/ DWORD AugRestrictions; 
/*0x150*/ DWORD LDTheme; 
/*0x154*/ DWORD LDCost; 
/*0x158*/ BYTE Unknown0x158[4]; 
/*0x15C*/ DWORD FactionModType[0x4]; 
/*0x16C*/ DWORD FactionModValue[0x4]; 
/*0x17c*/ BYTE CharmFile[0x20]; 
/*0x19c*/ FLOAT QuestValue; //everything over 1.00000 is a good thing... ring of the ancients is 777.500 
/*0x1a0*/ BYTE Unknown0x1a0[0x8]; 
/*0x1a8*/ DWORD ProcRate; 
/*0x1ac*/ DWORD FocusId; 
/*0x1b0*/ DWORD CombatEffects; 
/*0x1b4*/ DWORD Shielding; 
/*0x1b8*/ DWORD StunResist; 
/*0x1bc*/ DWORD DoTShielding; 
/*0x1c0*/ DWORD StrikeThrough; 
/*0x1c4*/ DWORD DmgBonusSkill; // SkillMinDamageMod; 
/*0x1c8*/ DWORD DmgBonusValue; // MinDamageMod; 
/*0x1cc*/ DWORD SpellShield; 
/*0x1d0*/ DWORD Avoidance; 
/*0x1d4*/ DWORD Accuracy; 
/*0x1d8*/ DWORD ScaleFactor; // 0x64=normal, 0x32=double all stats 
/*0x1dc*/ DWORD CastTime; 
union { 
/*0x1e0*/ DWORD MaxCharges; 
/*0x1e0*/ DWORD Stackable; 
}; 
/*0x1e4*/ BYTE EffectType; 
/*0x1e5*/ BYTE BookType; // 0=note, !0=book 
/*0x1e6*/ BYTE BookLang; 
/*0x1e7*/ CHAR BookFile[0x1d]; 
/*0x204*/ BYTE Skill; 
/*0x205*/ BYTE Combine; 
/*0x206*/ BYTE Slots; 
/*0x207*/ BYTE SizeCapacity; 
/*0x208*/ BYTE WeightReduction; 
/*0x209*/ BYTE Unknown0x209[0x3]; 
/*0x20c*/ DWORD Favor; // Tribute Value 
/*0x210*/ DWORD Unknown0x210; // Has to do with Favor 
/*0x214*/ BYTE Unkonwn0x214; // Has to do with No Drop 
/*0x215*/ BYTE Unknown0x215[0x3]; 
/*0x218*/ DWORD Endurance; 
/*0x21c*/ DWORD Attack; 
/*0x220*/ DWORD HPRegen; 
/*0x224*/ DWORD ManaRegen; 
/*0x228*/ DWORD Haste; 
/*0x22c*/ DWORD DamShield; 
/*0x230*/ DWORD Recast; 
/*0x234*/ DWORD TimerID; 
/*0x238*/ DWORD SolventNeeded; //ID# of Solvent (Augs only)
/*0x23c*/ 
} ITEMINFOOLD, *PITEMINFOOLD;

// 7-18-04 Size 0x58 
typedef struct _CONTENTSOLD { 
/*0x00*/ struct _ITEMINFO *Item; 
   union { 
/*0x04*/ struct _CONTENTSOLD *Contents[0x0a]; //addresses to whats inside the bag if its a bag 
/*0x04*/ struct _ITEMINFO *Augments[0x0a]; //Only 1-5 are actually used (for now) 
   }; 
/*0x2c*/  DWORD   StackCount; 
/*0x30*/  BYTE    Unknown0x30[0xc]; 
/*0x3c*/  DWORD   Charges; 
/*0x40*/  DWORD   ItemSlot;// slotid for Player Items 
/*0x44*/  BYTE    Unknown0x44[0x4]; 
/*0x48*/  DWORD   ItemSlot2;// slotid for Merchant Items 
/*0x4c*/  DWORD   Unknown0x4c; 
/*0x50*/  DWORD   Price; //price a player vendor set the item at 
/*0x54*/  DWORD   Open; 
/*0x58*/ 
} CONTENTSOLD, *PCONTENTSOLD;
typedef struct _COMMON {
/*0x0e4*/	signed char STR;
/*0x0e5*/	signed char STA;
/*0x0e6*/	signed char CHA;
/*0x0e7*/	signed char DEX;
/*0x0e8*/	signed char INT;
/*0x0e9*/	signed char AGI;
/*0x0ea*/	signed char WIS;
/*0x0eb*/	signed char SvMagic;
/*0x0ec*/	signed char SvFire;
/*0x0ed*/	signed char SvCold;
/*0x0ee*/	signed char SvDisease;
/*0x0ef*/	signed char SvPoison;
/*0x0f0*/	signed short HP;
/*0x0f2*/	signed short Mana;
/*0x0f4*/	signed short AC;
/*0x0f6*/	BYTE Unknown0x0f6[2];
/*0x0f8*/	BYTE Light;
/*0x0f9*/	BYTE Delay;
/*0x0fa*/	BYTE Damage;
/*0x0fb*/	BYTE Skill;//*** confirm
/*0x0fc*/	BYTE Range;
/*0x0fd**/	BYTE ItemType;
/*0x0fe*/	BYTE Magic;
/*0x0ff*/	BYTE CastingLevel0;
/*0x100*/	BYTE Material;
/*0x101*/	BYTE Level;//*** needs confirm
/*0x102*/	BYTE ProcRate;//*** needs confirm
/*0x103*/	BYTE Unknown0x103;
/*0x104*/	DWORD Color;
/*0x108*/	BYTE Unknown0x108[2];
/*0x10a*/	WORD SpellId0;
/*0x10c*/	WORD Classes;
/*0x10e*/   BYTE Unknown0x10e[2];
/*0x110*/	WORD Races;
/*0x112*/	BYTE Unknown0x112[2];
/*0x114*/	BYTE Stackable;
/*0x115*/	BYTE CastingLevel;
	union {
/*0x116*/	BYTE StackCount;
/*0x116*/	BYTE Charges;
	};
/*0x117*/	BYTE EffectType;
/*0x118*/	WORD SpellId;
/*0x11c*/	WORD CastTime;//*** needs confirm
/*0x11e*/	BYTE InstrumentMod;//*** needs confirm

/*0x11f*/
} COMMON, *PCOMMON;

typedef struct _BOOK {
/*0x0e4*/	BYTE Unknown0x0e4[3];
/*0x0e7*/	CHAR File[0xf];
/*0x0f6*/
} BOOK, *PBOOK;

typedef struct _CONTAINER {
/*0x0e4*/	struct _ITEMINFO *Contents[0xa];
/*0x10c*/	BYTE Combine;
/*0x10d*/	BYTE Slots;
/*0x10e*/	BYTE Open;
/*0x10f*/	BYTE SizeCapacity;
/*0x110*/	BYTE WeightReduction;
/*0x111*/
} CONTAINER, *PCONTAINER;
typedef struct _ITEMINFO {
/*0x000*/	CHAR Name[0x40];
/*0x040*/	CHAR LoreName[0x50];
/*0x090*/	CHAR IDFile[0x10];
/*0x0a0*/	BYTE Unknown0a0[0xa];
/*0x0aa*/	BYTE InstrumentType;//check/***
/*0x0ab*/	BYTE Summoned;//check/***
/*0x0ac*/	BYTE Lore;//check/***
/*0x0ad*/	BYTE Magic;//check/***
/*0x0ae*/	BYTE Weight;
/*0x0af*/	BYTE NoRent;
/*0x0b0*/	BYTE NoDrop;
/*0x0b1*/	BYTE Size;
/*0x0b2*/	BYTE Type;
/*0x0b3*/	BYTE Unknown0x0b3;
/*0x0b4*/	WORD ID;//ItemNumber
/*0x0b6*/	WORD IconID;//IconNumber
/*0x0b8*/	DWORD EquipSlot;
/*0x0bc*/	DWORD EquipableSlots;
/*0x0c0*/	DWORD Cost;
/*0x0c4*/	DWORD Price;//*** needs confirm
/*0x0c8*/	BYTE  Unknown0c4[0x1c];
/*0x0e4*/	union { 
		COMMON    Common;
		CONTAINER Container;
		BOOK      Book;
	};
} ITEMINFO, *PITEMINFO;
// eqmac eqmule
// Size 0xc
typedef struct _SPELLBUFF {
/*0x00*/    BYTE      Unknown0x00;
/*0x01*/    BYTE      Level;
/*0x02*/    CHAR      Modifier; // bard song modifier, divide by 10 to get 2.8 etc
/*0x03*/    CHAR      DamageShield;  // maybe.. I've noticed this is -1 on a lot of ds's.
/*0x04*/    WORD      SpellID;// -1 or 0 for no spell..
/*0x06*/    WORD     Duration;
/*0x08*/    WORD     DamageAbsorbRemaining;  // Melee or Spellshield type
/*0x0c*/
} SPELLBUFF, *PSPELLBUFF;

typedef struct _SPELLBUFFOLD
{
/*0x00*/	WORD  Unknown0000;
/*0x02*/	BYTE  Level;
/*0x03*/	BYTE  Unknown0003;
/*0x04*/	WORD  Unknown0004;
/*0x06*/	WORD  SpellID;
/*0x08*/	DWORD Duration;
/*0x0c*/	DWORD Unknown;
} SPELLBUFFOLD, *PSPELLBUFFOLD;

#define MAX_INV_SIZE 29
// 12-23-2003   TheColonel
//eqmac fixed for eqgame.exe dec 2002
typedef struct _INVENTORY { 
/*0x00**/  struct	_ITEMINFO* LeftEar; //1
/*0x04**/  struct	_ITEMINFO* Head; //2
/*0x0c*/  struct	_ITEMINFO* Face; //3
/*0x0c**/  struct	_ITEMINFO* RightEar; //4
/*0x14*/  struct	_ITEMINFO* Neck; //5
/*0x18*/  struct	_ITEMINFO* Shoulders;//6 
/*0x1c*/  struct	_ITEMINFO* Arms; //7
/*0x20*/  struct	_ITEMINFO* Back; //8
/*0x24*/  struct	_ITEMINFO* LeftWrist;//9 
/*0x28*/  struct	_ITEMINFO* RightWrist; //10
/*0x2c*/  struct	_ITEMINFO* Range; //11
/*0x30**/  struct	_ITEMINFO* Hands; //12
/*0x34*/  struct	_ITEMINFO* Primary; //13
/*0x38*/  struct	_ITEMINFO* Secondary; //14
/*0x3c*/  struct	_ITEMINFO* LeftFinger; //15
/*0x40*/  struct	_ITEMINFO* RightFinger; //16
/*0x44*/  struct	_ITEMINFO* Chest; //17
/*0x48*/  struct	_ITEMINFO* Legs; //18
/*0x4c*/  struct	_ITEMINFO* Feet; //19
/*0x50*/  struct	_ITEMINFO* Waist; //20
/*0x50*/  struct	_ITEMINFO* Ammo; //21
/*0x58*/  struct	_ITEMINFO* Pack[0x8]; 
} INVENTORY, *PINVENTORY; 

#define      NUM_BANK_SLOTS         0x8
#define      NUM_BOOK_SLOTS         0x200

// Size: 0xab34 on 8/11/2004
typedef struct _CHARINFO { 
/*0x0000*/   BYTE		Unknown0x0000[2];    
/*0x0002*/   CHAR		Name[0x40];    
/*0x0042*/   CHAR		Lastname[0x20];    
/*0x0062*/   BYTE		Unknown0x0062[0x26];    
/*0x0088*/   BYTE		Gender;    
/*0x0089*/   BYTE		Unknown0x0089;    
/*0x008a**/   BYTE		Race;    
/*0x008b*/   BYTE		Unknown0x008b;    
/*0x008c**/   BYTE		Class;    
/*0x008d*/   BYTE		Unknown0x008d[0x3];    
/*0x0090**/   DWORD		Level;    
/*0x0094**/   DWORD		Exp;    
/*0x0098**/   WORD		PracticePoints;    
/*0x009a**/   WORD		Mana;    
/*0x009c**/   WORD		BaseHP;
/*0x009e**/   BYTE		Stunned;
/*0x009f**/   BYTE		Unknown0x009f;
/*0x00a0**/   WORD		BaseSTR;    
/*0x00a2**/   WORD		BaseSTA;    
/*0x00a4**/   WORD		BaseCHA;    
/*0x00a6**/   WORD		BaseDEX;    
/*0x00a8**/   WORD		BaseINT;    
/*0x00aa**/   WORD		BaseAGI;    
/*0x00ac**/   WORD		BaseWIS;    
/*0x00ae**/   BYTE		Unknown0x00ae[0x6a];
/*0x0118**/   BYTE		languages[0x20];  
/*0x0138*/   BYTE		Unknown0x0138[0x12c];
/*0x0264**/   struct	_SPELLBUFF   Buff[0x0f];   //0x96 
/*0x02fa**/   BYTE		Unknown0x02fa[0x438];
/*0x0732**/   WORD		SpellBook[NUM_BOOK_SLOTS];    
/*0x0b32**/   WORD		MemorizedSpells[0x8];    
/*0x0b42*/   BYTE		Unknown0x0b42[0x12];
/*0x0b54**/   FLOAT		y;    //updates are seldom, but when u press escape from a banker it updates...
/*0x0b58**/   FLOAT		x;    
/*0x0b5c**/   FLOAT		z;    
/*0x0b60**/   FLOAT		heading;    
/*0x0b64*/   BYTE		standstate;    
/*0x0b65*/   BYTE		Unknown0x0b65[0x3];    
/*0x0b68**/   DWORD		Plat;    
/*0x0b6c**/   DWORD		Gold;    
/*0x0b70**/   DWORD		Silver;    
/*0x0b74**/   DWORD		Copper;    
/*0x0b78**/   DWORD		BankPlat;    
/*0x0b7c**/   DWORD		BankGold;    
/*0x0b80**/   DWORD		BankSilver;    
/*0x0b84**/   DWORD		BankCopper;    
/*0x0b88**/   DWORD		CursorPlat; 
/*0x0b8c**/   DWORD		CursorGold; 
/*0x0b90**/   DWORD		CursorSilver; 
/*0x0b94**/   DWORD		CursorCopper;
/*0x0b98*/   BYTE		Unknown0x0b98[0x10];
/*0x0ba8**/   WORD		Skill[0x7e];  
/*0x0ca4*/   BYTE		Unknown0x0ca4[0xb0];
/*0x0d54**/   DWORD		hungerlevel; 
/*0x0d58**/   DWORD		thirstlevel;
/*0x0d5c*/   BYTE		Unknown0x0d5c[0x14];
/*0x0d70**/   WORD		zoneId;    
/*0x0d72**/   WORD		Instance;    
/*0x0d74**/   struct _SPAWNINFO*	pSpawn;      //-->d80 
/*0x0d78**/   struct _ITEMINFO*		Cursor;    
union {
/*0x0d7c**/   struct _INVENTORY		Inventory; 
/*0x0d7c**/	  struct _ITEMINFO*		InventoryArray[0x1d];    
};
/*0x0df0*/   BYTE		Unknown0x0df0[0x74];
/*0x0e64**/   WORD		CombatAbilities[0x28];
/*0x0eb4*/   BYTE		Unknown0x0eb4[0x10];
/*0x0ec4**/   DWORD		ZoneBoundId; 
/*0x0ec8*/   BYTE		Unknown0xec8[0x10];    
/*0x0ed8**/   FLOAT		ZoneBoundY;    
/*0x0edc*/   BYTE		Unknown0x0edc[0x10];    
/*0x0eec**/   FLOAT		ZoneBoundX;    
/*0x0ef0*/   BYTE		Unknown0x0ef0[0x10];    
/*0x0f00*/   FLOAT		ZoneBoundZ;    
/*0x0f04*/   BYTE		Unknown0x0f04[0x448];
/*0x134c**/   WORD		Deity; 
/*0x134e**/   WORD		GuildID;
/*0x1350*/   BYTE		Unknown0x1350[0xe];
/*0x135e**/   BYTE		Fatigue; 
/*0x135f*/   BYTE		Unknown0x135f[0x31];
/*0x1390**/   CHAR		GroupMember1[0x40];    
/*0x13d0**/   CHAR		GroupMember2[0x40]; 
/*0x1410**/   CHAR		GroupMember3[0x40]; 
/*0x1450**/   CHAR		GroupMember4[0x40]; 
/*0x1490**/   CHAR		GroupMember5[0x40];
/*0x14d0*/   BYTE		Unknown0x14d0[0xbe4];
/*0x20b4**/   struct		_ITEMINFO*   Bank[NUM_BANK_SLOTS]; 
/*0x????*/    
} CHARINFO, *PCHARINFO; 

typedef struct _MODELINFONAME {
/*0x00*/    DWORD Unknown0000;
/*0x04*/    DWORD Unknown0004;
/*0x08*/    PCHAR Name;
/*0x0c*/
} MODELINFONAME, *PMODELINFONAME;

typedef struct _MODELINFO_GENERIC {
/*0x00*/    DWORD Type;
/*0x04*/    DWORD Unknown0x04;
/*0x08*/    DWORD Unknown0x08;
/*0x0c*/    DWORD Unknown0x0c;
/*0x10*/    DWORD Unknown0x10;
/*0x14*/
} MODELINFO_GENERIC, *PMODELINFO_GENERIC;

typedef struct _MODELINFO_48 {
/*0x00*/    struct _MODELINFO_GENERIC Header;
/*0x14*/    FLOAT Float1;
/*0x18*/    FLOAT Float2;
/*0x1c*/    FLOAT Float3;
/*0x20*/    struct _MODELINFONAME *pModelName;
/*0x24*/
} MODELINFO_48, *PMODELINFO_48;

typedef struct _MODELINFO_51 {
/*0x00*/    struct _MODELINFO_GENERIC Header;
/*0x14*/    struct _MODELINFONAME *pFontName;
/*0x18*/    PCHAR LabelText;
/*0x1c*/
} MODELINFO_51, *PMODELINFO_51;

// 10/09/2003 build      plazmic
// 12/24/2003 verified   Amadeus
typedef struct _MODELINFO {
/*0x00*/    DWORD   Unknown;
/*0x04*/    PCHAR NameDAG;
/*0x08*/    struct _MODELINFO_GENERIC *pModelInfo;
/*0x0c*/    struct _MODELINFO *pNextInChain;
/*0x10*/    PVOID pUnknown;
/*0x14*/    struct _MODELINFONAME *pTrack1;
/*0x18*/    struct _MODELINFONAME *pTrack2;
   //moredata
} MODELINFO, *PMODELINFO;

// 4/30/2003 build      eqmule
typedef struct _CAMERAINFO {
/*0x00*/   DWORD Unknown0x00;
/*0x04*/   DWORD Unknown0x04;
/*0x08*/   BYTE Unknown0x08[0x8];
/*0x10*/   FLOAT Y;
/*0x14*/   FLOAT X;
/*0x18*/   FLOAT Z;
/*0x1c*/   FLOAT LightRadius;
/*0x20*/
} CAMERAINFO, *PCAMERAINFO;

// unknown size
typedef struct _ACTOREX {
/*0x00*/   BYTE Unknown0x00;
} ACTOREX, *PACTOREX;


// actual size 0xd68h  8-11-2004 
typedef struct _ACTORINFO { 
/*0x000*/ struct       _ACTOREX *pActorEx; 
/*0x004*/ DWORD        T3D_POINTLIGHT; 
/*0x008**/ CHAR         ActorDef[0x40]; 
/*0x048**/ FLOAT        Floor;            // Z coordinates for the floor where standing 
/*0x04c**/ FLOAT        Ceiling;			// Z coordinates for the ceiling where standing
/*0x050**/ DWORD        Unknown0x050; 
/*0x054**/ DWORD        Unknown0x054;//hash/checksum for EQPlayer__CheckForUnderFloor? 
/*0x058**/ DWORD        TimeStamp;      // Some kind of timestamp in microseconds. Updates as fast as my display can refresh. 
/*0x05c**/ DWORD        LastTick;      // Being set to TimeStamp on every tick? 
/*0x060*/ BYTE         Unknown0x060[0x40]; 
/*0x0a0**/ BYTE         UnderWater;      // 5 = Underwater; otherwise zero 
/*0x0a1**/ BYTE         Swimming;      // 5 = Swimming (under or on top of water); otherwise zero 
/*0x0a2**/ BYTE         FeetWet;      // 5 = Feet are in the water; otherwise zero 
/*0x0a3**/ BYTE         LeftWater;      // 5 = Just got out of water, but still very close to shore 
/*0x0a4*/ BYTE         Unknown0x0a4[0x20]; 
/*0x0c4**/ DWORD        Stunned;//EQ_Character__UnStunMe
/*0x0c8*/ BYTE         Unknown0x0c8[0x4];
/*0x0cc**/ DWORD        SpellETA;      // Calculated TimeStamp when current spell being cast will land. 0 while not casting. 
/*0x0d0*/ BYTE         Unknown0x0d0[0xa0]; 
/*0x170**/ DWORD        FishingETA;      // EQMisc__SteveGetTime
/*0x174*/ BYTE         Unknown0x174[0x8];
/*0x17c**/ VOID         *FaceRelatedActorStruct; 
/*0x180*/ BYTE         Unknown0x180[0x4];
/*0x184**/ DWORD        Animation; 
/*0x188*/ BYTE         Unknown0x188[0x3];
/*0x18b**/ BYTE         FishingEvent;   // 0=not fishing, 1=some event, 2-6=some other event
/*0x18c*/ BYTE         Unknown0x18c[0x8];
/*0x194**/ struct       _SPAWNINFO *Mount; // NULL if no mount present 
/*0x198*/ BYTE         Unknown0x198[0x2a];
/*0x1c2**/ WORD        PetID; 
/*0x1c4**/ BYTE        Unknown0x1c4[0xb8];
/*0x27c**/ WORD		   SpellID;//If spawn is casting a spell, it shows up here, otherwise 0xFFFF
/*0x27e*/ BYTE        Unknown0x27e[0xa];
/*0x288**/ struct T3D_DAG *			pActorTint;
/*0x28c*/ BYTE         Unknown0x28c[0x1ac]; 
/*0x438**/ DWORD	   LFG;
/*0x43c**/ DWORD        Trader;            //0=normal 1=trader 
/*0x440*/ BYTE         Unknown0x43c[0x789]; 
/*0xbC9*/ CHAR         NameOfLastSuccessfulTargetHit[0x40]; 
/*0xc09*/ BYTE         Unknown0xc09[0x3];
/*0xc0c*/ struct	   _MODELINFO *Model[0x11];  // 0x11 is the correct number, or are there more?
/*0xc54*/ BYTE		   Unknown0xc54[0x28];
/*0xc78*/ DWORD		   InvitedToGroup; // 1=currently invited to group
/*0xc7c*/ BYTE		   Unknown0xc7c[0x8];
/*0xc84*/ DWORD        CastingSpellID;      // -1 = not casting a spell 
/*0xc88*/ DWORD        CastingAnimation;  //unsure, FF for not casting, low numbers while casting 
/*0xc8c*/ DWORD        Unknown0x52e0[0x7]; 
/*0xca8*/ struct       _SPAWNINFO *WhoFollowing; // NULL if autofollow off 
/*0xcac*/ BYTE         Unknown0x5308[0xc]; 
/*0xcb8*/ FLOAT        CastingY; 
/*0xcbc*/ FLOAT        CastingX; 
/*0xcc0*/ BYTE         Unknown0x531c[0x10]; 
/*0xcd0*/ FLOAT        LastPacketZ; 
/*0xcd4*/ FLOAT        LastPacketY; 
/*0xcd8*/ FLOAT        LastPacketSpeedY; 
/*0xcdc*/ FLOAT        LastPacketX; 
/*0xce0*/ FLOAT        LastPacketSpeedZ; 
/*0xce4*/ FLOAT        LastPacketSpeedX; 
/*0xce8*/ DWORD        LastPacketHeadingTurning; 
/*0xcec*/ BYTE         Unknown0x5348[0x2c]; 
/*0xd1c*/ BYTE         Unknown0x5378[0x4c]; 
/*0xd68*/ 
} ACTORINFO, *PACTORINFO; 

typedef struct _ACTORINFOOLD { 
/*0x000*/ struct       _ACTOREX *pActorEx; 
/*0x004*/ DWORD        T3D_POINTLIGHT; 
/*0x008*/ CHAR         ActorDef[0x40]; 
/*0x048*/ FLOAT        Z;            // Z coordinates for the floor where standing 
/*0x04c*/ BYTE         Unknown0x04c[0x4]; 
/*0x050*/ DWORD        TimeStamp;      // Some kind of timestamp in microseconds. Updates as fast as my display can refresh. 
/*0x054*/ DWORD        Unknown0x054;   // Being set to TimeStamp about once per second 
/*0x058*/ DWORD        LastTick;      // Being set to TimeStamp on every tick? 
/*0x05c*/ DWORD        Unknown0x05c;   // Being set to TimeStamp at unknown intervals 
/*0x060*/ BYTE         Unknown0x060[0x14]; 
/*0x074*/ DWORD        Unknown0x074;   // Being set to TimeStamp at unknown intervals 
/*0x078*/ DWORD        Unknown0x078;   // Being set to TimeStamp at unknown intervals 
/*0x07c*/ BYTE         Unknown0x07c[0x20]; 
/*0x09c*/ DWORD        UnderWaterMirror; //copy of UnderWater 
/*0x0a0*/ DWORD        SwimmingMirror; //copy of Swimming 
/*0x0a4*/ DWORD        FeetWetMirror;   //copy of FeetWet 
/*0x0a8*/ BYTE         UnderWater;      // 5 = Underwater; otherwise zero 
/*0x0a9*/ BYTE         Swimming;      // 5 = Swimming (under or on top of water); otherwise zero 
/*0x0aa*/ BYTE         FeetWet;      // 5 = Feet are in the water; otherwise zero 
/*0x0ab*/ BYTE         LeftWater;      // 5 = Just got out of water, but still very close to shore 
/*0x0ac*/ BYTE         Unknown0x0ac[0x28]; 
/*0x0d4*/ DWORD        SpellETA;      // Calculated TimeStamp when current spell being cast will land. 0 while not casting. 
/*0x0d8*/ BYTE         Unknown0x0d8[0x40]; 
/*0x118*/ DWORD        FishingETA;      // EQMisc__SteveGetTime 
/*0x11c*/ BYTE         Unknown0x11c[0x8]; 
/*0x124*/ VOID         *FaceRelatedActorStruct; 
/*0x128*/ DWORD        Unknown0x0128;
/*0x12c*/ DWORD        Animation; 
/*0x130*/ DWORD        Unknown0x130; 
/*0x134*/ BYTE         Unknown0x134[0x12]; 
/*0x146*/ BYTE         FishingEvent;   // 0=not fishing, 1=some event, 2-6=some other event 
/*0x147*/ BYTE         Unknown0x147[0x9]; 
/*0x150*/ struct       _SPAWNINFO *Mount; // NULL if no mount present 
/*0x154*/ BYTE         Unknown0x0154[0xc]; 
/*0x160*/ DWORD        PetID; 
/*0x164*/ struct       _SPAWNINFO *pGroupAssistNPC[1];
/*0x168*/ struct       _SPAWNINFO *pRaidAssistNPC[3]; 
/*0x174*/ struct       _SPAWNINFO *pGroupMarkNPC[3]; 
/*0x180*/ struct       _SPAWNINFO *pRaidMarkNPC[3]; 
/*0x18C*/ struct       _SPAWNINFO *pTargetOfTarget; 
/*0x190*/ BYTE         Unknown0x190[0xf8]; 
/*0x288*/ struct T3D_DAG *			pActorTint;
/*0x28c*/ BYTE         Unknown0x28c[0x93d]; 
/*0xbC9*/ CHAR         NameOfLastSuccessfulTargetHit[0x40]; 
/*0xc09*/ BYTE         Unknown0xc09[0x3];
/*0xc0c*/ struct	   _MODELINFO *Model[0x11];  // 0x11 is the correct number, or are there more?
/*0xc54*/ BYTE		   Unknown0xc54[0x28];
/*0xc78*/ DWORD		   InvitedToGroup; // 1=currently invited to group
/*0xc7c*/ BYTE		   Unknown0xc7c[0x8];
/*0xc84*/ DWORD        CastingSpellID;      // -1 = not casting a spell 
/*0xc88*/ DWORD        CastingAnimation;  //unsure, FF for not casting, low numbers while casting 
/*0xc8c*/ DWORD        Unknown0x52e0[0x7]; 
/*0xca8*/ struct       _SPAWNINFO *WhoFollowing; // NULL if autofollow off 
/*0xcac*/ BYTE         Unknown0x5308[0xc]; 
/*0xcb8*/ FLOAT        CastingY; 
/*0xcbc*/ FLOAT        CastingX; 
/*0xcc0*/ BYTE         Unknown0x531c[0x10]; 
/*0xcd0*/ FLOAT        LastPacketZ; 
/*0xcd4*/ FLOAT        LastPacketY; 
/*0xcd8*/ FLOAT        LastPacketSpeedY; 
/*0xcdc*/ FLOAT        LastPacketX; 
/*0xce0*/ FLOAT        LastPacketSpeedZ; 
/*0xce4*/ FLOAT        LastPacketSpeedX; 
/*0xce8*/ DWORD        LastPacketHeadingTurning; 
/*0xcec*/ BYTE         Unknown0x5348[0x2c]; 
/*0xd18*/ DWORD        Trader;            //0=normal 1=trader 
/*0xd1c*/ BYTE         Unknown0x5378[0x4c]; 
/*0xd68*/ 
} ACTORINFOOLD, *PACTORINFOOLD; 

#define MODEL_LABEL         0 
#define MODEL_LABELINFO     1
#define MODEL_NULL2         2
#define MODEL_HELD_R        3
#define MODEL_HELD_L        4
#define MODEL_SHIELD        5
#define MODEL_NULL6         6

/*
//Work in progress...
#define MODEL_HEAD			0x00
#define MODEL_HEAD_POINT	0x01
#define MODEL_NULL_1		0x02
#define MODEL_HELD_R		0x03
#define MODEL_HELD_L		0x04
#define MODEL_SHIELD		0x05
#define MODEL_NULL_2		0x06
#define MODEL_TUNIC			0x07
#define MODEL_HAIR			0x08
#define MODEL_BEARD			0x09
#define MODEL_CHEST			0x0a
#define MODEL_GLOVES		0x0b
#define MODEL_GLOVES2		0b0c
*/

typedef struct _ARGBCOLOR {
    union {
        struct {
            BYTE B;
            BYTE G;
            BYTE R;
            BYTE A;
        };
        DWORD ARGB;
    };
} ARGBCOLOR, *PARGBCOLOR;

// 10-22-2003 Lax
typedef struct _EQUIPMENT {
   union {
      struct// EQUIPARRAY
      {
         DWORD Item[9];
      };// Array;
      struct //EQUIPUNIQUE
      {
         DWORD Head;
         DWORD Chest;
         DWORD Arms;
         DWORD Wrists;
         DWORD Hands;
         DWORD Legs;
         DWORD Feet;
         DWORD Primary;
         DWORD Offhand;
      };// Unique;
   };
} EQUIPMENT, *PEQUIPMENT;

// sizeof(_SPAWNINFO) is 0x290 (7/14/2004) 
typedef struct _SPAWNINFOOLD { 
/*0x000*/   BYTE	Unknown0x0; 
/*0x001*/   CHAR	Lastname[0x40];  // // Surname on PCs, Newbie Tag on NPCs 
/*0x041*/   BYTE	Unknown0x41[0x3]; 
/*0x044*/   BYTE	Unknown0x44[0x4]; 
/*0x048*/   FLOAT   Y; /*0x028*/
/*0x04c*/   FLOAT   X; /*0x02c*/
/*0x050*/   FLOAT   Z; /*0x030*/
/*0x054*/   FLOAT   SpeedY; /*0x034*/
/*0x058*/   FLOAT   SpeedX; /*0x038*/
/*0x05C*/   FLOAT   SpeedZ; /*0x03C*/
/*0x060*/   FLOAT   SpeedRun; /*0x040*/
/*0x064*/   FLOAT   Heading; /*0x044*/
/*0x068*/   FLOAT   field_48; /*0x048*/
/*0x06c*/   DWORD   field_4C; /*0x04c*/
/*0x070*/   DWORD   field_50; /*0x050*/
/*0x074*/   FLOAT   CameraAngle; /*0x054*/
/*0x078**/   struct  _SPAWNINFO *pNext; /*0x1c4*/
/*0x07c**/   struct  _SPAWNINFO *pPrev; /*0x1d0*/
/*0x080*/   BYTE    Unknown0x80[0x4];
/*0x084*/   struct  _ACTORINFO   *pActorInfo; /*0x164*/ 
/*0x088*/   struct  _CHARINFO  *pCharInfo; /*0x1c8*/
/*0x08c*/   BYTE    Unknown0x8c[0x54];
/*0x0e0*/   CHAR    Name[0x40]; /*0x0e0*/ // ie priest_of_discord00 
/*0x120*/   CHAR    DisplayedName[0x40]; /*0x120*/// ie Priest of Discord 
/*0x160*/   FLOAT   SpeedHeading;  /*0x160*/
/*0x168*/   DWORD   field_168; /*0x168*/
/*0x16c*/   BYTE    CanFindLocation; /*0x16c*/
/*0x16d*/   BYTE    Sneak;  /*0x16d*/// returns 01 on both Sneak and Shroud of Stealth 
/*0x16e*/   BYTE    Linkdead; /*0x16e*/ // Uncharmable flag when used on mobs? 
/*0x16f*/   BYTE    field_16F; /*0x16f*/
/*0x170*/   BYTE    LFG; /*0x170*/
/*0x171*/   BYTE    field_171; /*0x171*/
/*0x172*/   BYTE	IsABoat; /*0x172*/// 1 = a type of boat 
/*0x173*/   BYTE    Unknown0x173; /*0x173*/
/*0x174*/   ARGBCOLOR ArmorColor[0x9];/*0x174*/  // Armor Dye if custom, otherwise Item Tint 
/*0x178*/   struct  _EQUIPMENT Equipment; /*0x198*/
/*0x1bc*/   WORD    Zone; /*0x1bc*/
/*0x1be*/   WORD    Instance; /*0x1be*/
/*0x1c0*/   DWORD   field_1c0; /*0x1c0*/
/*0x1cc*/   DWORD   field_1cC; /*0x1cc*/
/*0x1d4*/   BYTE    Unknown0x1d4[0x4]; /*0x1d4*/
/*0x1d8*/   FLOAT   field_1d8; /*0x1d8*/
/*0x1dc*/   DWORD   field_1dC; /*0x1dc*/
/*0x1e0*/   FLOAT   RunSpeed; /*0x1e0*/
/*0x1e4*/   FLOAT   field_1e4; 
/*0x1e8*/   FLOAT   field_1e8; 
/*0x1ec*/   FLOAT   AvatarHeight;  // height of avatar from ground when standing 
/*0x1f0*/   FLOAT   WalkSpeed; 
/*0x1f4*/   BYTE    Type; 
/*0x1f5*/   BYTE    HairColor;      
/*0x1f6*/   BYTE	BeardColor; 
/*0x1f7*/   BYTE	Field_1f7; 
/*0x1f8*/   BYTE    Eyes; 
/*0x1f9*/   BYTE    Eyes2;     
/*0x1fa*/   BYTE    BeardType; 
/*0x1fb*/   BYTE    Holding;   // 0=holding/wielding nothing 
/*0x1fc*/   BYTE    Level; 
/*0x1fd*/   BYTE    FaceHair;  // Face/Hair combination with headgear 
/*0x1fe*/   BYTE    Gender; 
/*0x1ff*/   BYTE    PvPFlag; 
/*0x200*/   BYTE    HideMode; 
/*0x201*/   BYTE    StandState; 
/*0x202*/   BYTE    Class; 
/*0x203*/   BYTE    Light; 
/*0x204*/   BYTE    InNonPCRaceIllusion;  // This is buggy ...not sure exact usage 
/*0x205*/   BYTE    Field_205;  // form related, unsure how 
/*0x206*/   BYTE    GM; 
/*0x207*/   BYTE    Field_207; 
/*0x208*/   DWORD   SpawnID; 
/*0x20c*/   DWORD   MasterID; 
/*0x210*/   DWORD   Race; 
/*0x214*/   DWORD   Anon; 
/*0x218*/   DWORD    field_218; 
/*0x21c*/   DWORD    AFK; 
/*0x220*/   DWORD   BodyType; 
/*0x224*/   DWORD   HPCurrent; 
/*0x228*/   BYTE   AARank; 
/*0x229*/   BYTE    Unknown0x229[0x3]; 
/*0x22c*/   DWORD   GuildStatus; 
/*0x230*/   DWORD   Deity; 
/*0x234*/   DWORD   HPMax; 
/*0x238*/   DWORD   GuildID; 
/*0x23c*/   BYTE    Levitate;   //0-normal state  2=levitating 3=mob (not levitating) 
/*0x23d*/   BYTE    Unknown0x23d[0xb]; 
/*0x240*/   BYTE     Unknown0x240[0x4]; 
/*0x244*/   DWORD    field_244; 
/*0x248*/   BYTE     Unknown0x248[0x47]; 
/*0x28f*/   BYTE     field_28F; 
/*0x290*/ 
} SPAWNINFOOLD, *PSPAWNINFOOLD; 

//for eqmac dec 2002 version
typedef struct _SPAWNINFO {
/*0x000*/	BYTE Unknown0x000;      // 3?
/*0x001*/	union {
	CHAR Name[0x40];
	CHAR DisplayedName[0x40];//ugly but at least plugins work...
};
/*0x041*/	BYTE Unknown0x041[0x3];
/*0x044*/	DWORD Zone;
/*0x048*/	FLOAT Y;
/*0x04c*/	FLOAT X;
/*0x050*/	FLOAT Z;
/*0x054*/	FLOAT Heading;
/*0x058*/	FLOAT Unknown0058;
/*0x05c*/	FLOAT SpeedRun;
/*0x060*/	FLOAT SpeedY;
/*0x064*/	FLOAT SpeedX;
/*0x068*/	FLOAT SpeedZ;
/*0x06c*/	FLOAT SpeedHeading;
/*0x070*/	FLOAT AvatarHeight;/***********/
/*0x074*/	FLOAT CameraAngle; // 128=up -128=down
/*0x078*/	struct _SPAWNINFO *pNext;
/*0x07c*/	struct _SPAWNINFO *pPrev;
/*0x080*/	PVOID pUnknown0x080;    // Unknown... pointer? always 0000000
/*0x084*/	PACTORINFO pActorInfo;
/*0x088*/	PCHARINFO pCharInfo;
/*0x08c*/	FLOAT CameraHeightOffset;
/*0x090*/	FLOAT ModelHeightOffset;
/*0x094*/	WORD SpawnID;
/*0x096*/	WORD MasterID;
/*0x098*/	DWORD HPMax;
/*0x09c*/	DWORD HPCurrent;
/*0x0a0*/	WORD GuildID;
/*0x0a2*/	BYTE Unknown0x0a2[6];
/*0x0a8*/	BYTE Type;
/*0x0a9*/	BYTE Class;
/*0x0aa*/	WORD Race;
/*0x0ac*/	BYTE Gender;
/*0x0ad*/	BYTE Level;
/*0x0ae*/	BYTE HideMode;
/*0x0af***/	BYTE Sneak;
/*0x0b0*/	BYTE Charmed;
/*0x0b1**/	BYTE StandState;
/*0x0b2*/	BYTE Levitate;
/*0x0b3**/	BYTE Light;
/*0x0b4*/	BYTE Unknown0x0b4[0xe];
/*0x0c2**/	WORD Primary;
/*0x0c4**/	WORD Secondary;
/*0x0c6*/	BYTE Unknown0x0c6[0x2a];
/*0x0f0*/	FLOAT Unknown0x0f0;//used in map functions is it height?
/*0x0f4*/	BYTE Unknown0x0f4[0xc];
/*0x100*/	FLOAT SpeedMultiplier;//prolly wrong... eqmule
/*0x104*/	FLOAT RunSpeed;
/*0x108**/	BYTE Linkdead;
/*0x109**/	BYTE GM;
/*0x10a*/	BYTE Guide;
/*0x10b*/	BYTE VisType;
/*0x10c**/  DWORD BodyType;
/*0x110**/  BYTE Unknown0x110[0x3];
/*0x113**/	BYTE Anon;
/*0x114**/	BYTE Role;
/*0x115**/  BYTE Unknown0x115[0x7];
/*0x11c**/	BYTE AFK;
/*0x11d**/  BYTE Unknown0x11d[0x7];
/*0x124**/	WORD AARank;
/*0x126**/  BYTE Unknown0x126[0x6];
/*0x12c*/	CHAR Lastname[0x22];
/*0x14e*/	WORD Deity;
/*0x150**/	BYTE Holding;
/*0x151*/	BYTE Unknown0x151[0x2f7];
/*0x448*/   struct  _EQUIPMENT Equipment; /*0x198*/
} SPAWNINFO, *PSPAWNINFO;


#define STANDSTATE_STAND            0x64
#define STANDSTATE_CASTING          0x66
#define STANDSTATE_BIND             0x69
#define STANDSTATE_SIT              0x6E
#define STANDSTATE_DUCK             0x6F
#define STANDSTATE_FEIGN            0x73
#define STANDSTATE_DEAD             0x78

#define MONITOR_SPAWN_X             1
#define MONITOR_SPAWN_Y             2
#define MONITOR_SPAWN_Z             4
#define MONITOR_SPAWN_HEADING       8
#define MONITOR_SPAWN_SPEEDRUN      16
#define MONITOR_SPAWN_HPCURRENT     32

typedef struct _SPAWNMONITORINFO {
    WORD SpawnID;
    FLOAT Y;
    FLOAT X;
    FLOAT Z;
    FLOAT Heading;
    FLOAT SpeedRun;
    DWORD HPCurrent;
    DWORD MonitorMask;
} SPAWNMONITORINFO, *PSPAWNMONITORINFO;

typedef struct _EQSWITCH {
/*0x00*/	DWORD		Value0x00;
/*0x04*/	DWORD		switchID;
/*0x08*/	PVOID		pUnknown0x08;
/*0x0C*/	DWORD		Value0x0C;
/*0x10*/	FLOAT		Y;
/*0x14*/	FLOAT		X;
/*0x18*/	FLOAT		Z;
/*0x1C*/	FLOAT		Heading;
/*0x20*/	DWORD		Unknown0x20;
/*0x24*/	DWORD		Unknown0x24;
/*0x28*/	DWORD		Value0x28;
/*0x2C*/	PVOID		pUnknown0x2C;
/*0x30*/	DWORD		Unknown0x30;
/*0x34*/	FLOAT		Value0x34;
/*0x38*/	FLOAT		Value0x38;
/*0x3C*/	DWORD		Unknown0x3C;
/*0x40*/	PVOID		pUnknown0x40;
/*0x44*/	PVOID		pUnknown0x44;
/*0x48*/	DWORD		Value0x48;
/*0x4C*/	DWORD		Value0x4C;
/*0x50*/	PVOID		pUnknown0x50;
/*0x54*/	DWORD		Unknown0x54;
/*0x58*/	DWORD		Unknown0x58;
/*0x5C*/	DWORD		Unknown0x5C;
/*0x60*/	DWORD		Value0x60;
/*0x64*/	PVOID		pUnknown0x64;
} EQSWITCH, *PEQSWITCH;

typedef struct _DOOR {
/*0x00*/   DWORD type;//not sure but its not ID cause they are all the same
/*0x04*/   struct _DOOR *pPrev;
/*0x08*/   struct _DOOR *pNext;
/*0x0c*/   BYTE ID;
/*0x0d*/   CHAR Name[0x0b];
/*0x18*/   DWORD Unknown0x018;
/*0x1c*/   DWORD Unknown0x01c;
/*0x20*/   FLOAT DefaultY;
/*0x24*/   FLOAT DefaultX;
/*0x28*/   FLOAT DefaultZ;
/*0x2c*/   FLOAT DefaultHeading;
/*0x30*/   FLOAT DoorAngle;
/*0x34*/   FLOAT Y;
/*0x38*/   FLOAT X;
/*0x3c*/   FLOAT Z;
/*0x40*/   FLOAT Heading;
/*0x44*/   DWORD Unknown0x44;
/*0x48*/   DWORD Unknown0x48;
/*0x4c*/   DWORD Unknown0x4c;//3
/*0x50*/   DWORD Unknown0x50;//0
/*0x54*/   DWORD Unknown0x54;//0xFFFFFFFF
/*0x58*/   DWORD Unknown0x58;//0
/*0x5c*/   WORD Unknown0x5c;//0
/*0x5e*/   WORD Unknown0x5e;//0xffffffff
/*0x60*/   BYTE Unknown0x60[0x4];
/*0x64*/   BYTE Clickable;//just a guess
/*0x65*/   DWORD Unknown0x65[0xb];
/*0x70*/   PVOID CXMLData__vfTable;//well it isnt always but i have seen it at this address... /eqmule
/*0x74*/   DWORD Unknown0x74;//0
/*0x78*/   DWORD Unknown0x78;//type? 2
/*0x7c*/   DWORD Unknown0x7c;//0
/*0x80*/   PEQSWITCH pSwitch; // (class EQSwitch *)
/*0x84*/   BYTE Unknown0x84[0x8];
/*0x8c*/   DWORD Unknown0x8c;
/*0x90*/   DWORD Unknown0x90;
/*0x94*/   WORD Unknown0x94;//type? 1f
/*0x96*/   WORD Unknown0x96;//type? 880
/*0x98*/
} DOOR, *PDOOR;
#define MAX_DOORS 0xFF
// eqmac dec 2002 version
typedef struct _DOORTABLE {
/*0x000*/   DOOR Doors[MAX_DOORS];
} DOORTABLE, *PDOORTABLE;

// actual size 0xe8 eqmac dec 2002
typedef struct _GROUNDITEM {
/*0x00*/ struct _GROUNDITEM *pPrev;
/*0x04*/ struct _GROUNDITEM *pNext;
/*0x08*/ DWORD ID;
/*0x0C*/ DWORD DropID;
/*0x10*/ DWORD ZoneID;
/*0x14*/ PEQSWITCH pSwitch; // (class EQSwitch *)
/*0x18*/ BYTE Unknown0x18[0x74];
/*0x8C*/ FLOAT Heading;
/*0x90*/ FLOAT Z;
/*0x94*/ FLOAT X;
/*0x98*/ FLOAT Y;
/*0x9C*/ CHAR Name[0x1e];
/*0xba*/ BYTE Unknown0xba[0x2e];
/*0xe8*/
} GROUNDITEM, *PGROUNDITEM;

#define   MAX_ZONES                                    0x151   
extern    PCHAR szZoneExpansionName[];     //defined in LibEQ_Utilities.cpp

typedef struct _ZONELIST { 
/*0x000*/   DWORD   Header; 
/*0x004*/   DWORD   Expansion;          // szZoneExpansionName[] 
/*0x008*/   WORD    Id; 
/*0x00a*/   WORD    Instance; 
/*0x00c*/   CHAR    ShortName[0x81]; 
/*0x08d*/   CHAR    LongName[0x103]; 
/*0x190*/   DWORD   Flags;              // (Flags & 0x100000) = HasMinLevel, 0x4000 no air, 0x2 newbie zone, 0x20 no bind, 0x400000 something 
/*0x194*/   DWORD   Id2;                // This is Id+2242 
/*0x198*/   DWORD   PoPValue;           // This has something to do with PoP zones. 
/*0x19c*/   DWORD   MinLevel;           // Minimum level to access 
/*0x1a0*/   WORD    Unknown0x1a0;          
/*0x1a2*/   BYTE    Unknown0x1a2[0x6];    
/*0x1a8*/   DWORD   Unknown0x1a8; 
/*0x1ac*/   DWORD   Unknown0x1ac; 
/*0x1b0      next zone in list*/ 
} ZONELIST, *PZONELIST;

typedef struct _WORLDDATA {
/*0x000*/ PVOID lpvTable;
/*0x004*/ BYTE Hour;
/*0x005*/ BYTE Minute;
/*0x006*/ BYTE Day;
/*0x007*/ BYTE Month;
/*0x008*/ DWORD Year;
/*0x00C*/ BYTE Unknown0x00c[0x10];
/*0x01C*/ PZONELIST ZoneArray[MAX_ZONES];
} WORLDDATA, *PWORLDDATA;

// 5-15-2003    Amadeus (discovered by Lax)
// Actual Size 0x240, old
//hmm i think this is 0x1a0 for eqmac but we start at the wrong offset.../ eqmule
typedef struct _ZONEINFO {
/*0x000*/   CHAR    CharacterName[0x40];
/*0x040*/   CHAR    ShortName[0x20];
/*0x060*/   CHAR    LongName[0x80];
/*0x0E0*/   CHAR    Unknown0x0e0[0x96];  // <-- this isnt part of zone name, see CEverQuest__CEverQuest
/*0x176*/   BYTE    ZoneType; // (usually FF)
/*0x177*/	ARGBCOLOR FogRed;
/*0x17b*/	ARGBCOLOR FogGreen;
/*0x17f*/	ARGBCOLOR FogBlue;
/*0x183*/   BYTE    Unknown0x183;
/*0x184*/   BYTE	Unknown0x184[0x10];
/*0x194*/   BYTE    Unknown0x194[0x10];
/*0x1a4*/   FLOAT   ZoneGravity;
/*0x1a8*/   BYTE    Unknown0x1a8;
/*0x1a9*/   BYTE    Unknown0x1a9[0x3];
/*0x1ac*/   BYTE    Unknown0x1ac[0x2e];
/*0x1da*/	BYTE	SkyType;	
/*0x1db*/	BYTE	Unknown0x1db[0x9];
/*0x1e4*/   FLOAT   ZoneExpModifier;    //This works for eqmac
/*0x1e8*/   FLOAT   Unknown0x1e8[3];
/*0x1f4*/   FLOAT   Ceiling;
/*0x1f8*/   FLOAT   Floor; 
/*0x1fc*/   FLOAT   MinClip; 
/*0x200*/   FLOAT   MaxClip; 
/*0x204*/
} ZONEINFO, *PZONEINFO;
//as of eqmac version dec 2002
#define   TOTAL_SPELL_COUNT         0xFA0       // (4000) # of spells in game
// note: fuck using TOTAL_SPELL_COUNT in the struct, but keep it for users to use
// because they cant figure out how to use pSpellMgr->InvalidSpell
typedef struct _SPELLMGR {
            struct  _SPELL*     Spells[TOTAL_SPELL_COUNT];
//            struct  _SPELL*     Spells2[TOTAL_SPELL_COUNT];
//			struct _SPELL*		InvalidSpell;
} SPELLMGR, *PSPELLMGR;

// Size is 0x224 as of 8.11.2004
typedef struct _SPELLOLD { 
/*0x000*/   DWORD   ID; 
/*0x004*/   FLOAT   Range; 
/*0x008*/   FLOAT   AERange; 
/*0x00c*/	FLOAT	PushBack;
/*0x010*/   BYTE    Unknown0x00c[0x04];  
/*0x014*/   DWORD   CastTime; 
/*0x018*/   DWORD   FizzleTime; 
/*0x01c*/   DWORD   RecastTime; 
/*0x020*/   DWORD   DurationType;       //DurationFormula on Lucy 
/*0x024*/   DWORD   DurationValue1; 
/*0x028*/   DWORD   Unknown0x028; 
/*0x02c*/   DWORD   Mana; 
/*0x030*/   LONG    Base[0x0c];         //Base1-Base12 
/*0x060*/   LONG    Base2[0x0c];     //Mostly unused, setting name to Base2 from Lucy for now 
/*0x090*/   LONG    Max[0x0c];          //Max1-Max12 
/*0x0c0*/   DWORD   BookIcon; 
/*0x0c4*/   DWORD   GemIcon; 
/*0x0c8*/   DWORD   ReagentId[0x4];     //ReagentId1-ReagentId4 
/*0x0d8*/   DWORD   ReagentCount[0x4];  //ReagentCount1-ReagentCount4 
/*0x0e8*/   BYTE	Unknown0x0e8[0x10]; 
/*0x0f8*/   BYTE	Calc[0x0c];         //Calc1-Calc12 
/*0x104*/   BYTE	LightType; 
/*0x105*/   BYTE	SpellType;          //0=detrimental, 1=Beneficial, 2=Beneficial, Group Only
/*0x106*/   BYTE	Unknown0x106; 
/*0x107*/   BYTE    Resist;             //0=un 1=mr 2=fr 3=cr 4=pr 5=dr 6=chromatic
/*0x108*/   DWORD	Attrib[0x0c];       //Attrib1-Attrib12 
/*0x138*/   BYTE    TargetType;         // 03=Group v1, 04=PB AE, 05=Single, 06=Self, 08=Targeted AE, 0e=Pet, 28=AE PC v2, 29=Group v2
/*0x139*/   BYTE	FizzleAdj; 
/*0x13a*/   BYTE	Skill; 
/*0x13b*/   BYTE    Location;            // 01=Outdoors, 02=dungeons, ff=Any 
/*0x13c*/   BYTE	Environment;
/*0x13d*/   BYTE	TimeOfDay;		     // 0=any, 1=day only, 2=night only
/*0x13e*/	BYTE	Unknown0x13e;
/*0x13f*/   BYTE    Level[0x10];         // per class. 
/*0x14f*/   BYTE    Unknown0x14f[0x12]; 
/*0x161*/   BYTE    CastingAnim;		
/*0x162*/	BYTE	Unknown0x162[0x6];
/*0x168*/   DWORD   descnum; 
/*0x16c*/   BYTE    Uninterruptable;  // 00=Interruptable, 01=Uninterruptable 
/*0x16d*/	BYTE	Unknown0x16d;
/*0x16e*/	BYTE	Deletable;
/*0x16f*/   BYTE    Unknown0x16f;	
/*0x170*/   DWORD   Autocast;  // SpellID of spell to instacast on caster when current spell lands on target 
/*0x174*/	BYTE	Unknown0x174[0x06];
/*0x17a*/   BYTE    DurationWindow; // 0=Long, 1=Short
/*0x17b*/   BYTE    Unknown0x17b;
/*0x17c*/   DWORD   Unknown144;  // Unknown144 from lucy 
/*0x180*/   DWORD   Unknown145;  // Unknown145 from lucy 
/*0x184*/   DWORD   Unknown0x184; 
/*0x188*/   BYTE    Unknown0x188;
/*0x189*/	BYTE	Unknown0x189;  //data here on detrimental spells
/*0x18a*/	BYTE	Unknown0x18a;  //data here on detrimental spells 
/*0x18b*/	BYTE	Unknown0x18b[0x51];
/*0x1dc*/   CHAR	*Name;
/*0x1e0*/   CHAR	*Target; 
/*0x1e4*/   CHAR	*Extra;			// This is 'Extra' from Lucy (portal shortnames etc)
/*0x1e8*/   CHAR	*Unknown0x1e8; 
/*0x1ec*/   CHAR	*Unknown0x1ec;      
/*0x1f0*/   CHAR	*CastOnYou; 
/*0x1f4*/   CHAR	*CastOnAnother; 
/*0x1f8*/   CHAR	*WearOff; 
/*0x1fc*/   CHAR	*Unknown0x1fc;  
/*0x200*/   DWORD   spaindex; 
/*0x204*/   CHAR	*Unknown0x204;      
/*0x208*/   DWORD   SpellAnim; 
/*0x20c*/   DWORD   Unknown0x20c; 
/*0x210*/   DWORD   Unknown130;    // This is Unknown130 from Lucy 
/*0x214*/   DWORD   Unknown0x214; 
/*0x218*/   DWORD   SpellIcon; 
/*0x21c*/	DWORD	ResistAdj;
/*0x220*/
} SPELLOLD, *PSPELLOLD;

typedef struct _SPELL { 
/*0x000*/   DWORD   ID; 
/*0x004*/   FLOAT   Range; 
/*0x008*/   FLOAT   AERange; 
/*0x00c*/	FLOAT	PushBack;
/*0x010*/   BYTE    Unknown0x00c[0x04];  
/*0x014*/   DWORD   CastTime; 
/*0x018*/   DWORD   FizzleTime; 
/*0x01c*/   DWORD   RecastTime; 
/*0x020*/   DWORD   DurationType;       //DurationFormula on Lucy 
/*0x024*/   DWORD   DurationValue1; 
/*0x028*/   BYTE   Unknown0x028[0x4];
/*0x02c**/  WORD	Mana;

/*0x02e*/   short    Base[0x0c];  //has to be signed for  ShowSpellSlotInfo to work      //Base1-Base12 
/*0x046**/   short    Max[0x0c];  //has to be signed for  ShowSpellSlotInfo to work        //Max1-Max12 

/*0x05e**/  WORD   BookIcon; 
/*0x060**/  WORD   GemIcon;

/*0x062**/   WORD   ReagentId[0x4];     //ReagentId1-ReagentId4 
/*0x06a**/   WORD   ReagentCount[0x4];  //ReagentCount1-ReagentCount4 
/*0x072*/   BYTE	Unknown0x072[0x8];
/*0x07a**/   BYTE	Calc[0x0c];         //Calc1-Calc12 
/*0x086*/   BYTE	LightType; 
/*0x087*/   BYTE	SpellType;          //0=detrimental, 1=Beneficial, 2=Beneficial, Group Only
/*0x088*/   BYTE	Unknown0x088;
/*0x089**/	BYTE	Resist; //0=un 1=mr 2=fr 3=cr 4=pr 5=dr 6=chromatic
/*0x08a**/	BYTE   Attrib[0xc]; 
/*0x096**/   BYTE    TargetType;         // 03=Group v1, 04=PB AE, 05=Single, 06=Self, 08=Targeted AE, 0e=Pet, 28=AE PC v2, 29=Group v2
/*0x097**/   BYTE	FizzleAdj; 
/*0x098**/   BYTE	Skill; 
/*0x099*/   BYTE    Location;            // 01=Outdoors, 02=dungeons, ff=Any 
/*0x09a*/   BYTE	Environment;
/*0x09b*/   BYTE	TimeOfDay;		     // 0=any, 1=day only, 2=night only
/*0x09c*/	BYTE	Unknown0x13e;
/*0x09d**/   BYTE    Level[0xf];         // per class. 
/*0x0a7*/   BYTE    Unknown0x14f[0x10]; 
/*0x0bc**/   BYTE    CastingAnim;		
/*0x0bd*/	BYTE	Unknown0x0bd[0x13];
/*0x0d0**/   CHAR	*Name;
/*0x0d4**/   CHAR	*Target; 
/*0x0d8**/   CHAR	*Extra;			// This is 'Extra' from Lucy (portal shortnames etc)
/*0x0dc**/   CHAR	*Unknown0x0dc; 
/*0x0e0**/   CHAR	*Unknown0x0e0;      
/*0x0e4**/   CHAR	*CastOnYou; 
/*0x0e8**/   CHAR	*CastOnAnother; 
/*0x0ec**/   CHAR	*WearOff; 
/*0x0f0*/   BYTE	Unknown0x0f0[0x1c]; 
/*0x10c**/   BYTE	ResistAdj; 
/*0x10d*/   BYTE	Unknown0x10d[0xb]; 
/*0x114*/
} SPELL, *PSPELL;
// Size 0x180 4-23-2004 Lax
typedef struct _SKILL {
/*0x000*/   DWORD nName;
/*0x004*/   DWORD ReuseTimer;
/*0x008*/   CHAR  Unknown0x008;
/*0x009*/   CHAR  Unknown0x009;
/*0x00A*/   CHAR  AltTimer;//compare to 2 all over.. alternate timer?
/*0x00B*/   CHAR  Unknown0x00B;
/*0x00C*/   CHAR  Unknown0x00C;
/*0x00D*/   CHAR  MinLevel[0x22];
/*0x02F*/   CHAR  Unused0x02F;
/*0x030*/   CHAR  StartingSkill[0x22];
/*0x052*/   CHAR  Unknown0x052[0x6];
/*0x058*/   DWORD SkillCapsPre50[0x22];
/*0x0E0*/   DWORD Unknown0x0E0;// 1 for backstab..
/*0x0E4*/   DWORD Unknown0x0E4;// 
/*0x0E8*/   DWORD Unknown0x0E8;
/*0x0EC*/   FLOAT Accuracy;
/*0x0F0*/   DWORD Unknown0x0F0;
/*0x0F4*/   DWORD SkillCapsPost50[0x22];
/*0x17C*/   DWORD Unknown0x17C;
/*0x180*/
} SKILL, *PSKILL;

#define MAX_GUILDS			0x200
//size 0x60 eqmac dec 2002 version

typedef struct _GUILDS {
/*0x00*/ CHAR		GuildName[MAX_GUILDS][0x60];//yes i know its not 0x60 bytes but its null terminated so what does it matter... the struct IS 0x60 bytes...
/*0x60*/
} GUILDS, *PGUILDS;

//eqmac dec 2002
#define EQ_INTERACTGROUNDITEM 0x402B
typedef struct _INTERACTGROUNDITEM {
	DWORD DropID;
	DWORD SpawnID;
} INTERACTGROUNDITEM, *PINTERACTGROUNDITEM;

typedef struct _SPELLFAVORITE {
/*0x000*/   DWORD   SpellId[8];
/*0x020*/   CHAR    Name[25];
/*0x039*/   BYTE    Byte_39;
/*0x03A*/   BYTE    Byte_3A;
/*0x03B*/   BYTE    Byte_3B;
/*0x03C*/
} SPELLFAVORITE, *PSPELLFAVORITE;

//eqmac version may 25 2013
typedef struct _CMDLIST {
    DWORD LocalizedStringID;
    PCHAR szName;
    PCHAR szLocalized;
    VOID  (__cdecl *fAddress)(PSPAWNINFO, PCHAR);
    WORD Restriction;
    WORD Category;
} CMDLIST, *PCMDLIST;

typedef struct _EQSOCIAL {
/*0x0000*/   CHAR   Name[0x10];
/*0x0010*/   CHAR   Line[0x5][0x100];
/*0x0510*/   BYTE   Color; 
} EQSOCIAL, *PEQSOCIAL;

typedef struct _EQFRIENDSLIST {
/*0x0000*/ CHAR Name[0x64][0x40];
/*0x1900*/
} EQFRIENDSLIST, *PEQFRIENDSLIST;

typedef struct _ALTABILITY {
/*0x00*/ BYTE  Unknown0x00[0x4];
/*0x04*/ DWORD UnknownData0x04;
/*0x08*/ DWORD UnknownData0x08;
/*0x0c*/ BYTE  Unknown0x0c[0xc];
/*0x18*/ DWORD UnknownData0x18;
/*0x1c*/ DWORD nShortName;
/*0x20*/ DWORD nShorterName;
/*0x24*/ DWORD nName;
/*0x28*/ DWORD nDesc;
/*0x2c*/ DWORD MinLevel;
/*0x30*/ DWORD UnknownData0x30;
/*0x34*/ DWORD MyAltAbilityIndex;     
/*0x38*/ DWORD UnknownData0x38;
/*0x3c*/ LONG  RequiresAbility;        //requires ability? (-1 for no)  
/*0x40*/ DWORD RequiresAbilityPoints;  //requires points in this ability? 
/*0x44*/ DWORD Type;
/*0x48*/ DWORD UnknownData0x48;
/*0x4c*/ DWORD UnknownData0x4c;
/*0x50*/ DWORD UnknownData0x50;
/*0x54*/ LONG  ReuseTimer;
/*0x58*/ DWORD UnknownData0x58;
/*0x5c*/ DWORD MaxRank;
/*0x60*/ DWORD Cost;     
/*0x64*/ LONG  SpellID;// -1 for no
/*0x68*/ DWORD UnknownData0x68;
/*0x6c*/ DWORD UnknownData0x6c;
/*0x70*/ DWORD Unknown0x70;
/*0x74*/ DWORD Unknown0x74;
/*0x78*/ DWORD Unknown0x78;
/* Still Missing:  AARankRequired */
} ALTABILITY, *PALTABILITY;

#define NUM_ALT_ABILITIES 0x1f4
typedef struct _ALTADVMGR {
/*0x00*/ BYTE Unknown0x00[0x24];
/*0x28*/ PALTABILITY Abilities[NUM_ALT_ABILITIES];
} ALTADVMGR, *PALTADVMGR;

// size 0x118 
typedef struct _EQRAIDMEMBER { 
/*0x00*/ CHAR Name[0x40]; 
/*0x40*/ CHAR RaidNote[0x40]; 
/*0x80*/ CHAR Level[0x08]; 
/*0x88*/ CHAR Class[0x20]; 
/*0xC8*/ BYTE Unknown0xC8[0x60]; 
/*0x108*/ DWORD nClass; 
/*0x10C*/ BYTE  RaidLeader; 
/*0x10D*/ BYTE  GroupLeader; 
/*0x10E*/ BYTE  Field_10E; 
/*0x10F*/ BYTE  Field_10F; 
/*0x110*/ BYTE  Field_110; 
/*0x111*/ BYTE  Padding0x111[0x3]; 
/*0x114*/ DWORD GroupNumber; 
/*0x118*/ 
} EQRAIDMEMBER, *PEQRAIDMEMBER;

// sizeof(_EQRAID) is 0x49b8 
typedef struct _EQRAID { 
/*0x0000*/  BYTE        Unknown0x0[0x154]; 
/*0x0154*/  CHAR        RaidMemberUsed[0x48]; 
/*0x019c*/  struct      _EQRAIDMEMBER RaidMember[0x48]; 
/*0x3e5c*/  DWORD       field_3E5C; 
/*0x3e60*/  DWORD       RaidMemberCount; 
/*0x3e64*/  CHAR        RaidLeaderName[0x40]; 
/*0x3ea4*/  BYTE        Unknown3ea4[0x100]; 
/*0x3fa4*/  CHAR        RaidMOTD[0x400]; 
/*0x43a4*/  BYTE        Unknown0x43a4[0x140]; 
/*0x44e4*/  DWORD       field_44E4; 
/*0x44e8*/  BYTE        Unknown0x44e8; 
/*0x44e9*/  BYTE        IsRaidLeader; 
/*0x44ea*/  BYTE        Unknown0x44ea[0x2]; 
/*0x44ec*/  DWORD       RaidTarget; 
/*0x44f0*/  DWORD       LootType; 
/*0x44f4*/  CHAR        RaidLooters[0x13][0x40]; 
/*0x49b4*/  DWORD       TotalRaidMemberLevels; 
/*0x49b8*/ 
} EQRAID, *PEQRAID;

// size 0x08
typedef struct _EQSTRING {
/*0x00*/	DWORD ID;
/*0x04*/	PCHAR String;
} EQSTRING, *PEQSTRING;

// size 0x10 4-28-2004 lax
typedef struct _EQSTRINGTABLE {
/*0x00*/ struct _EQSTRING **StringItems;
/*0x04*/ DWORD Size;
/*0x08*/ DWORD Count;
/*0x0c*/ DWORD Unknown0x0c;
/*0x10*/
} EQSTRINGTABLE, *PEQSTRINGTABLE;
typedef struct _CHATCHANNELS {
/*0x000*/ PCHAR  ChannelName[0xa];
/*0x004*/
} CHATCHANNELS, *PCHATCHANNELS;

//eqmac version
typedef struct _CHATSERVICE {
/*0x000*/ DWORD   vftable;
/*0x004*/ struct _EVERQUEST   *ptr;
/*0x008*/ BYTE   Unknown0x008[0x14];
/*0x01c*/ CHAR   ChatID[0x30];     // "ServerName.CharName" (0x60?)
/*0x04c*/ BYTE   EncodedChannelname[0x30];//"alliance" for example is 6ffb173f
/*0x07c*/ CHAR   ServerName[0x30]; // "ServerName."
/*0x0b0*/ // more data
} CHATSERVICE, *PCHATSERVICE;

//eqmac version
typedef struct _EVERQUEST {
/*0x000*/ void *vTable;
/*0x004*/ CHAR	ChatServerName[0x80];
/*0x084*/ DWORD Unknown0x084;
/*0x088*/ CHAR   ChannelPlayerName[0x90];
/*0x118*/ DWORD	 njoinedchannels;//just guessing
/*0x11c*/ BYTE	Unknown0x11c[0x6c];
/*0x188*/ CHAR   ChannelName[0x10][0x10];//encoded alliance is 6ffb173f
/*0x288**/ struct _CHATSERVICE *ChatService;
/*0x28c*/ BOOL   bJoinedChannel;
/*0x290*/ BYTE   Unknown0x290[0x31c];
/*0x5ac**/ DWORD  GameState;
/*0x5b0*/ // more data
} EVERQUEST, *PEVERQUEST;

#define EQ_BEGIN_ZONE                   0x4155  // CEverQuest__SavePCForce         20130619
#define EQ_END_ZONE                     0x400A  // CEverQuest__DoMainLoop+B2F      20130619
};
using namespace EQData;
