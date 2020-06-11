#include "Aimbot.h"

namespace Aimbot
{
	void Trigger(bool * p_trigger) {
		MemorieManager * Mem = new MemorieManager();
		// Local Resurces
		DWORD LocalPlayer_Base;
		int LocalPlayer_inCrosshair;
		int LocalPlayer_Team;
		DWORD EntityList_EntityBase;
		int EntityTeam;
		bool EntityDormant;
		int Punch;
		while (true) {
			// read
			LocalPlayer_Base = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer);
			LocalPlayer_inCrosshair = Mem->Read<int>(LocalPlayer_Base + hazedumper::netvars::m_iCrosshairId);
			LocalPlayer_Team = Mem->Read<int>(LocalPlayer_Base + hazedumper::netvars::m_iTeamNum);
			// aimpunch velocity
			Punch = Mem->Read<int>(Mem->ClientDLL_Base + hazedumper::netvars::m_aimPunchAngle);
			// std::cout << "Punch:" << Punch << std::endl;
			// Entitaet erhalten
			EntityList_EntityBase = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwEntityList + ((LocalPlayer_inCrosshair - 1) * 0x10));
			EntityTeam = Mem->Read<int>(EntityList_EntityBase + hazedumper::netvars::m_iTeamNum);
			// Muss ins UPDATE
			EntityDormant = Mem->Read<bool>(EntityList_EntityBase + iDormant);
			/*
			--- Schiessen
			*/
			if ((LocalPlayer_inCrosshair > 0 && LocalPlayer_inCrosshair <= 64) && (EntityList_EntityBase != NULL) && (EntityTeam != LocalPlayer_Team) && (!EntityDormant) && (*p_trigger) && GetAsyncKeyState(VK_XBUTTON2) == -32768) {
				// schiessen Extern
				// std::cout << "shoot" << std::endl;
				mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
				Sleep(20); // delay waehrend den Events
				mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
				Sleep(200); // delay nach dem Event
				//schiessen mit mem write
				//Sleep(50); //Delay before shooting
				//Mem->Write<int>(Mem->ClientDLL_Base + m_dwForceAttack, 5);
				//Sleep(20); //Delay between shots
				//Mem->Write<int>(Mem->ClientDLL_Base + m_dwForceAttack, 4);
				//Sleep(200); //Delay after shooting
			}
		}
	}
}