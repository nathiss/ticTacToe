#pragma once

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "SettingsBag.hpp"
#include "State.hpp"
#include "MenuState.hpp"
#include "OptionsState.hpp"
#include "GameState.hpp"
#include "EndState.hpp"

class Game {
 public:
    Game();
    ~Game();

    void run();
    int getCode() const;

  private:
    void loadConsts();
    void loadFonts();
    State* createState(State::Type);

    std::shared_ptr<SettingsBag> bag;
    std::shared_ptr<sf::RenderWindow> window;
    std::unique_ptr<State> state;

    int code{};
};
