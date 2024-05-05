#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @name rz_files
 *
 * @brief everything around files
 *
 * @version 1.0.0
 *
 * @author RZheng
 */
namespace rz_files
{
  namespace fs = std::filesystem;
  std::string test();
  bool checkFileExtension(std::string &pathToFile, std::string extension);
  bool isReadAble(std::string &pathToFile);
  std::string getOnlyFilename(std::string &pathToFile);

} // namespace rz_files