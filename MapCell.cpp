#include "MapCell.hpp"

MapCell::MapCell() {
  value = NONE;
  bag = SettingsBag::Instance();

  border.setFillColor(sf::Color::Transparent);
  border.setOutlineColor(bag->get<sf::Color>("color.main"));
  border.setOutlineThickness(borderThickness);
  border.setSize(sf::Vector2f(width, height));

  symbol.setString(" ");
  symbol.setCharacterSize(75);
  symbol.setFillColor(bag->get<sf::Color>("color.neutral"));
}

MapCell::~MapCell() {

}

MapCell::Value MapCell::negate(MapCell::Value value) {
  if(value == X)
    return O;
  if(value == O)
    return X;
  return NONE;
}

void MapCell::setFont(sf::Font& f) {
  font = f;
  symbol.setFont(font);
}

void MapCell::setValue(MapCell::Value v) {
  value = v;
  if(value == X)
    symbol.setString("X");
  else if(value == O)
    symbol.setString("O");
  else
    symbol.setString(" ");
}

MapCell::Value MapCell::getValue() const {
  return value;
}

void MapCell::setPosition(float x, float y) {
  border.setPosition(x, y);
  symbol.setPosition(x + textXShift, y + textYShift);
}

void MapCell::setPosition(const sf::Vector2f& v) {
  setPosition(v.x, v.y);
}

const sf::Vector2f& MapCell::getPosition() const {
  return border.getPosition();
}

bool MapCell::contains(const sf::Vector2f& p) const {
  sf::FloatRect rect = border.getGlobalBounds();
  if(p.x >= rect.left &&
     p.x <= rect.left + rect.width &&
     p.y >= rect.top &&
     p.y <= rect.top + rect.height)
    return true;
  return false;
}

void MapCell::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const {
  target.draw(border);
  if(value != NONE)
    target.draw(symbol);
}