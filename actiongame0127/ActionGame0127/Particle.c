//Header file related to the implementation
#include "Particle.h"

#include "Emitter.h"
#include "TextureList.h"

//Standard library headers
#include <math.h>
#include <time.h>
#include <stdlib.h>


void ParticleCreate(ParticleList* pList, const Entity* pEmitter, const PSType particleType,
	float x, float y, float vx, float vy, float life, float scale, float rotation)
{
	int textureID = 0;

	if (pList->headParticle == NULL)
	{
		pList->headParticle = (Particle*)malloc(sizeof(Particle));
		pList->headParticle->pPrev = NULL;
		pList->tailParticle = pList->headParticle;
		pList->tailParticle->pNext = NULL;
		pList->tailParticle->pPrev = NULL;
	}

	else
	{
		pList->tailParticle->pNext = (Particle*)malloc(sizeof(Particle));
		pList->tailParticle->pNext->pPrev = pList->tailParticle;
		pList->tailParticle = pList->tailParticle->pNext;
		pList->tailParticle->pNext = NULL;
	}

	switch (particleType){
	case PS_JUMP:
		break;
	case PS_ROLL:
		break;
	case PS_SHOOT:
		break;
	case PS_HIT:
		textureID = TextureList_GetID(TX_PS_TEST);
		ParticleSetting(pList, pEmitter, textureID,
			x, y, 1, 1, vx, vy, life, scale, rotation);
		break;
	case PS_DIE:
		textureID = TextureList_GetID(TX_PS_TEST);
		ParticleSetting(pList, pEmitter, textureID,
			x, y, 1, 1, vx, vy, life, scale, rotation);
		break;
	case PS_LAND:
		break;
	case PS_MOVEMENT:
		break;
	}
}

void ParticleSetting(ParticleList* pList, const Entity* pEmitter, int textureID, float x, float y, float ax, float ay,
	float vx, float vy, float life, float scale, float rotation)
{
	Particle* pParticle = pList->tailParticle;

	pParticle->owner = pEmitter;

	pParticle->base.texture = textureID;
	pParticle->base.pos.x = x;
	pParticle->base.pos.y = y;
	pParticle->base.vel.x = vx;
	pParticle->base.vel.y = vy;
	pParticle->base.accel.x = ax;
	pParticle->base.accel.y = ay;
	pParticle->base.life = life;
	pParticle->base.maxHp = life;
	pParticle->base.scale.x = scale;
	pParticle->base.scale.y = scale;
	pParticle->base.rotation = rotation;
	pParticle->base.isDead = FALSE;

	pParticle->base.color.r = (char)WERandIntMinMax(0, 255);
	pParticle->base.color.g = (char)WERandIntMinMax(0, 255);
	pParticle->base.color.b = (char)WERandIntMinMax(0, 255);
	pParticle->base.color.a = (char)WERandIntMinMax(100, 150);
}

void ParticleUpdate(ParticleList* pList, float dt)
{
	Particle* pParticle = pList->headParticle;
	while (pParticle)
	{

		pParticle->base.vel.x += pParticle->base.accel.x * dt;
		pParticle->base.vel.y += pParticle->base.accel.y * dt;

		pParticle->base.vel.x += pParticle->owner->gravity.x * dt;
		pParticle->base.vel.y += pParticle->owner->gravity.y * dt;

		pParticle->base.pos.x += pParticle->base.vel.x * dt;
		pParticle->base.pos.y += pParticle->base.vel.y * dt;

		pParticle->base.life -= dt;

		pParticle->base.scale.x = pParticle->base.life * pParticle->base.scale.x / pParticle->base.maxHp;
		pParticle->base.scale.y = pParticle->base.scale.x;


		if (pParticle->base.life <= 0.0f)
		{
			pParticle->base.life = 0.f;
			pParticle->base.isDead = TRUE;
		}


		pParticle = pParticle->pNext;
	}
}
void ParticleDraw(ParticleList* pList)
{
	Particle* pParticle = pList->headParticle;

	while (pParticle)
	{
		WEMtx44 transform;
		WEMtx44MakeTransform(&transform,
			pParticle->base.scale.x,
			pParticle->base.scale.y,
			pParticle->base.rotation,
			pParticle->base.pos.x,
			pParticle->base.pos.y,
			0.f);

		WEGraphicsSetTexture(pParticle->base.texture);
		WEGraphicsSetAttributeColor4(
			pParticle->base.color.r,
			pParticle->base.color.g,
			pParticle->base.color.b,
			pParticle->base.color.a);
		WEGraphicsDraw(&transform);

		pParticle = pParticle->pNext;
	}
}

void ParticleDelete(ParticleList* pList)
{
	Particle* pParticle = pList->headParticle;

	while (pParticle != NULL)
	{
		if (pParticle->base.isDead)
		{
			if (pParticle == pList->headParticle)
			{
				if (pParticle->pNext != NULL)
				{
					pList->headParticle = pParticle->pNext;
					pList->headParticle->pPrev = NULL;
					free(pParticle);
					return;
				}
				else
				{
					free(pParticle);
					pList->headParticle = NULL;
					pList->tailParticle = NULL;
					return;
				}
			}
		}
		pParticle = pParticle->pNext;
	}
}

void ParticleAllDelete(ParticleList* pList)
{
	Particle* pParticle = pList->headParticle;

	while (pParticle != NULL)
	{
		Particle* tempParticle = pParticle;
		pParticle = pParticle->pNext;
		free(tempParticle);
	}
}