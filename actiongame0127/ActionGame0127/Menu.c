/******************************************************************************/
/*!
\file   Menu.c
\author Minji Kim
\par    email: seraminji2146\@gmail.com
\brief
This is the source file about Digipen Splash
*/
/******************************************************************************/

//Header file related to the implementation
#include "Menu.h"

//Project-related headers
#include "Camera.h"
#include "EMP.h"
#include "time.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>

#define NUMBER_PARTICLE 30

/*static int helloTextureId;
static int tileTextureId;
static Entity MainBody;
static MainBody testObj;
static Entity testBullet;
static TileMap map;*/

typedef void(*ButtonFunc)(void);

//set buttons
typedef struct
{
	int textureID;
	WEVec2 pos;
	WEVec2 scale;
	ButtonFunc pAction;
	unsigned char color[4];
}Button;

typedef struct
{
	int texture;
	WEVec2 pos;
	WEVec2 scale;
	WEVec2 vel;
	float rot;
	int active;
	unsigned char color[4];
}Object;

static Button buttons[4];
static Object objects[NUMBER_PARTICLE];

static int isGround = 1;
static int groundId;
static float menuTimer;
static const float duration = 0.2f;
static float buttonTimer;

//Button Functions
static void EMP_NextState(void)
{
	WESMSetNextState(EMP_Play);
}
static void EMP_QuitState(void)
{
	WESMSetQuit(1);
}

void MenuLoad(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
	//WEDEBUG_CREATE_CONSOLE();

	//buttons[0].textureID = WEGraphicsLoadTexture("Textures//Ex.tga");
	buttons[0].textureID = WEGraphicsLoadTexture("Textures//PlayMenu.tga");
	buttons[1].textureID = WEGraphicsLoadTexture("Textures//RePlay.tga");
	buttons[2].textureID = WEGraphicsLoadTexture("Textures//Credit.tga");
	groundId = WEGraphicsLoadTexture("Textures//Diamond.tga");
	WEGraphicsSetCamera(0.f, 0.f, 12.f, 0.f);

	WEGraphicsSetToOrtho();

}



void MenuInit(WEGameData* pGameData)
{
	int j = 0;
	//time_t t;
	WEUNUSED_PARAM(pGameData);
	WEGraphicsSetBackGroundColor(0.976f, 0.894f, 0.701f);
	
	////Exit button
	//buttons[0].scale.x = 300;
	//buttons[0].scale.y = 150;
	//buttons[0].pos.x   = 1280 - buttons[0].scale.x / 2;
	//buttons[0].pos.y   = 720 - buttons[0].scale.y / 2;
	//buttons[0].pAction = EMP_QuitState;

	//Get next stage
	
		buttons[0].scale.x = 150;
		buttons[0].scale.y = 100;
		buttons[0].pos.x = 1280 - (buttons[0].scale.x * 2);
		buttons[0].pos.y = 720 - (buttons[0].scale.y * 5);
		buttons[0].pAction = EMP_NextState;
	

	srand((int)time(0));
	
	for (j = 0; j < NUMBER_PARTICLE; ++j)
	{
		objects[j].texture = groundId;
		objects[j].scale.x = 25;
		objects[j].scale.y = 10;
		objects[j].vel.x = 30;
		objects[j].vel.y = -30;
		objects[j].pos.x = (float)rand();
		objects[j].pos.y = (float)rand();

		objects[j].color[0] = 255;
		objects[j].color[1] = 255;
		objects[j].color[2] = 255;
		objects[j].color[3] = 255;
		objects[j].active = 0;
	}

	buttonTimer = 0;

}

