#pragma once

#include <SFML/Graphics.hpp>
#include "MapCell.hpp"
#include "SettingsBag.hpp"

class Map : public sf::Drawable {
  public:
    Map();
    ~Map();

    bool set(uint8_t, uint8_t, MapCell::Value);
    bool set(const sf::Vector2i&, MapCell::Value);

    MapCell::Value get(uint8_t, uint8_t) const;

    void setPosition(float, float);
    void setPosition(const sf::Vector2f&);

    const sf::Vector2f& getPosition() const;

    sf::FloatRect getLocalBounds() const;

    MapCell::Value getWinner() const;
    bool isFull() const;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

  protected:
    MapCell::Value getWinnerRows() const;
    MapCell::Value getWinnerColumns() const;
    MapCell::Value getWinnerCross() const;

  private:
    MapCell map[3][3]{};
};