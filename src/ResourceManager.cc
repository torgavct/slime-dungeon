#include "ResourceManager.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <stdexcept>
#include <vector>


sf::Sprite ResourceManager::getSpriteWithName(Texture_Name name)
{
  sf::Sprite res {};
  sf::Texture* resText {};
  sf::IntRect offset {};
  float scale {2.f}; 
  res.setScale(sf::Vector2f(scale, scale));
  

  auto it = std::find(tilemap_textures.begin(),tilemap_textures.end(), name);
  
  if(it != tilemap_textures.end())
  {
      switch(name)
      {
      case Texture_Name::Floor:
      {
          offset = sf::IntRect(192,256,32,32);
          resText = &textures[Texture_Name::Tilemap];
          break;
      }
      case Texture_Name::Wall:
      {
          offset = sf::IntRect(0,0,32,32);
          resText = &textures[Texture_Name::Tilemap];
          break;
      }
      case Texture_Name::Door:
      {
          offset = sf::IntRect(192,32,32,32);
          resText = &textures[Texture_Name::Tilemap];
          break;
      }
      default:
      {
          throw new std::runtime_error("Error: Texture not found");
      }
      }
            
  }
  else
  {
    resText = &textures[name];
  }
  
  
  res.setTextureRect(offset);
  res.setTexture(*resText);
  
  return res;
}

sf::Vector2u ResourceManager::getSize(std::string name)
{
  if(name == "room")
    return sf::Vector2u(64,64);

  return sf::Vector2u(0,0);
}

void ResourceManager::LoadAssets()
{
  textures[Tex::Player].loadFromFile("resources/scientist2.gif");
  textures[Tex::Background].loadFromFile("resources/background-scaled.jpg");
  textures[Tex::Tilemap].loadFromFile("resources/RPG.jpeg");
  textures[Tex::Melee].loadFromFile("resources/green-slime.png");
  textures[Tex::Ranged].loadFromFile("resources/purple-slime.png");
  textures[Tex::Boss].loadFromFile("resources/boss-slime.png");
  textures[Tex::Watergun].loadFromFile("resources/watergun.png");
  textures[Tex::Supersoaker].loadFromFile("resources/supersoaker.png");
  textures[Tex::Powerwasher].loadFromFile("resources/powerwasher.png");
  textures[Tex::Projectile].loadFromFile("resources/projectile2.png");
  textures[Tex::Heart].loadFromFile("resources/heart-scaled.png");
}
