#include "Utils.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

sf::Vector2f Utils::GetDirection(sf::Vector2f pos_a, sf::Vector2f pos_b)
{
    return {pos_a.x - pos_b.x, pos_a.y - pos_b.y};
}

float Utils::GetMagnitude(sf::Vector2f input)
{
    return std::sqrt(input.x * input.x + input.y * input.y);
}

sf::Vector2f Utils::GetNormalized(sf::Vector2f dist)
{
    float magnitude = GetMagnitude(dist);

    return {dist.x / magnitude, dist.y / magnitude};
}

sf::Vector2f Utils::GetNormalizedDirection(sf::Vector2f pos_a, sf::Vector2f pos_b)
{
    return GetNormalized(GetDirection(pos_a, pos_b));
}

float Utils::GetDistance(sf::Vector2f pos_a, sf::Vector2f pos_b)
{
    return GetMagnitude(GetDirection(pos_a, pos_b));
}


float Utils::GetDeltaTime()
{
    return clockObj.restart().asSeconds();
}

float Utils::FloatLerp(float a, float b, float f)
{
    return a + f * (b - a);
}

sf::Vector2f Utils::VectorLerp(sf::Vector2f start, sf::Vector2f end, float duration)
{
    return {FloatLerp(start.x,end.x,duration), FloatLerp(start.y,end.y,duration)};
}

