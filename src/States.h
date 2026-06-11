#pragma once
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

class State
{
public:
    State(sf::RenderWindow* window) : window{window} {}
    virtual ~State() = default;
    //! @brief logic for handling input from keyboard and/or mouse
    virtual State* handle_input() = 0;;
    //! @brief logic for rendering to the screen (menu or game)
    virtual void render() = 0;;
    //! @brief logic for updating the state every frame
    virtual void update() = 0;

    sf::RenderWindow* window; //!< the game window
};

class GameState : public State
{
public:
    GameState(sf::RenderWindow* window);
;
    State* handle_input() override;
    void update() override;
    void render() override;
    bool paused;
private:
    sf::Font font;
    Player player;
    Level currentLevel;
    void checkCollisions();
};

class MenuState : public State
{
public:
    MenuState(sf::RenderWindow* window);

    State* handle_input() override;
    void update() override;
    void render() override;

private:
    sf::Font font;
    sf::Sprite background;
    sf::Sprite start;
    sf::Sprite quit;
};

class PauseState : public State
{
public:
    PauseState(GameState* game);

    State* handle_input() override;
    void update() override;
    void render() override;

private:
    GameState* game;
    sf::Font font;

    sf::Sprite background;
    sf::Sprite start;
    sf::Sprite quit;
    
};
