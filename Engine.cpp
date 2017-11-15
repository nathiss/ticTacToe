#include "Engine.hpp"

Engine::Engine(std::shared_ptr<Map> m) {
  map = m;
  byteMap.fill(0);

  character = MapCell::NONE;
  computer = 1;
  player = -1;
}

Engine::~Engine() {

}

void Engine::setCharacter(MapCell::Value v) {
  character = v;
  if(v == MapCell::O) {
    computer = 1;
    player = -1;
  }
  else {
    computer = -1;
    player = 1;
  }
}

MapCell::Value Engine::getCharacter() const {
  return character;
}

bool Engine::makeMove() {
  simplifyMap();
  
  int8_t idx = -1;
  int8_t score = -2;

  for(uint8_t i=0; i<9; i++)
    if(byteMap[i] == 0) {
      byteMap[i] = computer;
      int8_t tmpScore = -minimax(player);
      byteMap[i] = 0;
      if(tmpScore > score) {
        score = tmpScore;
        idx = i;
      }
    }

  return map->set(idx / 3, idx % 3, character);
}

void Engine::simplifyMap() {
  for(uint8_t i=0; i<3; i++)
    for(uint8_t j=0; j<3; j++) {
      MapCell::Value tmp = map->get(i, j);
      if(tmp == MapCell::NONE)
        byteMap[3*i + j] = 0;
      else if(tmp == character)
        byteMap[3*i + j] = computer;
      else
        byteMap[3*i + j] = player;
    }
}

int8_t Engine::minimax(int8_t player) {
  int8_t winner = win();
  if(winner != 0)
      return winner*player;

  int8_t move = -1;
  int8_t score = -2;
  for(uint8_t i=0; i<9; i++)
    if(byteMap[i] == 0) {
      byteMap[i] = player;
      int8_t thisScore = -minimax(player * -1);
      if(thisScore > score) {
        score = thisScore;
        move = i;
      }
      byteMap[i] = 0;
    }
  if(move == -1)
    return 0;
  return score;
}

int8_t Engine::win() {
    uint8_t wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(uint8_t i = 0; i < 8; i++) {
        if(byteMap[wins[i][0]] != 0 &&
           byteMap[wins[i][0]] == byteMap[wins[i][1]] &&
           byteMap[wins[i][0]] == byteMap[wins[i][2]])
            return byteMap[wins[i][2]];
    }
    return 0;
}