// MQ2ChatWnd.cpp : Defines the entry point for the DLL application.
//

// Single-window MQ Chat

//#define DEBUG_TRY 1
#define MAX_CHAT_SIZE 700
#define LINES_PER_FRAME 3
#include "../MQ2Plugin.h"
#include <vector>
#include <map>
#include "resource.h"
PreSetup("MQ2MapWnd");

void CreateMapWindow();
void CreateEditLabelWindow();
void CreateMapToolbarWindow();
class CMQ2MapWnd;
class CMQ2MapToolbarWnd;
class CMQ2EditLabelWnd;
struct XYZ
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
};
extern "C" {
DWORD CurrentMapLabel = 0;
CMQ2EditLabelWnd *g_pEditLabelWnd = 0;
CMQ2MapToolbarWnd *g_pMapToolbarWnd = 0;
CMQ2MapWnd *g_pMapViewWnd=0;
int __cdecl t3dGetWorldExtents(DWORD displayptr,struct T3D_XYZ *out1,struct T3D_XYZ *out2);
int __cdecl CMapViewWnd_Activate(void);
int __cdecl CMapViewWnd_StoreIniInfo(void);
int __cdecl CMapViewWnd_LoadIniInfo(void);
int __cdecl CMapViewWnd_PostDraw(void);
int __cdecl CMapViewWnd_CMapViewWnd(class CXWnd *);
int __cdecl _MapViewMap__SetZoneExtents(int,int,int,int);
int __cdecl _MapViewMap__MapViewMap(void);
int __cdecl _MapViewMap__dMapViewMap(void);
void __cdecl _MapViewMap__SetZoom(float);
void __cdecl _CMapViewWnd__Init(void);
void __cdecl MapViewMap_ClearActiveLayer(void);
void __cdecl MapViewMap_Clear(void);
int __cdecl _MapViewMap__GetMinZ(void);
int __cdecl _MapViewMap__GetMaxZ(void);
void __cdecl _CMapViewWnd__SetCurrentZone(enum EQZoneIndex,struct T3D_XYZ *,struct T3D_XYZ *);
int __cdecl CMapViewWnd_OnProcessFrame(void);
int __cdecl CMapViewWnd_Deactivate(void);
int __cdecl CMapViewWnd_WndNotification(class CXWnd *,unsigned __int32,void *);

int __cdecl CMapViewWnd_HandleLButtonDown(class CXPoint,unsigned __int32);
int __cdecl CMapViewWnd_HandleLButtonUp(class CXPoint,unsigned __int32);
int __cdecl CMapViewWnd_HandleLButtonHeld(class CXPoint,unsigned __int32);
int __cdecl CMapViewWnd_HandleLButtonUpAfterHeld(class CXPoint,unsigned __int32);
int __cdecl CMapViewWnd_HandleWheelMove(class CXPoint,int,unsigned __int32);
float unk_5DF7B0[2];
float unk_5DF7C0[2];
//_CMapToolbarWnd_WndNotification
int __cdecl CMapToolbarWnd_WndNotification(class CXWnd *,unsigned __int32,void *);
int __cdecl CMapToolbarWnd_OnProcessFrame(void);
int __cdecl CMapToolbarWnd_Deactivate(void);
int __cdecl CEditLabelWnd_WndNotification(class CXWnd *,unsigned __int32,void *);
int __cdecl CEditLabelWnd_Deactivate(void);
}

FUNCTION_AT_ADDRESS( MapViewMap::MapViewMap(void),_MapViewMap__MapViewMap);
FUNCTION_AT_ADDRESS( MapViewMap::~MapViewMap(void),_MapViewMap__dMapViewMap);
FUNCTION_AT_ADDRESS(void  MapViewMap::SetZoneExtents(int,int,int,int),_MapViewMap__SetZoneExtents);
FUNCTION_AT_ADDRESS(void  MapViewMap::SetZoom(float),_MapViewMap__SetZoom);
FUNCTION_AT_ADDRESS(void  CMapViewWnd::Init(void),_CMapViewWnd__Init);
FUNCTION_AT_ADDRESS(int  MapViewMap::GetMinZ(void),_MapViewMap__GetMinZ);
FUNCTION_AT_ADDRESS(int  MapViewMap::GetMaxZ(void),_MapViewMap__GetMaxZ);
FUNCTION_AT_ADDRESS(void  CMapViewWnd::Activate(void),CMapViewWnd_Activate);
FUNCTION_AT_ADDRESS(void  CMapViewWnd::Deactivate(void),CMapViewWnd_Deactivate);
FUNCTION_AT_ADDRESS(void  CMapViewWnd::SetCurrentZone(enum EQZoneIndex,struct T3D_XYZ *,struct T3D_XYZ *),_CMapViewWnd__SetCurrentZone);
FUNCTION_AT_ADDRESS(void  MapViewMap::ClearActiveLayer(void),MapViewMap_ClearActiveLayer);
FUNCTION_AT_ADDRESS(void  MapViewMap::Clear(void),MapViewMap_Clear);

