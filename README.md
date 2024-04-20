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
1.0.2

### DESC:

<span id="description"></span>
C++20 program to read and consolidate Shelly Plug consumption.csv.

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

### SYNTAX:

<span id="syntax"></span>
Usage:

```
./shellyield -h
./shellyield --help
```

```
ShellYield [OPTION...]
  -c, --csv arg     <pathTo/inputfile.csv>
  -l, --list        list values
  --writecsv arg    <pathTo/outputfile.csv>
  --writejson arg   <pathTo/outputfile.json>
  --writelog arg    <pathTo/logfile.log>
  -h, --help        Print usage
  -v, --version     Version
```

<p align="right">(<a href="#top">back to top</a>)</p>

#### EXAMPLES:

<span id="examples"></span>

- cleanup to csv

```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writecsv ./new.csv
```

- cleanup to json

```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writejson ./new.json
```

- add several csv (eg. several Shelly Plugs from same month) to clean csv and cumulated json

```
./shellyield --csv GH_Solar-1_0108202331082023_consumption.csv --writecsv ./GH_Solar_2023.csv

./shellyield --csv GH_Solar-2_0108202331082023_consumption.csv --writecsv ./GH_Solar_2023.csv

./shellyield --csv ./GH_Solar_2023.csv --writejson ./GH_Solar_2023.json
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

#### Binary:

compiled on:

```
Linux beelink 5.15.0-87-generic #97-Ubuntu SMP Mon Oct 2 21:09:21 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
```

Compiler/Linker:

```
gcc version 12.3.0 (Ubuntu 12.3.0-1ubuntu1~22.04)
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
2023-08-05,682.140
2023-08-06,1757.170
2023-08-07,2030.430
2023-08-08,2830.230
2023-08-09,845.770
2023-08-10,3496.440
2023-08-11,3649.010
2023-08-12,2967.770
2023-08-13,3179.720
2023-08-14,3414.040
2023-08-15,1521.920
2023-08-16,1511.120
2023-08-17,3413.260
2023-08-18,3525.140
2023-08-19,3394.840
2023-08-20,3577.620
2023-08-21,3511.590
2023-08-22,2656.190
2023-08-23,3377.280
2023-08-24,3376.590
2023-08-25,2267.050
2023-08-26,2062.610
2023-08-27,600.000
2023-08-28,743.910
2023-08-29,693.810
2023-08-30,2048.360
2023-08-31,2043.190
```

- example output (json):

```
{
    "2023": {
        "11": [
            {
                "10": 1643.3699951171875,
                "11": 1243.0899658203125,
                "12": 381.1700134277344,
                "13": 132.63999938964844,
                "14": 199.4600067138672,
                "15": 292.6400146484375,
                "16": 344.4800109863281,
                "17": 359.7099914550781,
                "18": 572.8800048828125,
                "19": 1137.3399658203125,
                "20": 1108.31005859375,
                "21": 1068.510009765625,
                "22": 112.25,
                "23": 553.9000244140625,
                "24": 141.5800018310547,
                "25": 197.47999572753906,
                "26": 91.51000213623047,
                "27": 301.95001220703125,
                "28": 109.2699966430664,
                "29": 85.20999908447266,
                "30": 30.790000915527344,
                "31": 2043.18994140625,
                "01": 1527.3199462890625,
                "02": 416.3500061035156,
                "03": 888.7000122070312,
                "04": 1059.699951171875,
                "05": 1304.72998046875,
                "06": 645.5,
                "07": 741.3099975585938,
                "08": 513.510009765625,
                "09": 506.75
            }
        ],
        "08": [
            {
                "10": 3496.43994140625,
                "11": 3649.010009765625,
                "12": 2967.77001953125,
                "13": 3179.719970703125,
                "14": 3414.0400390625,
                "15": 1521.9200439453125,
                "16": 1511.1199951171875,
                "17": 3413.260009765625,
                "18": 3525.139892578125,
                "19": 3394.840087890625,
                "20": 3577.6201171875,
                "21": 3511.590087890625,
                "22": 2656.18994140625,
                "23": 3377.280029296875,
                "24": 3376.590087890625,
                "25": 2267.050048828125,
                "26": 2062.610107421875,
                "27": 556.3699951171875,
                "28": 743.9099731445312,
                "29": 693.8099975585938,
                "30": 2048.360107421875,
                "31": 2043.18994140625,
                "01": 1363.2900390625,
                "02": 2596.5,
                "03": 3572.159912109375,
                "04": 1889.2099609375,
                "05": 682.1400146484375,
                "06": 1757.1700439453125,
                "07": 2030.4300537109375,
                "08": 2830.22998046875,
                "09": 845.77001953125
            }
        ]
    }
}
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

<img src="https://raw.githubusercontent.com/Zheng-Bote/solaryield/main/Examples/graph.png"  width="100%" height="auto" />

<p align="right">(<a href="#top">back to top</a>)</p>

### HISTORY:

<span id="history"></span>

> | Version | Date       | Developer | Comments      |
> | ------- | ---------- | --------- | ------------- |
> | 1.0.0   | 2023-10-28 | RZheng    | created       |
> | 1.0.1   | 2023-11-01 | RZheng    | JSON modified |
> | 1.0.2   | 2024-04-20 | RZheng    | JSON modified |

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
