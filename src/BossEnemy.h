#include "Entity.h"
#include "Weapon.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "BossWeapon.h"

class BossEnemy : public Entity
{
public:
    BossEnemy(sf::Vector2f pos);
    void shoot(float angle) override;
    void collide(Object* other) override;
    void move(sf::Vector2f playerpos) override;

private:
    float mainAngle;
};
