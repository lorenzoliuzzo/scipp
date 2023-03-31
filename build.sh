mkdir build
cmake -S . -B build
cmake --build build
# doxygen doc/Doxyfile
# cd doc/latex
# make refman.pdf
# open doc/html/index.html
# evince refman.pdf