#include "Entity.h"
#include "Weapon.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class RangedEnemy : public Entity
{
public:
    //! @brief the constructor for creating a new ranged enemy
    //! @param pos - the initial position of the enemy
    RangedEnemy(sf::Vector2f pos);
    void collide(Object* other) override;
    void move(sf::Vector2f playerpos) override;

};
