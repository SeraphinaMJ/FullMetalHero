/******************************************************************************/
/*!
\file   Fall.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about fall state of MainBody.
*/
/******************************************************************************/
#ifndef FALL_H
#define FALL_H

//Declaration structs
typedef struct State State;

/*Fall Idle State*/
void MakeMainBodyFallIdleState(State* pResult);
void MainBodyStateFallIdleStart(State* pState);
void MainBodyStateFallIdleUpdate(State* pState, float dt);
void MainBodyStateFallIdleEnd(State* pState);

/*****************************************************************************/
/*****************************************************************************/
/*Fall Run State*/
void MakeMainBodyFallRunState(State* pResult);
void MainBodyStateFallRunStart(State* pState);
void MainBodyStateFallRunUpdate(State* pState, float dt);
void MainBodyStateFallRunEnd(State* pState);

#endif//FALL_H