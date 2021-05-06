/******************************************************************************/
/*!
\file   Idle.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about Idle state of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "Idle.h"

//Project-related headers
#include "Player.h"
#include "Entity.h"
#include "KeyInput.h"
#include "State.h"
#include "StackFSM.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <math.h>

void MakeMainBodyIdleState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateIdleStart,
		MainBodyStateIdleUpdate,
		MainBodyStateIdleEnd);
}

void MainBodyStateIdleStart(State* pState)
{
	pState;
}
void MainBodyStateIdleUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	//If user is pressing only right or only left arrow button
	if (WEInputIsPressed(WE_D)
		^ WEInputIsPressed(WE_A))
		//Change MainBody's state to runstate.
	{
		FSM_ChangeState(fsm, pPlayer->playerRun);
		return;
	}
	else
		Player_Stop(pPlayer, dt);

	//If the MainBody is on ground and the user pressed spacebar,
	//change the state to jumpstate
	if (WEInputIsTriggered(KEY_JUMP) && pPlayer->onGround == TRUE)
	{
		//MainBody prepares to jump.
		Player_Jump(pPlayer);
		FSM_ChangeState(fsm, pPlayer->playerJumpIdle);
		return;
	}
	//else if the MainBody is in the air,
	//change the state to fallstate
	else if (pPlayer->onGround == FALSE)
	{
		FSM_ChangeState(fsm, pPlayer->playerFallIdle);
		return;
	}
}
void MainBodyStateIdleEnd(State* pState)
{
	pState = 0;
}