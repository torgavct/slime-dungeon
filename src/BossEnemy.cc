#include "BossEnemy.h"
#include "BossWeapon.h"
#include "Projectile.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "ResourceManager.h"
#include "Utils.h"

BossEnemy::BossEnemy(sf::Vector2f pos)
    : Entity(pos, ResourceManager::getSpriteWithName(Tex::Boss),
             25, 1, new BossWeapon{pos}), mainAngle{0}
{
    sprite.setPosition(pos);
}

void BossEnemy::collide(Object* other)
{
    if(dynamic_cast<Projectile*>(other) != nullptr
       && !(dynamic_cast<Projectile*>(other)->isEnemyFired))
    {
        change_hp(-1);
    }

    Entity::collide(other);
}

void BossEnemy::move(sf::Vector2f playerpos)
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

void BossEnemy::shoot(float angle)
{
    BossWeapon* bweapon {dynamic_cast<BossWeapon*>(weapon)};

    if(bweapon == nullptr)
        return;

    if(bweapon->clock.getElapsedTime().asSeconds() > 1.f/static_cast<float>(2))
    {
        bweapon->clock.restart();
   
        
        sf::Vector2f spawnPoint {pos.x + 64, pos.y + 64};
        Projectile* p1 {bweapon->use(spawnPoint, 0.f + mainAngle)};
        Projectile* p2 {bweapon->use(spawnPoint, 1.5f + mainAngle)};
        Projectile* p3 {bweapon->use(spawnPoint, -3.14f + mainAngle)};
        Projectile* p4 {bweapon->use(spawnPoint, -1.5f + mainAngle)};

        if(p1 != nullptr)
            projectiles.push_back(p1);

        if(p2 != nullptr)
            projectiles.push_back(p2);

        if(p3 != nullptr)
            projectiles.push_back(p3);

        if(p4 != nullptr)
            projectiles.push_back(p4);

        mainAngle += 0.3f;
        // if(mainAngle == 0.f)
        //     mainAngle = 0.75f;
        // else if (mainAngle == 0.75f)
        //     mainAngle = 1.5f;
        // else if (mainAngle == 1.5f)
        //     mainAngle = -0.75f;
        // else if (mainAngle == -0.75f)
        //     mainAngle = -1.5f;
        // else if (mainAngle == -1.5f)
        //     mainAngle = 0.f;
                
            
            
    }
}