class CMQ2MapWnd : public CCustomMapWnd
{
public:
	CMQ2MapWnd():CCustomMapWnd("MapViewWnd")
	{

		DebugSpew("CMQ2MapWnd()");
		SetvfTable(33,(DWORD)&CMapViewWnd_WndNotification);
		SetvfTable(4,(DWORD)&CMapViewWnd_PostDraw);
		SetvfTable(43,(DWORD)&CMapViewWnd_OnProcessFrame);
		SetvfTable(34,(DWORD)&CMapViewWnd_Deactivate);

		SetvfTable(13,(DWORD)&CMapViewWnd_HandleLButtonDown);
		SetvfTable(14,(DWORD)&CMapViewWnd_HandleLButtonUp);
		SetvfTable(15,(DWORD)&CMapViewWnd_HandleLButtonHeld);
		SetvfTable(16,(DWORD)&CMapViewWnd_HandleLButtonUpAfterHeld);
		SetvfTable(24,(DWORD)&CMapViewWnd_HandleWheelMove);
		//decomment theese when heigh filter is sorted...
		SetvfTable(63,(DWORD)&CMapViewWnd_LoadIniInfo);
		SetvfTable(64,(DWORD)&CMapViewWnd_StoreIniInfo);
		//this->dShow=1;
		this->Unknown0x1a4_MVW_MapRenderArea=GetChildItem("MVW_MapRenderArea");
		this->Unknown0x138_MVW_PanLeftButton = GetChildItem("MVW_PanLeftButton");
		this->Unknown0x13c_MVW_PanRightButton = GetChildItem("MVW_PanRightButton");
		this->Unknown0x140_MVW_PanUpButton = GetChildItem("MVW_PanUpButton");
		this->Unknown0x144_MVW_PanDownButton = GetChildItem("MVW_PanDownButton");
		this->Unknown0x148_MVW_PanResetButton = GetChildItem("MVW_PanResetButton");
		this->Unknown0x14c_MVW_ZoomInButton = GetChildItem("MVW_ZoomInButton");
		this->Unknown0x150_MVW_ZoomOutButton = GetChildItem("MVW_ZoomOutButton");
		this->Unknown0x154_MVW_ToolbarButton = GetChildItem("MVW_ToolbarButton");
		//this->Unknown0x154_MVW_ToolbarButton->Enabled = 0;
		this->Unknown0x178_MVW_LabelsToggleButton = GetChildItem("MVW_LabelsToggleButton");
		this->Unknown0x17c_MVW_MinZEditBox = GetChildItem("MVW_MinZEditBox");
		this->Unknown0x180_MVW_MaxZEditBox = GetChildItem("MVW_MaxZEditBox");
		this->Unknown0x184_MVW_ZFilterButton = GetChildItem("MVW_ZFilterButton");
		this->Unknown0x188_MVW_Layer0Button = GetChildItem("MVW_Layer0Button");
		this->Unknown0x18c_MVW_Layer1Button = GetChildItem("MVW_Layer1Button");
		this->Unknown0x190_MVW_Layer2Button = GetChildItem("MVW_Layer2Button");
		this->Unknown0x194_MVW_Layer3Button = GetChildItem("MVW_Layer3Button");
		this->Unknown0x198_MVW_Layer1ActiveButton = GetChildItem("MVW_Layer1ActiveButton");
		this->Unknown0x19c_MVW_Layer2ActiveButton = GetChildItem("MVW_Layer2ActiveButton");
		this->Unknown0x1a0_MVW_Layer3ActiveButton = GetChildItem("MVW_Layer3ActiveButton");
		Sleep(0);
		CButtonWnd *button = (CButtonWnd *)this->Unknown0x188_MVW_Layer0Button;
		button->SetCheck(1);
		button = (CButtonWnd *)this->Unknown0x18c_MVW_Layer1Button;
		button->SetCheck(1);
		button = (CButtonWnd *)this->Unknown0x190_MVW_Layer2Button;
		button->SetCheck(1);
		button = (CButtonWnd *)this->Unknown0x194_MVW_Layer3Button;
		button->SetCheck(1);
		button = (CButtonWnd *)this->Unknown0x198_MVW_Layer1ActiveButton;
		button->SetCheck(1);
		button = (CButtonWnd *)this->Unknown0x19c_MVW_Layer2ActiveButton;
		button->SetCheck(1);
		button = (CButtonWnd *)this->Unknown0x1a0_MVW_Layer3ActiveButton;
		button->SetCheck(1);
		XYZ xyz1 = {0};
		XYZ xyz2 = {0};
		DWORD address = (DWORD)pDisplay;
		DWORD addr = *(DWORD *)(address+4);
		int in = t3dGetWorldExtents(addr,(T3D_XYZ *)&xyz1,(T3D_XYZ *)&xyz2);
		CXRect rect = this->Unknown0x1a4_MVW_MapRenderArea->GetRelativeRect();
		//this->MapViewMap0x1a8._78_Unknown = 1.0;
		//xyz1 = {X=-1192.24048 Y=-637.587463 Z=-558.568848 }
		//xyz2 = {X=1190.76514 Y=1840.13281 Z=741.622253 }
		this->MapViewMap0x1a8.SetZoneExtents(1000,-1000,1000,-1000);
		this->MapViewMap0x1a8.SetZoom(2.0);//its 2.0 in titanium client so i guess its ok...
		this->MapViewMap0x1a8._74_MVW_ZFilterButtonChecked = 0;
		this->MapViewMap0x1a8._75_Unknown = 0;
		this->MapViewMap0x1a8._76_Unknown = 0;
		this->MapViewMap0x1a8._77_Unknown = 0;
		this->MapViewMap0x1a8._78_Unknown = 0;
		this->MapViewMap0x1a8._7C_Unknown = 0;
		this->MapViewMap0x1a8._81_Unknown = 0;
		this->MapViewMap0x1a8._82_Unknown = 0;
		this->MapViewMap0x1a8._83_Unknown = 0;
		int width = rect.Right-rect.Left;
		int height = rect.Bottom-rect.Top;
		this->MapViewMap0x1a8._10_MapWidth=(FLOAT)width;//width
		this->MapViewMap0x1a8._14_MapHeight=(FLOAT)height;//rect.Bottom-rect.Top;//height
		this->MapViewMap0x1a8._18_Unknown = (FLOAT)20.0;//indent? not sure...
		this->MapViewMap0x1a8._1C_Unknown = (FLOAT)20.0;//not sure...
		this->MapViewMap0x1a8._20_1c8_Unknown = 0;
		this->MapViewMap0x1a8._24_1cc_Unknown = 0;
		ZeroMemory(this->MapViewMap0x1a8._48_Unknown,0x10);
		//this->MapViewMap0x1a8.Map2Right0x1c0=20.000000;
		//this->MapViewMap0x1a8.Map2Bottom0x1c4=20.000000;
		/*this->MapViewMap0x1a8.MapLeft0x1a8=-1299.000000;//faking surefall glade map extent
		this->MapViewMap0x1a8.MapTop0x1ac=-2998.000000;
		this->MapViewMap0x1a8.MapRight0x1b0=1499.000000;
		this->MapViewMap0x1a8.MapBottom0x1b4=867.000000;*/
		//this->MapViewMap0x1a8.Map2Left0x1b8=rect.Right-rect.Left;//width
		//Unknown0x134=0;
		Unknown0x135=0;//AutoMapping
		//Unknown0x136=0;
		//Unknown0x137=0;
		((CMapViewWnd*)this)->Init();
		button = (CButtonWnd *)this->Unknown0x178_MVW_LabelsToggleButton;
		button->SetCheck((bool)this->MapViewMap0x1a8._80_MVW_LabelsToggleButtonChecked);
		button = (CButtonWnd *)this->Unknown0x184_MVW_ZFilterButton;
		button->SetCheck((bool)this->MapViewMap0x1a8._74_MVW_ZFilterButtonChecked);
		int minz = this->MapViewMap0x1a8.GetMinZ();
		CHAR szminz[32] = {0};
		itoa(minz,szminz,10);
		CXWnd *cwnd = (CXWnd *)this->Unknown0x17c_MVW_MinZEditBox;
		cwnd->SetWindowTextA(szminz);
		int maxz = this->MapViewMap0x1a8.GetMaxZ();
		itoa(maxz,szminz,10);
		cwnd = (CXWnd *)this->Unknown0x180_MVW_MaxZEditBox;
		cwnd->SetWindowTextA(szminz);//surefallglade zone extent:
		
		//if(gGameState==GAMESTATE_INGAME)
		//SetWndNotification(CMQ2MapWnd);
		
		
		/*
		-2998.81250;//-2998.81250      -1299.46875      -43.9687500
			xyz1.Y = -1299.46875;
			xyz1.Z = -43.9687500;
		unk_5DF7C0[0] = 867.656250;//867.656250       1499.40625       779.687500
		unk_5DF7C0[1] = 1499.40625;
		unk_5DF7C0[2] = 779.687500;
		*/
		this->Unknown0x134=0;//active
		if(!in) {
			xyz1.X = -2000.0;//using default values...
			xyz1.Y = -2000.0;//i dont think this should happen...
			xyz1.Z = -2000.0;
			xyz2.X = 2000.0;
			xyz2.Y = 2000.0;
			xyz2.Z = 2000.0;
		}
		T3D_XYZ *t3d1 = (T3D_XYZ *)&xyz1;
		T3D_XYZ *t3d2 = (T3D_XYZ *)&xyz2;
		((CMapViewWnd*)this)->SetCurrentZone((EQZoneIndex)*(DWORD *)0x7B9648,t3d1,t3d2);
	}
	~CMQ2MapWnd()
	{
//		this->pvfTable->vector_deleting_destructor();
	}

