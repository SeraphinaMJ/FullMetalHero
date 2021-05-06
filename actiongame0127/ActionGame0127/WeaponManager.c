#include "WeaponManager.h"

#include "UpperBody.h"
#include "BulletList.h"

void MakeWeapon(Weapon* pWeapon)
{
	pWeapon->coolDown.countTime = 0.0f;
	pWeapon->coolDown.machineGunCD = 0.2f;
	pWeapon->coolDown.missileGunCD = 0.3f;
	pWeapon->coolDown.basicEnemyGunCD = 2.f;
}

