#include "MenuState.hpp"

MenuState::MenuState(std::shared_ptr<sf::RenderWindow> w) {
  window = w;
  bag = SettingsBag::Instance();
  loadFonts();

  title.setString(bag->get<std::string>("window.title"));
  title.setFont(mainFont);
  title.setCharacterSize(72);
  title.setStyle(sf::Text::Bold);
  title.setFillColor(bag->get<sf::Color>("color.main"));
  title.setPosition(centerHorizontally(title.getLocalBounds()), 20.f);

  // TODO: change it to imgs
  buttons[0].setString("Start");
  buttons[1].setString("Exit");
  for(uint8_t i = 0; i < buttons.size(); i++) {
    buttons[i].setFont(menuFont);
    buttons[i].setCharacterSize(48);
    buttons[i].setFillColor(bag->get<sf::Color>("color.neutral"));
    buttons[i].setPosition(centerHorizontally(buttons[i].getLocalBounds()), 200.f + 75 * i);
  }

  cpyrht.setString("Copyright (c) 2017 Kamil Rusin");
  cpyrht.setFont(menuFont);
  cpyrht.setCharacterSize(12);
  cpyrht.setFillColor(bag->get<sf::Color>("color.neutral"));
  cpyrht.setPosition(5.f, window->getSize().y - cpyrht.getLocalBounds().height - 5.f);
}

MenuState::~MenuState() {

}

void MenuState::pollEvent() {
	while(window->pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				window->close();
				break;
      case sf::Event::MouseMoved:
        for(sf::Text& button : buttons) {
          if(mouseOver(button))
            button.setFillColor(bag->get<sf::Color>("color.main"));
          else
            button.setFillColor(bag->get<sf::Color>("color.neutral"));
        }
        break;
      case sf::Event::MouseButtonReleased:
        if(mouseOver(buttons[0]))
          State::setType(OPTIONS);
        if(mouseOver(buttons[1]))
          window->close();
        break;
      default:
        break;
		}
	}
}

void MenuState::update() {

}

void MenuState::draw() {
  window->draw(title);
  for(const sf::Text& t : buttons) {
    window->draw(t);
  }
  window->draw(cpyrht);
}

void MenuState::loadFonts() {
  if(!mainFont.loadFromFile("./data/Unique/Unique.ttf")) {
    throw std::runtime_error("Could not load font ./data/Unique/Unique.ttf");
  }
  if(!menuFont.loadFromFile("./data/GlacialIndifference/GlacialIndifference-Regular.otf")) {
    throw std::runtime_error("Could not load font ./data/GlacialIndiffrence/GlacialIndiffrence-Regular.otf");
  }
}