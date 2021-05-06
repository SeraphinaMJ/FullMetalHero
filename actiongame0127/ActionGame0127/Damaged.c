/******************************************************************************/
/*!
\file   Damaged.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about damage state of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "Damaged.h"

//Project-related headers
//#include "MainBody.h"
#include "Entity.h"
#include "StackFSM.h"
#include "State.h"

//Third-party headers
#include "WarpEngine.h"

void MakeMainBodyDamagedState(State* pResult)
{
	MakeState(pResult,
		MainBodyDamagedStateStart,
		MainBodyDamagedStateUpdate,
		MainBodyDamagedStateEnd);
}
void MainBodyDamagedStateStart(State* pState)
{
	Entity* pPlayer = pState->actor;
	WEVec2 newVel;
	WEVec2 currentVel = pPlayer->vel;

	if (currentVel.x > 0.f)
	{
		newVel.x = -10.f;
	}
	else
	{
		newVel.x = 10.f;
	}
	newVel.y = 0.f;

	pPlayer->damageTimer = 0.f;
	pPlayer->vel = newVel;
}
void MainBodyDamagedStateUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	//pMainBody->Stop(pMainBody, dt);

	pPlayer->damageTimer += dt;
	if (pPlayer->damageTimer >= 0.2f)
	{
		FSMPop(fsm);
		return;
	}
}
void MainBodyDamagedStateEnd(State* pState)
{
	Entity* pPlayer = pState->actor;
	pPlayer->damageTimer = 0.f;
	pPlayer->isDamaged = FALSE;
}
