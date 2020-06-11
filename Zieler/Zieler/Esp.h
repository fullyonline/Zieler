#pragma once
#include <Windows.h>
#include "ProzessMemorie.h"
#include "Offsets.h"
#include "Structs.h"
#include "Tools.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Dwmapi.h> 
#include <TlHelp32.h>

namespace Esp
{
	void Glow(bool * p_esp, bool * p_radar);
	void Radar(bool * p_radar);
	void DrawBox(int x, int y, int width, int height, D3DCOLOR color, IDirect3DDevice9 * d3dev);
	void DrawPlayers();
	void DrawExternalEsp(bool* externalEsp);
}