/******************************************************************************/
/*!
\file   pinvinciblestates.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about states related to invincible of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "pinvinciblestates.h"

//Project-related headers
#include "MainBody.h"
#include "State.h"
#include "StackFSM.h"

//Third-party headers
#include "WarpEngine.h"

void MakeMainBodyNormalState(State* pResult)
{
	MakeState(pResult,
		MainBodyNormalStateStart,
		MainBodyNormalStateUpdate,
		MainBodyNormalStateEnd);
}
void MainBodyNormalStateStart(State* pState)
{
	pState;
	Entity* pPlayer = pState->actor;
	pPlayer->color.a = 255;
}
void MainBodyNormalStateUpdate(State* pState, float dt)
{
	pState;
	dt;
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->invincibleFSM;

	if (pPlayer->isInvincible == TRUE)
	{
		//Change to invincible state
		FSM_ChangeState(fsm, pPlayer->playerinvincible);
		return;
	}

	//WEUNUSED_PARAM(dt);
}
void MainBodyNormalStateEnd(State* pState)
{
	WEUNUSED_PARAM(pState);
}

/******************************************************************************/
/******************************************************************************/

void MakeMainBodyInvincibleState(State* pResult)
{
	MakeState(pResult,
		MainBodyInvincibleStateStart,
		MainBodyInvincibleStateUpdate,
		MainBodyInvincibleStateEnd);
}
void MainBodyInvincibleStateStart(State* pState)
{
	Entity* pPlayer = pState->actor;
	pPlayer->color.a = 120;
}
void MainBodyInvincibleStateUpdate(State* pState, float dt)
{
	pState;
	dt;
	Entity* pPlayer = pState->actor;
	StackFSM* pFsm = pPlayer->invincibleFSM;

	pPlayer->invincibleTimer += dt;
	if (pPlayer->invincibleTimer >= 2.f)
	{
		pPlayer->invincibleTimer = 0.f;
		//Change to normal state.
		pFsm->ChangeState(pFsm, pPlayer->playerNonInvincible);
		return;
	}
}
void MainBodyInvincibleStateEnd(State* pState)
{
	Entity* pPlayer = pState->actor;
	pPlayer->isInvincible = FALSE;
	/*MainBody* pMainBody = pState->actor;

	pMainBody->SetInvincibleFlag(pMainBody, FALSE);*/
}