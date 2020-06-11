#include "Tools.h"

namespace Tools
{
	int GetClassID(int entity) // getting classid for various things example checking for players
	{
		MemorieManager * Mem = new MemorieManager();
		DWORD dwClientNetworkable = Mem->Read<int>(entity + 0x8); // IClientNetworkable VTABLE Location
		DWORD dwGetClientClassFn = Mem->Read<int>(dwClientNetworkable + 2 * 0x4); // Third function in the vtable /GetClientClass/
		DWORD dwEntityClientClass = Mem->Read<int>(dwGetClientClassFn + 1); //pointer to ClientClass struct

		return Mem->Read<int>(dwEntityClientClass + 0x14); // actual class id
	}
}