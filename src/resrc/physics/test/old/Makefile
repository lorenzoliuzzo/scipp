CXX = g++
CXXFLAGS = -g -Wall --pedantic -fno-elide-constructors -fconcepts -std=c++20 -O3
MEASUREMENTS_PATH = -I ~/Desktop/codes/measurements/include
GEOMETRY_PATH = -I ~/Desktop/codes/geometry/include
PHYSICS_PATH = -I ~/Desktop/codes/physics/include
ROOT_FLAGS = `root-config  --glibs --cflags` 
PLOT_FLAGS = -I ~/Desktop/codes/plots -I /usr/include/python3.10 -lpython3.10

position: position.cpp
	$(CXX) $(CXXFLAGS) $(MEASUREMENTS_PATH) $(GEOMETRY_PATH) $(PHYSICS_PATH) -o $@ $<

reference_system: reference_system.cpp
	$(CXX)  $< -o $@  $(CXXFLAGS) $(MEASUREMENTS_PATH) $(GEOMETRY_PATH) $(PHYSICS_PATH) $(PLOT_FLAGS)

root_plot: root_plot.cpp
	$(CXX)  $< -o $@  $(CXXFLAGS) $(MEASUREMENTS_PATH) $(GEOMETRY_PATH) $(PHYSICS_PATH) $(ROOT_FLAGS)

mass: mass.cpp
	$(CXX)  $< -o $@  $(CXXFLAGS) $(MEASUREMENTS_PATH) $(GEOMETRY_PATH) $(PHYSICS_PATH) $(PLOT_FLAGS)

solar: solar.cpp
	$(CXX)  $< -o $@  $(CXXFLAGS) $(MEASUREMENTS_PATH) $(GEOMETRY_PATH) $(PHYSICS_PATH) $(PLOT_FLAGS)

earth_sun_mars: earth_sun_mars.cpp
	$(CXX)  $< -o $@  $(CXXFLAGS) $(MEASUREMENTS_PATH) $(GEOMETRY_PATH) $(PHYSICS_PATH) $(PLOT_FLAGS)
