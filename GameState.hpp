#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "SettingsBag.hpp"
#include "Map.hpp"
#include "MapCell.hpp"
#include "Engine.hpp"
#include "OptionsState.hpp"

class GameState : public State {
  public:
    GameState(std::shared_ptr<sf::RenderWindow>);
    ~GameState();

    virtual void pollEvent() override;
    virtual void update() override;
    virtual void draw() override;

  protected:
    void setUpTexts();

    void checkWin();

  private:
    std::shared_ptr<Map> map;
    MapCell::Value playerChar;

    std::unique_ptr<Engine> engine;

    sf::Font font;
    sf::Text exit;
};