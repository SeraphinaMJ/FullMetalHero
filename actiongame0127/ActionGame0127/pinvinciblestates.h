/******************************************************************************/
/*!
\file   pinvinciblestates.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about states related to invincible of MainBody.
*/
/******************************************************************************/

#ifndef PINVINCIBLESTATES_H
#define PINVINCIBLESTATES_H

//Declaration structs
typedef struct State State;

void MakeMainBodyNormalState(State* pResult);
void MainBodyNormalStateStart(State* pState);
void MainBodyNormalStateUpdate(State* pState, float dt);
void MainBodyNormalStateEnd(State* pState);

/******************************************************************************/
/******************************************************************************/

void MakeMainBodyInvincibleState(State* pResult);
void MainBodyInvincibleStateStart(State* pState);
void MainBodyInvincibleStateUpdate(State* pState, float dt);
void MainBodyInvincibleStateEnd(State* pState);

#endif