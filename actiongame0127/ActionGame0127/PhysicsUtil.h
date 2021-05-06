#ifndef	PHYSICSUTIL_H
#define PHYSICSUTIL_H

typedef struct Entity Entity;
typedef struct TileMap TileMap;
typedef struct Enemy Enemy;

void Physics_CollideAndUpdateVelocity(
	Entity* pEntity, const TileMap* pMap, float dt);

void Physics_MainBodyVsEnemy(Entity* pMainBody, Entity* pEnemy);

#endif