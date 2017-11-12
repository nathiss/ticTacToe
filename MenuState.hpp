#pragma once

#include <memory>
#include <stdexcept>
#include <cstdint>
#include <array>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "SettingsBag.hpp"

class MenuState : public State {
  public:
    MenuState(std::shared_ptr<sf::RenderWindow>);
    ~MenuState();

    virtual void pollEvent() override;
    virtual void update() override;
    virtual void draw() override;
    
  private:
    void loadFonts();

    sf::Font mainFont;
    sf::Font menuFont;
    sf::Text title;
    std::array<sf::Text, 2> buttons;
    sf::Text cpyrht;
};