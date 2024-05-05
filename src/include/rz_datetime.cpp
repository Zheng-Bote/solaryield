#include "rz_datetime.h"

namespace rz_datetime
{

  std::string test() { return ("rz_datetime: Hello World"); }

  /**
   * @name splitDate
   * @brief split a given date with given delimiter
   *
   * @param string  <date>      (e.g.: "2024-05-04" or "10:13:00")
   * @param char    <delimiter> (e.g.: '-' or ':')
   * @return const std::vector<std::string>
   */
  const std::vector<std::string> splitDateTime(std::string string, char delimiter)
  {
    std::string val1, val2, val3 = "";
    std::vector<std::string> v{};

    std::stringstream ss(string);
    std::getline(ss, val1, delimiter);
    std::getline(ss, val2, delimiter);
    std::getline(ss, val3, delimiter);

    v.push_back(val1);
    v.push_back(val2);
    v.push_back(val3);

    return (v);
  }

  /**
   * @brief returns the current date time
   *
   * @param format
   * human    (e.g.: 2023-03-25 15:41:32)
   * tz       (e.g.: 2023-03-25T15:41:32CET)
   * string   (e.g.: 2023-03-25_15-41-32)
   * date     (e.g.: 2024-05-04)
   * time     (e.g.: 11:43:10)
   *
   * @return const std::string
   */
  const std::string getCurrentDateTime(std::string format)
  {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format

    if (format.compare("human") == 0)
    {
      strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    }
    else if (format.compare("tz") == 0)
    {
      strftime(buf, sizeof(buf), "%Y-%m-%dT%X%Z", &tstruct);
    }
    else if (format.compare("string") == 0)
    {
      strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
    }
    else if (format.compare("YYYY-MM-DD") == 0)
    {
      strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    }
    else if (format.compare("YYYY-MM") == 0)
    {
      strftime(buf, sizeof(buf), "%Y-%m", &tstruct);
    }
    else if (format.compare("YYYY") == 0)
    {
      strftime(buf, sizeof(buf), "%Y", &tstruct);
    }
    else if (format.compare("MM") == 0)
    {
      strftime(buf, sizeof(buf), "%m", &tstruct);
    }
    else if (format.compare("DD") == 0)
    {
      strftime(buf, sizeof(buf), "%d", &tstruct);
    }
    else if (format.compare("time") == 0)
    {
      strftime(buf, sizeof(buf), "%X", &tstruct);
    }
    else if (format.compare("H") == 0)
    {
      strftime(buf, sizeof(buf), "%H", &tstruct);
    }
    else if (format.compare("M") == 0)
    {
      strftime(buf, sizeof(buf), "%M", &tstruct);
    }
    else if (format.compare("S") == 0)
    {
      strftime(buf, sizeof(buf), "%S", &tstruct);
    }
    return buf;
  }

} // namespace rz_datetime
