//Header file related to the implementation
#include "Play.h"

//Project-related headers
#include "Camera.h"
#include "PhysicsUtil.h"
#include "Enemy.h"
#include "UpperBody.h"
#include "EMP.h"
#include "soundmanager.h"
#include "Emitter.h"
#include "PS.h"
#include "EntityManager.h"
#include "Play.h"
#include "Entity.h"
//#include "MainBody.h"
#include "TileMap.h"
#include "Emitter.h"
#include "Player.h"
#include "TextureList.h"
#include "BulletList.h"
#include "Hp.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>


/*lllllllllllllllll*/
#define DEADLINE 1400
#define LEFTSTATICBAR 1160.f
#define WE_ANI_TIMER .1f
//static float transWidth = 1200.f;


static int upperBodyTextureId;
//static int lowerBodyTextureId;
static int starTextureId;
static int helloTextureId;
static int jumpTextureId;
static int BarTextureId;
static int LifeBarTextureId;
static int bulletTextureId;
static int mainbodyTextureId;
//static float textCoord;
//static float totalTime;
static TileMap map;

static float MainBodyCoord = 0.f;

static void EMP_NextState(void)
{
	WESMSetNextState(EMP_GameOver);
}

void PlayLoad(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);

	
	SoundManager_Create();
	SoundManager_LoadSound("Sounds//bgm1.mp3");
	SoundManager_LoadSound("Sounds//shoot_sound.mp3");

	//Initialize TextureList
	TextureList_Init();
	TextureList_LoadTexture("Textures//MachineGun_Bullet.tga", TX_BULLET);
	TextureList_LoadTexture("Textures//EnemyBullet.tga", TX_ENEMY_BULLET);
	TextureList_LoadTexture("Textures//Player_UpperBody.tga", TX_PLAYER_UPPERBODY);
	TextureList_LoadTexture("Textures//Player_MainBody.tga", TX_PLAYER_MAINBODY);
	TextureList_LoadTexture("Textures//OutBoss.tga", TX_BOSS);
	TextureList_LoadTexture("Textures//InBoss.tga", TX_BOSS_BAR);
	TextureList_LoadTexture("Textures//circle.tga", TX_CIRCLE);
	TextureList_LoadTexture("Textures//Test.tga", TX_PS_TEST);
	TextureList_LoadTexture("Textures//Eyes.tga", TX_BOSS_EYE);
	TextureList_LoadTexture("Textures//Tile.tga", TX_TILE_SOLID);
	TextureList_LoadTexture("Textures//TileOneWay.tga", TX_TILE_ONEWAY);

	//starTextureId = WEGraphicsLoadTexture("Textures//Star.tga");
	helloTextureId = WEGraphicsLoadTexture("Textures//Hello.tga");
	jumpTextureId = WEGraphicsLoadTexture("Textures//Jump.tga");
	BarTextureId = WEGraphicsLoadTexture("Textures//Bar.tga");
	LifeBarTextureId = WEGraphicsLoadTexture("Textures//LifeBar.tga");
	

	//lowerBodyTextureId = WEGraphicsLoadTexture("Textuers//EMP.tga");
	mainbodyTextureId = WEGraphicsLoadTexture("Textures//mainbody.tga");

	NewTileMapFromFile(&map, 0, 0, TextureList_GetID(TX_TILE_SOLID), 
		TextureList_GetID(TX_TILE_ONEWAY), "mapdata.txt");

	//WEGraphicsSetCamera(0.f, 0.f, 12.f, 0.f);
}
void PlayInit(WEGameData* pGameData)
{
	WEGraphicsSetBackGroundColor(0.917f, 0.815f, 0.713f);
	//WEDEBUG_CREATE_CONSOLE();

	WEGraphicsSetTexture(TextureList_GetID(TX_PLAYER_MAINBODY));
	//WEGraphicsSetAttributeColor4(0, 85, 85, 255);

	//camera Initialize
	CameraInit(&map,
		/*manager.pPlayer->mainBody.base.pos.x,
		manager.pPlayer->mainBody.base.pos.y*/
		TileCoordsToWorldX(&map, 17), 0.f);

	MakeEntityManager(&map);
	//textCoord = 0.0f;
	//totalTime = 0.0f;
	
	


	SoundManager_PlaySound(BGM_1);
	ParticleSystemInit();
	
	//////////////////////////////////////////
	//Test for EntityList/////////////////////
	//////////////////////////////////////////

	//MakeEnemy(&objectA, 5, 5, -4.f, 0.f, 5.f, 5.f, 3.f, 20.f, helloTextureId, &testObj);

	//////////////////////////////////////////
	//HACOMPU/////////////////////////////////
	//////////////////////////////////////////

	WEUNUSED_PARAM(pGameData);

}
void PlayUpdate(WEGameData* pGameData, float dt)
{
	WEUNUSED_PARAM(pGameData);
	//Quit if MainBody presses spacebar.
	if (WEInputIsPressed(WE_ESCAPE))
		WESMSetQuit(1);

	//totalTime += dt;
	///*Update state logic*/
	//if (totalTime > WE_ANI_TIMER)
	//{
	//	totalTime = 0.0f;
	//	textCoord += .25f;
	//	WEMathWrap(textCoord, 0.0f, 1.0f);
	//}


	EntityManager_Update(&map, dt);
	/**************** For testing (yeongjin) *********/
	/*************************************************/

	//Collide(&testObj, &testBullet);
	//testObj.UpdateSM(&testObj, dt);
	//objectA.Update(&objectA, dt);
	//UpdateVelocity(&map, &testObj.base, dt);
	//Physics_CollideAndUpdateVelocity(&list, &map, dt);
	////////////////////////////////////////////////
	//WEGraphicsSetCamera(testObj.base.pos.x, testObj.base.pos.y, 7.f, 0.f);
	//if(objectA.base.life > 0)
	//Physics_MainBodyVsEnemy(&testObj, &objectA);

	/**************** For testing (yeongjin) *********/
	/*upperBody.Update(&upperBody, &testObj);
	upperBody.UpdateSM(&upperBody, dt);
	upperBody.AimController(&upperBody);*/

	//BulletCollision(&manager.pUpperBody->bulletManager, &map, &manager.enemies);
	BulletUpdate(&map, GetEntityManager(), dt);
	ParticleSystemUpdate(dt);

	CameraUpdate(/*manager.pPlayer->mainBody.base.pos.x, */
				 /*pPlayer->mainBody.base.pos.x,*/
				 dt);
	PlayDraw();
	//TileCoordsToWorldX(&map, map.width-1);

	BulletDelete();

}

