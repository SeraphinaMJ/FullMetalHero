/******************************************************************************/
/*!
\file   Idle.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about idle state of MainBody.
*/
/******************************************************************************/
#ifndef IDLE_H
#define IDLE_H

//Declaration structs
typedef struct State State;

void MakeMainBodyIdleState(State* pResult);

void MainBodyStateIdleStart(State* pState);
void MainBodyStateIdleUpdate(State* pState, float dt);
void MainBodyStateIdleEnd(State* pState);

#endif//IDLE_H