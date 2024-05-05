#include "rz_files.h"

namespace rz_files
{

  std::string test() { return ("rz_files: Hello World"); }

  /**
   * @name getOnlyFilename
   * @brief Get the Filename without path and without extension
   *
   * @param pathToFile
   * @return std::string
   */
  std::string getOnlyFilename(std::string &pathToFile)
  {
    namespace fs = std::filesystem;
    return (fs::path(pathToFile).stem());
  }

  /**
   * @brief checkFileExtension
   *
   * @param pathToFile
   * @param extension
   * @return true
   * @return false
   */
  bool checkFileExtension(std::string &pathToFile, std::string extension)
  {
    namespace fs = std::filesystem;
    std::string fileExtension = fs::path(pathToFile).extension();
    if (fileExtension.compare(extension) == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool isReadAble(std::string &pathToFile)
  {
    bool isReadAble = false;

    namespace fs = std::filesystem;

    fs::file_status s = fs::status(pathToFile);
    switch (s.type())
    {
    case fs::file_type::regular:
      isReadAble = true;
      break;
    default:
      return false;
    }

    std::filesystem::perms permFile = fs::status(pathToFile).permissions();

    using std::filesystem::perms;

    std::string ergeb;
    auto show = [=](char op, perms perm)
    {
      char erg = (perms::none == (perm & permFile) ? '-' : op);
      return erg;
    };

    ergeb = show('r', perms::owner_read);
    ergeb = show('r', perms::group_read);
    ergeb = show('r', perms::others_read);

    (ergeb.compare("r")) ? isReadAble = false : isReadAble = true;

    return isReadAble;
  }

} // namespace rz_files