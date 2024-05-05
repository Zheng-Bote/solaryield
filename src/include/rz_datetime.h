#pragma once

#include <chrono>
#include <string>

#include <iostream>
#include <sstream>
#include <vector>

/**
 * @name rz_datetime
 *
 * @brief everything around date and time
 *
 * @version 1.0.0
 *
 * @author RZheng
 */
namespace rz_datetime
{
  std::string test();
  const std::string getCurrentDateTime(std::string format);
  const std::vector<std::string> splitDateTime(std::string string, char delimiter);
} // namespace rz_datetime