void MenuUpdate(WEGameData* pGameData, float dt)
{
	WEUNUSED_PARAM(pGameData);
	WEUNUSED_PARAM(dt);
	WEGraphicsSetToPerspective(); 
	WEGraphicsSetCamera(0, 0, 60, 0);
	WEVec2 botLeft = WEGraphicsGetWorldBotLeft();
	WEVec2 topLeft = WEGraphicsGetWorldTopLeft();
	//WEVec2 topRight = WEGraphicsGetWorldTopRight();

	WEMtx44 mtx;//for drawing objects
	WEVec2 mouse;
	int i = 0;
	int j = 0;

	WEGraphicsSetToOrtho();
	mouse.x = (float)WEInputGetMouseX();
	mouse.y = (float)WEInputGetMouseY();
	

	if (WEInputIsPressed(WE_ESCAPE))
		WESMSetQuit(1);

	//button click
	WEGraphicsConvertScreenToWorld(&mouse.x, &mouse.y);
		if (WEIntersectionPointRect(&mouse,
									&buttons[i].pos,
									buttons[i].scale.x,
									buttons[i].scale.y))
		{

			//buttons[i].scale.x = 150;
			//buttons[i].scale.y = 100;
			if (WEInputIsTriggered(WE_MOUSE_LEFT))
			{
				buttons[i].pAction();
			}


		}
		/*else if (!WEIntersectionPointRect(&mouse,
										&buttons[i].pos,
										buttons[i].scale.x,
										buttons[i].scale.y))
		{
			buttons[i].scale.x = 150;
			buttons[i].scale.y = 100;
		}

	}*/
	WEGraphicsSetAttributeColor(0xFFFFFFFF);
	WEGraphicsSetToPerspective();

	
	//buttonTimer = WEMathWrap(buttonTimer, 0.f, 255.f);
	if (buttonTimer <= 250.f)
	{
		buttonTimer++;
		for (i = 0; i < 1; i++)
		{
			buttons[i].color[0] = (unsigned char)buttonTimer;
			buttons[i].color[1] = (unsigned char)buttonTimer;
			buttons[i].color[2] = (unsigned char)buttonTimer;
			buttons[i].color[3] = (unsigned char)buttonTimer;
		}
	}
	menuTimer -= dt;

	if (menuTimer <= 0.f)
	{
		for (j = 0; j < NUMBER_PARTICLE; ++j)
		{
			if (objects[j].active == 1)
				continue;
			objects[j].pos.x = topLeft.x;
			objects[j].pos.y = botLeft.x;//botLeft.x;
			objects[j].scale.x = WERandFloatMinMax(5, 10);
			objects[j].scale.y = objects[j].scale.x;
			objects[j].vel.x = WERandFloatMinMax(15, 30);
			objects[j].vel.y = WERandFloatMinMax(15, 45);
			/*objects[i].rot.x   = WERandFloatMinMax(5.f, 10.f);
			objects[i].rot.y   = WERandFlaotMinMax(5.f, 10.f);*/

			objects[j].color[0] = (unsigned char)WERandIntMinMax(100, 255);
			objects[j].color[1] = (unsigned char)WERandIntMinMax(100, 204);
			objects[j].color[2] = (unsigned char)WERandIntMinMax(100, 170);
			objects[j].color[3] = (unsigned char)WERandIntMinMax(200, 255);
			objects[j].active = 1;
			break;
		}
		menuTimer = duration;
	}
	

	for (j = 0; j < NUMBER_PARTICLE; ++j)
	{
		if (objects[j].active == 0)
			continue;
		objects[j].pos.y = objects[j].pos.y + objects[j].vel.y * dt;
		objects[j].pos.x = objects[j].pos.x + objects[j].vel.x * dt;

		if (objects[j].pos.y > topLeft.y || objects[j].pos.x < topLeft.x)
			objects[j].active = 0;
	}

	WEGraphicsSetToPerspective();
	//WEGraphicsSetCamera(0, 0, 60, 0);

	//Draw functions objects
	WEGraphicsStartDraw();
	for (j = 0; j < NUMBER_PARTICLE; j++)
	{
		if (objects[j].active == 0)
			continue;
		WEGraphicsSetTexture(objects[j].texture);
		WEGraphicsSetAttributeColor(*(unsigned*)objects[j].color);

		WEMtx44MakeTransform(&mtx,
			objects[j].scale.x,
			objects[j].scale.y,
			objects[j].rot,
			objects[j].pos.x,
			objects[j].pos.y,
			0);
		WEGraphicsDraw(&mtx);

	}
	WEGraphicsSetAttributeColor(0xFFFFFFFF);
	WEGraphicsSetToOrtho();

	if (buttonTimer < 255)
	{
		for (i = 0; i < 1; i++)
		{
			WEGraphicsSetTexture(buttons[i].textureID);
			WEGraphicsSetAttributeColor(*(unsigned*)buttons[i].color);
			WEMtx44MakeTransform(&mtx,
				buttons[i].scale.x,
				buttons[i].scale.y,
				0,
				buttons[i].pos.x,
				buttons[i].pos.y,
				0);

			WEGraphicsDraw(&mtx);

		}
	}
	WEGraphicsSetToPerspective();
	WEGraphicsEndDraw();
}

void MenuShutdown(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
}

void MenuUnload(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);
	//WEDEBUG_DESTROY_CONSOLE();

	WEGraphicsUnloadTexture(buttons[0].textureID);
	WEGraphicsUnloadTexture(buttons[1].textureID);
	WEGraphicsUnloadTexture(buttons[2].textureID);
	WEGraphicsUnloadTexture(groundId);

}

