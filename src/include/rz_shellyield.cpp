#include "rz_shellyield.h"

/* 3.0. */

/// @brief
/// @param inFile
ShellyYield::ShellyYield(const std::string *inFile /* = "" */)
{
  _inFile = inFile;
}

ShellyYield::~ShellyYield()
{
}

std::string ShellyYield::getInFile()
{
  return *_inFile;
}

std::string ShellyYield::getInFileType()
{
  namespace fs = std::filesystem;

  std::string msg = *_inFile;
  fs::file_status s = fs::status(*_inFile);

  switch (s.type())
  {
  case fs::file_type::none:
    msg += " has `not-evaluated-yet` type";
    break;
  case fs::file_type::not_found:
    msg += " does not exist";
    break;
  case fs::file_type::regular:
    msg += " is a regular file";
    break;
  case fs::file_type::directory:
    msg += " is a directory";
    break;
  case fs::file_type::symlink:
    msg += " is a symlink";
    break;
  case fs::file_type::block:
    msg += " is a block device";
    break;
  case fs::file_type::character:
    msg += " is a character device";
    break;
  case fs::file_type::fifo:
    msg += " is a named IPC pipe";
    break;
  case fs::file_type::socket:
    msg += " is a named IPC socket";
    break;
  case fs::file_type::unknown:
    msg += " has `unknown` type";
    break;
  default:
    msg += " has `implementation-defined` type";
    break;
  }

  return msg;
}

/// @brief
/// @param pathToFile
/// @return
std::string ShellyYield::getFilePerms(std::filesystem::perms pathToFile)
{

  using std::filesystem::perms;
  std::string ergeb;
  auto show = [=](char op, perms perm)
  {
    char erg = (perms::none == (perm & pathToFile) ? '-' : op);
    return erg;
  };
  ergeb = show('r', perms::owner_read);
  ergeb += show('w', perms::owner_write);
  ergeb += show('x', perms::owner_exec);
  ergeb += " ";
  ergeb += show('r', perms::group_read);
  ergeb += show('w', perms::group_write);
  ergeb += show('x', perms::group_exec);
  ergeb += " ";
  ergeb += show('r', perms::others_read);
  ergeb += show('w', perms::others_write);
  ergeb += show('x', perms::others_exec);

  return (ergeb);
}

