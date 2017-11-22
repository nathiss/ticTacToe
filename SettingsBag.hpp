#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <any>

class SettingsBag {
  public:
    ~SettingsBag();

    template <class T> void set(const std::string&, const T&);
    template <class T> const T& get(const std::string&) const;

    static std::shared_ptr<SettingsBag> Instance();

  protected:
    SettingsBag();

  private:
    std::unordered_map<std::string, std::any> map;
    static std::shared_ptr<SettingsBag> instance;
};

template <class T>
void SettingsBag::set(const std::string& key, const T& value) {
  map[key] = std::make_any<const T&>(value);
}

template <class T>
const T& SettingsBag::get(const std::string& key) const {
  return std::any_cast<const T&>(map.at(key));
}
