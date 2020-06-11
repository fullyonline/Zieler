#include "Esp.h"

namespace Esp
{
	void Radar(bool * p_radar)
	{
		MemorieManager * Mem = new MemorieManager();

		while (true)
		{
			Sleep(40);
			for (int i = 1; i < 64; i++)
			{
				int dwEntity = Mem->Read<int>(Mem->ClientDLL_Base + hazedumper::signatures::dwEntityList + i * 0x10); // looping through 64 entitys in the list
				bool dormant = Mem->Read<bool>(dwEntity + iDormant); // getting the entitys dormant status and saving it in our boolean
				DWORD LocalPlayer = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer);
				int MyTeam = Mem->Read<int>(LocalPlayer + hazedumper::netvars::m_iTeamNum);

				if (dormant) continue; // continue if entity is dormant

				int pEntTeam = Mem->Read<int>(dwEntity + hazedumper::netvars::m_iTeamNum); // getting the entityteamnum and saving it in our integer

				if (pEntTeam == MyTeam) continue; // continue if the entitys teamnumber equals our localplayers one

				Mem->Write<int>(dwEntity + hazedumper::netvars::m_bSpotted, true); // writting bspotted to true to achieve a ingameradar

			}
		}
	}

	void Glow(bool * p_esp, bool * p_radar) {

		MemorieManager * Mem = new MemorieManager();
					
		while (true) {

			if (*p_esp) //|| *p_radar 
			{
				DWORD LocalPlayer = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwLocalPlayer);

				DWORD GlowObjManager = Mem->Read<DWORD>(Mem->ClientDLL_Base + hazedumper::signatures::dwGlowObjectManager);

				for (int i = 0; i < 64; i++) {


					int GlowCurrentPlayer = Mem->Read< int >(Mem->ClientDLL_Base + hazedumper::signatures::dwEntityList + ((i - 1) * 16));
					
					bool dormant = Mem->Read<bool>(GlowCurrentPlayer + iDormant); // getting the entitys dormant status and saving it in our boolean

					int GlowCurrentPlayerTeam = Mem->Read< int >(GlowCurrentPlayer + hazedumper::netvars::m_iTeamNum);

					int GlowCurrentPlayerIndex = Mem->Read< int >(GlowCurrentPlayer + hazedumper::netvars::m_iGlowIndex);

					int GlowCurrentPlayerFlashed = Mem->Read< int >(GlowCurrentPlayer + hazedumper::netvars::m_flFlashDuration);

					int myTeam = Mem->Read<int>(LocalPlayer + hazedumper::netvars::m_iTeamNum);
					
					/*
					if (*p_radar && myTeam != GlowCurrentPlayerTeam && !dormant)
					{
						Mem->Write<int>(GlowCurrentPlayer + hazedumper::netvars::m_bSpotted, true); // writting bspotted to true to achieve a ingameradar
					}
					*/

					if (myTeam != GlowCurrentPlayerTeam && *p_esp) // && Tools::GetClassID(GlowCurrentPlayer) == 38
					{

						Mem->Write< float >((GlowObjManager + ((GlowCurrentPlayerIndex * 0x38) + 0x4)), 1.f);
						Mem->Write< float >((GlowObjManager + ((GlowCurrentPlayerIndex * 0x38) + 0x8)), 0.f);
						Mem->Write< float >((GlowObjManager + ((GlowCurrentPlayerIndex * 0x38) + 0xC)), 0.f);
						Mem->Write< float >((GlowObjManager + ((GlowCurrentPlayerIndex * 0x38) + 0x10)), 0.49f);
						Mem->Write< BOOL >((GlowObjManager + ((GlowCurrentPlayerIndex * 0x38) + 0x24)), true);
						Mem->Write< BOOL >((GlowObjManager + ((GlowCurrentPlayerIndex * 0x38) + 0x25)), false);

					}
				}
			}

			Sleep(1);

		}

	}

	void DrawExternalEsp(bool * externalEsp) // flickert / ungenau auch mit DirectX --> internal ist besser
	{

	}

	void DrawPlayers()
	{

	}

	void DrawBox(int x, int y, int width, int height, D3DCOLOR color, IDirect3DDevice9 * d3dev)
	{
		D3DRECT rect = { x, y, 1, 1 };
		d3dev->Clear(1, &rect, D3DCLEAR_TARGET, color, 1.0f, NULL);
	}
}