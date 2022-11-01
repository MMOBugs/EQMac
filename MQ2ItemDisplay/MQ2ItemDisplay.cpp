// MQ2ItemDisplay.cpp : Defines the entry point for the DLL application.
//

// PLUGIN_API is only to be used for callbacks.  All existing callbacks at this time
// are shown below. Remove the ones your plugin does not use.  Always use Initialize
// and Shutdown for setup and cleanup, do NOT do it in DllMain.



#include "../MQ2Plugin.h"
PreSetup("MQ2ItemDisplay");

extern "C" {
__declspec(dllexport) ITEMINFO g_Item;
}


// *************************************************************************** 
// Function:    ItemDisplayHook
// Description: Our Item display hook 
// *************************************************************************** 
class ItemDisplayHook
{
public:
   VOID SetItem_Trampoline(class EQ_Item *pitem,bool unknown);
   VOID SetItem_Detour(class EQ_Item *pitem,bool unknown)
   {
      PEQITEMWINDOW This=(PEQITEMWINDOW)this;
	  PITEMINFO Item=(PITEMINFO)pitem;
      CHAR out[MAX_STRING] = {0};
	  CHAR temp[MAX_STRING] = {0};
      PCHAR lore = NULL;
      SetItem_Trampoline(pitem,unknown);

      // keep a global copy of the last item displayed...
      memcpy(&g_Item, Item, sizeof(ITEMINFO));

      strcpy(out,"<BR><c \"#00FFFF\">");
	 if (Item->Cost>0) {
		  DWORD cp = Item->Cost;
		  DWORD sp = cp/10; cp=cp%10;
		  DWORD gp = sp/10; sp=sp%10;
		  DWORD pp = gp/10; gp=gp%10;
		  strcat_s(out,"Value:");
		  if (pp>0) {
			  sprintf(temp," %dpp",pp);
			  strcat_s(out,temp);
		  }
		  if (gp>0) {
			  sprintf(temp," %dgp",gp);
			  strcat_s(out,temp);
		  }
		  if (sp>0) {
			  sprintf(temp," %dsp",sp);
			  strcat_s(out,temp);
		  }
		  if (cp>0) {
			  sprintf(temp," %dcp",cp);
			  strcat_s(out,temp);
		  }
		  strcat_s(out,"<BR>");
	 }

	 /*if ( Item->Favor > 0 ) {
		 sprintf(temp,"Tribute Value: %d<br>", Item->Favor);
		 strcat_s(out, temp);
	 }*/

     lore=Item->LoreName;
     if (lore[0]=='*') lore++;
     if (strcmp(lore,Item->Name)) {
      sprintf(temp,"Item Lore: %s<BR>",Item->LoreName);
      strcat_s(out,temp);
     }

     // This really should be a compare against some field in the item...
     if (strstr(This->ItemInfo->Text,"(Combat)")) {
	   if (Item->Common.CastingLevel0 == 0 )
		   sprintf(temp, "Procs at level 1 (Proc rate modifier: %d)<BR>", Item->Common.ProcRate );
	   else
	       sprintf(temp,"Procs at level %d (Proc rate modifier: %d)<BR>",Item->Common.Level, Item->Common.ProcRate);
       strcat_s(out,temp);
     } else if (Item->Common.SpellId==/*Haste*/998) {
      sprintf(temp,"%d%% Haste<BR>",Item->Common.Level+1);
      strcat_s(out,temp);
     }
	
	 // Just in case...
	 if ( (!strstr(This->ItemInfo->Text,"(Combat)")) && Item->Common.ProcRate > 0 )
	 {
		 sprintf(temp, "Proc rate Modifier: %d<BR>", Item->Common.ProcRate );
		 strcat_s(out,temp);
	 }

	 // Teh_Ish (02/08/2004) 
     if ( Item->Common.EffectType==4 || Item->Common.EffectType==1 || Item->Common.EffectType==5) {
        if ( Item->Common.Level == 0 )
			sprintf(temp, "Clickable at level 1<br>", Item->Common.Level );
		else
            sprintf(temp,"Clickable at level %d<BR>",Item->Common.Level); 
        strcat_s(out,temp); 
     }
	 //*** needs confirm
	 /*if (Item->Common.InstrumentType != 0){ 
       float instrumentmod = ((float)Item->InstrumentMod)/10.0f; 
       sprintf(temp,"Instrument mod: %3.1f to %s.<BR>", instrumentmod, szItemTypes[Item->InstrumentType]); 
       strcat_s(out,temp);       
     } 
 /**/

     if (Item->Type == ITEMTYPE_PACK) {
        sprintf(temp,"Container Type: %s<BR>",szCombineTypes[Item->Container.Combine]);
        strcat_s(out,temp);
     }

     if (out[0]!=17) {
      strcat_s(out,"</c>");
	  //((CXStr)This->ItemInfo)+=
      AppendCXStr(&This->ItemInfo,&out[0]);
     }
   }

