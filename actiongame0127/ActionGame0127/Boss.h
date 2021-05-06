#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"
#include "StackFSM.h"
#include "State.h"
#include "Player.h"

Entity* Boss_New(float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, 
	int gearTextureID, int hpBarTextureID, int eyeTextureID,
	float health, Entity* pTarget);
void Boss_Release(Entity** ppSelf);

void Boss_Update(Entity* pSelf, float dt);
void Boss_Draw(const Entity* pSelf);

#endif//BOSS_H