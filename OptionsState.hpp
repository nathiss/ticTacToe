#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "SettingsBag.hpp"
#include "MapCell.hpp"

class OptionsState : public State {
  public:
    OptionsState(std::shared_ptr<sf::RenderWindow>);
    ~OptionsState();

    static constexpr uint8_t player = 0;
    static constexpr uint8_t computer = 1;

    virtual void pollEvent() override;
    virtual void update() override;
    virtual void draw() override;

  private:
    sf::Font menuFont;
    std::array<sf::Text, 3> orderOption;
    std::array<sf::Text, 3> characterOption;

    uint8_t optionIdx;
};