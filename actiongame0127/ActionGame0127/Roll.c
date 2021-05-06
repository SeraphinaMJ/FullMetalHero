/******************************************************************************/
/*!
\file   Roll.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about roll state of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "Roll.h"

//Project-related headers
#include "Player.h"
#include "Entity.h"
#include "State.h"
#include "StackFSM.h"

void MakeMainBodyRollState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateRollStart,
		MainBodyStateRollUpdate,
		MainBodyStateRollEnd);
}

void MainBodyStateRollStart(State* pState)
{
	Entity* pPlayer = pState->actor;

	//We should modify it later
	//if velocity < 0 -> if MainBody is flip
	if (pPlayer->vel.x > 0)
		pPlayer->vel.x = pPlayer->rollSpeed;
	else if (pPlayer->vel.x < 0)
		pPlayer->vel.x = -pPlayer->rollSpeed;

	//isRolling is true when the MainBody is rolling.
	pPlayer->isRolling = TRUE;
	
}
void MainBodyStateRollUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	//Keep timer going.
	pPlayer->rollTimer += dt;

	if (pPlayer->vel.x > 0.f)
		pPlayer->rotation -= 10.f * dt;
	else
		pPlayer->rotation += 10.f * dt;

	//Few seconds after, 
	//the MainBody goes previous state.
	if (pPlayer->rollTimer >= pPlayer->rollDuration)
	{
		fsm->Pop(fsm);
		pPlayer->rollTimer = 0.f;
		return;
	}

}
void MainBodyStateRollEnd(State* pState)
{
	Entity* pPlayer = pState->actor;

	pPlayer->rotation = 0.f;
	pPlayer->isRolling = FALSE;
}