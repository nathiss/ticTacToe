#include "Map.hpp"

Map::Map() {
  if(!font.loadFromFile("./data/Inconsolata/Inconsolata-Regular.ttf")) {
    throw std::runtime_error("Could not load font ./data/Inconsolata/Inconsolata-Regular.ttf");
  }

  for(uint8_t i=0; i<3; i++)
    for(uint8_t j=0; j<3; j++)
      map[i][j].setFont(font);

  setPosition(0.f, 0.f);
}

Map::~Map() {

}

bool Map::set(uint8_t x, uint8_t y, MapCell::Value value) {
  if(map[x][y].getValue() == MapCell::NONE) {
    map[x][y].setValue(value);
    return true;
  }
  return false;
}

bool Map::set(const sf::Vector2i& mouse, MapCell::Value value) {
  for(uint8_t i=0; i<3; i++)
    for(uint8_t j=0; j<3; j++)
      if(map[i][j].contains(sf::Vector2f(mouse.x, mouse.y)))
        return set(i, j, value);
  return false;
}

MapCell::Value Map::get(uint8_t x, uint8_t y) const {
  return map[x][y].getValue();
}

void Map::setPosition(float x, float y) {
  for(uint8_t i=0; i<3; i++)
    for(uint8_t j=0; j<3; j++)
      map[i][j].setPosition(x + MapCell::width * j, y + MapCell::height * i);
}

void Map::setPosition(const sf::Vector2f& v) {
  setPosition(v.x, v.y);
}

const sf::Vector2f& Map::getPosition() const {
  return map[0][0].getPosition();
}

sf::FloatRect Map::getLocalBounds() const {
  sf::FloatRect rect;
  rect.top = 0;
  rect.left = 0;
  rect.width = MapCell::width * 3;
  rect.height = MapCell::height * 3;
  return rect;
}

MapCell::Value Map::getWinner() const {
  if(getWinnerRows() != MapCell::NONE)
    return getWinnerRows();
  if(getWinnerColumns() != MapCell::NONE)
    return getWinnerColumns();
  if(getWinnerCross() != MapCell::NONE)
    return getWinnerCross();
  return MapCell::NONE;
}

bool Map::isFull() const {
  for(uint8_t i=0; i<3; i++)
    for(uint8_t j=0; j<3; j++)
      if(map[i][j].getValue() == MapCell::NONE)
        return false;
  return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const {
  for(uint8_t i=0; i<3; i++)
    for(uint8_t j=0; j<3; j++)
      target.draw(map[i][j]);
}

MapCell::Value Map::getWinnerRows() const {
  for(uint8_t i=0; i<3; i++) {
    MapCell::Value v0 = map[0][i].getValue();
    MapCell::Value v1 = map[1][i].getValue();
    MapCell::Value v2 = map[2][i].getValue();
    if(v0 == v1 && v1 == v2 && v2 != MapCell::NONE)
      return v0;
  }
  return MapCell::NONE;
}

MapCell::Value Map::getWinnerColumns() const {
  for(uint8_t i=0; i<3; i++) {
    MapCell::Value v0 = map[i][0].getValue();
    MapCell::Value v1 = map[i][1].getValue();
    MapCell::Value v2 = map[i][2].getValue();
    if(v0 == v1 && v1 == v2 && v2 != MapCell::NONE)
      return v0;
  }
  return MapCell::NONE;
}

MapCell::Value Map::getWinnerCross() const {
  if(map[0][0].getValue() == map[1][1].getValue() &&
     map[1][1].getValue() == map[2][2].getValue() &&
     map[2][2].getValue() != MapCell::NONE)
    return map[0][0].getValue();
  if(map[2][0].getValue() == map[1][1].getValue() &&
     map[1][1].getValue() == map[0][2].getValue() &&
     map[0][2].getValue() != MapCell::NONE)
    return map[2][0].getValue();
  return MapCell::NONE;
}