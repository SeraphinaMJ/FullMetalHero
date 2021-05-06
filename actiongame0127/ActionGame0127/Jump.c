/******************************************************************************/
/*!
\file   Jump.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about jump state of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "Jump.h"

//Project-related headers
#include "Player.h"
#include "Entity.h"
#include "State.h"
#include "StackFSM.h"
#include "KeyInput.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <math.h>

/*Jump Idle State*/
void MakeMainBodyJumpIdleState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateJumpIdleStart,
		MainBodyStateJumpIdleUpdate,
		MainBodyStateJumpIdleEnd);
}

void MainBodyStateJumpIdleStart(State* pState)
{
	pState;
}
void MainBodyStateJumpIdleUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	//If user is pressing only right or only left arrow button
	if (WEInputIsPressed(WE_D)
		^ WEInputIsPressed(WE_A))
		//Change MainBody's state to jumprunstate.
	{
		FSM_ChangeState(fsm, pPlayer->playerJumpRun);
		return;
	}
	else
		Player_Stop(pPlayer, dt);

	//If the user pressed spacebar 
	//and MainBody is in the air
	//and restjump is remained yet,
	//Jump one mor time(double jump)
	if (WEInputIsTriggered(KEY_JUMP)
		&& pPlayer->onGround == FALSE
		&& pPlayer->restJump > 0)
		Player_Jump(pPlayer);

	//If the MainBody's y velocity becomes zero,
	//which means MainBody is IDLE,
	//Change MainBody's state to "idle"
	if (pPlayer->vel.y == 0 && pPlayer->onGround == TRUE)
	{
		FSM_ChangeState(fsm, pPlayer->playerIdle);
		return;
	}

	//If the MainBody's y velocity becomes less than zero,
	//which means MainBody starts falling,
	//Change MainBody's state to "falling"
	if (pPlayer->vel.y < 0)
	{
		FSM_ChangeState(fsm, pPlayer->playerFallIdle);
		return;
	}
}
void MainBodyStateJumpIdleEnd(State* pState)
{
	pState;
}

/*****************************************************************************/
/*****************************************************************************/
/*Jump Run State*/
void MakeMainBodyJumpRunState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateJumpRunStart,
		MainBodyStateJumpRunUpdate,
		MainBodyStateJumpRunEnd);
}

void MainBodyStateJumpRunStart(State* pState)
{
	pState;
}
void MainBodyStateJumpRunUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;
	
	if (WEInputIsPressed(WE_D)
		== WEInputIsPressed(WE_A))
	{
		FSM_ChangeState(fsm, pPlayer->playerJumpIdle);
		return;
	}
	//MainBody runs if the user is pressing 
	//only right or only left arrow button.
	else if (WEInputIsPressed(WE_D))
		Player_Run(pPlayer, 1, dt);
	else if (WEInputIsPressed(WE_A))
		Player_Run(pPlayer, -1, dt);

	//If the user pressed spacebar 
	//and MainBody is in the air
	//and restjump is remained yet,
	//Jump one mor time(double jump)
	if (WEInputIsTriggered(KEY_JUMP)
		&& pPlayer->onGround == FALSE
		&& pPlayer->restJump > 0)
	{
		Player_Jump(pPlayer);
	}

	//If the MainBody's y velocity becomes zero,
	//which means MainBody is IDLE,
	//Change MainBody's state to "idle"
	if (pPlayer->vel.y == 0 && pPlayer->onGround == TRUE)
	{
		FSM_ChangeState(fsm, pPlayer->playerRun);
		return;
	}

	//If the MainBody's y velocity becomes zero,
	//which means MainBody starts falling,
	//Change MainBody's state to "falling"
	if (pPlayer->vel.y < 0)
	{
		FSM_ChangeState(fsm, pPlayer->playerFallRun);
		return;
	}

	//Push the roll state if
	//the MainBody presses 's' key.
	if (WEInputIsTriggered(KEY_ROLL))
	{
		FSMPush(fsm, pPlayer->playerRoll);
		return;
	}
}

void MainBodyStateJumpRunEnd(State* pState)
{
	//pState is unused in this project.
	pState = 0;
}