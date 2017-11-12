#include "GameState.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> w) {
  if(!font.loadFromFile("./data/GlacialIndifference/GlacialIndifference-Regular.otf")) {
    throw std::runtime_error("Could not load font ./data/GlacialIndiffrence/GlacialIndiffrence-Regular.otf");
  }
  window = w;
  bag = SettingsBag::Instance();
  map = std::make_shared<Map>();
  playerChar = bag->get<MapCell::Value>("option.playerChar");
  engine = std::make_unique<Engine>(map);

  setUpTexts();
  map->setPosition(centerHorizontally(map->getLocalBounds()), 100.f);
  engine->setCharacter(MapCell::negate(playerChar));

  if(bag->get<uint8_t>("option.order") == OptionsState::computer)
    engine->makeMove();
}

GameState::~GameState() {

}

void GameState::pollEvent() {
  while(window->pollEvent(event)) {
    switch(event.type) {
      case sf::Event::Closed:
        window->close();
        break;
      case sf::Event::MouseMoved:
        if(mouseOver(exit))
          exit.setFillColor(bag->get<sf::Color>("color.main"));
        else
          exit.setFillColor(bag->get<sf::Color>("color.neutral"));
        break;
      case sf::Event::MouseButtonReleased:
        if(mouseOver(exit)) {
          window->close();
          break;
        }
        if(map->set(sf::Mouse::getPosition(*window), playerChar)) {
          checkWin();
          engine->makeMove();
          checkWin();
        }
        break;
      default:
        break;
    }
  }
}

void GameState::update() {

}

void GameState::draw() {
  window->draw(*map);
  window->draw(exit);
}

void GameState::setUpTexts() {
  exit.setString("Exit");
  exit.setFont(font);
  exit.setCharacterSize(32);
  exit.setFillColor(bag->get<sf::Color>("color.neutral"));
  exit.setStyle(sf::Text::Bold);
  exit.setPosition(centerHorizontally(exit.getLocalBounds()), bag->get<uint32_t>("window.height") - 50.f);
}

void GameState::checkWin() {
  if(map->isFull() || map->getWinner() != MapCell::NONE) {
    bag->set<MapCell::Value>("winner", map->getWinner());
    State::setType(END);
  }
}