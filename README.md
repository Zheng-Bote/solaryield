<div id="top"></div>
<br />
<div align="center">
  <h3 align="center">ShellYield</h3>
        read and consolidate Shelly Plug S consumption.csv
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
    <li><a href="#history">History</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>
<br/>

#### BRIEF: 
<span id="brief"></span>
read and consolidate Shelly Plug S consumption.csv

### VERSION: 
<span id="version"></span>
0.2.0

### DESC: 
<span id="description"></span>
C++20 program to read and consolidate Shelly Plug S consumption.csv.

Output to terminal, CSV or JSON file.

Several entries for the same day will be accumulated.

### DEPENDENCIES: 
<span id="dependencies"></span>
#### cxxopts

a lightweight C++ option parser library, supporting the standard GNU style syntax for options.

Source: https://github.com/jarro2783/cxxopts

License: gpl2

### AUTHOR: 
<span id="author"></span>
ZHENG Robert

### SOURCE: 
<span id="source"></span>
https://github.com/Zheng-Bote/solaryield

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
  -h, --help        Print usage
  -v, --version     Version
```
<p align="right">(<a href="#top">back to top</a>)</p>

### EXAMPLES: 
<span id="examples"></span>
```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writecsv ./new.csv
```
```
./shellyield --csv GH_Solar_0108202331082023_consumption.csv --writejson ./new.json
```

### RETURNS: 
<span id="returns"></span>
```
0 => OK
1 => NOK
```

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


### HISTORY:
<span id="history"></span>

> | Version | Date       | Developer | Comments           |
> | ------- | ---------- | --------- | ------------------ |
> | 0.1.0   | 2023-10-28 | RZheng    | created            |
> | 0.2.0   | 2023-10-29 | RZheng    | added: JSON output |

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
