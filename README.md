# CLI Bookstore Application Project
The cli bookstore application is a simple project that demonstrates the extent of my understanding of C/C++ and CMake.

![Screenshot from 2024-08-27 23-53-51](https://github.com/user-attachments/assets/8ae74c12-8511-4bbc-aac1-fb14e76ca991)

![Screenshot from 2024-08-27 23-54-31](https://github.com/user-attachments/assets/b51d66f8-d165-4227-b179-ab5df7b1d9cc)

![Screenshot from 2024-08-27 23-55-14](https://github.com/user-attachments/assets/e7655f0f-d1e6-48c6-8adc-7d7a495dd49f)


* * *
## Installation
The program will have to be compiled from source.
### Windows
If you are using visual studio, then it should probably work fine. Make sure to generate import files from sqlite def first.

1) Otherwise, first install a suitable c/cpp compiler: MinGW
2) Then, install cmake and navigate to the build directory
3) Navigate to sqlitedll and generate import files from sqlite.def `dlltool -d sqlite3.def -l libsqlite3.a`
4) Open a terminal in the build directory
5) Make sure the environment variable for MinGW libraries are set and run
   `cmake -G "MinGW Makefiles" ..`
6) Run `cmake ../ && cmake --build . && ./BookstoreApp`

### Linux
#### Debian/Ubuntu
Install the sqlite3 & libsqlite-dev package:
  `sudo apt install sqlite3 libsqlite-dev`

Then, run the following commands:
`cd build && cmake ../ && cmake --build . && ./BookstoreApp`
