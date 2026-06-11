#pragma once
#include "Object.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Projectile;
class Weapon;


class Entity : public Object
{
public:
    
    //! @brief Constructor for creating a new Entity
    Entity(sf::Vector2f pos, sf::Sprite sprite, int max_health, int speed, Weapon* weapon);
    
    //! @brief Destructor for deleting an Entity.
    virtual ~Entity();

    
    //! @brief logic for movement.
    virtual void move(sf::Vector2f playerpos) = 0;


    
    //! @brief push this entity towards targetPos.
    void pushback();
    
    //! @brief handles collision with other objects
    void collide(Object* other) override;
    
    //! @brief custom behaviour for drawing
    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;

    
    //! @brief logic for shooting if a weapon is set in the constructer.
    virtual void shoot(float angle);
    //! @brief function for changing the hp.
    //! @param diff - how much hp to change, can be neg. or pos.
    void change_hp(int diff);
    //! @brief returns the hp
    int get_hp();
    //! @brief return any projectiles this entity has fired.
    std::vector<Projectile*>& get_projectiles();
    //! @brief remove a projectile this entity may have fired.
    void remove_projectile(Projectile* p);
    //! @brief moves this entity to the old position it was when moveTopos was called.
    void goto_old_pos();
    
    bool isDead; //!< true if this entity is dead and should be removed from the gameworld.
    Weapon* weapon; //!< ptr to a weapon which is used when calling shoot() 
protected:
    bool isPushed; //!< true if this entity is currently in the process of being pushed to targetPos.
    int hp; //!< how much hp this entity currently has.
    int max_health; //!< as much hp this entity can have.
    int speed; //!< how fast the entity is, used for calculating movement per frame.

    std::vector<Projectile*> projectiles; //!< vector with ptrs to all projectiles this entity has fired
    sf::Vector2f old_pos; //!< the old position it had before moveToPos() was called.

    //varibles for lerping when getting pushed
    float time; //!< used when lerping to targetPos
    sf::Vector2f targetPos; //!< the position where the entity will be pushed to if a certain collision event has occured.
};

