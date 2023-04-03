doxygen doc/Doxyfile
cd doc/latex
make all
evince refman.pdf
cd ../html
open index.html