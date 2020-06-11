#include "Misc.h"

namespace Misc
{
	void Bhop(bool * p_bhop) {
		MemorieManager * Mem = new MemorieManager();
		// Local Resurces
		DWORD LocalPlayer_Base;
		DWORD EntityList;
		bool EntityDormant;
		int flag;
		while (true) 
		{
			Sleep(20);
			LocalPlayer_Base = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer);
			
			EntityDormant = Mem->Read<bool>(EntityList + iDormant);
			// Player zustand
			flag = Mem->Read<int>(LocalPlayer_Base + hazedumper::netvars::m_fFlags);
			if ((*p_bhop) && (GetAsyncKeyState(VK_SPACE) == -32768) && (flag == 257)) {
				// +Jump
				Mem->Write(Mem->ClientDLL_Base + hazedumper::signatures::dwForceJump, 1);
				Sleep(50);
				// -Jump
				Mem->Write(Mem->ClientDLL_Base + hazedumper::signatures::dwForceJump, 0);
			}
		}
	}
}