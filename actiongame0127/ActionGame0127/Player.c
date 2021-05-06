#include "Player.h"
//#include "EnemyList.h"
#include "Entity.h"
#include "StackFSM.h"
#include "State.h"
#include "Idle.h"
#include "Run.h"
#include "Jump.h"
#include "Fall.h"
#include "Roll.h"
#include "Damaged.h"
#include "pinvinciblestates.h"
#include "ShootMachineGun.h"
#include "ShootMissileGun.h"
#include "ShootGuidedProjectile.h"
#include "PhysicsUtil.h"
#include "WeaponManager.h"
#include "Camera.h"
#include "EMP.h"
#include "BulletList.h"
#include <stdlib.h>
#include <math.h>
#include "Emitter.h"

//Allocate dynamic memory to a new pointer to a player.
//Return the pointer.
Entity* Player_New(float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, float jumpSpeed,
	int upperTextureID, int mainTextureID)
{
	Entity* pNew = (Entity*)malloc(sizeof(Entity));
	pNew->pArm = malloc(sizeof(Entity));

	//Player body
	MakeEntity(pNew, width, height, x, y, scaleX, scaleY, maxSpeed,
		jumpSpeed, mainTextureID, ET_PLAYER, 100.f);
	pNew->isDamaged = FALSE;
	pNew->isInvincible = FALSE;
	pNew->isRolling = FALSE;
	pNew->walkSpeed = maxSpeed;
	pNew->rollSpeed = maxSpeed * 2;
	pNew->restJump = 2;
	pNew->damageTimer = 0.f;
	pNew->invincibleTimer = 0.f;
	pNew->rollTimer = 0.f;
	pNew->rollDuration = 0.4f;
	pNew->playerIdle = malloc(sizeof(State));
	pNew->playerRun = malloc(sizeof(State));
	pNew->playerJumpIdle = malloc(sizeof(State));
	pNew->playerJumpRun = malloc(sizeof(State));
	pNew->playerFallIdle = malloc(sizeof(State));
	pNew->playerFallRun = malloc(sizeof(State));
	pNew->playerDamaged = malloc(sizeof(State));
	pNew->playerRoll = malloc(sizeof(State));
	pNew->playerNonInvincible = malloc(sizeof(State));
	pNew->playerinvincible = malloc(sizeof(State));
	MakeMainBodyIdleState(pNew->playerIdle);
	MakeMainBodyRunState(pNew->playerRun);
	MakeMainBodyJumpIdleState(pNew->playerJumpIdle);
	MakeMainBodyJumpRunState(pNew->playerJumpRun);
	MakeMainBodyFallIdleState(pNew->playerFallIdle);
	MakeMainBodyFallRunState(pNew->playerFallRun);
	MakeMainBodyDamagedState(pNew->playerDamaged);
	MakeMainBodyRollState(pNew->playerRoll);
	MakeMainBodyNormalState(pNew->playerNonInvincible);
	MakeMainBodyInvincibleState(pNew->playerinvincible);

	pNew->moveFSM = malloc(sizeof(StackFSM));
	pNew->invincibleFSM = malloc(sizeof(StackFSM));

	MakeStackFSM(pNew->moveFSM, pNew, 10);
	FSMPush(pNew->moveFSM, pNew->playerIdle);
	MakeStackFSM(pNew->invincibleFSM, pNew, 3);
	FSMPush(pNew->invincibleFSM, pNew->playerNonInvincible);

	//Player's arm
	MakeEntity(pNew->pArm, 0.f, 0.f, x, y, scaleX * 2.5f, scaleX * 2.5f, 0.f, 0.f, upperTextureID,
		ET_PLAYERARM, 0.f);
	pNew->pArm->armShootMachineGun = malloc(sizeof(State));
	pNew->pArm->armNotShootMachineGun = malloc(sizeof(State));
	pNew->pArm->armShootMissileGun = malloc(sizeof(State));
	pNew->pArm->armNotShootMissileGun = malloc(sizeof(State));
	pNew->pArm->armShootGuidedProjectile = malloc(sizeof(State));
	pNew->pArm->armNotShootGuidedProjectile = malloc(sizeof(State));
	MakeMachineGunShootState(pNew->pArm->armShootMachineGun);
	MakeMachineGunNotShootState(pNew->pArm->armNotShootMachineGun);
	MakeMissileGunShootState(pNew->pArm->armShootMissileGun);
	MakeMissileGunNotShootState(pNew->pArm->armNotShootMissileGun);
	MakeGuidedProjectileShootState(pNew->pArm->armShootGuidedProjectile);
	MakeGuidedProjectileNotShootState(pNew->pArm->armNotShootGuidedProjectile);

	WEVec2Set(&pNew->pArm->aimInfo.mousePos, 0.f, 0.f);
	WEVec2Set(&pNew->pArm->aimInfo.difference, 0.f, 0.f);
	WEVec2Set(&pNew->pArm->aimInfo.unitVector, 0.f, 0.f);
	pNew->pArm->aimInfo.angle = 0;

	MakeWeapon(&pNew->pArm->weapon);
	pNew->pArm->weapon.ownerType = OT_PLAYER;
	pNew->pArm->weapon.weaponType = MACHINE_GUN;

	pNew->pArm->shootFSM = malloc(sizeof(StackFSM));
	MakeStackFSM(pNew->pArm->shootFSM, pNew->pArm, 3);
	FSMPush(pNew->pArm->shootFSM, pNew->pArm->armNotShootMachineGun);

	//Player doesn't use upperbody's aabb. So its aabb sets (0, 0).
	//And also upperbody doesn't have maxspeed, and jumpspeed.
	/*UpperBodyMake(&(pNew->upperBody), 0.f, 0.f, x, y / 2.f,
		scaleX*0.1f, scaleY * 0.1f, 0.f, 0.f, upperTextureID);
	MakeMainBody(&(pNew->mainBody), width, height, x, y,
		scaleX, scaleY, maxSpeed, jumpSpeed, mainTextureID);*/

	return pNew;
}


