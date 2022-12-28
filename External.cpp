                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "ExternalUtils.h"
#include "d3d9_x.h"
#include <dwmapi.h>
#include <vector>
#include "skStr.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "D3DX/d3dx9math.h"
#include "lib.hpp"
#include <thread>
#include <Windows.h>
#include <direct.h>
#include <string>
#include "skStr.h"
#include "comms.h"
#include "settings.h"
#include <intrin.h>
#include <list>
#include "dtcnerds.h"
#include "zerogui.h"
RECT GameRect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;
static ImColor cas;

ImFont* Verdana, * DefaultFont;

MSG Message = { NULL };
const MARGINS Margin = { -1 };
HWND game_wnd;
float testslider = 100;
int screen_width;
int screen_height;
bool nigger = false;
static void xCreateWindow();
static void xInitD3d();
static void xMainLoop();                     
static void xShutdown();
bool test = true;
static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static HWND Window = NULL;
IDirect3D9Ex* p_Object = NULL;                         
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;

int center_x = GetSystemMetrics(0) / 2 - 3;
int center_y = GetSystemMetrics(1) / 2 - 3;

DWORD UDPID;
uintptr_t baseaddy;
DWORD ScreenCenterX;
DWORD ScreenCenterY;
static int aimkeypos = 3;
static int aimbone = 1;

int AimFOV = 180;

bool boosterissue = false;


template <typename T>
T vmread(const uintptr_t address)
{
	T buffer{ };
	Comms::ReadProcessMemory(UDPID, address, (uint8_t*)&buffer, sizeof(T));
	return buffer;
}


template <typename T>
void vmwrite(const uintptr_t address, T value)
{
	Comms::WriteProcessMemory(UDPID, address, (uint8_t*)&value, sizeof(T));
}

namespace settings
{
	DWORD_PTR Uworld;
	DWORD_PTR LocalPawn;
	DWORD_PTR PlayerState;
	DWORD_PTR Localplayer;
	DWORD_PTR Rootcomp;
	DWORD_PTR PlayerController;
	DWORD_PTR Persistentlevel;
	DWORD_PTR Gameinstance;
	DWORD_PTR LocalPlayers;
	uint64_t PlayerCameraManager;
	uint64_t WorldSettings;
	Vector3 localactorpos;
	Vector3 relativelocation;
	Vector3 Relativelocation;
	DWORD_PTR AActors;
	DWORD ActorCount;
}

//STRUCTURES
typedef struct _TT {
	uint64_t Actor;
	int ID;
	uint64_t mesh;
	uint64_t root;
	uint64_t PlayerState;
	uint64_t LocalPlayerState;
	uint32_t LocalTeamID;
	uint32_t TeamID69;
	Vector3 pos;
	std::string name;
	bool Spotted;
}TT;

typedef struct _FNlEntity {
	uint64_t Actor;
	int ID;
	uint64_t mesh;

}FNlEntity;

struct FVector {
	double X; // 0x00(0x08)
	double Y; // 0x08(0x08)
	double Z; // 0x10(0x08)
};

// Size: 0x18 (Inherited: 0x00)
struct FRotator {
	double Pitch; // 0x00(0x08)
	double Yaw; // 0x08(0x08)
	double Roll; // 0x10(0x08)
};

// Size: 0x770 (Inherited: 0x00)
struct FMinimalViewInfo {
	struct FVector Location; // 0x00(0x18)
	struct FRotator Rotation; // 0x18(0x18)
	float FOV; // 0x30(0x04)
	float DesiredFOV; // 0x34(0x04)
	float OrthoWidth; // 0x38(0x04)
	float OrthoNearClipPlane; // 0x3c(0x04)
	float OrthoFarClipPlane; // 0x40(0x04)
	float AspectRatio; // 0x44(0x04)
	char bConstrainAspectRatio : 1; // 0x48(0x01)
	char bUseFieldOfViewForLOD : 1; // 0x48(0x01)
	char pad_48_2 : 6; // 0x48(0x01)
	char pad_49[0x3]; // 0x49(0x03)
	char pad_4D[0x3]; // 0x4d(0x03)
	float PostProcessBlendWeight; // 0x50(0x04)
	char pad_54[0xc]; // 0x54(0x0c)
	char pad_700[0x70]; // 0x700(0x70)
};

// ScriptStruct FortniteGame.FortPlayerAttributeSets
// Size: 0x50 (Inherited: 0x00)
struct FFortPlayerAttributeSets {
	struct UFortRegenHealthSet* HealthSet; // 0x00(0x08)
	struct UFortControlResistanceSet* ControlResistanceSet; // 0x08(0x08)
	struct UFortDamageSet* DamageSet; // 0x10(0x08)
	struct UFortMovementSet* MovementSet; // 0x18(0x08)
	struct UFortAdvancedMovementSet* AdvancedMovementSet; // 0x20(0x08)
	struct UFortConstructionSet* ConstructionSet; // 0x28(0x08)
	struct UFortPlayerAttrSet* PlayerAttrSet; // 0x30(0x08)
	struct UFortCharacterAttrSet* CharacterAttrSet; // 0x38(0x08)
	struct UFortWeaponAttrSet* WeaponAttrSet; // 0x40(0x08)
	struct UFortHomebaseSet* HomebaseSet; // 0x48(0x08)
};

typedef struct _LootEntity {
	std::string GNames;
	uintptr_t ACurrentItem;
}LootEntity;

// ScriptStruct FortniteGame.FortPlayerPawnStats
// Size: 0xd8 (Inherited: 0xc0)
struct FFortPlayerPawnStats {
	float MaxJumpTime; // 0xc0(0x04)
	float MaxStamina; // 0xc4(0x04)
	float StaminaRegenRate; // 0xc8(0x04)
	float StaminaRegenDelay; // 0xcc(0x04)
	float SprintingStaminaExpenditureRate; // 0xd0(0x04)
};

