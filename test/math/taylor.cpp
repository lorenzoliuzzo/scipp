/**
 * @file    test/math/taylor.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-17
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"

using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::functions; 
using namespace math::differentials; 


#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

struct Node {
    std::string name;
    double value;
    std::function<double()> compute;  // Function to compute the value of the node
};

class ExpressionGraph {
private:
    std::unordered_map<std::string, Node*> nodes;

public:
    Node* createVariable(const std::string& name, double value) {
        Node* node = new Node{name, value, [&]() { return value; }};
        nodes[name] = node;
        return node;
    }

    Node* createOperation(const std::string& name, const std::vector<Node*>& parents, std::function<double(const std::vector<double>&)> operation) {
        Node* node = new Node{name, 0.0, [&]() {
            std::vector<double> parentValues;
            for (const Node* parent : parents) {
                parentValues.push_back(parent->compute());
            }
            return operation(parentValues);
        }};
        nodes[name] = node;
        return node;
    }

    void printGraph() {
        for (const auto& pair : nodes) {
            std::cout << "Node: " << pair.first << ", Value: " << pair.second->compute() << std::endl;
        }
    }
};

int nodes() {
    ExpressionGraph graph;

    // Create variable nodes
    Node* x = graph.createVariable("x", 2.0);
    Node* y = graph.createVariable("y", 3.0);

    // Create an operation node
    Node* z = graph.createOperation("z", {x, y}, [](const std::vector<double>& parentValues) {
        return parentValues[0] + parentValues[1];
    });

    // Print the expression graph
    graph.printGraph();

    return 0;
}


int main() { 


    timer t;
    t.start(); 
    t.stop(); 
    auto time = t.elapsed(); 

    taylor_series<5, double> taylor(0.0, 1.0, 0.0, -1./6., 0.0, 1./120.);
    auto x = 0.04; 

    t.start(); 
    auto f_x = taylor(x); 
    t.stop(); 
    time = t.elapsed(); 
    
    print<std::nano>("time elapsed", time);
    print<std::nano>("taylor series", f_x);
    print<std::nano>("true value", op::sin(x));


    auto i = nodes(); 
    return 0;

}