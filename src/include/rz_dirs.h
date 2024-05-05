#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @name rz_dirs
 *
 * @brief everything around directories
 *
 * @version 1.0.0
 *
 * @author RZheng
 */
namespace rz_dirs
{
  namespace fs = std::filesystem;
  std::string test();

  bool dir_exist(std::string &target_path);
  std::string getCanonicalPath(std::string path);
  bool create_directory(const std::filesystem::path &path) noexcept;

} // namespace rz_dirs