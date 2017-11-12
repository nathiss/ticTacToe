#include "Game.hpp"

Game::Game() {
  bag = SettingsBag::Instance();
  loadConsts();

	window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(bag->get<uint32_t>("window.width"), bag->get<uint32_t>("window.height")),
    bag->get<std::string>("window.title"),
    bag->get<uint32_t>("window.style"),
    bag->get<sf::ContextSettings>("window.settings")
  );
  window->setFramerateLimit(bag->get<uint32_t>("window.fps"));

	State::setType(State::MENU);
  state.reset(new MenuState(window));
}

Game::~Game() {

}

void Game::run() {
  State::Type currentState = State::getType();

	while(window->isOpen()) {
    if(currentState != State::getType()) {
      currentState = State::getType();
      state.reset(createState(currentState));
    }
    state->run();
  }
  
	code = 0;
}

int Game::getCode() const {
  return code;
}

void Game::loadConsts() {
  bag->set<uint32_t>("window.width", 700);
  bag->set<uint32_t>("window.height", 600);
  bag->set<uint32_t>("window.fps", 30);
  bag->set<std::string>("window.title", "TicTacToe");
  bag->set<uint32_t>("window.style", sf::Style::Titlebar | sf::Style::Close);
  bag->set<sf::ContextSettings>("window.settings", sf::ContextSettings(0, 0, 8));
  bag->set<sf::Color>("color.main", sf::Color(0xff9060ff));
  bag->set<sf::Color>("color.bg", sf::Color(0x57c785ff));
  bag->set<sf::Color>("color.neutral", sf::Color::White);
}

State* Game::createState(State::Type type) {
  if(type == State::MENU)
    return new MenuState(window);
  if(type == State::OPTIONS)
    return new OptionsState(window);
  if(type == State::GAME)
    return new GameState(window);
  if(type == State::END)
    return new EndState(window);
  return nullptr;
}