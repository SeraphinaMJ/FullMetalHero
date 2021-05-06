/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/
#if defined(DEBUG) | defined(_DEBUG) 
#define CRTDBG_MAP_ALLOC 
#include <stdlib.h>  
#include <crtdbg.h> 
#endif 
/******************************************************************************/
#include <windows.h> //WinMain

//Include the engine functions
#include "WarpEngine.h"
#include "Play.h"

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
	WEUNUSED_PARAM(instance);

	//We should set up our game data values here
	gData.yourGameDataHere = 1;

	//We must set up our init app values.
	initData.fullScreen = 0;
	initData.width = 640;
	initData.height = 480;
	initData.title = "PhysicsEngine";
	initData.instance = instance; // This is important.
	initData.gameDataSize = sizeof(WEGameData);
	initData.pGData = &gData;

	//We must init/update/shutdown the application.
	WEApplicationInit(&initData);

	//I must add my states here.
	state.pLoadFunc = PlayLoad;
	state.pInitFunc = PlayInit;
	state.pUpdateFunc = PlayUpdate;
	state.pShutdownFunc = PlayShutdown;
	state.pUnloadFunc = PlayUnload;

	stateId = WESMAddState(&state); // WarpEngineStateManager
	WESMSetStartState(stateId);

	WEAppliationUpdate();
	WEAppliationShutdown();

	return 0;
}