//Release player.
//This function takes a pointer to the pointer to the player
//since the pointer to the player should be set as NULL.
void Player_Release(Entity** ppSelf)
{
	//Release the memory in the player.
	/*UpperBodyDelete(&((*ppSelf)->upperBody));
	DeleteMainBody(&((*ppSelf)->mainBody));
	free(*ppSelf);
	*ppSelf = 0;*/

	Entity* pSelf = *ppSelf;

	if (pSelf)
	{
		//Release player's arm
		free(pSelf->pArm->armShootMachineGun);
		free(pSelf->pArm->armNotShootMachineGun);
		free(pSelf->pArm->armShootMissileGun);
		free(pSelf->pArm->armNotShootMissileGun);
		free(pSelf->pArm->armShootGuidedProjectile);
		free(pSelf->pArm->armNotShootGuidedProjectile);
		FSMDeleteStack(pSelf->pArm->shootFSM);
		free(pSelf->pArm->shootFSM);
		free(pSelf->pArm);

		//Release player itself
		free(pSelf->playerIdle);
		free(pSelf->playerRun);
		free(pSelf->playerJumpIdle);
		free(pSelf->playerJumpRun);
		free(pSelf->playerFallIdle);
		free(pSelf->playerFallRun);
		free(pSelf->playerDamaged);
		free(pSelf->playerRoll);
		free(pSelf->playerNonInvincible);
		free(pSelf->playerinvincible);
		FSMDeleteStack(pSelf->moveFSM);
		FSMDeleteStack(pSelf->invincibleFSM);
		free(pSelf->moveFSM);
		free(pSelf->invincibleFSM);
		free(pSelf);
		*ppSelf = 0;
	}
}


void Player_Update(Entity* pSelf, TileMap* pMap,
	EnemyList* pEnemyList, float dt)
{
	pEnemyList;

	if (pSelf->onGround && pSelf->restJump < 2)
		Player_ResetJump(pSelf);
	if (WEInputIsTriggered(WE_S))
	{
		pSelf->vel.y = -pSelf->jumpSpeed * 2.f;
	}
	FSMUpdate(pSelf->moveFSM, dt);
	FSMUpdate(pSelf->invincibleFSM, dt);
	Physics_CollideAndUpdateVelocity(pSelf, pMap, dt);

	//Update player's arm
	Player_ArmAimControl(pSelf);
	FSMUpdate(pSelf->pArm->shootFSM, dt);
	pSelf->pArm->pos.x = pSelf->pos.x;
	pSelf->pArm->pos.y = pSelf->pos.y;
	
	Camera* pCamera = GetCamera();

	pSelf->pos.x = WEMathClamp(pSelf->pos.x, 
		pCamera->cPos.x - pCamera->size.x / 2.f,
		pCamera->cPos.x + pCamera->size.x / 2.f);
	
	

	if (pSelf->pos.x == pCamera->cPos.x - pCamera->size.x / 2.f)
	{
		WESMSetNextState(EMP_GameOver);
	}
	/*MainBodySMUpdate(&(pSelf->mainBody), dt);
	Physics_CollideAndUpdateVelocity(&pSelf->mainBody.base, pMap, dt);
	UpperBodyUpdate(&(pSelf->upperBody), &(pSelf->mainBody), pMap, pEnemyList, dt);*/
}

