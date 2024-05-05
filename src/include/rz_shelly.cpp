#include "rz_shelly.h"

namespace rz_shelly
{
  std::string test() { return ("rz_shelly: Hello World"); }

  /**
   * @brief writeJson
   *
   * @param mapKeys
   * @param pathToFile
   * @param name
   * @return true
   * @return false
   */
  bool writeJson(std::map<std::string, float> &mapKeys, std::string &pathToFile, std::string &name)
  {
    std::ofstream ofs;

    std::map<std::string, std::string> mapMonths = {{"01", "January"}, {"02", "February"}, {"03", "March"}, {"04", "April"}, {"05", "May"}, {"06", "June"}, {"07", "July"}, {"08", "August"}, {"09", "September"}, {"10", "October"}, {"11", "November"}, {"12", "December"}};
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
              {"name", name},
              {"month", month},
              {"month_name", mapMonths[month]},
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

  /**
   * @brief write cleasn CSV
   *
   * @param mapKeys
   * @param pathToFile
   * @return true
   * @return false
   */
  bool writeCSV(std::map<std::string, float> &mapKeys, std::string &pathToFile)
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

  /**
   * @name parseFileToMapKey
   * @brief read the csv and map it
   *
   * @param mapKeys
   * @param pathToFile
   * @return true
   * @return false
   */
  bool parseFileToMapKey(std::map<std::string, float> &mapKeys, std::string &pathToFile)
  {
    std::ifstream ifs;
    std::string str;

    // Shelly first 2 lines
    const std::regex regex_verbrauch(".*Verbrauch.*");
    const std::regex regex_zeitwh(".*Zeit, Wh.*");
    // Shelly csv 01/02/2024 00:00 , 480.69
    const std::regex regex_ddmmyyyy("(\\d){2}/(\\d){2}/(\\d){4}");
    // cleaned csv 2024-02-01,480.69
    const std::regex regex_yyyymmdd("(\\d){4}-(\\d){2}-(\\d){2}");

    RZ_Main *main = new RZ_Main();

    ifs.open(pathToFile, std::ios::in);

    if (ifs)
    {
      while (!ifs.eof())
      {
        std::string line, key, token = "";
        float val = 0.0;
        std::vector<std::string> v{};

        std::getline(ifs, str);
        str = main->trim(str);

        if (str.length() > 0 && str.compare(" Verbrauch") != 0 && str.compare("Zeit, Wh") != 0 && !std::regex_match(str, regex_verbrauch) && !std::regex_match(str, regex_zeitwh))
        {
          // todo: ss needed?
          std::stringstream ss(str);

          // get the key
          std::getline(ss, line, ',');
          line = main->trim(line);
          token = line.substr(0, line.find(" "));

          if (std::regex_match(token, regex_ddmmyyyy))
          {
            // 01/02/2024 00:00 , 480.69
            v = {rz_datetime::splitDateTime(token, '/')};
            key = v.at(2) + "-" + v.at(1) + "-" + v.at(0);
          }
          else if (std::regex_match(token, regex_yyyymmdd))
          {
            // 2024-02-01,480.69
            v = {rz_datetime::splitDateTime(line, '-')};
            key = v.at(0) + "-" + v.at(1) + "-" + v.at(2);
          }

          // get the value 480.69
          v = {};
          v = {rz_datetime::splitDateTime(str, ',')};
          val = std::stof(main->trim(v.at(1)));

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
    }
    else
    {
      // std::cout << "ERROR: Unable to open file to read: " << pathToFile << std::endl;
      return false;
    }

    ifs.close();
    return true;
  }

  /**
   * @name displayMap
   * @brief displays the map key-value
   *
   * @param mapKeys
   */
  void displayMap(std::map<std::string, float> &mapKeys)
  {
    float totalVals = 0;

    std::cout << "== Display Map (key...value) ==" << std::endl;
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

} // namespace rz_shelly