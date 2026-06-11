#include "BossWeapon.h"
#include "Entity.h"
#include "Weapon.h"
#include <SFML/System/Vector2.hpp>
#include "ResourceManager.h"
#include "Projectile.h"


BossWeapon::BossWeapon(sf::Vector2f pos) : Weapon(pos, ResourceManager::getSpriteWithName(Tex::Watergun),20,4, true), clock{} {}


Projectile* BossWeapon::use(sf::Vector2f pos, float angle)
{
    return new Projectile{pos, angle, speed, isEnemyGun};
}