void PlayDraw(void)
{
	//WEMtx44 transform;
	WEGraphicsSetToPerspective();
	WEGraphicsStartDraw();


	BulletDraw();
	DrawTileMap(&map);

	EntityManager_Draw();

	// Particle Draw Function
	ParticleSystemDraw();

	//Draw the tile map.

	//////////////////////////////////////////
	//HACOMPU/////////////////////////////////
	//////////////////////////////////////////
	
	
	//Life HUD////////////////////////////////////////////////////////////////////////
	MainBodyCoord += 0.1f;
	MainBodyCoord = WEMathWrap(MainBodyCoord, 0, 1);
	/*Draw main character*/
	WEGraphicsSetTexture(bulletTextureId);
	WEGraphicsSetAttributeColor(0xFFFFFFFF);

	/*WEGraphicsSetToOrtho();
	//Red Bar
	WEGraphicsSetTexture(BarTextureId);
	WEMtx44MakeTransform(&transform, GetEntityManager()->pPlayer->hp * 4.f, 25.f, 0.0f,
		(float)WEApplicationGetWidth() - 1250.f,
		(float)WEApplicationGetHeight() - 50, 0.0f);
	WEGraphicsSetAttributeColor(0xffffffff);
	WEGraphicsDraw(&transform);

	//Gray life bar
	WEGraphicsSetTexture(LifeBarTextureId);
	WEMtx44MakeTransform(&transform, 250.f, 50.f, 0.0f,
		(float)WEApplicationGetWidth() - LEFTSTATICBAR,
		(float)WEApplicationGetHeight() - 50, 0.0f);
	WEGraphicsDraw(&transform);


	//Boss Bar
	WEGraphicsSetTexture(TextureList_GetID(TX_BOSS_BAR));
	WEMtx44MakeTransform(&transform, ratio, 30.f, 0.0f,
		transX,
		(float)WEApplicationGetHeight() - 700.f, 0.0f);
	WEGraphicsDraw(&transform);


	//Score text
	WEGraphicsDrawText("Score", 
		(float)WEApplicationGetWidth() / 1.14f,
		(float)WEApplicationGetHeight() / 1.05f);

	//get score
	char string[100];
	_itoa_s((int)GetEntityManager()->pPlayer->mainBody.base.hp, string, 100, 10);
	WEGraphicsDrawText(string, 
		(float)WEApplicationGetWidth()*9/10, 
		(float)WEApplicationGetHeight()*9/10);*/

	//////////////////////////////////////////////////////////////////////////////////////

	WEGraphicsSetToPerspective();


	
	WEGraphicsEndDraw();
}