struct Camera
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
}; Camera vCamera;

// ScriptStruct Engine.TViewTarget
// Size: 0x790 (Inherited: 0x00)
struct FTViewTarget {
	struct FMinimalViewInfo POV; // 0x10(0x770)
};

struct FFortGameplayAttributeData {
	float Minimum; // 0x10(0x04)
	float Maximum; // 0x14(0x04)
	bool bIsCurrentClamped; // 0x18(0x01)
	bool bIsBaseClamped; // 0x19(0x01)
	bool bShouldClampBase; // 0x1a(0x01)
	char pad_1B[0x1]; // 0x1b(0x01)
	float UnclampedBaseValue; // 0x1c(0x04)
	float UnclampedCurrentValue; // 0x20(0x04)
	char pad_24[0x4]; // 0x24(0x04)
};

// Class FortniteGame.AthenaBigBaseWall
// Size: 0xa58 (Inherited: 0x9c8)
struct AAthenaBigBaseWall{
	float WallGravity; // 0x9c8(0x04)
	float TimeUntilWallComesDown; // 0x9cc(0x04)
	bool bResetBool; // 0x9d0(0x01)
	//enum class EBarrierState BarrierState; // 0x9d1(0x01)
	char pad_9D2[0x6]; // 0x9d2(0x06)
	//struct FScalableFloat ZKillLevel; // 0x9d8(0x28)
	char pad_A00[0x58]; // 0xa00(0x58)

	void WallStartingToComeDown(bool bIsOnBurgerSide); // Function FortniteGame.AthenaBigBaseWall.WallStartingToComeDown // (Event|Protected|BlueprintEvent) // @ game+0x1036c24
	void UpdateWallTime(float, float, float, float); // Function FortniteGame.AthenaBigBaseWall.UpdateWallTime // (Event|Protected|BlueprintEvent) // @ game+0x1036c24
	void ShowOrHideTimer(bool bNewVisibleState); // Function FortniteGame.AthenaBigBaseWall.ShowOrHideTimer // (Event|Protected|BlueprintEvent) // @ game+0x1036c24
	void OnRep_WallGravity(); // Function FortniteGame.AthenaBigBaseWall.OnRep_WallGravity // (Final|Native|Protected) // @ game+0x78b3450
	void OnRep_TimeUntilWallComesDown(); // Function FortniteGame.AthenaBigBaseWall.OnRep_TimeUntilWallComesDown // (Final|Native|Protected) // @ game+0x78b32cc
	void OnRep_ResetBool(); // Function FortniteGame.AthenaBigBaseWall.OnRep_ResetBool // (Final|Native|Protected) // @ game+0x24b6bc4
	void OnRep_BarrierState(); // Function FortniteGame.AthenaBigBaseWall.OnRep_BarrierState // (Final|Native|Protected) // @ game+0x78b2e88
	void OnNewBarrierState(enum class EBarrierState NewState); // Function FortniteGame.AthenaBigBaseWall.OnNewBarrierState // (Event|Protected|BlueprintEvent) // @ game+0x1036c24
};

////////////


D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

D3DMATRIX matrixx(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}


bool IsVec3Valid(Vector3 vec3)
{
	return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
}

bool IsInScreen(Vector3 pos, int over = 30) {
	if (pos.x > -over && pos.x < Width + over && pos.y > -over && pos.y < Height + over) {
		return true;
	}
	else {
		return false;
	}
}

FTransform GetBoneIndex(DWORD_PTR mesh, int index)
{
	DWORD_PTR bonearray;
	bonearray = vmread<DWORD_PTR>(mesh + 0x5c0);

	if (bonearray == NULL)
	{
		bonearray = vmread<DWORD_PTR>(mesh + 0x5D0);  //(mesh + 0x5e8) + 0x5a));
	}
	return vmread<FTransform>(bonearray + (index * 0x60));
}

Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
{
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = vmread<FTransform>(mesh + 0x240);

	D3DMATRIX Matrix;
	Matrix = matrixx(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

bool isVisible(uint64_t mesh)
{
	float tik = vmread<float>(mesh + 0x330);
	float tok = vmread<float>(mesh + 0x338);
	const float tick = 0.06f;
	return tok + tick >= tik;

}

Camera GetCamera(__int64 a1)
{
	Camera FGC_Camera;
	__int64 v1;
	__int64 v6;
	__int64 v7;
	__int64 v8;

	v1 = vmread<__int64>(settings::Localplayer + 0xd0);
	__int64 v9 = vmread<__int64>(v1 + 0x8); // 0x10

	FGC_Camera.FieldOfView = 80.f / (vmread<double>(v9 + 0x7F0) / 1.19f); // 0x600

	FGC_Camera.Rotation.x = vmread<double>(v9 + 0x9C0);
	FGC_Camera.Rotation.y = vmread<double>(a1 + 0x148);

	uint64_t FGC_Pointerloc = vmread<uint64_t>(settings::Uworld + 0x110);
	FGC_Camera.Location = vmread<Vector3>(FGC_Pointerloc);


	//v6 = driver.read<__int64>(Localplayer + 0x70);
	//v7 = driver.read<__int64>(v6 + 0x98);
	//v8 = driver.read<__int64>(v7 + 0xF8);
	//FGC_Camera.Location = driver.read<Vector3>(Uworld + 0x100); // 0x20

	return FGC_Camera;
}

Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	Camera vCamera = GetCamera(settings::Rootcomp);
	vCamera.Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / M_PI);

	D3DMATRIX tempMatrix = Matrix(vCamera.Rotation);

	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}


