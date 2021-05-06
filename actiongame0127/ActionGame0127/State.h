/******************************************************************************/
/*!
\file   State.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about basic empty state.
*/
/******************************************************************************/
#ifndef STATE_H
#define STATE_H

typedef struct State State;

typedef void(*StartFunc) (State*);
typedef void(*UpdateFunc) (State*, float);
typedef void(*EndFunc) (State*);

typedef struct State{
	void* actor;
	StartFunc Start;
	UpdateFunc Update;
	EndFunc End;
}State;

void MakeState(State* pResult, StartFunc startFunc,
	UpdateFunc updateFunc, EndFunc endFunc);

#endif//STATE_H