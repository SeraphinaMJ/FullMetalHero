/******************************************************************************/
/*!
\file   Shoot.c
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the source file about shoot state of upperBody
*/
/******************************************************************************/
//Header file related to the implementation
#include "Shoot.h"

//Project-related headers
#include "BulletManager.h"
#include "Bullet.h"
#include "soundmanager.h"
#include "UpperBody.h"

//Standard library headers
#include <time.h>

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeUpperBodyShootState(State* pResult)
{
	MakeState(pResult,
		UpperBodyStateShootStart,
		UpperBodyStateShootUpdate,
		UpperBodyStateShootEnd);
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyStateShootStart(State* pState)
{
	pState = 0;
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyStateShootUpdate(State* pState, float dt)
{
	UpperBody* pSelf = pState->actor;

	if (!WEInputIsPressed(WE_MOUSE_LEFT))
	{
		pSelf->fsm.Pop(&pSelf->fsm);
		return;
	}

	//Count time
	pSelf->bulletManager.countTime += dt;

	//If countTime > gapTime
	if (pSelf->bulletManager.countTime > pSelf->bulletManager.gapTime)
	{
		//Get the MainBody position to bullet manager
		WEVec2Set(&pSelf->bulletManager.ownerPosition,
			pSelf->base.pos.x, pSelf->base.pos.y);

		//Create new bullet
		BulletCreate(&pSelf->bulletManager);

		//Initialize countTime to zero
		pSelf->bulletManager.countTime = 0;

		//Bullet sound
		SoundManager_PlaySound(SHOOT_SOUND);
	}
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyStateShootEnd(State* pState)
{
	pState = 0;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeUpperBodyNotShootState(State* pResult)
{
	MakeState(pResult,
		UpperBodyStateNotShootStart,
		UpperBodyStateNotShootUpdate,
		UpperBodyStateNotShootEnd);
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyStateNotShootStart(State* pState)
{
	pState = 0;
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyStateNotShootUpdate(State* pState, float dt)
{
	UpperBody* pSelf = pState->actor;
	WEUNUSED_PARAM(dt);

	if (WEInputIsPressed(WE_MOUSE_LEFT))
	{
		pSelf->fsm.Push(&pSelf->fsm, &pSelf->shootState);
		return;
	}
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyStateNotShootEnd(State* pState)
{
	UpperBody* pSelf = pState->actor;

	pSelf->bulletManager.countTime = pSelf->bulletManager.gapTime;
}
/******************************************************************************/
/******************************************************************************/

