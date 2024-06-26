<div id="top"></div>
<br />
<div align="center">
  <h3 align="center">ShellYield</h3>
        read and consolidate Shelly Plug consumption.csv
<br/>
<br/>
  <a href="https://github.com/Zheng-Bote/solaryield/issues">Report Bug</a>
  <a href="https://github.com/Zheng-Bote/solaryield/issues">Request Feature</a>
  <br/>
</div>

<br/>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#brief">Brief</a></li>
    <li><a href="#description">Description</a></li>
    <li><a href="#author">Author</a></li>
    <li><a href="#source">Source</a></li>
    <li><a href="#dependencies">Dependencies</a></li>
    <li><a href="#syntax">Syntax</a></li>
    <li><a href="#examples">Examples</a></li>
    <li><a href="#returns">Returns</a></li>
    <li><a href="#setup">Setup</a></li>
    <li><a href="#scenario">example scenario</a></li>
    <li><a href="#history">History</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>
<br/>

#### BRIEF:

<span id="brief"></span>
read and consolidate Shelly Plug consumption.csv

### VERSION:

<span id="version"></span>
4.0.0

### Status

![ops](https://img.shields.io/badge/Status-usable-green)

### DESC:

<span id="description"></span>
C++20 program to read, clean and consolidate Shelly Plug consumption.csv.

Output to terminal, CSV or JSON file.

Several entries for the same day will be accumulated.

### AUTHOR:

<span id="author"></span>
ZHENG Robert

### SOURCE:

<span id="source"></span>
https://github.com/Zheng-Bote/solaryield

### DEPENDENCIES:

<span id="dependencies"></span>

#### cxxopts

a lightweight C++ option parser library, supporting the standard GNU style syntax for options.

Source: https://github.com/jarro2783/cxxopts

License: MIT

#### plog

Plog - portable, simple and extensible C++ logging library

Source: https://github.com/SergiusTheBest/plog

License: MIT

#### nlohmann/json

JSON for Modern C++

Source: https://github.com/nlohmann/json

License: MIT

### SYNTAX:

<span id="syntax"></span>
Usage:

```
./shellyield -h
./shellyield --help
```

```
shellyield -h
collect Shelly yields
Usage:
  output/shellyield [OPTION...]

  -c, --csv arg        <pathTo/inputfile.csv>
  -l, --list           list values
      --writecsv arg   output to clean csv. If "": <yyyy-mm>_<1st_part_of_csvInputFile>.csv (default: "")
      --csvout arg     <path to csv output folder>. If "": ./csv_out/ (default: "")
      --writejson arg  output to JSON. If "": <yyyy-mm>_<1st_part_of_csvInputFile>.json (default: "")
      --jsonout arg    <path to JSON output folder>. If "": ./json_out/ (default: "")
      --logpath arg    <pathToLogfile>. if "": ./log (default: "")
  -h, --help           Print usage
  -v, --version        Version
      --fullversion    Full Version
      --program        Program
```

<p align="right">(<a href="#top">back to top</a>)</p>

#### EXAMPLES:

<span id="examples"></span>

- list csv entries

```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv -l
```

- cleanup to csv

```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writecsv ""
```

- cleanup to json

```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writejson new.json
```

- add several csv (eg. several Shelly Plugs from same month) to clean csv and cumulated json

```
./shellyield --csv GH_Solar-1_0108202331082023_consumption.csv --writecsv GH_Solar_2023.csv

./shellyield --csv GH_Solar-2_0108202331082023_consumption.csv --writecsv GH_Solar_2023.csv

./shellyield --csv ./GH_Solar_2023.csv --writejson GH_Solar_2023.json
```

- default output file but custom output path

```
./shellyield --csv ./GH_Solar_2023.csv --writejson "" --jsonout /data/sol/out/
```

- custom output file but default output path

```
./shellyield --csv ./GH_Solar_2023.csv --writecsv my_output.csv --csvout ""
```

### RETURNS:

<span id="returns"></span>

```
0 => OK
1 => NOK
```

<p align="right">(<a href="#top">back to top</a>)</p>

### SETUP:

<span id="setup"></span>

#### Debug:

```
g++-12 -std=c++20 -g3 -O0 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -c -MMD src/main.cpp  -o src/main.o
g++-12 -std=c++20 -g3 -O0 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion  -o output/shellyield src/main.o src/include/rz_shellyield.o
```

#### Release:

```
g++-12 -std=c++20 -O3 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -c -MMD src/main.cpp  -o src/main.o
g++-12 -std=c++20 -O3 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -c -MMD src/include/rz_shellyield.cpp  -o src/include/rz_shellyield.o
g++-12 -std=c++20 -O3 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion  -o output/shellyield src/main.o src/include/rz_shellyield.o
```

**_see also_**

Makefile

```
./make
```

#### Binary:

compiled on:

```
Linux beelink 5.15.0-87-generic #97-Ubuntu SMP Mon Oct 2 21:09:21 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
```

Compiler/Linker:

```
g++ (gcc) version 12.3.0 (Ubuntu 12.3.0-1ubuntu1~22.04)
```

<p align="right">(<a href="#top">back to top</a>)</p>

#### Example Scenario

<span id="scenario"></span>

- in your Shelly app, choose a month and export the consumption as csv-file
  <img src="https://raw.githubusercontent.com/Zheng-Bote/solaryield/main/Examples/shelly_plug_monthly_export.jpg" max-width="180px" height="auto" />
- copy your csv-file to your linux machine
- iwatch will automatically start the shellyield program:

```
<?xml version="1.0" ?>
<!DOCTYPE config SYSTEM "/etc/iwatch/iwatch.dtd" >

<config charset="utf-8">
<guard email="dummy@localhost" name="iWatch"/>
<watchlist>
	<title>Solar</title>
	<contactpoint email="dummy" name="Administrator"/>
	<path type="single" alert="off" events="create,move" exec="/usr/bin/sleep 2; /Mounts/Usb/Solar/shellyield --writecsv /Mounts/Usb/Solar/Output/shellies.csv --writelog /Mounts/Usb/Solar/Log/shellies.log --csv %f">/Mounts/Usb/Solar/Input</path>
</watchlist>
</config>
```

  <img src="https://raw.githubusercontent.com/Zheng-Bote/solaryield/main/Examples/iwatch.png"  width="100%" height="auto" />

- example output (csv):

```
2023-08-01,1363.290
2023-08-02,2596.500
2023-08-03,3572.160
2023-08-04,1889.210
```

- example output (json):

```
[
    {
        "months":
            [
                {
                    "days":
                        [
                            {"day":"01","val":1428.0},
                            {"day":"02","val":328.30999755859375},
                            {"day":"03","val":727.3200073242188},
                            {"day":"04","val":967.3699951171875}
                        ],
                    "month": "08",
                    "month_name": "August",
                    "name": "garten",
                    "watt_per_month": 1865.679931640625
                }
            ],
        "year":"2023"
    }
]
```

- example logfile:

```
2023-11-01 11:58:10.713 INFO  [35911] [main@141] started: output/shellyield-0.3.0
2023-11-01 11:58:10.631 INFO  [35911] [main@142] OK: Inputfile: Examples/GH_Solar_0108202331082023_consumption.csv
2023-11-01 11:58:10.714 INFO  [35911] [main@159] OK: Outputfile: Examples/new.csv
2023-11-01 11:58:10.086 INFO  [36007] [main@141] started: output/shellyield-0.3.0
2023-11-01 11:58:10.086 INFO  [36007] [main@142] OK: Inputfile: Examples/GH_Solar_0108202331082023_consumption.csv
2023-10-30 16:08:40.086 INFO  [36007] [main@175] OK: Outputfile: Examples/new.json
```

- example Graph:

see <a href="https://github.com/Zheng-Bote/solargraph" alt="solargraph" title="https://github.com/Zheng-Bote/solargraph">Angular webapp to visualize ShellYield json</a>

<img src="https://raw.githubusercontent.com/Zheng-Bote/solaryield/main/Examples/graph.png"  width="100%" height="auto" />

<p align="right">(<a href="#top">back to top</a>)</p>

### HISTORY:

<span id="history"></span>

> | Version | Date       | Developer | Comments                                       |
> | ------- | ---------- | --------- | ---------------------------------------------- |
> | 1.0.0   | 2023-10-28 | RZheng    | created                                        |
> | 1.0.1   | 2023-11-01 | RZheng    | JSON modified                                  |
> | 2.0.0   | 2024-04-20 | RZheng    | JSON modified                                  |
> | 3.0.0   | 2024-04-28 | RZheng    | new input format due to Shelly firmware update |
> | 3.1.0   | 2024-05-04 | RZheng    | JSON output enriched                           |
> | 4.0.0   | 2024-05-05 | RZheng    | changed to object oriented due to enhancements |

## Contributing

<span id="contributing"></span>

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

<span id="contact"></span>

ZHENG Robert Zhèng Bó Tè 郑 伯特

Project Link: [https://github.com/Zheng-Bote/solaryield/](https://github.com/Zheng-Bote/solaryield/)

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>
