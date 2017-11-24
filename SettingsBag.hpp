#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>

class SettingsBag {
  public:
    ~SettingsBag();

    template <class T> void set(const std::string&, const T&);
    template <class T> const T& get(const std::string&) const;

    static std::shared_ptr<SettingsBag> Instance();

  protected:
    SettingsBag();

  private:
    std::unordered_map<std::string, void*> map;
    static std::shared_ptr<SettingsBag> instance;
};

template <class T>
void SettingsBag::set(const std::string& key, const T& value) {
  if(map.count(key))
    delete reinterpret_cast<T*>(map.at(key));
  map[key] = reinterpret_cast<void*>(new T(value));
}

template <class T>
const T& SettingsBag::get(const std::string& key) const {
  return *reinterpret_cast<T*>(map.at(key));
}
