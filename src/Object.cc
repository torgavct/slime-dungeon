
#include "Object.h"
#include <SFML/Graphics/Sprite.hpp>
static int globalObjID {0};
Object::Object(sf::Vector2f pos, sf::Sprite sprite)
    : id{globalObjID++}, pos{pos}, sprite{sprite}
{
     sprite.setPosition(pos);
}
  
sf::Sprite& Object::get_sprite()
{
    return sprite;
}

sf::Vector2f Object::get_pos()
{
    return pos;
}

int Object::get_id()
{
    return id;
}

void Object::moveToPos(sf::Vector2f newPos)
{
    pos = newPos;
    setPosition(newPos);
    sprite.setPosition(newPos);
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
