#include "EndState.hpp"

EndState::EndState(std::shared_ptr<sf::RenderWindow> w) {
  window = w;
  bag = SettingsBag::Instance();
  sf::Font *menu = bag->get<sf::Font*>("font.menu");

  info.setString(getStringInfo());
  info.setFont(*menu);
  info.setFillColor(bag->get<sf::Color>("color.main"));
  info.setCharacterSize(72);
  info.setPosition(centerHorizontally(info.getLocalBounds()), 20.f);

  buttons[0].setString("Restart");
  buttons[1].setString("Go to options");
  buttons[2].setString("Exit");
  for(uint8_t i=0; i<3; i++) {
    buttons[i].setFont(*menu);
    buttons[i].setFillColor(bag->get<sf::Color>("color.neutral"));
    buttons[i].setCharacterSize(24);
    buttons[i].setPosition(centerHorizontally(buttons[i].getLocalBounds()), 400.f + 40.f * i);
  }
}

EndState::~EndState() {

}

void EndState::pollEvent() {
  while(window->pollEvent(event)) {
    switch(event.type) {
      case sf::Event::Closed:
        window->close();
        break;
      case sf::Event::MouseMoved:
        for(sf::Text& button : buttons)
          if(mouseOver(button))
            button.setFillColor(bag->get<sf::Color>("color.main"));
          else
            button.setFillColor(bag->get<sf::Color>("color.neutral"));
        break;
      case sf::Event::MouseButtonReleased:
        if(mouseOver(buttons[0]))
          State::setType(GAME);
        else if(mouseOver(buttons[1]))
          State::setType(OPTIONS);
        else if(mouseOver(buttons[2]))
          window->close();
        break;
      default:
        break;
    }
  }
}

void EndState::update() {

}

void EndState::draw() {
  window->draw(info);
  for(const sf::Text& button : buttons)
    window->draw(button);
}

std::string EndState::getStringInfo() const {
  MapCell::Value winner = bag->get<MapCell::Value>("winner");
  if(winner == MapCell::NONE)
    return std::string("TIE");
  if(winner == bag->get<MapCell::Value>("option.playerChar"))
    return std::string("Player won!");
  return std::string("Computer won!");
}