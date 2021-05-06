/******************************************************************************/
/*!
\file   Run.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about run state of MainBody.
*/
/******************************************************************************/
#ifndef RUN_H
#define RUN_H

//Declaration structs
typedef struct State State;

void MakeMainBodyRunState(State* pResult);

void MainBodyStateRunStart(State* pState);
void MainBodyStateRunUpdate(State* pState, float dt);
void MainBodyStateRunEnd(State* pState);

#endif//RUN_H