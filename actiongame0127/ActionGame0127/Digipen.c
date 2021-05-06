/******************************************************************************/
/*!
\file   Digipen.c
\author Minji Kim
\par    email: seraminji2146\@gmail.com
\brief
This is the source file about Digipen Splash
*/
/******************************************************************************/
//Header file related to the implementation
#include "Digipen.h"

//Project-related headers
#include "Camera.h"
#include "EMP.h"

//Standard library headers
#include <stdlib.h>

#define MAX_TIME 1.f

static int DigipenLogoId;
static 	float timer = 0;

static void EMP_QuitState(void)
{
	WESMSetQuit(1);
}

void DigipenLoad(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
	WEDEBUG_CREATE_CONSOLE();
	DigipenLogoId = WEGraphicsLoadTexture("Textures//DigiLogo.tga");
	WEGraphicsSetCamera(0.f, 0.f, 12.f, 0.f);
	//WEApplicationSetFullScreen(1);
}

void DigipenInit(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
	WEGraphicsSetBackGroundColor(0.976f, 0.894f, 0.701f);
	
}

void DigipenUpdate(WEGameData* pGameData, float dt)
{
	WEUNUSED_PARAM(pGameData);
	WEUNUSED_PARAM(dt);

	//WEMtx44 transform;
	WEMtx44 mtx;


	if (WEInputIsPressed(WE_ESCAPE))
		WESMSetQuit(1);
	timer += dt;
	if (timer > MAX_TIME)
	{
		WESMSetNextState(EMP_TeamLogo);
	}

	WEGraphicsStartDraw();
	WEGraphicsSetToOrtho();

	WEGraphicsSetTexture(DigipenLogoId);
	WEMtx44MakeTransform(&mtx, 1100.f, 300.f, 0.0f,
		(float)WEApplicationGetWidth() /2,
		(float)WEApplicationGetHeight() /2, 0.0f);
	WEGraphicsDraw(&mtx);

	WEGraphicsSetToPerspective();
	WEGraphicsEndDraw();
}
void DigipenShutdown(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
}
void DigipenUnload(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);

	WEGraphicsUnloadTexture(DigipenLogoId);
}
