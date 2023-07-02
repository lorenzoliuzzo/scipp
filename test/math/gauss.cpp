#include <iostream>
#include <cmath>
#include <vector>
#include "scipp"

using namespace scipp;
using namespace scipp::math;
using namespace scipp::math::functions;



void generateGaussianQuadrature(int numPoints, std::vector<double>& quadraturePoints, std::vector<double>& weights) {
    quadraturePoints.resize(numPoints);
    weights.resize(numPoints);
    
    for (int i = 0; i < numPoints; ++i) {
        double x = cos((2 * i + 1) * M_PI / (2 * numPoints));
        double prev = 0.0;
        double current = 1.0;
        
        double dp;
        while (std::abs(prev - current) > 1e-10) {
            double p0 = 1.0;
            double p1 = x;
            double p2;
            
            for (int j = 2; j <= numPoints; ++j) {
                p2 = ((2 * j - 1) * x * p1 - (j - 1) * p0) / j;
                p0 = p1;
                p1 = p2;
            }
            
            dp = numPoints * (x * p2 - p1) / (x * x - 1);
            prev = current;
            current = x;
            x = current - p2 / dp;
        }
        
        quadraturePoints[i] = x;
        weights[i] = 2 / ((1 - x * x) * dp * dp);
    }
}

// Function to integrate (change it to the desired function)
double function(double x) {
    return std::sin(x * x);
}

// Gaussian quadrature algorithm
double gaussianQuadrature(double a, double b, int numPoints) {
    std::vector<double> quadraturePoints;
    std::vector<double> weights;
    
    // Generate the quadrature points and weights
    generateGaussianQuadrature(numPoints, quadraturePoints, weights);
    
    // Transform the integration limits
    double scaledA = (b - a) / 2.0;
    double scaledB = (b + a) / 2.0;
    
    // Perform the Gaussian quadrature
    double sum = 0.0;
    for (int i = 0; i < numPoints; ++i) {
        double x = scaledA * quadraturePoints[i] + scaledB;
        sum += weights[i] * function(x);
    }
    
    // Scale the result
    double result = scaledA * sum;
    
    return result;
}

int main() {
    double lowerLimit = 0.0;  // Lower limit of integration
    double upperLimit = 1.0;  // Upper limit of integration
    int numPoints = 40;        // Number of quadrature points
    
    // Perform Gaussian quadrature and get the result
    double result = gaussianQuadrature(lowerLimit, upperLimit, numPoints);
    auto exact = integrals::simpson<compose<sine<double>, square<double>>, std::micro>(curves::interval(lowerLimit, upperLimit));
    // Output the result
    std::cout << "Approximation: " << result << std::endl;
    tools::print(exact);

    return 0;
}
