mkdir build
cd build
cmake ..
make 
cd ..
doxygen Doxyfile
open doc/html/index.html