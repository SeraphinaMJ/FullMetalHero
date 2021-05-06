/******************************************************************************/
/*!
\file   ShootMachineGun.c
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the source file about shoot state of upperBody
*/
/******************************************************************************/
//Header file related to the implementation
#include "ShootMachineGun.h"

//Project-related headers
#include "BulletList.h"
#include "soundmanager.h"
#include "Player.h"

//Standard library headers
#include <time.h>

/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeMachineGunShootState(State* pResult)
{
	MakeState(pResult,
		MachineGunStateShootStart,
		MachineGunStateShootUpdate,
		MachineGunStateShootEnd);
}
/******************************************************************************/
/******************************************************************************/
void MachineGunStateShootStart(State* pState)
{
	Entity* pArm = pState->actor;
	pArm->weapon.coolDown.countTime = pArm->weapon.coolDown.machineGunCD / 2.f;
}
/******************************************************************************/
/******************************************************************************/
void MachineGunStateShootUpdate(State* pState, float dt)
{
	Entity* pArm = pState->actor;

	if (!WEInputIsPressed(WE_MOUSE_LEFT))
	{
		FSMPop(pArm->shootFSM);
		return;
	}

	//Count time
	pArm->weapon.coolDown.countTime += dt;
	//pSelf->bulletManager.time.countTime += dt;


	if (pArm->weapon.coolDown.countTime > pArm->weapon.coolDown.machineGunCD)
	{
		//Create new bullet
		BulletAddToEnd(pArm, pArm->weapon.weaponType, 
			pArm->weapon.ownerType, pArm->aimInfo.unitVector);

		//Initialize countTime to zero
		pArm->weapon.coolDown.countTime = 0;

		//Bullet sound
		SoundManager_PlaySound(SHOOT_SOUND);
	}
}
/******************************************************************************/
/******************************************************************************/
void MachineGunStateShootEnd(State* pState)
{
	pState = 0;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeMachineGunNotShootState(State* pResult)
{
	MakeState(pResult,
		MachineGunStateNotShootStart,
		MachineGunStateNotShootUpdate,
		MachineGunStateNotShootEnd);
}
/******************************************************************************/
/******************************************************************************/
void MachineGunStateNotShootStart(State* pState)
{
	Entity* pArm = pState->actor;

	pArm->weapon.weaponType = MACHINE_GUN;
	pArm->weapon.coolDown.countTime = pArm->weapon.coolDown.machineGunCD;
}
/******************************************************************************/
/******************************************************************************/
void MachineGunStateNotShootUpdate(State* pState, float dt)
{
	Entity* pArm = pState->actor;
	WEUNUSED_PARAM(dt);

	if (WEInputIsPressed(WE_MOUSE_LEFT))
	{
		FSMPush(pArm->shootFSM, pArm->armShootMachineGun);
		return;
	}

	if (WEInputIsTriggered(WE_MOUSE_RIGHT))
	{
		FSM_ChangeState(pArm->shootFSM, pArm->armNotShootMissileGun);
		return;
	}
}
/******************************************************************************/
/******************************************************************************/
void MachineGunStateNotShootEnd(State* pState)
{
	pState;
}
/******************************************************************************/
/******************************************************************************/

