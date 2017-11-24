#include "OptionsState.hpp"

uint8_t OptionsState::player = 0;
uint8_t OptionsState::computer = 1;

OptionsState::OptionsState(std::shared_ptr<sf::RenderWindow> w) {
  window = w;
  bag = SettingsBag::Instance();
  optionIdx = 0;

  orderOption[0].setString("Who starts?");
  orderOption[1].setString("Player");
  orderOption[2].setString("Computer");

  characterOption[0].setString("Player character is:");
  characterOption[1].setString("X");
  characterOption[2].setString("0");

  orderOption[0].setFillColor(bag->get<sf::Color>("color.main"));
  orderOption[0].setCharacterSize(48);
  orderOption[0].setStyle(sf::Text::Bold);

  characterOption[0].setFillColor(bag->get<sf::Color>("color.main"));
  characterOption[0].setCharacterSize(48);
  characterOption[0].setStyle(sf::Text::Bold);

  for(uint8_t i=1; i<3; i++) {
    orderOption[i].setFillColor(bag->get<sf::Color>("color.neutral"));
    orderOption[i].setCharacterSize(32);

    characterOption[i].setFillColor(bag->get<sf::Color>("color.neutral"));
    characterOption[i].setCharacterSize(32);
  }

  sf::Font *menu = bag->get<sf::Font*>("font.menu");
  for(uint8_t i=0; i<3; i++) {
    orderOption[i].setFont(*menu);
    characterOption[i].setFont(*menu);

    orderOption[i].setPosition(centerHorizontally(orderOption[i].getLocalBounds()), 200.f + 60*i);
    characterOption[i].setPosition(centerHorizontally(characterOption[i].getLocalBounds()), 200.f + 60*i);
  }
}

OptionsState::~OptionsState() {

}

void OptionsState::pollEvent() {
  while(window->pollEvent(event)) {
    switch(event.type) {
      case sf::Event::Closed:
        window->close();
        break;
      case sf::Event::MouseMoved:
        switch(optionIdx) {
          case 0:
            for(uint8_t i=1; i<3; i++)
              if(mouseOver(orderOption[i]))
                orderOption[i].setFillColor(bag->get<sf::Color>("color.main"));
              else
                orderOption[i].setFillColor(bag->get<sf::Color>("color.neutral"));
            break;
          case 1:
            for(uint8_t i=1; i<3; i++)
              if(mouseOver(characterOption[i]))
                characterOption[i].setFillColor(bag->get<sf::Color>("color.main"));
              else
                characterOption[i].setFillColor(bag->get<sf::Color>("color.neutral"));
            break;
          default:
            break;
        }
        break;
      case sf::Event::MouseButtonReleased:
        switch(optionIdx) {
          case 0:
            for(uint8_t i=1; i<3; i++) {
              if(mouseOver(orderOption[1])) {
                bag->set<uint8_t>("option.order", player);
                optionIdx = 1;
              }
              if(mouseOver(orderOption[2])) {
                bag->set<uint8_t>("option.order", computer);
                optionIdx = 1;
              }
            }
            break;
          case 1:
            for(uint8_t i=1; i<3; i++) {
              if(mouseOver(characterOption[1])) {
                bag->set<MapCell::Value>("option.playerChar", MapCell::X);
                State::setType(GAME);
              }
              if(mouseOver(characterOption[2])) {
                bag->set<MapCell::Value>("option.playerChar", MapCell::O);
                State::setType(GAME);
              }
            }
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
}

void OptionsState::update() {

}

void OptionsState::draw() {
  switch(optionIdx) {
    case 0:
      for(const sf::Text& text : orderOption)
        window->draw(text);
      break;
    case 1:
      for(const sf::Text& text : characterOption)
        window->draw(text);
      break;
    default:
      break;
  }
}
