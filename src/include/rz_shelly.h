#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <list>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "rz_main.h"
#include "rz_datetime.h"

/**
 * @name rz_shelly
 *
 * @brief everything around the Shelly Plug
 *
 * @version 1.0.0
 *
 * @author RZheng
 */
namespace rz_shelly
{
  namespace fs = std::filesystem;
  std::string test();

  bool parseFileToMapKey(std::map<std::string, float> &mapKeys, std::string &pathToFile);
  void displayMap(std::map<std::string, float> &mapKeys);
  bool writeCSV(std::map<std::string, float> &mapKeys, std::string &pathToFile);
  bool writeJson(std::map<std::string, float> &mapKeys, std::string &pathToFile, std::string &name);
} // namespace rz_shelly