   VOID SetSpell_Trampoline(int SpellID,bool HasSpellDescr,int unknown_int);
   VOID SetSpell_Detour(int SpellID,bool HasSpellDescr,int unknown_int)
   {
     PEQITEMWINDOW This=(PEQITEMWINDOW)this;
     PCHARINFO pCharInfo = NULL;
     if (NULL == (pCharInfo = GetCharInfo())) return;
     PSPELL pSpell = GetSpellByID(SpellID);

     CHAR out[MAX_STRING] = {0};
     CHAR temp[MAX_STRING] = {0};
     SetSpell_Trampoline(SpellID,HasSpellDescr,unknown_int);
	 strcpy(out,"<BR><c \"#00FFFF\">");

	 sprintf(temp, "ID: %04d&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;", pSpell->ID );
	 strcat_s(out,temp);

	 DWORD Tics=GetSpellDuration(pSpell,pCharInfo->pSpawn);
     if (Tics==0xFFFFFFFF)
	    strcat_s(out, "Duration: Permanent<br>" );
     else if (Tics==0xFFFFFFFE) 
	    strcat_s(out, "Duration: Unknown<br>" );
	 else if (Tics==0) {
	    // It's "instant", who cares?
		 strcat_s(out,"<br>");
	 }
     else {
		sprintf(temp, "Duration: %1.1f minutes<br>",(float)((Tics*6.0f)/60.0f));
		strcat_s(out, temp);
     }

	 sprintf(temp, "RecoveryTime: %1.2f&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;RecastTime: %1.2f <br>", (float)(pSpell->FizzleTime/1000.0f), (float)(pSpell->RecastTime/1000.0f) );
	 strcat_s(out,temp);

	 if (pSpell->Range > 0.0f ) {
		 sprintf(temp, "Range: %1.0f", pSpell->Range );
		 strcat_s(out,temp);
		 if ( pSpell->PushBack == 0.0f && pSpell->AERange == 0.0f)
			 strcat_s(out, "<br>");
	 }

	 if (pSpell->PushBack != 0.0f ) {
		 if (pSpell->Range > 0.0f ) 
			 strcat_s(out, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" );
		 sprintf(temp, "PushBack: %1.1f", pSpell->PushBack );
		 strcat_s(out, temp);
		 if (pSpell->AERange == 0.0f || pSpell->Range > 0.0f )
			 strcat_s(out, "<br>" );
	 }

	 if (pSpell->AERange > 0.0f ) {
		 if (pSpell->Range > 0.0f)
			 strcat_s(out, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" );
		 else if (pSpell->PushBack > 0.0f )
			 strcat_s(out, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" );
		 sprintf(temp, "AERange: %1.0f<br>", pSpell->AERange );
		 strcat_s(out, temp);
	 }

	 if (pSpell->TargetType != 0x06 && pSpell->TargetType != 0x0e && pSpell->TargetType != 0x03 && pSpell->TargetType != 0x28 && pSpell->TargetType != 0x29 ) {
		switch(pSpell->Resist) {
			case 6:	strcat_s(out, "Resist: Chromatic" ); break;
			case 5:	strcat_s(out, "Resist: Disease" ); break;
			case 4:	strcat_s(out, "Resist: Poison" ); break;
			case 3:	strcat_s(out, "Resist: Cold/Ice" ); break;
			case 2:	strcat_s(out, "Resist: Fire" ); break;
			case 1:	strcat_s(out, "Resist: Magic" ); break;
			case 0:	strcat_s(out, "Resist: Unresistable" ); break;
		}
		if (pSpell->ResistAdj != 0 ) {
			sprintf(temp, "&nbsp;&nbsp;&nbsp;(Resist Adj.: %d)<br>", pSpell->ResistAdj );
			strcat_s(out,temp);
		}
		else
			strcat_s(out,"<br>");
	 }

	 strcat_s(out, "<br>" );
	 CHAR szSlotInfo[MAX_STRING] = {0};
	 ShowSpellSlotInfo(pSpell,szSlotInfo);
	 strcat_s(out, szSlotInfo );
	 //show usable classes routine by Koad//
	 strcat_s(out, "<br>" );
     for (int j=0; j<16; j++) 
     { 
      if (pSpell->Level[j]>0 && pSpell->Level[j]<=65) 
      { 
		 sprintf(temp,"%s(%d)&nbsp;&nbsp;&nbsp;&nbsp;", GetClassDesc(j+1), pSpell->Level[j]); 
         strcat_s(out, temp); 
      } 
     }

	 if (out[0]!=17) {
     strcat_s(out,"</c>");
	 //((CXStr)This->ItemInfo)+=
	 AppendCXStr(&This->ItemInfo,&out[0]);   
     }
   }
};

DETOUR_TRAMPOLINE_EMPTY(VOID ItemDisplayHook::SetItem_Trampoline(class EQ_Item *,bool)); 
DETOUR_TRAMPOLINE_EMPTY(VOID ItemDisplayHook::SetSpell_Trampoline(int SpellID,bool HasSpellDescr,int));

// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializePlugin(VOID)
{
	DebugSpewAlways("Initializing MQ2ItemDisplay");

	// Add commands, macro parameters, hooks, etc.

//   EasyClassDetour(CItemDisplayWnd__SetItem,ItemDisplayHook,SetItem_Detour,void,(class EQ_Item *, bool),SetItem_Trampoline);
	EzDetour(CItemDisplayWnd__SetItem,&ItemDisplayHook::SetItem_Detour,&ItemDisplayHook::SetItem_Trampoline);
//   EasyClassDetour(CItemDisplayWnd__SetSpell,ItemDisplayHook,SetSpell_Detour,void,(int SpellID,bool HasSpellDescr,int),SetSpell_Trampoline);
	EzDetour(CItemDisplayWnd__SetSpell,&ItemDisplayHook::SetSpell_Detour,&ItemDisplayHook::SetSpell_Trampoline);
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownPlugin(VOID)
{
	DebugSpewAlways("Shutting down MQ2ItemDisplay");

	// Remove commands, macro parameters, hooks, etc.
	RemoveDetour(CItemDisplayWnd__SetItem);
	RemoveDetour(CItemDisplayWnd__SetSpell);
}
