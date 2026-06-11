#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile(sf::Vector2f pos, float angle, int speed, bool isEnemyFired);
    void collide(Object* other) override;
    void move(sf::Vector2f playerpos) override {};
    //! @brief custom move-function since projectiles doesn't rely on the player position
    void move();
    bool isEnemyFired; //!< true if the enemy has fired this and should only damage the player
private:
    float angle;
};
