/*
TITLE:        ShellYield

BRIEF:        read and consolidate Shelly Plug S consumption.csv

VERSION:      1.0.2

DESC:         C++20 program to read and consolidate Shelly Plug S consumption.csv.
              Output to terminal, CSV or JSON file.
              Several entries for the same day will be accumulated.

AUTHOR:       ZHENG Robert

SOURCE:       https://github.com/Zheng-Bote/solaryield

DEPENDENCIES: cxxopts
              a lightweight C++ option parser library, supporting the standard GNU style syntax for options.
              Source: https://github.com/jarro2783/cxxopts
              License: gpl2

              plog
              Plog - portable, simple and extensible C++ logging library
              Source: https://github.com/SergiusTheBest/plog
              License: MIT

SYNTAX:       Usage:
              ShellYield [OPTION...]

              -c, --csv arg     <pathTo/inputfile.csv>
              -l, --list        list values
              --writecsv arg    <pathTo/outputfile.csv>
              --writejson arg   <pathTo/outputfile.json>
              -h, --help        Print usage
              -v, --version     Version

EXAMPLES:     ./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writecsv ./new.csv
              ./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writejson ./new.json

RETURNS:      0 => OK
              1 => NOK

SETUP:        Debug:
              g++-12 -std=c++20 -g3 -O0 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -c -MMD src/main.cpp  -o src/main.o
              g++-12 -std=c++20 -g3 -O0 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion  -o output/shellyield src/main.o src/include/rz_shellyield.o

              Release:
              g++-12 -std=c++20 -O3 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -c -MMD src/main.cpp  -o src/main.o
              g++-12 -std=c++20 -O3 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -c -MMD src/include/rz_shellyield.cpp  -o src/include/rz_shellyield.o
              g++-12 -std=c++20 -O3 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion  -o output/shellyield src/main.o src/include/rz_shellyield.o

              Binary:
              compiled on:
              Linux beelink 5.15.0-87-generic #97-Ubuntu SMP Mon Oct 2 21:09:21 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
              Compiler/Linker:
              gcc version 12.3.0 (Ubuntu 12.3.0-1ubuntu1~22.04)

HISTORY:
Version | Date       | Developer | Comments
--------|------------|-----------|------------------------------------
1.0.0   | 2023-10-28 | RZheng    | created                            |
1.0.1   | 2023-11-01 | RZheng    | JSON modified                      |
1.0.2   | 2024-04-20 | RZheng    | JSON modified                      |
*/

#include <iostream>
#include <filesystem>
#include <string>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include "lib/cxxopts.hpp"
#include "include/rz_shellyield.h"

using namespace std;

const std::string VERSION = "1.0.2";

// happy coding ^_^

std::string getFilename(char &argv0)
{
  return std::filesystem::path(&argv0).stem();
}

int main(int argc, char *argv[])
{
  std::string singleFile = "";
  std::string logFile = getFilename(*argv[0]) + ".log";

  cxxopts::Options options("ShellYield", "collect Shelly yields");
  options.add_options()("c,csv", "<pathTo/inputfile.csv>", cxxopts::value<std::string>())("l,list", "list values")("writecsv", "<pathTo/outputfile.csv>", cxxopts::value<std::string>())("writejson", "<pathTo/outputfile.json>", cxxopts::value<std::string>())("writelog", "<pathTo/logfile.log>", cxxopts::value<std::string>())("h,help", "Print usage")("v,version", "Version");

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (result.count("version"))
  {
    std::cout << argv[0] << "-" << VERSION << std::endl;
    exit(0);
  }
  if (result.count("csv") && result["csv"].as<std::string>().length() >= 1)
  {
    singleFile = result["csv"].as<std::string>();
  }
  else
  {
    std::cout << "missing inputfile\n"
              << std::endl;
    std::cout << options.help() << std::endl;
    exit(1);
  }

  if (result.count("writelog"))
  {
    logFile = result["writelog"].as<std::string>();
  }

  if (argc <= 1)
  {
    std::cout << "missing inputfile\n"
              << std::endl;
    std::cout << options.help() << std::endl;
    exit(1);
  }

  // ok-la, let's do something

  plog::init(plog::debug, logFile.c_str(), 5000, 3);

  plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::get()->addAppender(&consoleAppender);

  ShellyYield *shellyData = new ShellyYield(&singleFile);
  PLOG_INFO << "started: " << argv[0] << "-" << VERSION;
  if (shellyData->checkFileExtension(&singleFile, ".csv"))
  {
    PLOG_INFO << "OK: Inputfile: " << shellyData->getInFile();
  }
  else
  {
    PLOG_ERROR << "NOK: Inputfile not a .csv: " << shellyData->getInFile();
    exit(EXIT_FAILURE);
  }
  std::map<std::string, float> mapKeys = {};

  shellyData->parseFileToMapKey(mapKeys, singleFile);

  if (result.count("list"))
  {
    shellyData->displayMap(mapKeys);
  }

  if (result.count("writecsv"))
  {

    std::string csvOutFile = result["writecsv"].as<std::string>();
    if (shellyData->writeCSV(mapKeys, csvOutFile))
    {
      PLOG_INFO << "OK: Outputfile: " << csvOutFile;
      exit(EXIT_SUCCESS);
    }
    else
    {
      PLOG_ERROR << "NOK: Outputfile: " << csvOutFile;
      exit(EXIT_FAILURE);
    }
  }

  if (result.count("writejson"))
  {

    std::string jsonOutFile = result["writejson"].as<std::string>();
    // if (shellyData->writeJson(mapKeys, jsonOutFile))
    if (shellyData->writeNewJson(mapKeys, jsonOutFile))
    {
      PLOG_INFO << "OK: Outputfile: " << jsonOutFile;
      exit(EXIT_SUCCESS);
    }
    else
    {
      PLOG_ERROR << "NOK: Outputfile: " << jsonOutFile;
      exit(EXIT_FAILURE);
    }
  }
}