/******************************************************************************/
/*!
\file   GameOver.c
\author Minji Kim
\par    email: seraminji2146\@gmail.com
\brief
This is the source file about GameOver
*/
/******************************************************************************/

//Header file related to the implementation
#include "GameOver.h"

//Project-related headers
#include "Camera.h"
#include "EMP.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>


static int GameOverId;
typedef void(*OverButton)(void);

typedef struct
{
	int textureID;
	WEVec2 pos;
	WEVec2 scale;
	OverButton pGoMenu;

}BackButton;

static BackButton backButtons[1];
static  int GoMenu = 0;

static void EMP_NextSate(void)
{
	WESMSetNextState(EMP_Menu);
}
static void EMP_QuitState(void)
{
	WESMSetQuit(1);
}

void GameOverLoad(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);

	backButtons[0].textureID = WEGraphicsLoadTexture("Textures//Menu.tga");
	GameOverId = WEGraphicsLoadTexture("Textures//GameOver.tga");

	WEGraphicsSetCamera(0.f, 0.f, 12.f, 0.f);
	//WEGraphicsSetOrtho();

}

void GameOverInit(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
	WEGraphicsSetBackGroundColor(0.976f, 0.894f, 0.701f);

	backButtons[0].scale.x = 350;
	backButtons[0].scale.y = 100;
	backButtons[0].pos.x = backButtons[0].scale.x / 2;
	backButtons[0].pos.y = backButtons[0].scale.y / 2;
	backButtons[0].pGoMenu = EMP_NextSate;

}

void GameOverUpdate(WEGameData* pGameData, float dt)
{
	WEUNUSED_PARAM(pGameData);
	WEUNUSED_PARAM(dt);
	
	//WEMtx44 transform;
	WEMtx44 mtx;

	WEVec2 GameOverMouse;
	int loop = 0;

	WEGraphicsSetToOrtho();
	GameOverMouse.x = (float)WEInputGetMouseX();
	GameOverMouse.y = (float)WEInputGetMouseY();

	if (WEInputIsPressed(WE_ESCAPE))
		WESMSetQuit(1);

	WEGraphicsConvertScreenToWorld(&GameOverMouse.x, &GameOverMouse.y);
	for (loop = 0; loop < 1; ++loop)
	{
		if (WEIntersectionPointRect(&GameOverMouse,
			&backButtons[loop].pos,
			backButtons[loop].scale.x,
			backButtons[loop].scale.y))
		{
			backButtons[loop].scale.x = 350;
			backButtons[loop].scale.y = 100;
			if (WEInputIsTriggered(WE_MOUSE_LEFT))
			{
				backButtons[loop].pGoMenu();
			}

		}
		/*else if (!WEIntersectionPointRect(&GameOverMouse,
			&backButtons[loop].pos,
			backButtons[loop].scale.x,
			backButtons[loop].scale.y))
		{
			backButtons[loop].scale.x = 300;
			backButtons[loop].scale.y = 150;
		}*/
	}
	WEGraphicsSetToPerspective();
	WEGraphicsSetCamera(0, 0, 60, 0);

	WEGraphicsStartDraw();
	WEGraphicsSetToOrtho();


	for (loop = 0; loop <1; loop++)
	{
		WEGraphicsSetTexture(backButtons[loop].textureID);
		WEMtx44MakeTransform(&mtx,
			backButtons[loop].scale.x,
			backButtons[loop].scale.y,
			0,
			backButtons[loop].pos.x,
			backButtons[loop].pos.y,
			0);

		/*All Draw code must goes here*/
		WEGraphicsDraw(&mtx);

	}
	WEGraphicsSetTexture(GameOverId);
	WEMtx44MakeTransform(&mtx, 600.f, 250.f, 0.0f,
		(float)WEApplicationGetWidth() - 600.f,
		(float)WEApplicationGetHeight() - 300, 0.0f);
	WEGraphicsDraw(&mtx);


	WEGraphicsSetToPerspective();
	WEGraphicsEndDraw();


}

void GameOverShutdown(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
}

void GameOverUnload(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);

	WEGraphicsUnloadTexture(backButtons[0].textureID);
	WEGraphicsUnloadTexture(GameOverId);
}

