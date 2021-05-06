//Header file related to the implementation
#include "Emitter.h"

//Project-related headers
#include "Particle.h"

#include "WarpEngine.h"

#include "PS.h"
#include "BulletList.h"
#include "TextureList.h"

//Standard library headers
#include <stdlib.h>
#include <math.h>
static EmitterList emitterList;

void EmitterInit(void)
{
	emitterList.headEmitter = 0;
	emitterList.tailEmitter = 0;
}

void EmitterCreate(const Entity* pOwner, PSType particleType)
{
	int textureID = 0;

	if (emitterList.headEmitter == NULL)
	{
		emitterList.headEmitter = (Emitter*)malloc(sizeof(Emitter));
		emitterList.headEmitter->pPrev = NULL;
		emitterList.tailEmitter = emitterList.headEmitter;
		emitterList.tailEmitter->pNext = NULL;
		emitterList.tailEmitter->pPrev = NULL;
	}

	else
	{
		emitterList.tailEmitter->pNext = (Emitter*)malloc(sizeof(Emitter));
		emitterList.tailEmitter->pNext->pPrev = emitterList.tailEmitter;
		emitterList.tailEmitter = emitterList.tailEmitter->pNext;
		emitterList.tailEmitter->pNext = NULL;
	}

	WEUNUSED_PARAM(pOwner);
	WEUNUSED_PARAM(particleType);

	switch (particleType){
	case PS_JUMP:
		break;
	case PS_ROLL:
		break;
	case PS_SHOOT:
		break;
	case PS_HIT:
		textureID = TextureList_GetID(TX_PS_TEST);
		EmitterSetting(pOwner, particleType, 10, 0, textureID,
			0.f, 0.f, pOwner->vel.x, pOwner->vel.y,
			0.f, 0.f, pOwner->accel.x, pOwner->accel.y, 2.f,
			0.f, 5.f, 0.f, 360.f, 2.f, 2.f);
		break;
	case PS_DIE:
		textureID = TextureList_GetID(TX_PS_TEST);
		EmitterSetting(pOwner, particleType, 200, 0, textureID,
			1.f, 1.f, pOwner->vel.x, pOwner->vel.y,
			1.f, 1.f, pOwner->accel.x, pOwner->accel.y, 10.f,
			5.f, 5.f, 5.f, 360.f, 10.f, 10.f);
		break;
	case PS_LAND:
		break;
	case PS_MOVEMENT:
		break;
	}


}

void EmitterSetting(const Entity* pOwner, PSType particleType,
	int numOfParticles, int drawOrNot, int textureID, 
	float x, float y,
	float vx, float vy, float gx, float gy, 
	float ax, float ay, float scale,
	float emitterSpeed, float emitterSpeedVar,
	float emitterAngle, float emitterAngleVar,
	float emitterLife, float emitterLifeVar)
{
	Emitter* pResult = emitterList.tailEmitter;
	int i;

	pResult->base.count = numOfParticles;
	pResult->base.pos.x = pOwner->pos.x + x; pResult->base.pos.y = pOwner->pos.y + y;
	pResult->base.vel.x = vx; pResult->base.vel.y = vy;
	pResult->base.gravity.x = gx; pResult->base.gravity.y = gy;
	pResult->base.accel.x = ax; pResult->base.accel.y = ay;
	pResult->base.scale.x = scale; pResult->base.scale.y = scale;
	pResult->base.texture = textureID;
	pResult->base.drawOrNot = drawOrNot;

	pResult->base.isDead = FALSE;

	pResult->particleList.headParticle = NULL;
	pResult->particleList.tailParticle = NULL;

	pResult->base.speed = emitterSpeed;
	pResult->base.speedVar = emitterSpeedVar;
	pResult->base.angle = WEMathDegreeToRadian(emitterAngle);
	pResult->base.angleVar = WEMathDegreeToRadian(emitterAngleVar);
	pResult->base.life = emitterLife;
	pResult->base.lifeVar = emitterLifeVar;

	for (i = 0; i < pResult->base.count; ++i)
	{
		WEVec2 vel;
		float angle = pResult->base.angle + 
			WERandFloatMinMax(-1.f * pResult->base.angleVar / 2.f, pResult->base.angleVar / 2.f);
		float speed = pResult->base.speed +
			WERandFloatMinMax(-1.f * pResult->base.speedVar / 2.f, pResult->base.speedVar / 2.f);
		float life = pResult->base.life +
			WERandFloatMinMax(-1.f * pResult->base.lifeVar / 2.f, pResult->base.lifeVar / 2.f);

		vel.x = cosf(angle) * speed;
		vel.y = sinf(angle) * speed;

		ParticleCreate(&pResult->particleList, &pResult->base,particleType,
			pResult->base.pos.x, pResult->base.pos.y,
			vel.x, vel.y, life, 
			scale, 0.f);
	}
	

}
/*
void EmitterAddParticle()
{
}*/

void EmitterUpdate(float dt)
{
	Emitter* pEmitter = emitterList.headEmitter;

	while (pEmitter != NULL)
	{
		if (pEmitter->particleList.headParticle == NULL)
			pEmitter->base.isDead = TRUE;

		ParticleUpdate(&pEmitter->particleList, dt);
		ParticleDelete(&pEmitter->particleList);

		pEmitter = pEmitter->pNext;
	}

	WEUNUSED_PARAM(dt);
}

void EmitterDraw(void)
{
	Emitter* pEmitter = emitterList.headEmitter;

	while (pEmitter != NULL)
	{
		ParticleDraw(&pEmitter->particleList);

		pEmitter = pEmitter->pNext;
	}
}

void EmitterDelete(void)
{
	Emitter* pEmitter = emitterList.headEmitter;

	while (pEmitter != NULL)
	{
		if (pEmitter->base.isDead)
		{
			if (pEmitter == emitterList.headEmitter)
			{
				if (pEmitter->pNext != NULL)
				{
					emitterList.headEmitter = pEmitter->pNext;
					emitterList.headEmitter->pPrev = NULL;
					free(pEmitter);
					return;
				}
				else
				{
					free(pEmitter);
					emitterList.headEmitter = NULL;
					emitterList.tailEmitter = NULL;
					return;
				}
			}
		}
		pEmitter = pEmitter->pNext;
	}
}

void EmitterAllDelete(void)
{
	Emitter* pEmitter = emitterList.headEmitter;

	while (pEmitter != NULL)
	{
		ParticleAllDelete(&pEmitter->particleList);
		
		Emitter* tempEmitter = pEmitter;
		pEmitter = pEmitter->pNext;
		free(tempEmitter);
	}
}


/**************************************************************************************************************/
/**************************************************************************************************************/