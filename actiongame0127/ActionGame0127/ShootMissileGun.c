/******************************************************************************/
/*!
\file   ShootMachineGun.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about shoot state of upperBody
*/
/******************************************************************************/
//Header file related to the implementation
#include "ShootMissileGun.h"

//Project-related headers
#include "WeaponManager.h"
#include "BulletList.h"
#include "Player.h"
#include "soundmanager.h"

//Standard library headers
#include <time.h>

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeMissileGunShootState(State* pResult)
{
	MakeState(pResult,
		MissileGunStateShootStart,
		MissileGunStateShootUpdate,
		MissileGunStateShootEnd);
}
void MissileGunStateShootStart(State* pState)
{
	pState = 0;
}
void MissileGunStateShootUpdate(State* pState, float dt)
{
	Entity* pArm = pState->actor;
	dt = 0;
	
	//Create new bullet
	//BulletManagerAddToEnd(&pSelf->bulletManager);
	BulletAddToEnd(pArm, pArm->weapon.weaponType, 
		pArm->weapon.ownerType, pArm->aimInfo.unitVector);

	//Initialize countTime to zero
	pArm->weapon.coolDown.countTime = 0;

	//Bullet sound
	SoundManager_PlaySound(SHOOT_SOUND);

	FSMPop(pArm->shootFSM);
	return;
}
void MissileGunStateShootEnd(State* pState)
{
	pState;
}

/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeMissileGunNotShootState(State* pResult)
{
	MakeState(pResult,
		MissileGunStateNotShootStart,
		MissileGunStateNotShootUpdate,
		MissileGunStateNotShootEnd);
}
void MissileGunStateNotShootStart(State* pState)
{
	Entity* pArm = pState->actor;

	pArm->weapon.weaponType = MISSILE_GUN;
	pArm->weapon.coolDown.countTime = pArm->weapon.coolDown.missileGunCD;
}
void MissileGunStateNotShootUpdate(State* pState, float dt)
{
	Entity* pArm = pState->actor;

	pArm->weapon.coolDown.countTime += dt;

	if (WEInputIsTriggered(WE_MOUSE_LEFT)
		&& pArm->weapon.coolDown.countTime > pArm->weapon.coolDown.missileGunCD)
	{
		FSMPush(pArm->shootFSM, pArm->armShootGuidedProjectile);
		return;
	}

	if (WEInputIsTriggered(WE_MOUSE_RIGHT))
	{
		FSM_ChangeState(pArm->shootFSM, pArm->armNotShootGuidedProjectile);
		return;
	}
}
void MissileGunStateNotShootEnd(State* pState)
{
	pState;
}

/******************************************************************************/
/******************************************************************************/