#ifndef PARTICLE_H
#define PARTICLE_H

//Project-related headers
#include "Enemy.h"

//Third-party headers
#include "WarpEngine.h"

typedef struct Emitter Emitter;

typedef struct Particle{
	struct Particle* pNext;
	struct Particle* pPrev;

	const Entity* owner;

	Entity base;

}Particle;

typedef struct ParticleList{
	Particle* headParticle;
	Particle* tailParticle;
}ParticleList;

void ParticleInit(void);

void ParticleCreate(ParticleList* pList, const Entity* pEmitter, const PSType particleType, 
	float x, float y, float vx, float vy, float life, float scale, float rotation);

void ParticleSetting(ParticleList* pList, const Entity* pEmitter, int textureID, float x, float y,
	float ax, float ay, float vx, float vy, float life, float scale, float rotation);

void ParticleUpdate(ParticleList* pList, float dt);
void ParticleDraw(ParticleList* pList);
void ParticleDelete(ParticleList* pList);
void ParticleAllDelete(ParticleList* pList);


#endif