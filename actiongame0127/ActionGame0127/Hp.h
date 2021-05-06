/******************************************************************************/
/*!
\file   Hp.h
\author Minji Kim
\par    email: seraminji2146\@gmail.com
\brief
This is the source file about health bar
*/
/******************************************************************************/

#ifndef HP_H
#define HP_H

#include "WarpEngine.h"

#include "Boss.h"
#include "EntityManager.h"


float ratio;
float transX;

typedef struct
{
	float HpLife;
	float HpMaxLife;

}HP_Bar;


static HP_Bar hp_bar;
//void HpBar_Init(Boss* pSelf);
void HpBar_Set(float health);
//void HpBar_Draw(void);

#endif