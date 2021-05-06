/******************************************************************************/
/*!
\file   Entity.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about entity(game object).
*/
/******************************************************************************/
#ifndef ENTITY_H
#define ENTITY_H

//Third-party headers
#include "WarpEngine.h"
#include "WeaponManager.h"
#include "State.h"//temp include
#include "StackFSM.h"//temp include

typedef enum EntityType{ET_BASE, ET_PLAYER, ET_PLAYERARM,
ET_MAINBODY, ET_UPPERBODY, ET_ENEMY, ET_BOSS, ET_BULLET, ET_FIREBALL}EntityType;

typedef enum EnemyType{ ENEMY_NORMAL, ENEMY_BOMB }EnemyType;

typedef enum PSType{ PS_JUMP, PS_ROLL, PS_SHOOT, PS_HIT, PS_DIE, PS_LAND, PS_MOVEMENT }PSType;


typedef struct Color4{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}Color4;

typedef struct AimInfo
{
	WEVec2 mousePos;		//Vector to get mouse position
	WEVec2 difference;		//Distance between the mouse and the MainBody.
	WEVec2 unitVector;
	float angle;			//Angle between the MainBody and mouse
}AimInfo;

typedef struct State State;
typedef struct StackFSM StackFSM;

typedef struct Entity{
	EntityType type;
	WEVec2 aabb;
	WEVec2 pos;
	WEVec2 scale;
	WEVec2 vel;
	WEVec2 accel;
	float rotation;
	float maxSpeed;
	float jumpSpeed; // initial jump speed
	int onGround;
	int texture;
	Color4 color;
	Color4 hpColor;
	float zOrder;
	float maxHp;
	float hp;
	float timer;
	BOOL isDead;

	/*************************************************************************/
	//Player
	struct Entity* pArm;
	BOOL isDamaged;
	BOOL isInvincible;
	BOOL isRolling;
	float walkSpeed;
	float rollSpeed;
	int restJump;
	float damageTimer;
	float invincibleTimer;
	float rollTimer;
	float rollDuration;

	State* playerIdle;
	State* playerRun;
	State* playerJumpIdle;
	State* playerJumpRun;
	State* playerFallIdle;
	State* playerFallRun;
	State* playerDamaged;
	State* playerRoll;

	State* playerNonInvincible;
	State* playerinvincible;

	StackFSM* moveFSM; //(use : Player, Boss1)
	StackFSM* invincibleFSM;
	/*************************************************************************/
	//Player's Arm
	AimInfo aimInfo;
	Weapon weapon; // Enemy(shooter) also uses this variable.

	State* armShootMachineGun;
	State* armNotShootMachineGun;
	State* armShootMissileGun;
	State* armNotShootMissileGun;
	State* armShootGuidedProjectile;
	State* armNotShootGuidedProjectile;

	StackFSM* shootFSM; //Enemy(shooter, bomb) also uses this.
	/*************************************************************************/
	//Enemy
	EnemyType enemyType;
	struct Entity* pTarget;//users : Enemy, Boss1
		//Shooter
	State* enemyShootState;
		//Bomb
	float explosionTimer;
	float explosionDelay;
	State* enemyIdleState;
	State* enemyExplodeState;
	/*************************************************************************/

	/*************************************************************************/
	//Boss1
	//pTarget, moveFSM
	//the boss uses timer var as delay between attack patterns.
	//and also for pattern3.
	//the boss uses texture var as a health bar texture.
	//the boss uses damage var as a pattern3's damage
	State* bossWalk; //moveFSM uses this state.
	
	int gearTexture;
	float gearAngle;
	float gearSpeed;
	int eyeTexture;
	float eyeAngle;
	float attackDelay;

	WEVec2 firstFireballOffset; // the position of the fireball shot first.
	WEVec2 lastFireballOffset; //the position of the fireball shot last.
	int maxNumOfFB;// max count of fireballs which boss shoots at once.
	int numOfFB;
	float fbShootTimer;
	float fbShootDuration;

	struct Entity* fireballArr;

	State* bossAttackIdle;
	State* bossPattern1[2];
	State* bossPattern2[2];
	State* bossPattern3[2];
	StackFSM* attackFSM;
	WEVec2 initialPos;
	/*************************************************************************/
	//Fireball
	//initialPos, pTarget
	//The fireball uses timer var as checking moveduration
	WEVec2 targetPos;
	State fireballMove[2];
	float damage;
	float moveDuration;
	float readyTimer;
	StackFSM fireballFSM;

	/*************************************************************************/
	/*************************************************************************/
	//Emitter
	BOOL drawOrNot;
	WEVec2 gravity;
	int count;
	float speed;
	float speedVar;
	float angle;
	float angleVar;
	float life;
	float lifeVar;
}Entity;

void MakeEntity(Entity* pResult, 
	float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, 
	float jumpSpeed, int textureID, EntityType type, float health);
//void Entity_Delete(Entity** ppToDelete);

void Entity_Draw(const Entity* pSelf, BOOL drawHealth);


#endif

/*struct camera
{
	x,y
		velocity
		sizex
		y
};

static int time = 0;
#define MAX_TIME 5

camerainit(float MainBodyx, float MainBodyy)
{
	camera.x = MainBodyx
	camera.y = y
	velocity = 0
}

camera(float x, y, dt)

	if (time + dt >= MAX_TIME)
	{
		IF
		= charater.x - .x
			= character.y - camera.y

			velocity.x = character.x - camera.x / MAX_TIME
			velocity.y = character.y - camera.y
			time = 0;
	}
	else
	{
		camera. = character.x
			camera = charater.y
	}

	int xdaas= camera position +  velocity;
	WEGraphicsSetCamera(camera position + velocity);
}
*/
