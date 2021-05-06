/******************************************************************************/
/*!
\file   Hp.c
\author Minji Kim
\par    email: seraminji2146\@gmail.com
\brief
This is the source file about health bar
*/
/******************************************************************************/

#include "Hp.h"

#include "Camera.h"
#include "EntityManager.h"

void HpBar_Set(float health)
{
	hp_bar.HpMaxLife = BOSS_LIFE;
	hp_bar.HpLife = health;

	//what if we killed a Boss? NEED TO FIX THE IF STATE
	if (hp_bar.HpLife)
	{
		ratio = (hp_bar.HpLife / hp_bar.HpMaxLife) * 500.f;
		transX = (((float)WEApplicationGetWidth() / 2) - (1 - ratio)/2);

	}
	else
	{
		transX = 0;
	}

}

