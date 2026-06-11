#include "MeleeEnemy.h"
#include "Entity.h"
#include "Projectile.h"
#include "Utils.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

MeleeEnemy::MeleeEnemy(sf::Vector2f pos)
    : Entity(pos, ResourceManager::getSpriteWithName(Tex::Melee),
	     5, 2, nullptr)
{
    sprite.setPosition(pos);
}

void MeleeEnemy::collide(Object* other)
{
    if(dynamic_cast<Projectile*>(other) != nullptr
       && !(dynamic_cast<Projectile*>(other)->isEnemyFired))
    {
        change_hp(-1);
    }

    Entity::collide(other);
}

void MeleeEnemy::move(sf::Vector2f playerpos)
{
    if(isPushed)
    {
        pushback();
        return;
    }
    
    old_pos = pos;
    sf::Vector2f newPos {Utils::GetNormalizedDirection(playerpos, pos)};
    moveToPos({pos.x + (newPos.x * float(speed)), pos.y + (newPos.y * float(speed))});
}
