/******************************************************************************/
/*!
\file   Fall.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about fall state of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "Fall.h"

//Project-related headers
#include "Player.h"
#include "Entity.h"
#include "StackFSM.h"
#include "State.h"
#include "KeyInput.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <math.h>

/*Fall Idle State*/
void MakeMainBodyFallIdleState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateFallIdleStart,
		MainBodyStateFallIdleUpdate,
		MainBodyStateFallIdleEnd);
}
void MainBodyStateFallIdleStart(State* pState)
{
	//pState is unused in this function
	pState = 0;
}
void MainBodyStateFallIdleUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	//If user is pressing only right or only left arrow button
	if (WEInputIsPressed(WE_D)
		^ WEInputIsPressed(WE_A))
		//Change MainBody's state to fallrunstate.
	{
		FSM_ChangeState(fsm, pPlayer->playerFallRun);
		return;
	}
	else
		Player_Stop(pPlayer, dt);

	//If the user pressed spacebar 
	//and the player is in the air
	//and restjump is remained yet,
	//Jump one mor time(double jump)
	if (WEInputIsTriggered(KEY_JUMP)
		&& pPlayer->onGround == FALSE
		&& pPlayer->restJump > 0)
	{
		//MainBody prepares to jump.
		Player_Jump(pPlayer);
		FSM_ChangeState(fsm, pPlayer->playerJumpIdle);
		return;
	}
	//If the MainBody is on ground,
	//change the state to idlestate
	else if (pPlayer->onGround == TRUE)
	{
		FSM_ChangeState(fsm, pPlayer->playerIdle);
		return;
	}
}
void MainBodyStateFallIdleEnd(State* pState)
{
	//pState is unused in this function
	pState = 0;
}

/*****************************************************************************/
/*****************************************************************************/
/*Fall Run State*/
void MakeMainBodyFallRunState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateFallRunStart,
		MainBodyStateFallRunUpdate,
		MainBodyStateFallRunEnd);
}
void MainBodyStateFallRunStart(State* pState)
{
	//pState is unused in this function
	pState;
}
void MainBodyStateFallRunUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	if (WEInputIsPressed(WE_D)
		== WEInputIsPressed(WE_A))
	{
		FSM_ChangeState(fsm, pPlayer->playerFallIdle);
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
		//MainBody prepares to jump.
		Player_Jump(pPlayer);
		FSM_ChangeState(fsm, pPlayer->playerJumpRun);
		return;
	}
	//If the MainBody is on ground,
	//change the state to idlestate
	else if (pPlayer->onGround == TRUE)
	{
		FSM_ChangeState(fsm, pPlayer->playerRun);
		return;
	}

	//Push the roll state if
	//the MainBody presses 's' key.
	if (WEInputIsTriggered(KEY_ROLL))
		FSMPush(fsm, pPlayer->playerRoll);
}
void MainBodyStateFallRunEnd(State* pState)
{
	//pState is unused in this function
	pState;
}