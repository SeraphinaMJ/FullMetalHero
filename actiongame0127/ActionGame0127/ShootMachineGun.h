/******************************************************************************/
/*!
\file   ShootMachineGun.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about shoot state of upperBody
*/
/******************************************************************************/
#ifndef SHOOTMACHINEGUN_H
#define SHOOTMACHINEGUN_H

//Declaration structs
typedef struct State State;

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeMachineGunShootState(State* pResult);
void MachineGunStateShootStart(State* pState);
void MachineGunStateShootUpdate(State* pState, float dt);
void MachineGunStateShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeMachineGunNotShootState(State* pResult);
void MachineGunStateNotShootStart(State* pState);
void MachineGunStateNotShootUpdate(State* pState, float dt);
void MachineGunStateNotShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/

#endif