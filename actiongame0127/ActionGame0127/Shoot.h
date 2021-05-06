/******************************************************************************/
/*!
\file   Shoot.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about shoot state of upperBody
*/
/******************************************************************************/
#ifndef SHOOT_H
#define SHOOT_H

//Declaration structs
typedef struct State State;

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeUpperBodyShootState(State* pResult);
void UpperBodyStateShootStart(State* pState);
void UpperBodyStateShootUpdate(State* pState, float dt);
void UpperBodyStateShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeUpperBodyNotShootState(State* pResult);
void UpperBodyStateNotShootStart(State* pState);
void UpperBodyStateNotShootUpdate(State* pState, float dt);
void UpperBodyStateNotShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/

#endif