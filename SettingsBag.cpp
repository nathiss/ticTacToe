#include "SettingsBag.hpp"

std::shared_ptr<SettingsBag> SettingsBag::instance = nullptr;

SettingsBag::SettingsBag() {

}

SettingsBag::~SettingsBag() {

}

std::shared_ptr<SettingsBag> SettingsBag::Instance() {
  if(instance == nullptr)
  	instance.reset(new SettingsBag());
  return instance;
}