std::vector<_FNlEntity> entityList;
std::vector<TT> itemList;
void ActorLoop()
{
	while (true)
	{
		vmread<uintptr_t>(baseaddy + 0x0060); // trigger veh set - add module to whitelist filter

		settings::Uworld = vmread<DWORD_PTR>(baseaddy + 0xe9ea3f8);
		settings::Gameinstance = vmread<DWORD_PTR>(settings::Uworld + 0x1B8);
		settings::LocalPlayers = vmread<DWORD_PTR>(settings::Gameinstance + 0x38);
		settings::Localplayer = vmread<DWORD_PTR>(settings::LocalPlayers);
		settings::PlayerController = vmread<DWORD_PTR>(settings::Localplayer + 0x30);
		settings::PlayerCameraManager = vmread<uint64_t>(settings::PlayerController + 0x340);
		settings::LocalPawn = vmread<DWORD_PTR>(settings::PlayerController + 0x330);
		settings::PlayerState = vmread<DWORD_PTR>(settings::LocalPawn + 0x2a8);
		settings::Rootcomp = vmread<DWORD_PTR>(settings::LocalPawn + 0x190);
		settings::relativelocation = vmread<Vector3>(settings::Rootcomp + 0x2e8);
		settings::Persistentlevel = vmread<DWORD_PTR>(settings::Uworld + 0x30);
		settings::ActorCount = vmread<DWORD>(settings::Persistentlevel + 0xA0);
		settings::AActors = vmread<DWORD_PTR>(settings::Persistentlevel + 0x98);

		std::vector<FNlEntity> Players;
		for (int i = 0; i < settings::ActorCount; ++i) {
			DWORD_PTR CurrentActor = vmread<DWORD_PTR>(settings::AActors + i * 0x8);
			int CurrentActorId = vmread<int>(CurrentActor + 0x18);

			float player_check = vmread<float>(CurrentActor + 0x4250);
			if (player_check == 10) {

				uint64_t CurrentActorMesh = vmread<uint64_t>(CurrentActor + 0x310);
				int curactorid = vmread<int>(CurrentActor + 0x18);

				FNlEntity fnlEntity{ };
				fnlEntity.Actor = CurrentActor;
				fnlEntity.mesh = CurrentActorMesh;
				fnlEntity.ID = curactorid;

				Players.push_back(fnlEntity);
			}
		}
		entityList.clear();
		entityList = Players;

		Sleep(1);
	}
}

std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

void DrawStrokeText(int x, int y, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);

	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), utf_8_2.c_str());
}


void DrawText1(int x, int y, const char* str, RGBA* color)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

void DrawFilledRect(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void draw_cornered_box(int x, int y, int w, int h, ImColor color, int thickness) {
	float line_w = (w / 1);
	float line_h = (h / 1);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + line_h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(x + line_w, y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w - line_w, y), ImVec2(x + w, y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + line_h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y + h - line_h), ImVec2(x, y + h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + line_w, y + h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w - line_w, y + h), ImVec2(x + w, y + h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w, y + h - line_h), ImVec2(x + w, y + h), color, thickness);
}

void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), text.c_str());
}

void draw_corner_boxx(int x, int y, int w, int h, ImVec4 Color, int thickness) {
	float lineW = (w / 4.f);
	float lineH = (h / 4.f);
	ImDrawList* p = ImGui::GetOverlayDrawList();

	//oben links nach unten
	p->AddLine(ImVec2(x, y), ImVec2(x, y + lineH), ImColor(255,0,255), thickness);

	//oben links nach rechts (l-mittig)
	p->AddLine(ImVec2(x, y), ImVec2(x + lineW, y), ImColor(255,0,255), thickness);

	//oben rechts (r-mittig) nach rechts
	p->AddLine(ImVec2(x + w - lineW, y), ImVec2(x + w, y), ImColor(255,0,255), thickness);

	//oben rechts nach vert-rechts (oberhalb)
	p->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + lineH), ImColor(255,0,255), thickness);

	//unten vert-links (unterhalb) nach unten links
	p->AddLine(ImVec2(x, y + h - lineH), ImVec2(x, y + h), ImColor(255,0,255), thickness);

	//unten links nach rechts (mittig)
	p->AddLine(ImVec2(x, y + h), ImVec2(x + lineW, y + h), ImColor(255,0,255), thickness);

	//unten rechts (mittig) nach rechts
	p->AddLine(ImVec2(x + w - lineW, y + h), ImVec2(x + w, y + h), ImColor(255,0,255), thickness);

	//unten rechts nach vert-rechts (unterhalb)
	p->AddLine(ImVec2(x + w, y + h - lineH), ImVec2(x + w, y + h), ImColor(255,0,255), thickness);
}

void DrawCrossNazi1(int buyukluk, DWORD color)
{
	ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	int crosspozisyon = window_pos.x + window_size.x * 0.5f;
	int crosspozisyony = window_pos.y + window_size.y * 0.5f;
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony - buyukluk), ImVec2(crosspozisyon, crosspozisyony + buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(crosspozisyon - buyukluk, crosspozisyony), ImVec2(crosspozisyon + buyukluk, crosspozisyony), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony + buyukluk), ImVec2(crosspozisyon - buyukluk, crosspozisyony + buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(crosspozisyon, crosspozisyony - buyukluk), ImVec2(crosspozisyon + buyukluk, crosspozisyony - buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(crosspozisyon - buyukluk, crosspozisyony), ImVec2(crosspozisyon - buyukluk, crosspozisyony - buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(crosspozisyon + buyukluk, crosspozisyony), ImVec2(crosspozisyon + buyukluk, crosspozisyony + buyukluk), ImColor(color));
}

void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImU32 color)
{

	DrawFilledRect(x + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x + w - w + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h, color); //left 
	DrawFilledRect(x, y + h - h + borderPx * 2, borderPx, h, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w - w + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);//right 
}

