#pragma once

#include <cstdint>
#include <memory>
#include <array>
#include <iostream>
#include "Map.hpp"
#include "MapCell.hpp"

class Engine {
  public:
    Engine() = delete;
    Engine(std::shared_ptr<Map>);
    ~Engine();

    void setCharacter(MapCell::Value);
    MapCell::Value getCharacter() const;

    bool makeMove();

  protected:
    void simplifyMap();
    int8_t minimax(int8_t);

    int8_t win();

  private:
    std::shared_ptr<Map> map;
    std::array<uint8_t, 9> byteMap;

    MapCell::Value character;
    uint8_t computer;
    uint8_t player;
};