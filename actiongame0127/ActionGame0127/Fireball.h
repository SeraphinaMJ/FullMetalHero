#ifndef FIREBALL_H
#define FIREBALL_H

typedef struct Entity Entity;

//Entity* Fireball_New(float vx, float vy);

void Fireball_Make(Entity* pResult, float x, float y,
	float vx, float vy, Entity* pTarget);

void Fireball_CollideToTarget(Entity* pBall);

#endif