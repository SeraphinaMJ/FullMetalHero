/******************************************************************************/
/*!
\file   Roll.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about roll state of MainBody.
*/
/******************************************************************************/
#ifndef ROLL_H
#define ROLL_H

//Declaration structs
typedef struct State State;

void MakeMainBodyRollState(State* pResult);

void MainBodyStateRollStart(State* pState);
void MainBodyStateRollUpdate(State* pState, float dt);
void MainBodyStateRollEnd(State* pState);

#endif