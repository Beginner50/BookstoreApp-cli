# CLI Bookstore Application Project
The cli bookstore application is a simple project that demonstrates the extent of my understanding of C/C++ and CMake.

![Screenshot from 2024-08-27 23-53-51](https://github.com/user-attachments/assets/8ae74c12-8511-4bbc-aac1-fb14e76ca991)

![Screenshot from 2024-08-27 23-54-31](https://github.com/user-attachments/assets/b51d66f8-d165-4227-b179-ab5df7b1d9cc)

![Screenshot from 2024-08-27 23-55-14](https://github.com/user-attachments/assets/e7655f0f-d1e6-48c6-8adc-7d7a495dd49f)


* * *
## Installation
The program will have to be compiled from source.
### Windows
Unfortunately, since windows requires the user to download the precompiled binaries for sqlite libraries first, I am unsure
if the CMakeLists.txt file will work as intended. I don't have windows either and so I can't test it out.

I will port the application to windows one day...

### Linux
#### Debian/Ubuntu
Install the sqlite3 & libsqlite-dev package:
  `sudo apt install sqlite3 libsqlite-dev`

Then, run the following commands:
`cd build && cmake ../ && cmake --build . && ./BookstoreApp`
