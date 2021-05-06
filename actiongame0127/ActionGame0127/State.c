/******************************************************************************/
/*!
\file   State.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about basic empty state.
*/
/******************************************************************************/
//Header file related to the implementation
#include "State.h"

void MakeState(State* pResult, StartFunc startFunc,
	UpdateFunc updateFunc, EndFunc endFunc)
{
	pResult->Start = startFunc;
	pResult->Update = updateFunc;
	pResult->End = endFunc;
}