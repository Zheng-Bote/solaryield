#include "rz_main.h"

/**
 * @brief Construct a new rz main::rz main object
 *
 */
RZ_Main::RZ_Main() {}

/**
 * @brief Destroy the rz main::rz main object
 *
 */
RZ_Main::~RZ_Main() {}

/**
 * @name getVersion
 *
 * @brief gets the short version
 *
 * @return std::string (e.g.: "1.2.3")
 */
std::string RZ_Main::getVersion()
{
  std::string version = std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "." + std::to_string(VERSION_PATCH);

  return version;
}

/**
 * @name getFullVersion
 *
 * @brief gets the full version
 *
 * @return std::string (e.g.: "progname v1.2.3")
 */
std::string RZ_Main::getFullVersion()
{
  std::string version = PROG_NAME;
  version.append(" v");
  version.append(RZ_Main::getVersion());
  return version;
}

/**
 * @name getProgName()
 *
 * @brief gets the program name in lower case
 *
 * @return std::string
 */
std::string RZ_Main::getProgName()
{
  std::string s = PROG_NAME;
  std::transform(s.begin(), s.end(), s.begin(),
                 // static_cast<int(*)(int)>(std::tolower)         // wrong
                 // [](int c){ return std::tolower(c); }           // wrong
                 // [](char c){ return std::tolower(c); }          // wrong
                 [](unsigned char c)
                 { return std::tolower(c); } // correct
  );
  return s;
}

/**
 * @brief ltrim(std::string &s)
 *
 * @details trims left site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &RZ_Main::ltrim(std::string &s)
{
  auto it = std::find_if(s.begin(), s.end(), [](char c)
                         { return !std::isspace<char>(c, std::locale::classic()); });
  s.erase(s.begin(), it);
  return s;
}

/**
 * @brief rtrim(std::string &s)
 *
 * @details trims the right site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &RZ_Main::rtrim(std::string &s)
{
  auto it = std::find_if(s.rbegin(), s.rend(), [](char c)
                         { return !std::isspace<char>(c, std::locale::classic()); });
  s.erase(it.base(), s.end());
  return s;
}

/**
 * @brief trim(std::string &s)
 *
 * @details trims right and left site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &RZ_Main::trim(std::string &s)
{
  s = std::regex_replace(s, std::regex("\\r\\n|\\r|\\n"), "");
  return RZ_Main::ltrim(RZ_Main::rtrim(s));
}