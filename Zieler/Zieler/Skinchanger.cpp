#include "Skinchanger.h"

namespace Skinchanger
{
	//Skinchanger method
	void ApplySkins()
	{
		MemorieManager* Mem = new MemorieManager();

		int WeaponID_Previous = NULL;
		int WeaponID = NULL;
		int WeapPrev = NULL;
		bool once = false;
		while (true)
		{
#pragma region READ INFOS ABOUT WEAPON
			DWORD Player = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer);
			DWORD WeaponIndex = Mem->Read<DWORD>(Player + hazedumper::netvars::m_hActiveWeapon) & 0xFFF;
			DWORD WeapEnt = Mem->Read<DWORD>((Mem->ClientDLL_Base + hazedumper::signatures::dwEntityList + WeaponIndex * EntLoopDist) - EntLoopDist);
			WeaponID = Mem->Read<int>(WeapEnt + hazedumper::netvars::m_iItemDefinitionIndex);
			int WeaponAccountID = Mem->Read<int>(WeapEnt + iAccountID);
			int MyAccountID = Mem->Read<int>(WeapEnt + hazedumper::netvars::m_OriginalOwnerXuidLow);
			/*
			DWORD Player = Mem->Read<DWORD>(Mem->ClientDLL_Base + dwLocalPlayer);
			DWORD WeaponIndex = Mem->Read<DWORD>(Player + hActiveWeapon) & 0xFFF;
			DWORD WeapEnt = Mem->Read<DWORD>((Mem->ClientDLL_Base + dwEntityList + WeaponIndex * EntLoopDist) - EntLoopDist);
			WeaponID = Mem->Read<int>(WeapEnt + iItemDefinitionIndex);
			int WeaponAccountID = Mem->Read<int>(WeapEnt + iAccountID);
			int MyAccountID = Mem->Read<int>(WeapEnt + OriginalOwnerXuidLow);
			*/
#pragma endregion

#pragma region SET WEAPONID_PREVIOUS
			if (WeaponID != WeaponID_Previous && !once)
			{
				WeaponID_Previous = WeaponID;
				ForceFullUpdate();
				once = true;
			}
#pragma endregion

			if (WeaponID != WeapPrev)
			{
				WeapPrev = WeaponID;
				ForceFullUpdate();
			}

#pragma region FORCES THE FALLBACK VALUES OF THE WEAPON

			//Force ItemIDLow = -1
			Mem->Write<int>(WeapEnt + iItemIDHigh, -1);


			//Force the PaintKit value to be our PaintKit
			//ak
			if (WeaponID == WEAPON_AK47) {
				Mem->Write<int>(WeapEnt + hazedumper::netvars::m_nFallbackPaintKit, 180);
			}
			//M4
			if (WeaponID == WEAPON_M4A1) {
				Mem->Write<int>(WeapEnt + hazedumper::netvars::m_nFallbackPaintKit, 309);
			}
			//usp
			if (WeaponID == WEAPON_USP_SILENCER) {
				Mem->Write<int>(WeapEnt + hazedumper::netvars::m_nFallbackPaintKit, 25);
			}
			//glock
			if (WeaponID == WEAPON_GLOCK) {
				Mem->Write<int>(WeapEnt + hazedumper::netvars::m_nFallbackPaintKit, 38);
			}
			//deagle
			if (WeaponID == WEAPON_DEAGLE) {
				Mem->Write<int>(WeapEnt + hazedumper::netvars::m_nFallbackPaintKit, 37);
			}
			//knife
			if (WeaponID == WEAPON_KNIFE || WeaponID == WEAPON_KNIFE_T) {
				Mem->Write<int>(WeapEnt + hazedumper::netvars::m_nFallbackPaintKit, 59);
			}

			//Force AccountID to solve StatTrak problem
			Mem->Write<int>(WeapEnt + iAccountID, MyAccountID);

#pragma endregion

			Sleep(20);
		}
	}

	//For skinchanger
	void ForceFullUpdate()
	{
		MemorieManager * Mem = new MemorieManager();
		DWORD _dwClientState = Mem->Read<DWORD>(Mem->EngineDLL_Base + hazedumper::signatures::dwClientState);
		Mem->Write<int>(_dwClientState + 0x16C, -1);
	}
	/*
	void Skins(bool * skins)
	{
		MemorieManager* Mem = new MemorieManager();

		while (true)
		{
			Sleep(3);

			if (!*skins)
				continue;

			int overrideTexture;

			int statTrak;

			int itemDefinition;

			for (int i = 1; i < 16; ++i)
			{
				DWORD LocalPlayer = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer);

				DWORD MyWeapons = Mem->Read<int>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer + hazedumper::netvars::m_hMyWeapons + (i - 1) * 0x4) & 0xFFF;

				DWORD m_iBase = Mem->Read<int>(Mem->ClientDLL_Base + hazedumper::signatures::dwEntityList + (MyWeapons - 1) * 0x10);

				DWORD m_iItemDefinitionIndex = Mem->Read<int>(m_iBase + hazedumper::netvars::m_iItemDefinitionIndex);

				DWORD m_iXuIDLow = Mem->Read<int>(m_iBase + hazedumper::netvars::m_OriginalOwnerXuidLow);

				DWORD m_iTexture = Mem->Read<int>(m_iBase + hazedumper::netvars::m_nFallbackPaintKit);

				switch (m_iItemDefinitionIndex)
				{
					// RIFLES

				case (int)WEAPON_AK47:
					overrideTexture = Settings.Skinchanger.WEAPON_AK47;
					statTrak = -1;
					itemDefinition = (int)WEAPON_AK47;
					break;

				case (int)WEAPON_AUG:
					overrideTexture = Settings.Skinchanger.WEAPON_AUG;
					statTrak = -1;
					itemDefinition = (int)WEAPON_AUG;
					break;

				case (int)WEAPON_AWP:
					overrideTexture = Settings.Skinchanger.WEAPON_AWP;
					statTrak = -1;
					itemDefinition = (int)WEAPON_AWP;
					break;

				case (int)WEAPON_BIZON:
					overrideTexture = Settings.Skinchanger.WEAPON_BIZON;
					statTrak = -1;
					itemDefinition = (int)WEAPON_BIZON;
					break;

				case (int)WEAPON_FAMAS:
					overrideTexture = Settings.Skinchanger.WEAPON_FAMAS;
					statTrak = -1;
					itemDefinition = (int)WEAPON_FAMAS;
					break;

				case (int)WEAPON_G3SG1:
					overrideTexture = Settings.Skinchanger.WEAPON_G3SG1;
					statTrak = -1;
					itemDefinition = (int)WEAPON_G3SG1;
					break;

				case (int)WEAPON_GALILAR:
					overrideTexture = Settings.Skinchanger.WEAPON_GALILAR;
					statTrak = -1;
					itemDefinition = (int)WEAPON_GALILAR;
					break;

				case (int)WEAPON_M4A1:
					overrideTexture = Settings.Skinchanger.WEAPON_M4A1;
					statTrak = -1;
					itemDefinition = (int)WEAPON_M4A1;
					break;

				case (int)WEAPON_SCAR20:
					overrideTexture = Settings.Skinchanger.WEAPON_SCAR20;
					statTrak = -1;
					itemDefinition = (int)WEAPON_SCAR20;
					break;

				case (int)WEAPON_SG556:
					overrideTexture = Settings.Skinchanger.WEAPON_SG556;
					statTrak = -1;
					itemDefinition = (int)WEAPON_SG556;
					break;

				case (int)WEAPON_SSG08:
					overrideTexture = Settings.Skinchanger.WEAPON_SSG08;
					statTrak = -1;
					itemDefinition = (int)WEAPON_SSG08;
					break;

				case (int)WEAPON_M4A1_SILENCER:
					overrideTexture = Settings.Skinchanger.WEAPON_M4A1_SILENCER;
					statTrak = -1;
					itemDefinition = (int)WEAPON_M4A1_SILENCER;
					break;

					#endregion

						#region SMG

				case (int)WEAPON_MAC10:
					overrideTexture = Settings.Skinchanger.WEAPON_MAC10;
					statTrak = -1;
					itemDefinition = (int)WEAPON_MAC10;
					break;

				case (int)WEAPON_P90:
					overrideTexture = Settings.Skinchanger.WEAPON_P90;
					statTrak = -1;
					itemDefinition = (int)WEAPON_P90;
					break;

				case (int)WEAPON_UMP45:
					overrideTexture = Settings.Skinchanger.WEAPON_UMP45;
					statTrak = -1;
					itemDefinition = (int)WEAPON_UMP45;
					break;

				case (int)WEAPON_MP7:
					overrideTexture = Settings.Skinchanger.WEAPON_MP7;
					statTrak = -1;
					itemDefinition = (int)WEAPON_MP7;
					break;

				case (int)WEAPON_MP9:
					overrideTexture = Settings.Skinchanger.WEAPON_MP9;
					statTrak = -1;
					itemDefinition = (int)WEAPON_MP9;
					break;

					#endregion

						#region HEAVY

				case (int)WEAPON_NEGEV:
					overrideTexture = Settings.Skinchanger.WEAPON_NEGEV;
					statTrak = -1;
					itemDefinition = (int)WEAPON_NEGEV;
					break;

				case (int)WEAPON_M249:
					overrideTexture = Settings.Skinchanger.WEAPON_M249;
					statTrak = -1;
					itemDefinition = (int)WEAPON_M249;
					break;

					#endregion

						#region PISTOLS

				case (int)WEAPON_DEAGLE:
					overrideTexture = Settings.Skinchanger.WEAPON_DEAGLE;
					statTrak = -1;
					itemDefinition = (int)WEAPON_DEAGLE;
					break;

				case (int)WEAPON_ELITE:
					overrideTexture = Settings.Skinchanger.WEAPON_ELITE;
					statTrak = -1;
					itemDefinition = (int)WEAPON_ELITE;
					break;

				case (int)WEAPON_FIVESEVEN:
					overrideTexture = Settings.Skinchanger.WEAPON_FIVESEVEN;
					statTrak = -1;
					itemDefinition = (int)WEAPON_FIVESEVEN;
					break;

				case (int)WEAPON_GLOCK:
					overrideTexture = Settings.Skinchanger.WEAPON_GLOCK;
					statTrak = -1;
					itemDefinition = (int)WEAPON_GLOCK;
					break;

				case (int)WEAPON_TEC9:
					overrideTexture = Settings.Skinchanger.WEAPON_TEC9;
					statTrak = -1;
					itemDefinition = (int)WEAPON_TEC9;
					break;

				case (int)WEAPON_HKP2000:
					overrideTexture = Settings.Skinchanger.WEAPON_HKP2000;
					statTrak = -1;
					itemDefinition = (int)WEAPON_HKP2000;
					break;

				case (int)WEAPON_USP_SILENCER:
					overrideTexture = Settings.Skinchanger.WEAPON_USP_SILENCER;
					statTrak = -1;
					itemDefinition = (int)WEAPON_USP_SILENCER;
					break;

				case (int)WEAPON_CZ75A:
					overrideTexture = Settings.Skinchanger.WEAPON_CZ75A;
					statTrak = -1;
					itemDefinition = (int)WEAPON_CZ75A;
					break;

				case (int)WEAPON_REVOLVER:
					overrideTexture = Settings.Skinchanger.WEAPON_REVOLVER;
					statTrak = -1;
					itemDefinition = (int)WEAPON_REVOLVER;
					break;

				case (int)WEAPON_P250:
					overrideTexture = Settings.Skinchanger.WEAPON_P250;
					statTrak = -1;
					itemDefinition = (int)WEAPON_P250;
					break;

					#endregion

						#region SHOTGUNS

				case (int)WEAPON_XM1014:
					overrideTexture = Settings.Skinchanger.WEAPON_XM1014;
					statTrak = -1;
					itemDefinition = (int)WEAPON_XM1014;
					break;

				case (int)WEAPON_MAG7:
					overrideTexture = Settings.Skinchanger.WEAPON_MAG7;
					statTrak = -1;
					itemDefinition = (int)WEAPON_MAG7;
					break;

				case (int)WEAPON_SAWEDOFF:
					overrideTexture = Settings.Skinchanger.WEAPON_SAWEDOFF;
					statTrak = -1;
					itemDefinition = (int)WEAPON_SAWEDOFF;
					break;

				case (int)WEAPON_NOVA:
					overrideTexture = Settings.Skinchanger.WEAPON_NOVA;
					statTrak = -1;
					itemDefinition = (int)WEAPON_NOVA;
					break;

					#endregion

				default:
					overrideTexture = 1337;
					statTrak = 1337;
					itemDefinition = 1337;
					break;
				}

				if (Structs.Weapons.m_iTexture != overrideTexture && overrideTexture != 1337)
				{
					Memory.WriteMemory<int>(Structs.Weapons.m_iBase + Offsets.m_iItemIDHigh, -1);
					Memory.WriteMemory<int>(Structs.Weapons.m_iBase + Offsets.m_nFallbackPaintKit, overrideTexture);
					Memory.WriteMemory<int>(Structs.Weapons.m_iBase + Offsets.m_nFallbackSeed, 661);
					Memory.WriteMemory<int>(Structs.Weapons.m_iBase + Offsets.m_nFallbackStatTrak, statTrak);
					Memory.WriteMemory<float>(Structs.Weapons.m_iBase + Offsets.m_flFallbackWear, 0.000000001f);
					Memory.WriteMemory<int>(Structs.Weapons.m_iBase + Offsets.m_iAccountID, Structs.Weapons.m_iXuIDLow);
					Memory.WriteMemory<int>(Structs.Weapons.m_iBase + Offsets.m_iItemDefinitionIndex, itemDefinition);

					cl_fullupdate();
				}
			}
		}


	}
	*/
}