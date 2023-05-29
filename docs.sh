doxygen docs/Doxyfile
cd docs/latex
make all
evince refman.pdf
cd ../html
open index.html