	int WndNotification(CXWnd *pWnd, unsigned int Message, void *data)
	{	
		return CSidlScreenWnd::WndNotification(pWnd,Message,data);
	};
};

class CMQ2EditLabelWnd : public CCustomEditLabelWnd
{
public:
	CMQ2EditLabelWnd():CCustomEditLabelWnd("EditLabelWnd")
	{
		DebugSpew("CMQ2EditLabelWnd()");
		this->ELW_LabelTextEditbox_0x140 = GetChildItem("ELW_LabelTextEditbox");
		this->ELW_ChooseColorButton_0x144 = GetChildItem("ELW_ChooseColorButton");
		this->ELW_LabelLargeButton_0x148 = GetChildItem("ELW_LabelLargeButton");
		this->ELW_LabelMediumButton0x14c = GetChildItem("ELW_LabelMediumButton");
		this->ELW_LabelSmallButton_0x150 = GetChildItem("ELW_LabelSmallButton");
		this->ELW_CancelButton_0x154 = GetChildItem("ELW_CancelButton");
		this->ELW_DoneButton_0x158 = GetChildItem("ELW_DoneButton");
		CButtonWnd *button = (CButtonWnd *)this->ELW_ChooseColorButton_0x144;
		button->SetCheck(0);
		button = (CButtonWnd *)this->ELW_LabelLargeButton_0x148;
		button->SetCheck(0);
		button = (CButtonWnd *)this->ELW_LabelMediumButton0x14c;
		button->SetCheck(0);
		button = (CButtonWnd *)this->ELW_LabelSmallButton_0x150;
		button->SetCheck(1);
		SetvfTable(33,(DWORD)&CEditLabelWnd_WndNotification);
		SetvfTable(34,(DWORD)&CEditLabelWnd_Deactivate);
	}

