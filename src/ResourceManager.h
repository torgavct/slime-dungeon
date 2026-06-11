#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <map>

class ResourceManager
{
public:
  enum Texture_Name
  {
    Background,
    Tilemap,
    Floor,
    Wall,
    Door,
    Player,
    Melee,
    Ranged,
    Boss,
    Watergun,
    Supersoaker,
    Powerwasher,
    Projectile,
    Heart,
  };
  
  static sf::Sprite getSpriteWithName(Texture_Name name);
  static sf::Vector2u getSize(std::string name);
  static void LoadAssets();

private:
  inline static std::map<Texture_Name, sf::Texture> textures;
  inline static std::vector<Texture_Name> const tilemap_textures =
  {
      Texture_Name::Floor,
      Texture_Name::Wall,
      Texture_Name::Door
  };
};

typedef ResourceManager::Texture_Name Tex;
