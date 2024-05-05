#pragma once

#define PROG_NAME "shellyield"
#define VERSION_MAJOR 4
#define VERSION_MINOR 0
#define VERSION_PATCH 0

#include <string>
#include <regex>

/**
 * @name RZ_Main
 *
 * @brief everything around the main program
 *
 * @version 1.0.0
 *
 * @author RZheng
 *
 * @syntax RZ_Main main = new RZ_Main();
 */
class RZ_Main
{
public:
  RZ_Main();
  ~RZ_Main();
  virtual std::string getVersion();
  virtual std::string getFullVersion();
  virtual std::string getProgName();

  virtual std::string &ltrim(std::string &s);
  virtual std::string &rtrim(std::string &s);
  virtual std::string &trim(std::string &s);
};