void DrawCornerBoxxx(int x, int y, int w, int h, int borderPx, ImU32 color)
{

	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h / 3, color); //left 
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
}

void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

void DrawCrossNazi(int buyukluk, DWORD color)
{
	ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	int crosspozisyon = window_pos.x + 900;
	int crosspozisyony = window_pos.y + 479;
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - buyukluk), ImVec2(Width / 2, Height / 2 + buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - buyukluk, Height / 2), ImVec2(Width / 2 + buyukluk, Height / 2), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 + buyukluk), ImVec2(Width / 2 - buyukluk, Height / 2 + buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - buyukluk), ImVec2(Width / 2 + buyukluk, Height / 2 - buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - buyukluk, Height / 2), ImVec2(Width / 2 - buyukluk, Height / 2 - buyukluk), ImColor(color));
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 + buyukluk, Height / 2), ImVec2(Width / 2 + buyukluk, Height / 2 + buyukluk), ImColor(color));
}

void DrawStringImColor(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
}

void DrawCircle(int x, int y, int radius, RGBA* color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

void DrawBox(float X, float Y, float W, float H, ImU32 Col)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), Col);
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), Col);
}

void fovcircle(int x, int y, int radius, ImU32 color, int segments, float thickness)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, thickness);
}

float powf_(float _X, float _Y) {
	return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
}
float sqrtf_(float _X) {
	return (_mm_cvtss_f32(_mm_sqrt_ps(_mm_set_ss(_X))));
}

double GetDistance(double x1, double y1, double z1, double x2, double y2) {
	//return sqrtf(powf_((x2 - x1), 2) + powf_((y2 - y1), 2));
	return sqrtf(powf((x2 - x1), 2) + powf_((y2 - y1), 2));
}

void SetWindowToTarget()
{
	while (true)
	{
		if (hwnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(hwnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);

			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(Window, GameRect.left, GameRect.top, Width, Height, true);
		}
		else
		{
			exit(0);
		}
	}
}

void setup_window()
{
	WNDCLASSEX win_class = {
		sizeof(WNDCLASSEX),
		0,
		WinProc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		TEXT("Bluestacks 5"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&win_class))
		exit(1);

	game_wnd = FindWindowW(NULL, TEXT("Fortnite  "));

	if (game_wnd) {
		screen_width = 1900;
		screen_height = 1070;
	}
	else
		exit(2);

	Window = CreateWindowExA(NULL, "Bluestacks 5", "Bluestacks 5", WS_POPUP | WS_VISIBLE, Width + 10, Height + 5, screen_width, screen_height, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(Window, &Margin);
	SetWindowLong(Window, GWL_EXSTYLE, (int)GetWindowLong(Window, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 0, ULW_COLORKEY);
	SetLayeredWindowAttributes(Window, 0, 255, LWA_ALPHA);
	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
}


void xInitD3d()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(16, 16, 16);
	style.Colors[ImGuiCol_ChildBg] = ImColor(24, 24, 24);
	style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
	style.Colors[ImGuiCol_CheckMark] = ImColor(24, 97, 172);
	style.Colors[ImGuiCol_Border] = ImColor(24, 97, 172);
	style.Colors[ImGuiCol_BorderShadow] = ImColor(24, 97, 172);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.080f, 0.080f, 0.080f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(24, 97, 172);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(24, 97, 172);

	ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 13);


    p_Object->Release();
}

void aimbot(float x, float y)
{
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	int AimSpeed = smooth;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	SonyDriverHelper::api::MouseMove(TargetX, TargetY);

	return;
}

char* drawBuff = (char*)malloc(1024);

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}