void Player_ArmAimControl(Entity* pPlayer)
{
	Entity* pArm = pPlayer->pArm;
	pArm->aimInfo.mousePos.x = (float)WEInputGetMouseX();
	pArm->aimInfo.mousePos.y = (float)WEInputGetMouseY();
	WEGraphicsConvertScreenToWorld(
		&pArm->aimInfo.mousePos.x,
		&pArm->aimInfo.mousePos.y);
	pArm->aimInfo.difference.x = pArm->aimInfo.mousePos.x - pArm->pos.x;
	pArm->aimInfo.difference.y = pArm->aimInfo.mousePos.y - pArm->pos.y;

	pArm->aimInfo.angle
		= atan2f(pArm->aimInfo.difference.y, pArm->aimInfo.difference.x);

	pArm->aimInfo.unitVector.x
		= pArm->aimInfo.difference.x / WEVec2Distance(&pArm->aimInfo.mousePos, &pArm->pos);
	pArm->aimInfo.unitVector.y
		= pArm->aimInfo.difference.y / WEVec2Distance(&pArm->aimInfo.mousePos, &pArm->pos);
	pArm->rotation = pArm->aimInfo.angle;
}

void Player_Draw(const Entity* pSelf)
{
	//UpperBodyDraw(&(pSelf->upperBody));
	//MainBody_Draw(&(pSelf->mainBody));
	Entity_Draw(pSelf, TRUE);
	Entity_Draw(pSelf->pArm, FALSE);
}

void Player_Run(Entity* pSelf, int direction, float dt)
{
	if (direction > 0)
	{
		pSelf->vel.x += pSelf->accel.x * dt;
		if (pSelf->vel.x < 0)
			pSelf->vel.x += pSelf->accel.x * dt * 0.5f;
		if (pSelf->vel.x > pSelf->maxSpeed)
			pSelf->vel.x = pSelf->maxSpeed;
	}
	else if (direction < 0)
	{
		pSelf->vel.x -= pSelf->accel.x * dt;
		if (pSelf->vel.x > 0)
			pSelf->vel.x -= pSelf->accel.x * dt * 0.5f;
		if (pSelf->vel.x < -pSelf->maxSpeed)
			pSelf->vel.x = -pSelf->maxSpeed;
	}
}

void Player_Stop(Entity* pSelf, float dt)
{
	//Make the object's velocity to zero gradually
	if (fabsf(pSelf->vel.x) > (pSelf->accel.x * dt))
	{
		if (pSelf->vel.x > 0.f)
			pSelf->vel.x -= pSelf->accel.x * dt;
		else if (pSelf->vel.x < 0.f)
			pSelf->vel.x += pSelf->accel.x * dt;
	}
	else
		pSelf->vel.x = 0.f;
}

void Player_Jump(Entity* pSelf)
{
	if (pSelf->restJump > 0)
	{
		pSelf->vel.y = pSelf->jumpSpeed;
		pSelf->restJump -= 1;
		pSelf->onGround = FALSE;
	}
}

void Player_ResetJump(Entity* pSelf)
{
	pSelf->restJump = 2;
}

void Player_ApplyDamage(Entity* pSelf, float damage)
{
	if (pSelf->isInvincible == TRUE)
		return;
	pSelf->hp -= damage;
	if (pSelf->hp < 0.f)
	{
		pSelf->hp = 0.f;
		EmitterCreate(pSelf, PS_DIE);
	}

	pSelf->isDamaged = TRUE;
	pSelf->isInvincible = TRUE;

	FSMPush(pSelf->moveFSM, pSelf->playerDamaged);
}