#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "SettingsBag.hpp"

class MapCell : public sf::Drawable {
  public:
    MapCell();
    ~MapCell();

    enum Value {
      NONE = 0,
      X = 1,
      O = 1 << 1
    };

    static Value negate(Value);

    static constexpr float width = 75.f;
    static constexpr float height = 75.f;
    static constexpr float borderThickness = 1.f;

    static constexpr float textXShift = 15.f;
    static constexpr float textYShift = -14.f;

    void setFont(sf::Font&);

    void setValue(Value);
    Value getValue() const;

    void setPosition(float, float);
    void setPosition(const sf::Vector2f&);

    const sf::Vector2f& getPosition() const;

    bool contains(const sf::Vector2f&) const;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

  private:
    Value value;
    std::shared_ptr<SettingsBag> bag;
    sf::RectangleShape border;
    sf::Text symbol;
    sf::Font font;
};