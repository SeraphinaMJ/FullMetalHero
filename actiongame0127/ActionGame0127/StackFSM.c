/******************************************************************************/
/*!
\file   StackFSM.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about stack-based finite state manager.
*/
/******************************************************************************/
//Header file related to the implementation
#include "StackFSM.h"

//Project-related headers
#include "Idle.h"
#include "Run.h"
#include "Jump.h"
#include "Fall.h"
#include "Roll.h"
#include "State.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>


void MakeStackFSM(StackFSM* pResult, void* actor, int size)
{
	pResult->actor = actor;
	pResult->NewStack = FSMNewStack;
	pResult->DeleteStack = FSMDeleteStack;
	pResult->Push = FSMPush;
	pResult->Pop = FSMPop;
	pResult->ChangeState = FSM_ChangeState;
	pResult->GetCurrentState = FSMGetCurrentState;
	pResult->Update = FSMUpdate;

	pResult->NewStack(pResult, size);
}

void FSMNewStack(StackFSM* pSelf, int size)
{
	pSelf->stack = (State*)malloc(sizeof(State) * size);
	
	pSelf->currentNum = -1;
	pSelf->size = size;
}
void FSMDeleteStack(StackFSM* pSelf)
{
	free(pSelf->stack);
	pSelf->stack = 0;
}
void FSMPush(StackFSM* pSelf, State* state)
{
	State* cState;

	/*if (pSelf->index >= pSelf->size - 1)
		return;*/
	state->actor = pSelf->actor;
	
	pSelf->stack[++pSelf->currentNum] = *state;
	cState = pSelf->GetCurrentState(pSelf);

	cState->Start(cState);
}
void FSMPop(StackFSM* pSelf)
{
	State* cState;

	///*if (pSelf->index < 0)
	//	return;*/
	cState = pSelf->GetCurrentState(pSelf);
	cState->End(cState);
	pSelf->currentNum--;
}
void FSM_ChangeState(StackFSM* pSelf, State* pState)
{
	pSelf->Pop(pSelf);
	pSelf->Push(pSelf, pState);
}
State* FSMGetCurrentState(const StackFSM* pSelf)
{
	if (pSelf->currentNum < 0 || pSelf->currentNum >= pSelf->size)
		return 0;
	else
		return &pSelf->stack[pSelf->currentNum];
}

void FSMUpdate(const StackFSM* pSelf, float dt)
{
	State* cState = pSelf->GetCurrentState(pSelf);
	if (cState)
		cState->Update(cState, dt);
}