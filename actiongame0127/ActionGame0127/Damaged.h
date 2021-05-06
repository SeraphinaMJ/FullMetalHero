/******************************************************************************/
/*!
\file   Damaged.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about damage state of MainBody.
*/
/******************************************************************************/
#ifndef DAMAGED_H
#define DAMAGED_H

//Declaration structs
typedef struct State State;

void MakeMainBodyDamagedState(State* pResult);
void MainBodyDamagedStateStart(State* pState);
void MainBodyDamagedStateUpdate(State* pState, float dt);
void MainBodyDamagedStateEnd(State* pState);

#endif//DAMAGED_H