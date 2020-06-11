#include "Main.h"

// deklarationen
bool b_running = true;
bool b_trigger = false;
bool b_bhop = false;
bool b_esp = false;
bool b_radar = false;

int main() {
	// get a pointer for thread
	bool * p_trigger = &b_trigger;
	bool * p_bhop = &b_bhop;
	bool * p_esp = &b_esp;
	bool * p_radar = &b_radar;
	/*
	-- threads
	*/
	std::thread t_trigger(Aimbot::Trigger, p_trigger);
	std::thread t_bhop(Misc::Bhop, p_bhop);
	// std::thread t_radar(Esp::Radar, p_radar);
	// std::thread t_esp(DrawPlayers, p_esp);
	std::thread t_esp(Esp::Glow, p_esp, p_radar);
	// std::thread t_skin(Skinchanger::ApplySkins);
	// Print Status once for info
	PrintStatus();
	// Main loop	
	while (b_running) {
		Sleep(10);
		// Menu
		GetKeyStrokes();
	}
	/*
	-- Aufraeumen
	*/
	t_trigger.detach();
	t_trigger.~thread();
	t_bhop.detach();
	t_bhop.~thread();
	t_esp.detach();
	t_esp.~thread();
	// t_radar.detach();
	// t_radar.~thread();
	// t_skin.detach();
	// t_skin.~thread();
	return 0;
}

void PrintStatus() {
	system("cls");
	std::cout << "To close the Hack press F11" << std::endl;
	if (b_trigger) 
	{
		std::cout << "Trigger: ON (T)" << std::endl;
	}
	else 
	{
		std::cout << "Trigger: OFF (T)" << std::endl;
	}
	if (b_esp) 
	{
		std::cout << "ESP: ON (F6)" << std::endl;
	}
	else 
	{
		std::cout << "ESP: OFF (F6)" << std::endl;
	}
	if (b_radar) 
	{
		std::cout << "Radar: ON (F7)" << std::endl;
	}
	else 
	{
		std::cout << "Radar: OFF (F7)" << std::endl;
	}
	if (b_bhop) 
	{
		std::cout << "Bunny: ON (F8)" << std::endl;
	}
	else 
	{
		std::cout << "Bunny: OFF (F8)" << std::endl;
	}
}

void GetKeyStrokes() 
{
	// zum anhalten
	if (GetAsyncKeyState(VK_F11)) 
	{
		b_running = !b_running;
		// Print Status
		PrintStatus();
		Sleep(100);
	}
	// Tigger
	if (GetAsyncKeyState(0x54)) 
	{
		//enable / disable
		b_trigger = !b_trigger;
		// Print Status
		PrintStatus();
		//warten
		Sleep(100);
	}
	// Glowingplayer
	if (GetAsyncKeyState(VK_F6)) 
	{
		//enable / disable
		b_esp = !b_esp;
		// Print Status
		PrintStatus();
		//warten
		Sleep(100);
	}
	// Radar
	if (GetAsyncKeyState(VK_F7)) 
	{
		//enable / disable
		b_radar = !b_esp;
		// Print Status
		PrintStatus();
		//warten
		Sleep(100);
	}
	// Bunnyhop
	if (GetAsyncKeyState(VK_F8)) 
	{
		//enable / disable
		b_bhop = !b_bhop;
		// Print Status
		PrintStatus();
		//warten
		Sleep(100);
	}
}
