#ifndef Emitter_H
#define Emitter_H

//Project-related headers
#include "Entity.h"
#include "Particle.h"

//Third-party headers
#include "WarpEngine.h"



typedef struct Emitter{
	struct Emitter* pNext;
	struct Emitter* pPrev;

	ParticleList particleList;

	Entity base;	
}Emitter;

typedef struct EmitterList{
	Emitter* headEmitter;
	Emitter* tailEmitter;
}EmitterList;

void EmitterInit(void);
void EmitterCreate(const Entity* pEntity, PSType particleType);
void EmitterSetting(const Entity* pOwner, PSType particleType,
	int numOfParticles, int drawOrNot, int textureID,
	float x, float y,
	float vx, float vy, float gx, float gy,
	float ax, float ay, float scale,
	float emitterSpeed, float emitterSpeedVar,
	float emitterAngle, float emitterAngleVar,
	float emitterLife, float emitterLifeVar);
void EmitterUpdate(float dt);
void EmitterDraw(void);
void EmitterDelete(void);
void EmitterAllDelete(void);

#endif
