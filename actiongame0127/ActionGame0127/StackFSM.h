/******************************************************************************/
/*!
\file   StackFSM.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about stack-based finite state manager.
*/
/******************************************************************************/
#ifndef STACKFSM_H
#define STACKFSM_H

//Declaration structs
typedef struct State State;

typedef struct StackFSM{
	void* actor;
	State* stack;
	int currentNum;
	int size;
	void(*NewStack)(struct StackFSM*, int);
	void(*DeleteStack)(struct StackFSM*);
	void(*Push)(struct StackFSM*, State*);
	void(*Pop)(struct StackFSM*);
	void(*ChangeState)(struct StackFSM*, State*);
	State*(*GetCurrentState)(const struct StackFSM*);
	void(*Update)(const struct StackFSM*, float);
}StackFSM;

void MakeStackFSM(StackFSM* pResult, void* actor, int size);
void FSMNewStack(StackFSM* pSelf, int size);
void FSMDeleteStack(StackFSM* pSelf);
void FSMPush(StackFSM* pSelf, State* state);
void FSMPop(StackFSM* pSelf);
void FSM_ChangeState(StackFSM* pSelf, State* pState);
State* FSMGetCurrentState(const StackFSM* pSelf);
void FSMUpdate(const StackFSM* pSelf, float dt);

#endif/*STACKFSM_H*/