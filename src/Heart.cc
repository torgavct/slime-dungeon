#include "Heart.h"
#include "ResourceManager.h"

Heart::Heart(sf::Vector2f pos)
    : Object(pos, sf::Sprite(ResourceManager::getSpriteWithName(Tex::Heart))), isPickedUp{false}
    {
        sprite.setPosition(pos);
    } 

void Heart::collide(Object* other)
{
}

Heart::~Heart()
{

}