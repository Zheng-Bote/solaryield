#include "rz_dirs.h"

namespace rz_dirs
{

  std::string test() { return ("rz_dirs: Hello World"); }

  /**
   * @brief Get the Canonical Path object
   *
   * @param path
   * @return std::string
   */
  std::string getCanonicalPath(std::string path)
  {
    return fs::canonical(path);
  }

  /**
   * @brief &dir_exist(string)
   *
   * @param target_path
   * @return true
   * @return false
   */
  bool dir_exist(std::string &target_path)
  {
    if (!fs::exists(target_path))
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  /**
   * @brief Create a directory object
   *
   * @param path
   * @return true
   * @return false
   */
  bool create_directory(const std::filesystem::path &path) noexcept
  {
    if (!std::filesystem::create_directories(path))
    {
      return false;
    }
    else
    {
      return true;
    }
  }

} // namespace rz_dirs