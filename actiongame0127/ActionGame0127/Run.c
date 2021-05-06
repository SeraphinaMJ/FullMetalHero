/******************************************************************************/
/*!
\file   Run.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about run state of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "Run.h"

//Project-related headers
#include "Player.h"
#include "Entity.h"
#include "State.h"
#include "StackFSM.h"
#include "KeyInput.h"

//Third-party headers
#include "WarpEngine.h"

void MakeMainBodyRunState(State* pResult)
{
	MakeState(pResult,
		MainBodyStateRunStart,
		MainBodyStateRunUpdate,
		MainBodyStateRunEnd);
}

void MainBodyStateRunStart(State* pState)
{
	pState;
}
void MainBodyStateRunUpdate(State* pState, float dt)
{
	Entity* pPlayer = pState->actor;
	StackFSM* fsm = pPlayer->moveFSM;

	if (WEInputIsPressed(WE_D)
		== WEInputIsPressed(WE_A))
	{
		FSM_ChangeState(fsm, pPlayer->playerIdle);
		return;
	}
	else if (WEInputIsPressed(WE_D))
		Player_Run(pPlayer, 1, dt);
	else if (WEInputIsPressed(WE_A))
		Player_Run(pPlayer, -1, dt);

	//If the MainBody is on ground and the user pressed spacebar,
	//change the state to jumpstate
	if (WEInputIsTriggered(KEY_JUMP) && pPlayer->onGround == TRUE)
	{
		//MainBody prepares to jump.
		Player_Jump(pPlayer);
		FSM_ChangeState(fsm, pPlayer->playerJumpRun);
		return;
	}
	//else if the MainBody is in the air,
	//change the state to fallstate
	else if (pPlayer->onGround == FALSE)
	{
		FSM_ChangeState(fsm, pPlayer->playerFallRun);
		return;
	}

	//Push the roll state if
	//the MainBody presses 's' key.
	if (WEInputIsTriggered(KEY_ROLL))
		FSMPush(fsm, pPlayer->playerRoll);

}
void MainBodyStateRunEnd(State* pState)
{
	pState;
}