#include "Weapon.h"
#include "Object.h"
#include "Projectile.h"
#include "Entity.h"
#include "ResourceManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

Weapon::Weapon(sf::Vector2f pos, sf::Sprite sprite,
               int frequency, float speed, bool isEnemyGun)
    : Object{pos, sprite}, frequency{frequency}, speed{speed}, clock{}, isPickedUp{false},isEnemyGun{isEnemyGun}
{
    
}

Weapon::Weapon(): Object{{},{}}
{}

Weapon* Weapon::CreateNewFromType(int type)
{
    if(type == 2)
    {
        return new Weapon{{0,0}, ResourceManager::getSpriteWithName(Tex::Supersoaker), 4, 6, false};
    }
    else if(type == 3)
    {
        return new Weapon{{0,0}, ResourceManager::getSpriteWithName(Tex::Powerwasher), 7, 8, false};
    }
}

void Weapon::collide(Object* other)
{
    
}

Projectile* Weapon::use(sf::Vector2f pos, float angle)
{
    if(clock.getElapsedTime().asSeconds() > 1.f/static_cast<float>(frequency))
    {
        clock.restart();
        return new Projectile(pos, angle, speed, isEnemyGun);
    }
    else 
        return nullptr;
}

