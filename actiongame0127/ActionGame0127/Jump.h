/******************************************************************************/
/*!
\file   Jump.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about jump state of MainBody.
*/
/******************************************************************************/
#ifndef JUMP_H
#define JUMP_H

//Declaration structs
typedef struct State State;

void MakeMainBodyJumpIdleState(State* pResult);

void MainBodyStateJumpIdleStart(State* pState);
void MainBodyStateJumpIdleUpdate(State* pState, float dt);
void MainBodyStateJumpIdleEnd(State* pState);


void MakeMainBodyJumpRunState(State* pResult);

void MainBodyStateJumpRunStart(State* pState);
void MainBodyStateJumpRunUpdate(State* pState, float dt);
void MainBodyStateJumpRunEnd(State* pState);

#endif//JUMP_H