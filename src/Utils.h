#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

class Utils
{
public:
    
    //! @brief returns a normalized vector pointing to the direction from pos_a to pos_b
    //! @param pos_a - the startpoint
    //! @param pos_b - the endpoint
    static sf::Vector2f GetNormalizedDirection(sf::Vector2f pos_a, sf::Vector2f pos_b);
    
    //! @brief returns the distance between two points
    //! @param pos_a - the first point
    //! @param pos_b - the second point
    static float GetDistance(sf::Vector2f pos_a, sf::Vector2f pos_b);
    
    //! @brief returns the time since the last frame
    static float GetDeltaTime();
    
    //! @brief lerps between two sf::Vector2f
    //! @param start - the startpoint
    //! @param end - the endpoint
    //! @param duration - the duration for the lerp
    static sf::Vector2f VectorLerp(sf::Vector2f start, sf::Vector2f end, float duration);
private:
    static sf::Vector2f GetDirection(sf::Vector2f pos_a, sf::Vector2f pos_b);
    static sf::Vector2f GetNormalized(sf::Vector2f input);
    static float GetMagnitude(sf::Vector2f input);
    static float FloatLerp(float a, float b, float f);
    inline static sf::Clock clockObj;
};
