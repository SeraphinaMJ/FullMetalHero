/******************************************************************************/
/*!
\file   ShootMissileGun.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about ShootMissileGun state of upperBody
*/
/******************************************************************************/
#ifndef SHOOTMISSILEGUN_H
#define SHOOTMISSILEGUN_H

//Declaration structs
typedef struct State State;

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeMissileGunShootState(State* pResult);
void MissileGunStateShootStart(State* pState);
void MissileGunStateShootUpdate(State* pState, float dt);
void MissileGunStateShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeMissileGunNotShootState(State* pResult);
void MissileGunStateNotShootStart(State* pState);
void MissileGunStateNotShootUpdate(State* pState, float dt);
void MissileGunStateNotShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/


#endif