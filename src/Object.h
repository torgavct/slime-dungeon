#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Object : public sf::Drawable, public sf::Transformable 
{
public:
    Object(sf::Vector2f pos, sf::Sprite sprite);
   
    virtual ~Object() = default;
    
    //! @brief  implementation of collision behaviors between Objects.
    //! @param The other Object that is colliding.
    virtual void collide(Object* other) = 0;

    //! @brief function for getting the sf::Sprite.
    sf::Sprite& get_sprite();
    //! @brief function for getting the position of the object.
    sf::Vector2f get_pos();
    //! @brief logic for moving this very frame.
    void moveToPos(sf::Vector2f newPos);
  
    //! @brief function for getting the unique global ID of the object.
    int get_id();

    //! @brief returns the rectangle of the space that the sprite is taking up, usable for checking collisions.
  sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds();}


protected:
    int id; //!< a unique global id which can be used to identity an instance.
    sf::Vector2f pos;//!< the position of this object.
    sf::Sprite sprite;//!< the sprite to draw to represent this object.
  
    //! @brief implementation of sf::Drawable's draw for custom behaviour when calling window.draw on this.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
