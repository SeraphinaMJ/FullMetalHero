/******************************************************************************/
/*!
\file   Entity.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about entity(game object).
*/
/******************************************************************************/
//Project-related headers
#include"Entity.h"
#include "LayerInfo.h"
#include <math.h>

void MakeEntity(Entity* pResult,
	float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, 
	float jumpSpeed, int textureID, EntityType type, float health)
{
	pResult->type = type;
	WEVec2Set(&pResult->aabb, width, height);
	WEVec2Set(&pResult->pos, x, y);
	WEVec2Set(&pResult->scale, scaleX, scaleY);
	WEVec2Set(&pResult->vel, 0, 0);
	WEVec2Set(&pResult->accel, 120.f, 0);
	pResult->rotation = 0.f;
	pResult->maxSpeed = maxSpeed;
	pResult->jumpSpeed = jumpSpeed;
	pResult->onGround = 0;
	pResult->texture = textureID;
	pResult->color.r = 255; pResult->color.g = 255;
	pResult->color.b = 255; pResult->color.a = 255;
	pResult->hpColor.r = 255; pResult->hpColor.g = 255;
	pResult->hpColor.b = 255; pResult->hpColor.a = 40;
	pResult->zOrder = LAYER_2;
	pResult->maxHp = health;
	pResult->hp = health;
	pResult->isDead = FALSE;
	pResult->timer = 0.f;
}

//void Entity_Delete(Entity** ppToDelete)
//{
//	if (*ppToDelete)
//	{
//		free(*ppToDelete);
//		*ppToDelete = NULL;
//	}
//}

void Entity_Draw(const Entity* pSelf, BOOL drawHealth)
{
	WEMtx44 transform;
	if (drawHealth)
	{
		WEMtx44MakeTransform(&transform,
			pSelf->scale.x,
			pSelf->scale.y,
			pSelf->rotation,
			pSelf->pos.x,
			pSelf->pos.y,
			pSelf->zOrder);
		WEGraphicsSetTexture(pSelf->texture);
		WEGraphicsSetAttributeColor4(
			pSelf->hpColor.r, pSelf->hpColor.g,
			pSelf->hpColor.b, pSelf->hpColor.a);
		WEGraphicsSetTextureCoords(1.f, 1.f, 0.f, 0.f, 0.f);
		WEGraphicsDraw(&transform);

		WEVec2 adjust;
		WEVec2Set(&adjust,
			0.f, pSelf->scale.y * (pSelf->hp / pSelf->maxHp - 1.f) / 2.f);
		WEVec2Set(&adjust,
			cosf(pSelf->rotation) * adjust.x - 
			sinf(pSelf->rotation) * adjust.y,
			sinf(pSelf->rotation) * adjust.x + 
			cosf(pSelf->rotation) * adjust.y);
		adjust.x += pSelf->pos.x;
		adjust.y += pSelf->pos.y;


		WEMtx44MakeTransform(&transform,
			pSelf->scale.x,
			pSelf->hp <= 0.f ? 0.f : pSelf->scale.y * (pSelf->hp / pSelf->maxHp),
			pSelf->rotation,
			adjust.x,
			adjust.y,
			pSelf->zOrder);
		WEGraphicsSetAttributeColor4(
			pSelf->color.r, pSelf->color.g,
			pSelf->color.b, pSelf->color.a);
		WEGraphicsSetTextureCoords(
			1.f, pSelf->hp / pSelf->maxHp, 0.f, 0.f, 0.f);
		WEGraphicsDraw(&transform);
		WEGraphicsSetTextureCoords(1.f, 1.f, 0.f, 0.f, 0.f);
	}
	else
	{
		WEMtx44MakeTransform(&transform,
			pSelf->scale.x,
			pSelf->scale.y,
			pSelf->rotation,
			pSelf->pos.x,
			pSelf->pos.y,
			pSelf->zOrder);
		WEGraphicsSetTexture(pSelf->texture);
		WEGraphicsSetAttributeColor4(
			pSelf->color.r, pSelf->color.g,
			pSelf->color.b, pSelf->color.a);
		WEGraphicsSetTextureCoords(1.f, 1.f, 0.f, 0.f, 0.f);
		WEGraphicsDraw(&transform);
	}
}