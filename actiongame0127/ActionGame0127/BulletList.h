#ifndef BULLETLIST_H
#define BULLETLIST_H

//Project-related headers
#include "Entity.h"

//Third-party headers
#include "WarpEngine.h"
#include "StackFSM.h"
#include "State.h"

typedef struct TileMap TileMap;
typedef struct EntityManager EntityManager;

typedef enum OwnerType{ OT_PLAYER, OT_ENEMY }OwnerType;

typedef enum WeaponType { MACHINE_GUN = 0, MISSILE_GUN, GUIDED_PROJECTILE, FIRE_BALL, ENEMY_BASIC}WeaponType;

typedef struct BulletNode{
	Entity base;

	WEVec2 targetPosition;

	StackFSM fsm;

	State machineGunBulletState;
	State missileGunBulletState;
	State guidedProjectileState;
	State enemyBasicBulletState;

	WeaponType weaponType;
	OwnerType ownerType;
	float time;
	float damage;
	BOOL dead;

	struct BulletNode* pNext;
	struct BulletNode* pPrev;

}BulletNode;

typedef struct BulletList{
	BulletNode* pHead;
	BulletNode* pTail;
}BulletList;

BulletNode* GetBulletHead(void);

void BulletAddToEnd(Entity* pUpperEntity, WeaponType weaponType, OwnerType ownerType, WEVec2 unitVector);

void BulletUpdate(const TileMap* pMap, EntityManager* pEntityManager, float dt);

void BulletDraw(void);

void BulletAllDelete(void);
void BulletDelete(void);



#endif