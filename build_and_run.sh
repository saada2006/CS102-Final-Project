# Reset and move to the build directory
rm -rf build
mkdir build
cd build

cmake ..
make

./src/CS102_FINAL_PROJ