	~CMQ2EditLabelWnd()
	{
	}
	int WndNotification(CXWnd *pWnd, unsigned int Message, void *data)
	{	
		return CSidlScreenWnd::WndNotification(pWnd,Message,data);
	};
};
class CMQ2MapToolbarWnd : public CCustomMapToolbarWnd
{
public:
	CMQ2MapToolbarWnd():CCustomMapToolbarWnd("MapToolbarWnd")
	{
		DebugSpew("CMQ2MapToolbarWnd()");
		this->MTW_StartLineButton_0x134 = GetChildItem("MTW_StartLineButton");
		this->MTW_EndLineButton_0x138 = GetChildItem("MTW_EndLineButton");
		this->MTW_AddPointButton_0x13c = GetChildItem("MTW_AddPointButton");
		this->MTW_RemoveLineButton_0x140 = GetChildItem("MTW_RemoveLineButton");
		this->MTW_ChangeLineColorButton_0x144 = GetChildItem("MTW_ChangeLineColorButton");
		this->MTW_JoinAtIntersectButton_0x148 = GetChildItem("MTW_JoinAtIntersectButton");
		this->MTW_AutoMapButton_0x14c = GetChildItem("MTW_AutoMapButton");
		this->MTW_AddLabelButton_0x150 = GetChildItem("MTW_AddLabelButton");
		this->MTW_EditLabelButton_0x154 = GetChildItem("MTW_EditLabelButton");
		this->MTW_MoveLabelToMeButton_0x158 = GetChildItem("MTW_MoveLabelToMeButton");
		this->MTW_RemoveLabelButton_0x15c = GetChildItem("MTW_RemoveLabelButton");
		this->MTW_SetCurrentColorButton_0x160 = GetChildItem("MTW_SetCurrentColorButton");
		this->MTW_ClearMapButton_0x164 = GetChildItem("MTW_ClearMapButton");
		this->MTW_ClearLayerButton_0x168 = GetChildItem("MTW_ClearLayerButton");
		this->MTW_SaveMapButton_0x16c = GetChildItem("MTW_SaveMapButton");
		SetvfTable(33,(DWORD)&CMapToolbarWnd_WndNotification);
		SetvfTable(34,(DWORD)&CMapToolbarWnd_Deactivate);
		SetvfTable(43,(DWORD)&CMapToolbarWnd_OnProcessFrame);
	}