bool ShellyYield::isReadAble(const std::string *pathToFile)
{
  bool isReadAble = false;

  namespace fs = std::filesystem;

  fs::file_status s = fs::status(*pathToFile);
  switch (s.type())
  {
  case fs::file_type::regular:
    isReadAble = true;
    break;
  default:
    isReadAble = false;
    return isReadAble;
  }

  std::filesystem::perms permFile = fs::status(*pathToFile).permissions();

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

bool ShellyYield::checkFileExtension(const std::string *pathToFile, std::string extension)
{
  namespace fs = std::filesystem;
  std::string fileExtension = fs::path(*pathToFile).extension();
  if (fileExtension.compare(extension) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief ltrim(std::string &s)
 *
 * @details trims left site of a given string
 *
 * @param s
 * @return std::string&
 */
std::string &ShellyYield::ltrim(std::string &s)
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
std::string &ShellyYield::rtrim(std::string &s)
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
std::string &ShellyYield::trim(std::string &s)
{
  s = std::regex_replace(s, std::regex("\\r\\n|\\r|\\n"), "");
  return ltrim(rtrim(s));
}

/**
 * @brief rmLastNewline(std::string s)
 *
 * @details remove Carriage Return / Line Feed
 *
 * @param s
 *
 * @return String
 */
std::string ShellyYield::rmLastNewline(std::string s)
{
  s = std::regex_replace(s, std::regex("\\r\\n|\\r|\\n"), "");
  return s;
}

std::string ShellyYield::formatKey(std::string key)
{
  const std::regex regex_yyyymmdd("(\\d){4}-([\\d]){2}-([\\d]){2}");
  if (std::regex_match(key, regex_yyyymmdd))
  {
    return key;
  }

  // input 01.Aug
  // output: 2023-08-01
  std::map<std::string, std::string> mapKeys = {{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, {"Mai", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, {"Okt", "10"}, {"Nov", "11"}, {"Dez", "12"}};
  std::string day = "";
  std::string month = "";
  std::string year = "";
  std::string newKey = "";

  std::stringstream ss(key);
  std::getline(ss, day, '/');
  std::getline(ss, month, '/');
  std::getline(ss, year, '/');

  newKey = year + "-" + month + "-" + day;
  std::cout << "formatKey: " << newKey << std::endl;

  return newKey;
}

std::string ShellyYield::formatKey2(std::string key, int place)
{
  std::string delimiter = "-";
  std::string token = key.substr(place, key.find(delimiter));
  return token;
}

void ShellyYield::parseFileToMapKey(std::map<std::string, float> &mapKeys, std::string pathToFile)
{
  std::ifstream ifs;
  std::string str;

  ifs.open(pathToFile, std::ios::in);

  if (ifs)
  {
    while (!ifs.eof())
    {
      std::string key, valStr = "";
      float val = 0.0;
      std::string day = "";
      std::string month = "";
      std::string year = "";

      const std::regex regex_ddmmyyyy("(\\d){2}/(\\d){2}/(\\d){4}");
      const std::regex regex_yyyymmdd("(\\d){4}-(\\d){2}-(\\d){2}");
      std::getline(ifs, str);
      str = trim(str);
      const std::regex regex_verbrauch(".*Verbrauch.*");
      const std::regex regex_zeitwh(".*Zeit, Wh.*");
      if (str.length() > 0 && str.compare(" Verbrauch") != 0 && str.compare("Zeit, Wh") != 0 && !std::regex_match(str, regex_verbrauch) && !std::regex_match(str, regex_zeitwh))
      {
        // 01/02/2024 00:00 , 480.69
        // 2024-01-01,279.150
        std::stringstream ss(str);

        std::getline(ss, key, ',');
        key = trim(key);

        std::string delimiter = " ";
        std::string token = key.substr(0, key.find(delimiter));

        if (std::regex_match(token, regex_ddmmyyyy))
        {
          std::stringstream dt(token);
          std::getline(dt, day, '/');
          std::getline(dt, month, '/');
          std::getline(dt, year, '/');

          std::stringstream sb(str);
          while (std::getline(sb, valStr, ' '))
          {
            // std::cout << "valStr: " << valStr << std::endl;
          }
          valStr = trim(valStr);
          val = std::stof(valStr);
        }
        else if (std::regex_match(token, regex_yyyymmdd))
        {
          std::stringstream dt(token);
          std::getline(dt, year, '-');
          std::getline(dt, month, '-');
          std::getline(dt, day, '-');

          std::stringstream sb(str);
          while (std::getline(sb, valStr, ','))
          {
            // std::cout << "valStr: " << valStr << std::endl;
          }
          valStr = trim(valStr);
          val = std::stof(valStr);
        }

        key = year + "-" + month + "-" + day;

        if (mapKeys.contains(key))
        {
          mapKeys[key] = mapKeys[key] + val;
        }
        else
        {
          mapKeys[key] = val;
        }
      }
    }
    ifs.close();
  }
  else
  {
    std::cout << "Unable to open file to read" << std::endl;
  }
}

void ShellyYield::displayMap(std::map<std::string, float> &mapKeys)
{
  float totalVals = 0;

  std::cout << "==Display Map==" << std::endl;
  for (auto const &[key, val] : mapKeys)
  {
    if (val > 0)
    {
      // std::cout << key << ":" << val << std::endl;
      std::cout << std::left << std::setfill('.') << std::setw(7) << key << std::right << std::setfill('.') << std::setw(15) << std::fixed << std::setprecision(3) << val << std::endl;
    }
    totalVals += val;
  }
  std::cout << std::left << std::setfill('.') << std::setw(10) << "total:" << std::right << std::setfill('.') << std::setw(15) << std::fixed << std::setprecision(3) << totalVals << " W (" << totalVals / 1000 << " kW)" << std::endl;
}

bool ShellyYield::writeCSV(std::map<std::string, float> &mapKeys, std::string pathToFile)
{
  std::ofstream csvFile;
  csvFile.open(pathToFile, std::ios::app);
  if (csvFile.is_open())
  {

    for (auto const &[key, val] : mapKeys)
    {
      if (val > 0)
      {
        csvFile << key << "," << std::fixed << std::setprecision(3) << val << std::endl;
      }
    }
    csvFile.close();
    return true;
  }
  else
  {
    return false;
  }
}

bool ShellyYield::writeJson(std::map<std::string, float> &mapKeys, std::string &pathToFile)
{
  std::ofstream ofs;

  std::map<std::string, std::string> mapMonths = {{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, {"Mai", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, {"Okt", "10"}, {"Nov", "11"}, {"Dez", "12"}};
  std::list<int> listDays = {1, 2, 3, 4, 5};

  ofs.open(pathToFile, std::ios::out);

  if (ofs.is_open())
  {

    json j;
    json j_arr_years = json::array();
    json j_arr_months = json::array();
    json j_arr_days = json::array();
    json j_obj;

    float totalVals = 0;
    std::string year, month, day = "0";

    // std::cout << std::left << std::setfill('.') << std::setw(10) << "total:" << std::right << std::setfill('.') << std::setw(15) << std::fixed << std::setprecision(3) << totalVals << " W (" << totalVals / 1000 << " kW)" << std::endl;

    for (auto const &[key, val] : mapKeys)
    {
      std::stringstream ss(key);
      std::getline(ss, year, '-');
      std::getline(ss, month, '-');
      std::getline(ss, day, '-');

      j_obj =
          {
              {"day", day},
              {"val", val}};
      j_arr_days.push_back(j_obj);
      totalVals += val;
    }

    j_obj =
        {
            {"month", month},
            {"watt_per_month", totalVals},
            {"days", j_arr_days}};
    j_arr_months.push_back(j_obj);

    j_obj =
        {
            {"year", year},
            {"months", j_arr_months}};
    j_arr_years.push_back(j_obj);

    j = j_arr_years;
    ofs << j;
    ofs.close();
    return true;
  }
  else
  {
    return false;
  }
}

std::string ShellyYield::getFilePerm(std::string pathToFile)
{
  namespace fs = std::filesystem;
  return (ShellyYield::getFilePerms(fs::status(pathToFile).permissions()));
}

std::string ShellyYield::getVersion()
{
  return "Shellyield-v" + _VERSION;
}