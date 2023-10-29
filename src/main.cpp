/*
TITLE:        ShellYield

BRIEF:        read and consolidate Shelly Plug S consumption.csv

VERSION:      0.2.0

DESC:         C++20 program to read and consolidate Shelly Plug S consumption.csv.
              Output to terminal, CSV or JSON file.
              Several entries for the same day will be accumulated.

DEPENDENCIES: cxxopts
              a lightweight C++ option parser library, supporting the standard GNU style syntax for options.
              Source: https://github.com/jarro2783/cxxopts
              License: gpl2

AUTHOR:       ZHENG Robert

SOURCE:       https://github.com/Zheng-Bote/solaryield

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
0.1.0   | 2023-10-28 | RZheng    | created                            |
0.2.0   | 2023-10-29 | RZheng    | added: JSON output                 |
*/

#include <iostream>
#include <string>

#include "lib/cxxopts.hpp"
#include "include/rz_shellyield.h"

using namespace std;

const std::string VERSION = "0.2.0";

int main(int argc, char *argv[])
{
  std::string singleFile = "";

  cxxopts::Options options("ShellYield", "collect Shelly yields");
  options.add_options()("c,csv", "<pathTo/inputfile.csv>", cxxopts::value<std::string>())("l,list", "list values")("writecsv", "<pathTo/outputfile.csv>", cxxopts::value<std::string>())("writejson", "<pathTo/outputfile.json>", cxxopts::value<std::string>())("h,help", "Print usage")("v,version", "Version");

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

  if (argc <= 1)
  {
    std::cout << "missing inputfile\n"
              << std::endl;
    std::cout << options.help() << std::endl;
    exit(1);
  }

  // ok-la, let's do something

  ShellyYield *shellyData = new ShellyYield(&singleFile);
  // std::cout << shellyData->getVersion() << std::endl;
  // std::cout << shellyData->getInFile() << std::endl;

  // shitty
  if (shellyData->isReadAble(&singleFile))
  {
    // std::cout << "is readable" << std::endl;
    // std::cout << "inFile Perms: " << shellyData->getFilePerm(singleFile) << std::endl;
  }
  else
  {
    // std::cout << "is not readable" << std::endl;
    // std::cout << "inFile Status: " << shellyData->getInFileType() << std::endl;
    // std::cout << "inFile Perms: " << shellyData->getFilePerm(singleFile) << std::endl;
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
      // std::cout << "OK: " << csvOutFile << std::endl;
      exit(EXIT_SUCCESS);
    }
    else
    {
      // std::cout << "NOK: " << csvOutFile << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  if (result.count("writejson"))
  {

    std::string jsonOutFile = result["writejson"].as<std::string>();
    if (shellyData->writeJson(mapKeys, jsonOutFile))
    {
      // std::cout << "OK: " << jsonOutFile << std::endl;
      exit(EXIT_SUCCESS);
    }
    else
    {
      // std::cout << "NOK: " << jsonOutFile << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}