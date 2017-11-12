#include "State.hpp"

State::Type State::type = State::MENU;

State::State()
{

}

State::~State()
{

}

void State::clear(sf::Color color)
{
    window->clear(color);
}

void State::display()
{
    window->display();
}

void State::run()
{
    pollEvent();
    update();
    clear(bag->get<sf::Color>("color.bg"));
    draw();
    display();
}

void State::setType(State::Type t)
{
    type = t;
}

State::Type State::getType()
{
    return type;
}

bool State::mouseOver(const sf::Text& button) const {
  const sf::Vector2i& mouse = sf::Mouse::getPosition(*window);
  const sf::Vector2f& position = button.getPosition();
  const sf::FloatRect& bounds = button.getGlobalBounds();
  if(mouse.x >= position.x && mouse.x <= position.x + bounds.width &&
     mouse.y >= position.y && mouse.y <= position.y + bounds.height)
    return true;
  return false;
}

float State::centerHorizontally(sf::FloatRect bounds) const {
  return (window->getSize().x - bounds.width) / 2.f;
}