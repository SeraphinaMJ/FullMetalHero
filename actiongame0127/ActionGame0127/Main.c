/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/
#if defined(DEBUG) | defined(_DEBUG) 
#define CRTDBG_MAP_ALLOC 
#include <stdlib.h>  
#include <crtdbg.h> 
#endif 
/******************************************************************************/
//Project-related headers
#include "Play.h"
#include "Menu.h"
#include "GameOver.h"
#include "Digipen.h"
#include "TeamLogo.h"
#include "WinGame.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <windows.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR commandLine,
	int show)
{
	//For setting window size and title
	WEInitData initData;
	//Our game data that will be shared by states
	WEGameData gData;

	WEState state;
	int stateId;

	//These are my parameters that I don't use. These need to be after
	//any data declarations.
	WEUNUSED_PARAM(prev);
	WEUNUSED_PARAM(commandLine);
	WEUNUSED_PARAM(show);

#if defined(DEBUG) | defined(_DEBUG)
	/* This will call _CrtDumpMemoryLeaks() on program exit.*/
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/*To show memory leaks in the output window */
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	/* If you have a leak, there is a number in curly braces next to the error.
	Put that number in this function and check the call stack to see when and
	where the allocation happened. Set it to -1 to have it not break.*/
	_CrtSetBreakAlloc(-1);
#endif

	//We should set up our game data values here
	gData.yourGameDataHere = 1;

	//We must set up our init app values.
	initData.fullScreen = 0;
	initData.width = 1280;
	initData.height = 720;
	initData.title = "Full Metal Hero";
	initData.instance = instance; // This is important.
	initData.gameDataSize = sizeof(WEGameData);
	initData.pGData = &gData;

	//We must init/update/shutdown the application.
	WEApplicationInit(&initData);

	//Digipen Splash
	state.pLoadFunc = DigipenLoad;
	state.pInitFunc = DigipenInit;
	state.pUpdateFunc = DigipenUpdate;
	state.pShutdownFunc = DigipenShutdown;
	state.pUnloadFunc = DigipenUnload;

	stateId = WESMAddState(&state);
	WESMSetStartState(stateId);

	//TeamLogo
	state.pLoadFunc = TeamLogoLoad;
	state.pInitFunc = TeamLogoInit;
	state.pUpdateFunc = TeamLogoUpdate;
	state.pShutdownFunc = TeamLogoShutdown;
	state.pUnloadFunc = TeamLogoUnload;

	stateId = WESMAddState(&state);

	//Menu State
	state.pLoadFunc = MenuLoad;
	state.pInitFunc = MenuInit;
	state.pUpdateFunc = MenuUpdate;
	state.pShutdownFunc = MenuShutdown;
	state.pUnloadFunc = MenuUnload;

	stateId = WESMAddState(&state); 

	//Play State
	state.pLoadFunc = PlayLoad;
	state.pInitFunc = PlayInit;
	state.pUpdateFunc = PlayUpdate;
	state.pShutdownFunc = PlayShutdown;
	state.pUnloadFunc = PlayUnload;

	stateId = WESMAddState(&state);

	state.pLoadFunc = WinGameLoad;
	state.pInitFunc = WinGameInit;
	state.pUpdateFunc = WinGameUpdate;
	state.pShutdownFunc = WinGameShutdown;
	state.pUnloadFunc = WinGameUnload;

	stateId = WESMAddState(&state);

	state.pLoadFunc = GameOverLoad;
	state.pInitFunc = GameOverInit;
	state.pUpdateFunc = GameOverUpdate;
	state.pShutdownFunc = GameOverShutdown;
	state.pUnloadFunc = GameOverUnload;

	stateId = WESMAddState(&state);
	//WESMSetStartState(stateId);


	WEApplicationUpdate();
	WEApplicationShutdown();

	return 0;
}