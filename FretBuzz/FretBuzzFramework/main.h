#pragma once
#include <fretbuzz_pch.h>
#include <system/game_startup.h>
//#include "game/scenes/gameplay_scene.h"

extern void SetStartupData(FRETBUZZ::GameStartup& a_GameStartupData);

int main(int argc, char** argv)
{
	FRETBUZZ::GameStartup m_GameStartupData;
	SetStartupData(m_GameStartupData);
	m_GameStartupData.run();
	return 0;
}