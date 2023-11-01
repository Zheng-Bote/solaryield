#pragma once

#include <iostream>
#include <string.h>

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>
#include <iomanip>
#include <ctime>

class ShellyYield
{
public:
  ShellyYield(const std::string *inFile);

  virtual ~ShellyYield();

  virtual std::string getVersion();
  virtual std::string getInFile();

  virtual std::string getInFileType();
  virtual std::string getFilePerm(std::string pathToFile);
  virtual std::string getFilePerms(std::filesystem::perms pathToFile);
  virtual bool isReadAble(const std::string *pathToFile);
  virtual bool checkFileExtension(const std::string *pathToFile, std::string extension);

  virtual void parseFileToMapKey(std::map<std::string, float> &mapKeys, std::string pathToFile);
  virtual void displayMap(std::map<std::string, float> &mapKeys);
  virtual bool writeCSV(std::map<std::string, float> &mapKeys, std::string pathToFile);
  virtual bool writeJson(std::map<std::string, float> &mapKeys, std::string &pathToFile);

  virtual std::string &ltrim(std::string &s);
  virtual std::string &rtrim(std::string &s);
  virtual std::string &trim(std::string &s);
  virtual std::string rmLastNewline(std::string s);
  virtual std::string formatKey(std::string key);

private:
  const std::string *_inFile;
  const std::string _VERSION = "0.3.0";
};