	~CMQ2MapToolbarWnd()
	{
	}

	int WndNotification(CXWnd *pWnd, unsigned int Message, void *data)
	{	
		return CSidlScreenWnd::WndNotification(pWnd,Message,data);
	};
};

PLUGIN_API VOID OnCleanUI(VOID);
PLUGIN_API VOID SetGameState(DWORD GameState);

VOID Style(PSPAWNINFO pChar, PCHAR szLine)
{
	if (!szLine || szLine[0]==0)
	{
		char out[256];
		sprintf(out,"Style 0x%X",g_pMapViewWnd->WindowStyle);
		WriteChatColor(out);
		return;
	}
	if (szLine[0]=='!')
	{
		int TurnOff;
		sscanf(&szLine[1],"%x",&TurnOff);
		BitOff(g_pMapViewWnd->WindowStyle,TurnOff);
	}
	else
	{
		int TurnOn;
		sscanf(&szLine[0],"%x",&TurnOn);
		BitOn(g_pMapViewWnd->WindowStyle,TurnOn);
	}
	char out[256];
	sprintf(out,"Style 0x%X",g_pMapViewWnd->WindowStyle);
	WriteChatColor(out);
}
class MQ2MapWndHooks {
public:
	void CConfirmationDialog__ProcessYes_Trampoline(void);
	void CConfirmationDialog__ProcessYes_Hook(void)
	{
		DWORD code = *(DWORD *)(this+0x148);
		if(code==0x2a) {//clear active layer
			/*mov     eax, g_pMapViewWnd ; class CMapViewWnd * g_pMapViewWn
			lea     ecx, [eax+1A8h]
			call    MapViewMap__ClearActiveLayer
			*/
			if(g_pMapViewWnd)
				g_pMapViewWnd->MapViewMap0x1a8.ClearActiveLayer();
			return;
		} else if(code==0x29) {//clear map
			if(g_pMapViewWnd)
				g_pMapViewWnd->MapViewMap0x1a8.Clear();
			return;
		}
		return CConfirmationDialog__ProcessYes_Trampoline();
	}
	void CSidlScreenWnd__CSidlScreenWnd_Trampoline(class CXWnd *,class CXStr,int,char *);
	void CSidlScreenWnd__CSidlScreenWnd_Hook(class CXWnd *wnd,class CXStr B,int C,char *D)
	{
		//CHAR szBuffer[MAX_STRING] = {0};
		//GetCXStr(B.Ptr,szBuffer);
		//DebugSpew("CSidlScreenWnd %x %s %x %x",wnd,szBuffer,C,D);
		//WriteChatf("CSidlScreenWnd %x %s %x %x",wnd,szBuffer,C,D);
		return CSidlScreenWnd__CSidlScreenWnd_Trampoline(wnd,B,C,D);
	}
};
DETOUR_TRAMPOLINE_EMPTY(void MQ2MapWndHooks::CSidlScreenWnd__CSidlScreenWnd_Trampoline(class CXWnd *,class CXStr,int,char *));
DETOUR_TRAMPOLINE_EMPTY(void MQ2MapWndHooks::CConfirmationDialog__ProcessYes_Trampoline(void));
VOID DoMQ2MapBind(PCHAR Name,BOOL Down)
{
	if (!Down)
	{
		if (g_pMapViewWnd)
		{
			if(g_pMapViewWnd->dShow==0) {
				//WriteChatf("CMapViewWnd address = %x",(DWORD)g_pMapViewWnd);
				//WriteChatf("MapViewWnd address = %x",(DWORD)g_pMapViewWnd+0x1a8);
				((CMapViewWnd*)g_pMapViewWnd)->Activate();
			}
			else
				((CMapViewWnd*)g_pMapViewWnd)->Deactivate();
		}
	}
}
struct mckey {
	union {
		int x;
		unsigned char a[4];
		char sa[4];
	};
};
void PatchEq(char *Filename,int resID,char *restype, int thecrc,BOOL bOptional=0)
{
	CHAR outfile[512] = {0};
	CHAR szFilename[MAX_STRING]={0};
	CHAR szDir[MAX_STRING]={0};
    PCHAR szProcessName = 0;
    GetModuleFileName(NULL,szFilename,MAX_STRING);
    szProcessName = strrchr(szFilename,'\\');
    szProcessName[0] = '\0';
	sprintf_s(szDir,"%s\\%s",szFilename,Filename);
	HANDLE hFile = CreateFile(szDir,               // file to open
                       GENERIC_READ,          // open for reading
                       FILE_SHARE_READ,       // share for reading
                       NULL,                  // default security
                       OPEN_EXISTING,         // existing file only
                       FILE_ATTRIBUTE_NORMAL, // normal file
                       NULL);                 // no attr. template
 
	BOOL patchneeded = 1;
    if (hFile != INVALID_HANDLE_VALUE) {
		DWORD size = 0;
		WIN32_FIND_DATA find = {0};
		FindFirstFile(szDir,&find);
		size = find.nFileSizeLow;
		HLOCAL hMem = LocalAlloc(LPTR,size);
		DWORD bytesread = 0;
		if(ReadFile(hFile,hMem,size,&bytesread,NULL)) {
			mckey key = {0};
			key.x = 12345678;
			int crc = memcheck0((unsigned char *)hMem,bytesread,key);
			if(crc==thecrc || bOptional) {
				patchneeded = 0;
			} else {
				CloseHandle(hFile);
				hFile = 0;
				CHAR szNewName[512] = {0};
				sprintf_s(szNewName,"%s.mq2mapold",szDir);
				MoveFile(szDir,szNewName);
			}
		}
		if(hMem)
			LocalFree(hMem);
		if(hFile)
			CloseHandle(hFile);
	}
	if(patchneeded) {
		HMODULE hHandle = GetModuleHandle("mq2mapwnd.dll");
		HRSRC hres = FindResource(hHandle,MAKEINTRESOURCE(resID),restype);
		HGLOBAL hglob = LoadResource(hHandle,hres);
		
		DWORD thesize = SizeofResource(hHandle,hres);
		hFile = CreateFile(szDir,                // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_ALWAYS,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template

		if (hFile != INVALID_HANDLE_VALUE) 
		{
			DWORD byteswritten = 0;
			WriteFile(hFile,hglob,thesize,&byteswritten,NULL);
			CloseHandle(hFile);
		} else {
			MessageBox(NULL,"Could not patch the files needed for mq2mapview to work","consult eqmule",MB_SYSTEMMODAL|MB_OK);
		}
	}
}
PLUGIN_API VOID InitializePlugin(VOID)
{
	DebugSpewAlways("Initializing MQMapWnd");
	//ok so in order to get map to work
	//we need theese EXACT files which is why I crc check them...
	//I took them from the titanium version - eqmule
	PatchEq("uifiles\\default\\EQUI.xml",IDR_EQUI,"XML",0xb2447bf0);
	PatchEq("eqstr_en.txt",IDR_EQSTR_EN,"BIN",0x3a770e94);
	PatchEq("uifiles\\default\\EQUI_MapViewWnd.xml",IDR_MAPVIEW,"XML",0x5ef0f114);
	PatchEq("uifiles\\default\\EQUI_BugReportWnd.xml",IDR_BUGREPORT,"XML",0xf698b5ec,1);
	PatchEq("uifiles\\default\\EQUI_EditLabelWnd.xml",IDR_EDITLABEL,"XML",0xe30247d8);
	PatchEq("uifiles\\default\\EQUI_MapToolbarWnd.xml",IDR_MAPTOOLBAR,"XML",0x627ebf06);
	PatchEq("uifiles\\default\\window_pieces04.tga",IDR_WINDOW_PIECES04,"BIN",0x7ce6605b);
	PatchEq("uifiles\\default\\cart01.tga",IDR_CART01,"BIN",0x6dea7944);
	PatchEq("uifiles\\default\\cart02.tga",IDR_CART02,"BIN",0xb72b9143);
	PatchEq("uifiles\\default\\cart03.tga",IDR_CART03,"BIN",0x269e876f);
	PatchEq("uifiles\\default\\cart04.tga",IDR_CART04,"BIN",0xd5175a57);

	// Add commands, macro parameters, hooks, etc.
	AddMQ2KeyBind("MQ2MAP",DoMQ2MapBind);
	EzDetour(CConfirmationDialog__ProcessYes,&MQ2MapWndHooks::CConfirmationDialog__ProcessYes_Hook,&MQ2MapWndHooks::CConfirmationDialog__ProcessYes_Trampoline);
	//EzDetour(CSidlScreenWnd__CSidlScreenWnd1,&MQ2MapWndHooks::CSidlScreenWnd__CSidlScreenWnd_Hook,&MQ2MapWndHooks::CSidlScreenWnd__CSidlScreenWnd_Trampoline);
	
}

PLUGIN_API VOID ShutdownPlugin(VOID)
{
	DebugSpewAlways("Shutting down MQMapWnd");
	RemoveMQ2KeyBind("MQ2MAP");
	OnCleanUI();
	//RemoveDetour(CSidlScreenWnd__CSidlScreenWnd1);
	RemoveDetour(CConfirmationDialog__ProcessYes);
}


// This is called every time WriteChatColor is called by MQ2Main or any plugin,
// IGNORING FILTERS, IF YOU NEED THEM MAKE SURE TO IMPLEMENT THEM. IF YOU DONT
// CALL CEverQuest::dsp_chat MAKE SURE TO IMPLEMENT EVENTS HERE
PLUGIN_API DWORD OnWriteChatColor(PCHAR Line, DWORD Color, DWORD Filter)
{
	return 0;
}

PLUGIN_API VOID OnZoned(VOID)
{
	DebugSpewAlways("MQ2MapWnd::OnZoned()");
	XYZ xyz1 = {0};
	XYZ xyz2 = {0};
	DWORD address = (DWORD)pDisplay;
	DWORD addr = *(DWORD *)(address+4);
	int in = t3dGetWorldExtents(addr,(T3D_XYZ *)&xyz1,(T3D_XYZ *)&xyz2);
	if(!in) {
		xyz1.X = -2000.0;//using default values...
		xyz1.Y = -2000.0;//i dont think this should happen...
		xyz1.Z = -2000.0;
		xyz2.X = 2000.0;
		xyz2.Y = 2000.0;
		xyz2.Z = 2000.0;
	}
	if(g_pMapViewWnd) {
		T3D_XYZ *t3d1 = (T3D_XYZ *)&xyz1;
		T3D_XYZ *t3d2 = (T3D_XYZ *)&xyz2;
		((CMapViewWnd*)g_pMapViewWnd)->SetCurrentZone((EQZoneIndex)*(DWORD *)0x7B9648,t3d1,t3d2);
	}
}
PLUGIN_API VOID OnReloadUI(VOID)
{
	//7B9648 currentzoneid
	DebugSpewAlways("MQ2MapWnd::OnReloadUI()");
	SetGameState(GAMESTATE_INGAME);//do this to force a recreate
	if(g_pMapViewWnd) {
		XYZ xyz1 = {0};
		XYZ xyz2 = {0};
		DWORD address = (DWORD)pDisplay;
		DWORD addr = *(DWORD *)(address+4);
		int in = t3dGetWorldExtents(addr,(T3D_XYZ *)&xyz1,(T3D_XYZ *)&xyz2);
		if(!in) {
			xyz1.X = -2000.0;//using default values...
			xyz1.Y = -2000.0;//i dont think this should happen...
			xyz1.Z = -2000.0;
			xyz2.X = 2000.0;
			xyz2.Y = 2000.0;
			xyz2.Z = 2000.0;
		}
		T3D_XYZ *t3d1 = (T3D_XYZ *)&xyz1;
		T3D_XYZ *t3d2 = (T3D_XYZ *)&xyz2;
		((CMapViewWnd*)g_pMapViewWnd)->SetCurrentZone((EQZoneIndex)*(DWORD *)0x7B9648,t3d1,t3d2);
	}
}
// Called once directly before shutdown of the cleanui system, and also
// every time the game calls CDisplay::CleanGameUI()
//FUNCTION_AT_VIRTUAL_ADDRESS(void CMQ2MapWnd::Destructor(void),0x04);
PLUGIN_API VOID OnCleanUI(VOID)
{
	DebugSpewAlways("MQ2MapWnd::OnCleanUI()");
	if (g_pMapViewWnd)
	{
		((CXWnd*)g_pMapViewWnd)->vector_deleting_destructor(0);
		//delete g_pMapViewWnd;
		g_pMapViewWnd=0;
		ppMapViewWnd=0;
		//ppMapViewWnd=(CMapViewWnd**)&g_pMapViewWnd;
	}
	if (g_pMapToolbarWnd)
	{
		delete g_pMapToolbarWnd;
		g_pMapToolbarWnd=0;
	}
	if (g_pEditLabelWnd)
	{
		delete g_pEditLabelWnd;
		g_pEditLabelWnd=0;
	}

}

// Called once directly after initialization, and then every time the gamestate changes
PLUGIN_API VOID SetGameState(DWORD GameState)
{
	DebugSpew("MQ2ChatWnd::SetGameState()");
	if (GameState==GAMESTATE_INGAME && !g_pEditLabelWnd)
	{
		// we entered the game, set up shop
		DebugTry(CreateEditLabelWindow());
	}
	if (GameState==GAMESTATE_INGAME && !g_pMapToolbarWnd)
	{
		// we entered the game, set up shop
		DebugTry(CreateMapToolbarWindow());
	}
	if (GameState==GAMESTATE_INGAME && !g_pMapViewWnd)
	{
		// we entered the game, set up shop
		DebugTry(CreateMapWindow());
		//pOptionsWnd->AddKeyboardAssignment(0x80,0x1a34,1);
		if(pWndMgr)
			pWndMgr->UpdateChildAndSiblingInfo();
	}
}

PLUGIN_API VOID OnPulse(VOID)
{
	
	/*if (gGameState==GAMESTATE_CHARSELECT && !g_pEditLabelWnd)
	{
		CreateEditLabelWindow();
	}
	if (gGameState==GAMESTATE_CHARSELECT && !g_pMapToolbarWnd)
	{
		CreateMapToolbarWindow();
	}
	if (gGameState==GAMESTATE_CHARSELECT && !g_pMapViewWnd)
	{
		CreateMapWindow();
	}*/
}

void CreateMapWindow()
{
	DebugSpew("MQMapWnd::CreateMapWindow()");
	if (!g_pMapViewWnd) {
		g_pMapViewWnd = new CMQ2MapWnd();
		if (!g_pMapViewWnd)
			return;
		//CMapToolbarWnd **ppMapToolbarWnd=(CMapToolbarWnd**)g_pMapViewWnd;
		//CMapViewWnd **myppMapViewWnd=(CMapViewWnd**)&g_pMapViewWnd;
		ppMapViewWnd=(CMapViewWnd**)&g_pMapViewWnd;
		//DWORD test = (DWORD)pMapViewWnd;
		//CMapViewWnd *test3 = pMapViewWnd;
		ppCurrentMapLabel=(PMAPLABEL *)&CurrentMapLabel;
		//PMAPLABEL *test56 = (PMAPLABEL *)&CurrentMapLabel;
		//DWORD tureee = (DWORD)pCurrentMapLabel;
		//Sleep(0);
		//CEditLabelWnd **ppEditLabelWnd=(CEditLabelWnd**)pinstCEditLabelWnd;
	}
}
void CreateEditLabelWindow()
{
	DebugSpew("CMQ2EditLabelWnd::CreateEditLabelWindow()");
	if (!g_pEditLabelWnd) {
		g_pEditLabelWnd = new CMQ2EditLabelWnd();
		if (!g_pEditLabelWnd)
			return;
	}
}
void CreateMapToolbarWindow()
{
	DebugSpew("CMQ2EditLabelWnd::CreateEditLabelWindow()");
	if (!g_pMapToolbarWnd) {
		g_pMapToolbarWnd = new CMQ2MapToolbarWnd();
		if (!g_pMapToolbarWnd)
			return;
	}
}

