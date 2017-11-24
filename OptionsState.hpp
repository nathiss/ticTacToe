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

    static uint8_t player;
    static uint8_t computer;

    virtual void pollEvent() override;
    virtual void update() override;
    virtual void draw() override;

  private:
    std::array<sf::Text, 3> orderOption;
    std::array<sf::Text, 3> characterOption;

    uint8_t optionIdx;
};