void blackballs()
{
	ImGui::GetOverlayDrawList()->AddText(ImVec2(15, 15), ImColor(255, 255, 255, 255), _("Pheonix Fortnite"));

	if (aimkeypos == 0)
	{
		aimkey = 0x01;//left mouse button
	}
	else if (aimkeypos == 1)
	{
		aimkey = 0x02;//right mouse button
	}
	else if (aimkeypos == 2)
	{
		aimkey = 0x04;//middle mouse button
	}
	else if (aimkeypos == 3)
	{
		aimkey = 0x05;//x1 mouse button
	}
	else if (aimkeypos == 4)
	{
		aimkey = 0x06;//x2 mouse button
	}
	else if (aimkeypos == 5)
	{
		aimkey = 0x03;//control break processing
	}
	else if (aimkeypos == 6)
	{
		aimkey = 0x08;//backspace
	}
	else if (aimkeypos == 7)
	{
		aimkey = 0x09;//tab
	}
	else if (aimkeypos == 8)
	{
		aimkey = 0x0c;//clear
	}
	else if (aimkeypos == 9)
	{
		aimkey == 0x0D;//enter
	}
	else if (aimkeypos == 10)
	{
		aimkey = 0x10;//shift
	}
	else if (aimkeypos == 11)
	{
		aimkey = 0x11;//ctrl
	}
	else if (aimkeypos == 12)
	{
		aimkey == 0x12;//alt
	}
	else if (aimkeypos == 13)
	{
		aimkey == 0x14;//caps lock
	}
	else if (aimkeypos == 14)
	{
		aimkey == 0x1B;//esc
	}
	else if (aimkeypos == 15)
	{
		aimkey == 0x20;//space
	}
	else if (aimkeypos == 16)
	{
		aimkey == 0x30;//0
	}
	else if (aimkeypos == 17)
	{
		aimkey == 0x31;//1
	}
	else if (aimkeypos == 18)
	{
		aimkey == 0x32;//2
	}
	else if (aimkeypos == 19)
	{
		aimkey == 0x33;//3
	}
	else if (aimkeypos == 20)
	{
		aimkey == 0x34;//4
	}
	else if (aimkeypos == 21)
	{
		aimkey == 0x35;//5
	}
	else if (aimkeypos == 22)
	{
		aimkey == 0x36;//6
	}
	else if (aimkeypos == 23)
	{
		aimkey == 0x37;//7
	}
	else if (aimkeypos == 24)
	{
		aimkey == 0x38;//8
	}
	else if (aimkeypos == 25)
	{
		aimkey == 0x39;//9
	}
	else if (aimkeypos == 26)
	{
		aimkey == 0x41;//a
	}
	else if (aimkeypos == 27)
	{
		aimkey == 0x42;//b
	}
	else if (aimkeypos == 28)
	{
		aimkey == 0x43;//c
	}
	else if (aimkeypos == 29)
	{
		aimkey == 0x44;//d
	}
	else if (aimkeypos == 30)
	{
		aimkey == 0x45;//e
	}
	else if (aimkeypos == 31)
	{
		aimkey == 0x46;//f
	}
	else if (aimkeypos == 32)
	{
		aimkey == 0x47;//g
	}
	else if (aimkeypos == 33)
	{
		aimkey == 0x48;//h
	}
	else if (aimkeypos == 34)
	{
		aimkey == 0x49;//i
	}
	else if (aimkeypos == 35)
	{
		aimkey == 0x4A;//j
	}
	else if (aimkeypos == 36)
	{
		aimkey == 0x4B;//k
	}
	else if (aimkeypos == 37)
	{
		aimkey == 0x4C;//L
	}
	else if (aimkeypos == 38)
	{
		aimkey == 0x4D;//m
	}
	else if (aimkeypos == 39)
	{
		aimkey == 0x4E;//n
	}
	else if (aimkeypos == 40)
	{
		aimkey == 0x4F;//o
	}
	else if (aimkeypos == 41)
	{
		aimkey == 0x50;//p
	}
	else if (aimkeypos == 42)
	{
		aimkey == 0x51;//q
	}
	else if (aimkeypos == 43)
	{
		aimkey == 0x52;//r
	}
	else if (aimkeypos == 44)
	{
		aimkey == 0x53;//s
	}
	else if (aimkeypos == 45)
	{
		aimkey == 0x54;//t
	}
	else if (aimkeypos == 46)
	{
		aimkey == 0x55;//u
	}
	else if (aimkeypos == 47)
	{
		aimkey == 0x56;//v
	}
	else if (aimkeypos == 48)
	{
		aimkey == 0x57;//w
	}
	else if (aimkeypos == 49)
	{
		aimkey == 0x58;//x
	}
	else if (aimkeypos == 50)
	{
		aimkey == 0x59;//y
	}
	else if (aimkeypos == 51)
	{
		aimkey == 0x5A;//z
	}
	else if (aimkeypos == 52)
	{
		aimkey == 0x60;//numpad 0
	}
	else if (aimkeypos == 53)
	{
		aimkey == 0x61;//numpad 1
	}
	else if (aimkeypos == 54)
	{
		aimkey == 0x62;//numpad 2
	}
	else if (aimkeypos == 55)
	{
		aimkey == 0x63;//numpad 3
	}
	else if (aimkeypos == 56)
	{
		aimkey == 0x64;//numpad 4
	}
	else if (aimkeypos == 57)
	{
		aimkey == 0x65;//numpad 5
	}
	else if (aimkeypos == 58)
	{
		aimkey == 0x66;//numpad 6
	}
	else if (aimkeypos == 59)
	{
		aimkey == 0x67;//numpad 7
	}
	else if (aimkeypos == 60)
	{
		aimkey == 0x68;//numpad 8
	}
	else if (aimkeypos == 61)
	{
		aimkey == 0x69;//numpad 9
	}
	else if (aimkeypos == 62)
	{
		aimkey == 0x6A;//multiply
	}

	static const auto size = ImGui::GetIO().DisplaySize;
	static const auto center = ImVec2(size.x / 2, size.y / 2);

	if (circle)
	{
		//fovcircle(Width / 2, Height / 2, AimFOV, ImColor(127, 255, 0), 1000, 0.5f);
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), AimFOV, ImColor(255, 255, 255), 100);
	}

	if (crosshair)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 - 10, Height / 2), ImColor(255, 0, 0), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 + 10, Height / 2), ImColor(255, 0, 0), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 - 10), ImColor(255, 0, 0), 1.0f); //change 10
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 + 10), ImColor(255, 0, 0), 1.0f);
	}

	if (filledfov)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(center, AimFOV, ImColor(0, 0, 0, 110), 100);
	}

	float closestDistance = FLT_MAX;
	auto itemListCopy = itemList;

	for (FNlEntity entity : entityList) {
		uintptr_t mesh = vmread<uintptr_t>(entity.Actor + 0x310);
		Vector3 Headpose = GetBoneWithRotation(mesh, 68);
		Vector3 bone00 = GetBoneWithRotation(mesh, 0);
		Vector3 bottome = ProjectWorldToScreen(bone00);
		Vector3 Headboxe = ProjectWorldToScreen(Vector3(Headpose.x, Headpose.y, Headpose.z + 15));
		Vector3 w2sheade = ProjectWorldToScreen(Headpose);
		Vector3 vHeadBone = GetBoneWithRotation(mesh, 68);
		Vector3 vRootBone = GetBoneWithRotation(mesh, 0);
		Vector3 vHeadBoneOut = ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15));
		Vector3 vRootBoneOut = ProjectWorldToScreen(vRootBone);

		float distance = settings::relativelocation.Distance(Headpose) / 100.f;


		float BoxHeight = abs(Headboxe.y - bottome.y);
		float BoxWidth = BoxHeight * 0.56;

		float LeftX = (float)Headboxe.x - (BoxWidth / 1);
		float LeftY = (float)bottome.y;

		float Height1 = abs(Headboxe.y - bottome.y);
		float Width1 = Height1 * 0.65;

		float CornerHeight = abs(Headboxe.y - bottome.y);
		float CornerWidth = CornerHeight * 0.5f;

		uint64_t CurrentVehicle = vmread<uint64_t>(settings::LocalPawn + 0x2348); //FortPlayerPawn::CurrentVehicle
			uintptr_t CurrentWeapon = vmread<uintptr_t>(settings::LocalPawn + 0x868); //FortPawn::CurrentWeapon 0x868
		auto selfstate = vmread<uint16_t>(settings::Localplayer + 0x2a8);

		auto UCharacterMovementComponent = vmread<uintptr_t>(settings::LocalPawn + 0x318); //DefaultPawn::MovementComponet
		if (!UCharacterMovementComponent) continue;

		if (exploits)
		{
			if (spinbot)
			{
				auto Mesh = vmread<uint64_t>(settings::LocalPawn + 0x310);
				static auto Cached = vmread<Vector3>(Mesh + 0x140);

				if (SonyDriverHelper::api::GetKey(VK_LBUTTON)) {
					vmwrite<Vector3>(Mesh + 0x140, Vector3(1, rand() % 361, 1));
				}
				else vmwrite<Vector3>(Mesh + 0x140, Cached);
			}

			if (carto)
			{
				if (SonyDriverHelper::api::GetKey(VK_SHIFT))
				{
					vmwrite<char>(CurrentVehicle + 0x6AA, 1);
				}
				else
				{
					vmwrite<char>(CurrentVehicle + 0x6AA, 0);
				}
			}



			if (boatspeed)
			{
				if (CurrentVehicle)
				{
					vmwrite<float>(CurrentVehicle + 0xCB4, 3);
					vmwrite<float>(CurrentVehicle + 0x918, 3 + 2);
					vmwrite<float>(CurrentVehicle + 0x91C, 3);
					vmwrite<float>(CurrentVehicle + 0x7AC, 3);
				}
			}

			if (fuel)
			{
				if (CurrentVehicle)
				{
					auto FuelComponent = vmread<uintptr_t>(CurrentVehicle + 0x10A0);
					vmwrite<float>(FuelComponent + 0xf0, 20000.f);
				}
			}

			if (samenrds)
			{
				auto AttributeSets = vmread<uintptr_t>(settings::PlayerState + 0x9F8);
				auto PlayerAttrSet = vmread<uintptr_t>(AttributeSets + 0x30);
				auto UFortPlayerAttrSet = vmread<uintptr_t>(PlayerAttrSet + 0xb0);

				//vmwrite<float>(UFortPlayerAttrSet + 0x60, 0.0000000000000f);
				//vmwrite<float>(UFortPlayerAttrSet + 0x88, 0.0000000000000f);
			}
		}


		int MyTeamId = vmread<int>(settings::PlayerState + 0x1098);
		DWORD64 otherPlayerState = vmread<uint64_t>(entity.Actor + settings::PlayerState);
		uintptr_t ActorState = vmread<uintptr_t>(entity.Actor + 0x290);
		float VisDist = 50.f;
		if (entity.Actor == settings::LocalPawn) continue;

		    if (Esp || MyTeamId != otherPlayerState || InLobby || distance < VisDist);
			{
				if (Esp_corner)
				{
					ImU32 ESPSkeletonn;
					if (isVisible(entity.mesh))
					{
						DrawCorneredBox(bottome.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(255, 255, 255), 1.5);
						//draw_corner_boxx(bottome.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(0, 255, 0), 1.5);
					}
					else if (!isVisible(entity.mesh))
					{
						DrawCorneredBox(bottome.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(255, 255, 255), 1.5);
						//draw_corner_boxx(bottome.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(255, 0, 0), 1.5);
					}

				}


				if (boxnerds)
				{
					if (isVisible(entity.mesh))
					{
						DrawCornerBoxxx(Headboxe.x - Width1 / 2 + 1, Headboxe.y, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						DrawCornerBoxxx(Headboxe.x - Width1 / 2 - 1, Headboxe.y, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						DrawCornerBoxxx(Headboxe.x - Width1 / 2, Headboxe.y + 1, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						DrawCornerBoxxx(Headboxe.x - Width1 / 2, Headboxe.y - 1, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						//DrawBox(Headboxe.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(255, 255, 255));
						//draw_corner_boxx(bottome.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(0, 255, 0), 1.5);

					}
					else if (!isVisible(entity.mesh))
					{
						DrawCornerBoxxx(Headboxe.x - Width1 / 2 + 1, Headboxe.y, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						DrawCornerBoxxx(Headboxe.x - Width1 / 2 - 1, Headboxe.y, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						DrawCornerBoxxx(Headboxe.x - Width1 / 2, Headboxe.y + 1, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						DrawCornerBoxxx(Headboxe.x - Width1 / 2, Headboxe.y - 1, Width1, Height1, 1.0f, ImGui::GetColorU32({ Settings::outline5[0], Settings::outline5[1], Settings::outline5[2], 1.0f }));
						//DrawBox(Headboxe.x - (BoxWidth / 2CornerWidth Headboxe.y, BoxWidth, BoxHeight, ImColor(255, 0, 0));
						//draw_corner_boxx(bottome.x - (BoxWidth / 2), Headboxe.y, BoxWidth, BoxHeight, ImColor(255, 0, 0), 1.5);
					}
				}

				if (Esp_line)
				{
					if (isVisible(entity.mesh))
					{
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height - Height), ImVec2(Headboxe.x, Headboxe.y), ImColor(127, 255, 0), 0.5);
					}
					else
					{
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height - Height), ImVec2(Headboxe.x, Headboxe.y), ImColor(255, 0, 0), 0.5);
					}
				}

				if (targetlines)
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(center_x, center_y), ImVec2(Headboxe.x, Headboxe.y), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), 1.f);
				}

				if (ammmoesp)
				{
					auto AmmoCount = vmread<int>(CurrentWeapon + 0xB64);

					char buffer[128];
					sprintf_s(buffer, "Ammo: %i", AmmoCount);
					if (buffer != "?")
					{
						ImVec2 DistanceTextSize = ImGui::CalcTextSize(buffer);
						DrawString(12, Headboxe.x - DistanceTextSize.x / 2, Headboxe.y + DistanceTextSize.y / 2 + 20, &Col.SilverWhite, false, false, buffer);
					}
				}


				if (Esp_distance)
				{
					char name[64];
					sprintf_s(name, "%2.fm", distance);
					DrawString(16, Headboxe.x, Headboxe.y - 15, &Col.SilverWhite, true, true, name);
				}

				if (boosterissue)
				{
					uintptr_t mesh = vmread<uintptr_t>(entity.Actor + 0x310);
					uintptr_t CurrentWeapon = vmread<uintptr_t>(settings::LocalPawn + 0x868); // FortPawn::CurrentWeapon 0x868
					vmwrite<float>(CurrentWeapon + 0x64, 70); // Actor::CustomTimeDilation 0x64
				}

				if (nigger)
				{
					vmwrite<Vector3>(mesh + 0x158, Vector3(BigPlayersScale, BigPlayersScale, BigPlayersScale));
					vmwrite<Vector3>(mesh + 0x158, Vector3(BigPlayersScale, BigPlayersScale, BigPlayersScale));
				}

				if (threeeeeed)
				{
					if (vHeadBoneOut.x != 0 || vHeadBoneOut.y != 0 || vHeadBoneOut.z != 0)
					{
						ImU32 ESPSkeleton;
						if (isVisible(entity.mesh))
						{
							ESPSkeleton = ImColor(0, 255, 0);
						}
						else if (!isVisible(entity.mesh))
						{
							ESPSkeleton = ImColor(255, 0, 0);
						}


						Vector3 bottom1 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 40, vRootBone.z));
						Vector3 bottom2 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 40, vRootBone.z));
						Vector3 bottom3 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y + 40, vRootBone.z));
						Vector3 bottom4 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y + 40, vRootBone.z));

						Vector3 top1 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y - 40, vHeadBone.z + 15));
						Vector3 top2 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y - 40, vHeadBone.z + 15));
						Vector3 top3 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y + 40, vHeadBone.z + 15));
						Vector3 top4 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y + 40, vHeadBone.z + 15));

						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ESPSkeleton, 2.0f);

						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ESPSkeleton, 2.0f);

						ImGui::GetOverlayDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ESPSkeleton, 2.0f);
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ESPSkeleton, 2.0f);
					}
				}

				if (weaponesp && settings::LocalPawn && settings::PlayerController)
				{
					auto curWep = vmread<uint64_t>(entity.Actor + 0x868);
					auto itemDef = vmread<uint64_t>(curWep + 0x3F0); // -> UFortWeaponItemDefinition -> WeaponData
					auto itemName = vmread<uintptr_t>(itemDef + 0x90);//all correct, checked not sure about second ones don't remove tier shit

					if (!itemName) continue;
					if (!itemDef) continue;
					auto bIsReloadingWeapon = vmread<bool>(curWep + 0x329);
					uint32_t StringLength = vmread<uint32_t>(itemName + 0x38);

					if (StringLength <= 32) {
						auto itemName2 = vmread<uintptr_t>(itemName + 0x30);

						auto tier = vmread<BYTE>(itemDef + 0x74);

						ImColor Color;

						if (tier == 2)
						{
							Color = IM_COL32(0, 255, 0, 255);
						}
						else if ((tier == 3))
						{
							Color = IM_COL32(0, 0, 255, 255);
						}
						else if ((tier == 4))
						{
							Color = IM_COL32(128, 0, 128, 255);
						}
						else if ((tier == 5))
						{
							Color = IM_COL32(255, 255, 0, 255);
						}
						else if ((tier == 6))
						{
							Color = IM_COL32(255, 255, 0, 255);
						}
						else if ((tier == 0) || (tier == 1))
						{
							Color = IM_COL32(255, 255, 255, 255);
						}


						if (!itemDef) continue;

						char query_cstr[100];
						size_t charsConverted;

						wchar_t* OutString = new wchar_t[uint64_t(StringLength) + 1];
						Comms::ReadProcessMemory(UDPID, (ULONG64)vmread<PVOID>(itemName + 0x30), OutString, StringLength * sizeof(wchar_t));

						wcstombs_s(&charsConverted, query_cstr, OutString, wcslen(OutString));

						const char* query_const = query_cstr;
						ImVec2 DistanceTextSize = ImGui::CalcTextSize(query_const);

						if (bIsReloadingWeapon)
							DrawString(16, bottome.x - DistanceTextSize.x / 2, bottome.y + DistanceTextSize.y / 2, &Col.SilverWhite, false, false, "Reloading");

						if (!bIsReloadingWeapon)
							DrawStringImColor(16, bottome.x - DistanceTextSize.x / 2, bottome.y + DistanceTextSize.y / 2, Color, false, false, query_cstr);
					}

				}

			}



			auto dx = w2sheade.x - (Width / 2);
			auto dy = w2sheade.y - (Height / 2);
			auto dist = sqrtf(dx * dx + dy * dy);

			if (dist < AimFOV && dist < closestDistance) {
				closestDistance = dist;
				closestPawn = entity.Actor;
			}

	}

	if (closestPawn != 0)
	{
		if (closestPawn && SonyDriverHelper::api::GetKey(aimkey))
		{
			if (Aimbot)
			{
				auto AimbotMesh = vmread<uint64_t>(closestPawn + 0x310);

				if (isVisible(AimbotMesh)) {
					Vector3 HeadPosition;
					Vector3 Head;

					if (aimbone == 0)
					{
						HeadPosition = GetBoneWithRotation(AimbotMesh, 68);
					}
					if (aimbone == 1)
					{
						HeadPosition = GetBoneWithRotation(AimbotMesh, 5);
					}
					if (aimbone == 2)
					{
						HeadPosition = GetBoneWithRotation(AimbotMesh, 2);
					}
					if (aimbone == 3)
					{
						HeadPosition = GetBoneWithRotation(AimbotMesh, 72);
					}

					Head = ProjectWorldToScreen(HeadPosition);

					if (Head.x != 0 || Head.y != 0 || Head.z != 0)
					{
						if ((GetDistance(Head.x, Head.y, Head.z, Width / 2, Height / 2) <= AimFOV))
						{
						if (Aimbot)
						{
							aimbot(Head.x, Head.y);
						}
					}
				}
			}
		}
	}
		else
		{
			closestDistance = FLT_MAX;
			closestPawn = NULL;
		}
	}
}