void PlayShutdown(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);

	
	BulletAllDelete();
	ParticleSystemShutdown();
	DeleteTileMap(&map);
	//DeleteMainBody(&testObj);
	//BulletAllDelete(&manager.pUpperBody->bulletManager);
	//FSMDeleteStack(&objectA.fsm);
	//FSMDeleteStack(&upperBody.fsm);
	 
	//////////////////////////////////////////
	//Test for EntityList/////////////////////
	//////////////////////////////////////////

	//DeleteEntityList(&list);
	//////////////////////////////////////////
	//HACOMPU/////////////////////////////////
	//////////////////////////////////////////

	DeleteEntityManager();
}
void PlayUnload(WEGameData* pGameData)
{
	WEUNUSED_PARAM(pGameData);

	//WEDEBUG_DESTROY_CONSOLE();

	SoundManager_Delete();

	WEGraphicsUnloadTexture(helloTextureId);
	WEGraphicsUnloadTexture(jumpTextureId);
	WEGraphicsUnloadTexture(BarTextureId);
	WEGraphicsUnloadTexture(LifeBarTextureId);
	//WEGraphicsUnloadTexture(starTextureId);

	WEGraphicsUnloadTexture(mainbodyTextureId);
	//WEGraphicsUnloadTextrue(lowerBodyTextureId);

	TextureList_UnloadAndFree();
}

