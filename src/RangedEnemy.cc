#include "RangedEnemy.h"
#include "Projectile.h"
#include <SFML/Graphics/Rect.hpp>
#include "ResourceManager.h"
#include "Utils.h"

RangedEnemy::RangedEnemy(sf::Vector2f pos)
    : Entity(pos, ResourceManager::getSpriteWithName(Tex::Ranged),
             5, 4, new Weapon{pos, ResourceManager::getSpriteWithName(Tex::Watergun),1,4, true})
{
    sprite.setPosition(pos);
}

void RangedEnemy::collide(Object* other)
{
    if(dynamic_cast<Projectile*>(other) != nullptr
       && !(dynamic_cast<Projectile*>(other)->isEnemyFired))
    {
        change_hp(-1);
    }

    Entity::collide(other);
}

void RangedEnemy::move(sf::Vector2f playerpos)
{
    if(isPushed)
    {
        pushback();
        return;
    }
    
    float safeDist {150.f};
    if(Utils::GetDistance(playerpos, pos) >= safeDist)
        return;

    old_pos = pos;

    //invert the positons we give to meleeenemy to get direction away from player
    sf::Vector2f newPos {Utils::GetNormalizedDirection(pos, playerpos)};
    moveToPos({pos.x + (newPos.x * float(speed)), pos.y + (newPos.y * float(speed))});
}
