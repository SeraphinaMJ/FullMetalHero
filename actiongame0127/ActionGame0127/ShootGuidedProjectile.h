/******************************************************************************/
/*!
\file   ShootGuidedProjectile.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about ShootGuidedProjectile state of upperBody
*/
/******************************************************************************/
#ifndef SHOOTGUIDEDPROJECTILE_H
#define SHOOTGUIDEDPROJECTILE_H

//Declaration structs
typedef struct State State;

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeGuidedProjectileShootState(State* pResult);
void GuidedProjectileStateShootStart(State* pState);
void GuidedProjectileStateShootUpdate(State* pState, float dt);
void GuidedProjectileStateShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeGuidedProjectileNotShootState(State* pResult);
void GuidedProjectileStateNotShootStart(State* pState);
void GuidedProjectileStateNotShootUpdate(State* pState, float dt);
void GuidedProjectileStateNotShootEnd(State* pState);

/******************************************************************************/
/******************************************************************************/


#endif