#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "MapCell.hpp"

class EndState : public State {
  public:
    EndState(std::shared_ptr<sf::RenderWindow>);
    ~EndState();

    virtual void pollEvent() override;
    virtual void update() override;
    virtual void draw() override;

  protected:
    std::string getStringInfo() const;

  private:
    sf::Text info;
    sf::Text buttons[3];
};