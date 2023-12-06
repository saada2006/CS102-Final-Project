# CS102 Final Project - 2048

This is our final project for Ohlone CS102 - Introduction to C++. It is a basic implementation of 2048.

## Compiling the program

### Windows (Untested)

First, install Git, CMake, and Visual Studio 2022. Use Google if you are unsure how to install them. Then, open a terminal, go to a directory where you want to download the project files in, and do the following steps:
```
git clone https://github.com/saada2006/CS102-Final-Project --recurse-submodule
cd CS102-Final-Project
cmake --build . --config Release
```
There should be a `.sln` file somewhere now. Double click on it to open it via Visual Studio 2022. From here, you can compile/run the project and edit the code.

### Mac OS (Untested) / Linux

First, install Git and CMake. Use Google if you are unsure how to install them. Then, open a terminal, go to a directory where you want to download the project files in, and do the following steps:
```
git clone https://github.com/saada2006/CS102-Final-Project --recurse-submodule
cd CS102-Final-Project
chmod +x ./build_and_run.sh
./build_and_run.sh
```
This will automatically compile and run the program for you.

## Project Structure

So now you've successfully compiled and run the program, it is time to start editing the code. All of the program code is in `src`. You only will need to worry about `src/logic_controller.cpp`, which handles the underlying logic for 2048. I need you guys to do bug testing and resolve any bugs. Once you have resolved any bugs, let me know and I will help you with updating this repo with your code. 