/*w.............................................................................................................................................................................................................................................................................................................................................................................................................w
w..........................................................................................................................................................oo.................................................................................................................................................................................................................................................w
w............................................................................ooooooooo......................................................................................................................................................................................................................................ooooooo.............................................................ooooooooo.....w
w.........................................................................................................................................................................................................................................................................................................................................................wwwwwwwwwww.........................................w
w.............................................................................................................................................................................................................................................................................................................................................................................................................w
w..........................................................................................................................................................oo.................................................................................................................................................................................................................................................w
w............................................................................ooooooooo......................................................................................................................................................................................................................................ooooooo.............................................................ooooooooo.....w
w.........................................................................................................................................................................................................................................................................................................................................................wwwwwwwwwww.........................................w
w..............................................................wwww..............................................ooooooooo...............................................................................................................................................ooooooooo............................................................................................................................w
w..............................................................wwww..............................................ooooooooo...............................................................................................................................................ooooooooo............................................................................................................................w
w...................wwwwwww...................................................................................................................................................................................................................oooooooo.....................................................wwwwwww.....................wwwwwww................................................................w
w.............................................................................................................................................................................................................................................................................................................................................................................................................w
w............................................................................................................................................oooooo...................................................oooooooo................................................................................................................................................................ooooooooo.......................w
w.............................................wwwwwwwwwwww....................................................................................................................................................................................................................................................................................................................................................w
w............................................wwwwwwwwwwwwww.....................................wwwwwwww.......................................................................................................................................................................................................................ooooo.............ooooooo.....................................ooo..............w
w...........................................wwwwwwwwwwwwwwwwwwww..............................................................................................................................................................................................................................................................................................................................................w
w..........................www............wwwwwwwwwwwwwwwwwwwwwwww..........................................................................................................................................................................wwwwwwww..........................oooooooooo..........................................................................oooooo......................................w
w........................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww................................................ooooooo.....................................oooooooooooo................................ooooooooo.......................................................................................................................................................................oooo...w
w................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww............................................................................................................................................................................................................................................................................................................................w
w.....................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.......................................................................................................................................................................................................................wwwwwwww.......................................................................................w
w................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...............................................................................................................................................................ooo....................................................................................oooooooooo..........................wwwwwwwwwww...........w
w..........wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww..............................................................................................................................................................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................................................................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwww.............................................wwwwwwwwwwwww...........................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwww.............................................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwww.............................................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
w..................................ooooooooo...............................................................wwwww......................................................................................................wwwwwwwwwwwww..........................................wwwwwwwwww.............................................................wwwwwww...ww.....w..wwww..................................w
w................................................wwwwwwwwwwwwww............................................wwwww......................................................................................................wwwwwwwwwwwww.ooooooooooooooooooooooooooooooooooooooooowwwwwwwwww.............................................................w.........w.w....w..w...w.................................w
w................................................wwwwwwwwwwwwww............................................wwwwwwwwwwwwwwwwwwwwwww....................................................................................wwwwwwwwwwwww..........................................wwwwwwwwww.............................................................wwwwwww...w..w...w..w.....w...............................w
w................................................wwwwwwwwwwwwww.....................................ooooooowwwwwwwwwwwwwwwwwwwwwww.................................................wwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww.............................................................w.........w...w..w..w....w................................w
w................................................wwwwwwwwwwwwww............................................wwwwwwwwwwwwwwwwwwwwwww.................................................wwwwwwwwwww........................wwwwwwwwwwwwwwwwwwwwwwww...............................wwwwwwwwww.............................................................wwwwwwww..w.....ww..wwww..................................w
w.........................................ooooooowwwwwwwwwwwwww....................................................................................................................wwwwwwwwwww...............................wwwwwwwwwwwwwwwww....................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................w
w................................................wwwwwwwwwwwwww....................................................................................................................wwwwwwwwwwwwwwwww.........................wwwwwwwwwwwwwwwwwoooooooooooooooooooowwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................w
w................................................wwwwwwwwwwwwwwwwwwwwwwwww.........................................................................................................wwwwwwwwwwwwwwwww.........................wwwwwwwwwwwwwwwww....................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................w
w................................................wwwwwwwwwwwwwwwwwwwwwwwww.......................................wwwwwwwwwwwwwwwwwwwwwwwwwwoooooooooooooooooooooooooooooooooooooooowwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
w.........................................ooooooowwwwwwwwwwwwwwwwwwwwwwwww.......................................wwwwwwwwwwwwwwwwwwwwwwwwww........................................wwwwwwwwww.........................wwwwwwwwwwwww.....................ooooooooo............wwwwwwwwww.......................................................................................................................w
w................................................wwwwwwwwwwwwwwwwwwwwwwwww.......................................wwwwwwwwwwwwwwwwwwwwwwwwww........................................wwwwwwwwww.........................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
w................................................wwwwwwwwwwwwww...............................wwwwwwwwwwooooooooowwwwwwwwwwwwwwwwwwwwwwwwww........................................wwwwwwwwww.........................wwwwwwwwwwwww........oooooooooo................oooooooowwwwwwwwww.......................................................................................................................w
w................................................wwwwwwwwwwwwww...............................................................wwwwwwwwwwwwwwwwwwwwwwwwwoooooooooooooooooooooooooooowwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww....................................................................................................................wwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww...........................wwwwwwwwwwwww...............................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.................wwwwwwwwww.........................................................................................wwwwwwwwwwwwwwwww....................................................oooooooooo...........wwwwwwwwww...........................wwwwwwwwwwwww...............................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww..........................................oooooooo..................................................................wwwwwwwwwwwwwwwww..............................................................................................................wwwwwwwwwwwww...............................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...............................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww................................................................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...............................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww................................................................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwww.............................................wwwwwwwwwwwww.................................................1.........................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwww.............................................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.........................................................................wwwww.........................................wwwwwwwwwwwwwwww.............................................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
w..................................ooooooooo...............................................................wwwww......................................................................................................wwwwwwwwwwwww..........................................wwwwwwwwww.............................................................wwwwwww...ww.....w..wwww..................................w
w................................................wwwwwwwwwwwwww............................................wwwww......................................................................................................wwwwwwwwwwwww.ooooooooooooooooooooooooooooooooooooooooowwwwwwwwww.............................................................w.........w.w....w..w...w.................................w
w................................................wwwwwwwwwwwwww..........................................1.wwwwwwwwwwwwwwwwwwwwwww....................................................................................wwwwwwwwwwwww..........................................wwwwwwwwww.............................................................wwwwwww...w..w...w..w.....w...............................w
w................................................wwwwwwwwwwwwww.....................................ooooooowwwwwwwwwwwwwwwwwwwwwww.................................................wwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww.............................................................w.........w...w..w..w....w................................w
w................................................wwwwwwwwwwwwww............................................wwwwwwwwwwwwwwwwwwwwwww.................................................wwwwwwwwwww........................wwwwwwwwwwwwwwwwwwwwwwww...............................wwwwwwwwww.............................................................wwwwwwww..w.....ww..wwww..................................w
w.........................................ooooooowwwwwwwwwwwwww....................................................................................................................wwwwwwwwwww...............................wwwwwwwwwwwwwwwww....................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................w
w................................................wwwwwwwwwwwwww....................................................................................................................wwwwwwwwwwwwwwwww.........................wwwwwwwwwwwwwwwwwoooooooooooooooooooowwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................w
w................................................wwwwwwwwwwwwwwwwwwwwwwwww.........................................................................................................wwwwwwwwwwwwwwwww.......................1.wwwwwwwwwwwwwwwww....................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...........................................................................................................w
w................................................wwwwwwwwwwwwwwwwwwwwwwwww.......................................wwwwwwwwwwwwwwwwwwwwwwwwwwoooooooooooooooooooooooooooooooooooooooowwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
w.........................................ooooooowwwwwwwwwwwwwwwwwwwwwwwww.......................................wwwwwwwwwwwwwwwwwwwwwwwwww........................................wwwwwwwwww.........................wwwwwwwwwwwww.....................ooooooooo............wwwwwwwwww.......................................................................................................................w
w................................................wwwwwwwwwwwwwwwwwwwwwwwww.......................................wwwwwwwwwwwwwwwwwwwwwwwwww........................................wwwwwwwwww.........................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
w................................................wwwwwwwwwwwwww...............................wwwwwwwwwwooooooooowwwwwwwwwwwwwwwwwwwwwwwwww........................................wwwwwwwwww.........................wwwwwwwwwwwww........oooooooooo................oooooooowwwwwwwwww.......................................................................................................................w
w................................................wwwwwwwwwwwwww...............................................................wwwwwwwwwwwwwwwwwwwwwwwwwoooooooooooooooooooooooooooowwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww.......................................................................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww....................................................................................................................wwwwwwwwwwwwwwwww..................wwwwwwwwwwwww..........................................wwwwwwwwww...........................wwwwwwwwwwwww...............................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.................wwwwwwwwww.........................................................................................wwwwwwwwwwwwwwwww....................................................oooooooooo...........wwwwwwwwww...........................wwwwwwwwwwwww...............................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww..........................................oooooooo..................................................................wwwwwwwwwwwwwwwww..............................................................................................................wwwwwwwwwwwww...............................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww............................................................1..wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww................................................................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.................................1...............................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...............................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww................................................................................................wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.................................................................w
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww*/