ImDrawList* draw;
void render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (SonyDriverHelper::api::GetKey(VK_INSERT)) 
	{
		ShowMenu = !ShowMenu;
		Sleep(200);
	}

	static int maintabs;
	static ImVec2 pos(180, 100);
	ImGui::PushFont(DefaultFont);
	ImGui::SetNextWindowSize({ 500, 500 });
	if (ShowMenu)
	{
		ImGui::Begin("pheonix", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

		ImGui::SetCursorPos({ 8.f,31.f });
		if (ImGui::Button("Aimbot", { 80,30 }))
		{
			maintabs = 0;
		}
		ImGui::SetCursorPos({ 95,31.f });
		if (ImGui::Button("Visuals", { 80, 30 }))
		{
			maintabs = 1;
		}
		ImGui::SetCursorPos({ 180,31.f });
		if (ImGui::Button("Misc", { 80,30 }))
		{
			maintabs = 2;
		}
		ImGui::SetCursorPos({ 267,31.f });
		if (ImGui::Button("Exploits", { 80,30 }))
		{
			maintabs = 3;
		}

		if (maintabs == 0)
		{
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Aimbot", &Aimbot);
			ImGui::SliderInt("Smoothness", &smooth, 1.0f, 10.0f);
			ImGui::Combo("Key", &aimkeypos, aimkeys, sizeof(aimkeys) / sizeof(*aimkeys));
			ImGui::Combo("Bone", &aimbone, aimatnotti, sizeof(aimatnotti) / sizeof(*aimatnotti));
		}

		if (maintabs == 1)
		{
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Corner Box", &Esp_corner);
			ImGui::Checkbox("Box Esp", &boxnerds);
			ImGui::Checkbox("3d Box", &threeeeeed);
			ImGui::Checkbox("Snaplines", &Esp_line);
			ImGui::Checkbox("Distance", &Esp_distance);
			ImGui::Checkbox("Target Lines", &targetlines);

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Ammo Esp", &ammmoesp);
			ImGui::Checkbox("Weapon Esp", &weaponesp);
		}

		if (maintabs == 2)
		{
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Crosshair", &crosshair);
			ImGui::Checkbox("Fov", &circle);
			ImGui::Checkbox("Filled Fov", &filledfov);
			ImGui::SliderInt("FOV", &AimFOV, 25.f, 800.f);
		}

		if (maintabs == 3)
		{
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Enable Exploits", &exploits);
			if (exploits)
			{
				ImGui::Checkbox("Spinbot", &spinbot);
				ImGui::Checkbox("Infinate Car Fuel", &fuel);
				ImGui::Checkbox("Car Fly (Shift)", &carto);
				ImGui::Checkbox("BoatSpeed", &boatspeed);
				ImGui::Checkbox("Stamina", &samenrds);
				ImGui::Checkbox("RapidFire", &boosterissue);
				ImGui::Checkbox("BIG PLAYERS", &nigger);

			}
		}

		ImGui::End();
    }

	blackballs();

	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}

}

void xMainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (SonyDriverHelper::api::GetKey(0x23) & 1)
			exit(8);

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (SonyDriverHelper::api::GetKey(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}

		render();

	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		xShutdown();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = D3dDevice->Reset(&d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void xShutdown()
{
	TriBuf->Release();
	D3dDevice->Release();
	p_Object->Release();

	DestroyWindow(Window);
	UnregisterClass((L"BlueStacks 5"), NULL);
}

DWORD GetProcessID(LPCWSTR processName) {
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	DWORD procID = NULL;

	if (handle == INVALID_HANDLE_VALUE)
		return procID;

	PROCESSENTRY32W entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(handle, &entry)) {
		if (!_wcsicmp(processName, entry.szExeFile)) {
			procID = entry.th32ProcessID;
		}
		else while (Process32NextW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);
	return procID;
}

int main()
{
	SonyDriverHelper::api::Init();
	SetConsoleTitleW(L"Chrome Browser.exe");
	if (Comms::Setup("")) {
		std::cout << "\n\n";
		std::cout << "  [driver] waiting for fortnite..";
		while (hwnd == NULL)
		{
			hwnd = FindWindowA(0, _("Fortnite  "));
			Sleep(100);
		}
		system("cls");
		std::cout << "\n\n";
		std::cout << "  [driver] found fortnite";
		UDPID = GetProcessID(L"FortniteClient-Win64-Shipping.exe");
		baseaddy = (uintptr_t)Comms::GetBaseAddress(UDPID, "FortniteClient-Win64-Shipping.exe");

		setup_window();
		xInitD3d();


		HANDLE World = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(ActorLoop), nullptr, NULL, nullptr);
		CloseHandle(World);


		xMainLoop();
		xShutdown();

	}
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            