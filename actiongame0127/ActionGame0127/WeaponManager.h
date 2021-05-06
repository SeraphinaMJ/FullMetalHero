/******************************************************************************/
/*!
\file   Bullet.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about bullet manager
*/
/******************************************************************************/\
#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

typedef enum OwnerType OwnerType;
typedef enum WeaponType WeaponType;

typedef struct CoolDown{
	float countTime;
	float machineGunCD;
	float missileGunCD;
	float basicEnemyGunCD;
}CoolDown;

typedef struct Weapon
{
	OwnerType ownerType;
	WeaponType weaponType;

	CoolDown coolDown;
}Weapon;

void MakeWeapon(Weapon* pWeapon);

#endif