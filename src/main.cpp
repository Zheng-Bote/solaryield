#include <iostream>
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include <iterator>

#include "lib/cxxopts.hpp"

#include "include/rz_main.h"
#include "include/rz_datetime.h"
#include "include/rz_dirs.h"
#include "rz_files.h"
#include "rz_shelly.h"

int main(int argc, char *argv[])
{
  std::string csvInputFile = "";
  std::string csvOutputPath = "./csv_out/";   // default
  std::string csvOutputFile = "";             // <yyyy-mm>_<1st_part_of_csvInputFile>.csv
  std::string jsonOutputPath = "./json_out/"; // default
  std::string jsonOutputFile = "";            // <yyyy-mm>_<1st_part_of_csvInputFile>.csv
  std::string logFile = "";                   // <yyyy-mm>_<program>.log
  std::string logFilePath = "./log/";         // default "./log/<program>"
  std::map<std::string, float> mapKeys = {};  // map Shelly date and value
  std::vector<std::string> yyyymm{};          // year and month of mapKey
  std::vector<std::string> dummy{};           // ragpicker

  cxxopts::Options options(argv[0], "collect Shelly yields");
  options.add_options()(
      "c,csv", "<pathTo/inputfile.csv>", cxxopts::value<std::string>())("l,list", "list values")("writecsv", "output to clean csv. If \"\": <yyyy-mm>_<1st_part_of_csvInputFile>.csv", cxxopts::value<std::string>()->default_value(""))("csvout", "<path to csv output folder>. If \"\": ./csv_out/", cxxopts::value<std::string>()->default_value(""))("writejson", "output to JSON. If \"\": <yyyy-mm>_<1st_part_of_csvInputFile>.json", cxxopts::value<std::string>()->default_value(""))("jsonout", "<path to JSON output folder>. If \"\": ./json_out/", cxxopts::value<std::string>()->default_value(""))("logpath", "<pathToLogfile>. if \"\": ./log", cxxopts::value<std::string>()->default_value(""))("h,help", "Print usage")("v,version", "Version")("fullversion", "Full Version")("program", "Program");

  auto result = options.parse(argc, argv);
  RZ_Main *main = new RZ_Main();

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(EXIT_SUCCESS);
  }
  if (result.count("version"))
  {
    std::cout << "v" << main->getVersion() << std::endl;
    exit(EXIT_SUCCESS);
  }
  if (result.count("fullversion"))
  {
    std::cout << main->getFullVersion() << std::endl;
    exit(EXIT_SUCCESS);
  }
  if (result.count("program"))
  {
    std::cout << argv[0] << std::endl;
    exit(EXIT_SUCCESS);
  }

  if (result.count("csv") && result["csv"].as<std::string>().length() >= 1)
  {
    csvInputFile = result["csv"].as<std::string>();
    if (!rz_files::checkFileExtension(csvInputFile, ".csv"))
    {
      std::cout << "ERROR: file is not a csv: " << csvInputFile << std::endl;
      exit(EXIT_FAILURE);
    }
    if (!rz_files::isReadAble(csvInputFile))
    {
      std::cout << "ERROR: csv file not readable: " << csvInputFile << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    std::cout << "missing inputfile\n"
              << std::endl;
    std::cout << options.help() << std::endl;
    exit(EXIT_FAILURE);
  }

  if (result.count("logpath") && result["logpath"].as<std::string>().length() >= 1)
  {
    logFilePath = result["logpath"].as<std::string>();
  }
  logFilePath.append(main->getProgName() + "/");
  logFile = rz_datetime::getCurrentDateTime("YYYY-MM");
  logFile.append("_");
  logFile.append(main->getProgName());
  logFile.append(".log");

  if (!rz_dirs::dir_exist(logFilePath))
  {
    if (!rz_dirs::create_directory(logFilePath))
    {
      std::cout << "ERROR: create logfile path failed: " << logFilePath << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  logFilePath.append(logFile);

  // ok-la, let's do something

  // init logging
  plog::init(plog::verbose, logFilePath.c_str(), 5000, 3);
  plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::get()->addAppender(&consoleAppender);
  PLOG_INFO << "started: " << rz_dirs::getCanonicalPath(argv[0]) << "-" << main->getVersion();
  PLOG_INFO << "logging to: " << rz_dirs::getCanonicalPath(logFilePath);

  // happy coding \^o^/
  if (!rz_shelly::parseFileToMapKey(mapKeys, csvInputFile))
  {
    PLOG_ERROR << "Error parsing " << csvInputFile;
    exit(EXIT_FAILURE);
  }

  if (result.count("list"))
  {
    PLOG_INFO << "display Map of: " << csvInputFile;
    rz_shelly::displayMap(mapKeys);
  }

  if (result.count("writecsv"))
  {
    // csvOutputPath
    if (result["csvout"].as<std::string>().length() >= 1)
    {
      csvOutputPath = result["csvout"].as<std::string>();
    }
    if (!rz_dirs::dir_exist(csvOutputPath))
    {
      if (!rz_dirs::create_directory(csvOutputPath))
      {
        PLOG_ERROR << "ERROR: create csv out path failed: " << csvOutputPath;
        exit(EXIT_FAILURE);
      }
    }

    //  csvOutputFile given
    if (result["writecsv"].as<std::string>().length() >= 1)
    {
      csvOutputPath.append(result["writecsv"].as<std::string>());
    }
    else
    {
      auto it = mapKeys.begin();
      std::advance(it, 0);
      yyyymm = {};
      yyyymm = {rz_datetime::splitDateTime(it->first, '-')};
      dummy = {};
      dummy = {rz_datetime::splitDateTime(rz_files::getOnlyFilename(csvInputFile), '_')};
      csvOutputPath.append(yyyymm.at(0) + "-" + yyyymm.at(1) + "_" + dummy.at(0) + ".csv");
    }
    PLOG_INFO << "csvOutputFile: " << csvOutputPath;

    if (!rz_shelly::writeCSV(mapKeys, csvOutputPath))
    {
      PLOG_ERROR << "Error writing CSV out: " << csvOutputPath;
      exit(EXIT_FAILURE);
    }
    PLOG_INFO << "Successful written CSV out: " << csvOutputPath;
  }

  if (result.count("writejson"))
  {
    // csvOutputPath
    if (result["jsonout"].as<std::string>().length() >= 1)
    {
      jsonOutputPath = result["jsonout"].as<std::string>();
    }
    if (!rz_dirs::dir_exist(jsonOutputPath))
    {
      if (!rz_dirs::create_directory(jsonOutputPath))
      {
        PLOG_ERROR << "ERROR: create json out path failed: " << jsonOutputPath;
        exit(EXIT_FAILURE);
      }
    }

    //  jsonOutputFile given
    if (result["writejson"].as<std::string>().length() >= 1)
    {
      jsonOutputPath.append(result["writejson"].as<std::string>());
    }
    else
    {
      auto it = mapKeys.begin();
      std::advance(it, 0);
      yyyymm = {};
      yyyymm = {rz_datetime::splitDateTime(it->first, '-')};
      dummy = {};
      dummy = {rz_datetime::splitDateTime(rz_files::getOnlyFilename(csvInputFile), '_')};
      jsonOutputPath.append(yyyymm.at(0) + "-" + yyyymm.at(1) + "_" + dummy.at(0) + ".json");
    }
    PLOG_INFO << "jsonOutputFile: " << jsonOutputPath;

    if (!rz_shelly::writeJson(mapKeys, jsonOutputPath, dummy.at(0)))
    {
      PLOG_ERROR << "Error writing JSON out: " << jsonOutputPath;
      exit(EXIT_FAILURE);
    }
    PLOG_INFO << "Successful written JSON out: " << jsonOutputPath;
  }

  // the end
  PLOG_INFO
      << "ended: " << rz_dirs::getCanonicalPath(argv[0]) << "-" << main->getVersion();
  exit(EXIT_SUCCESS);
}