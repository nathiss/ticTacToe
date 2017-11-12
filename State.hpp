#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "SettingsBag.hpp"

class State {
  public:
  	State();
  	virtual ~State();

  	enum Type {
  		MENU = 0,
      OPTIONS = 1,
  		GAME = 1 << 1,
  		END = 1 << 2
  	};

  	virtual void pollEvent() = 0;
  	virtual void update() = 0;
  	virtual void clear(sf::Color);
  	virtual void draw() = 0;
  	void display();

  	void run();

  	static void setType(Type);
  	static Type getType();

  protected:
    bool mouseOver(const sf::Text& button) const;
    float centerHorizontally(sf::FloatRect bounds) const;

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<SettingsBag> bag;
    sf::Event event{};

  private:
    static Type type;
};