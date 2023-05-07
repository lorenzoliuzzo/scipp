/**
 * @file position.cpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief Test file for position.hpp
 * @date 2022-12-19
 * 
 * @copyright Copyright (c) 2023
 */

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph2D.h" 

#include "physics.hpp"

using namespace physics;


int main(int argc, char **argv) {

    size_t n = std::atoi(argv[1]);
    tools::random_generator rg; 

    TApplication app{"app", 0, 0};
    TGraph2D graph{};
    TCanvas c("c", "Graph2D example", 0, 0, 600, 600);

    for (size_t i{}; i < n; i++) 
        graph.SetPoint(i, rg.unif(-10, 10), rg.unif(-10, 10), rg.unif(-10, 10));

    c.cd();
    c.SetGrid();
    graph.SetTitle("Graph2D title");
    graph.GetXaxis()->SetTitle("x");
    graph.GetYaxis()->SetTitle("y");
    graph.GetZaxis()->SetTitle("z");
    graph.Draw("P");
    app.Run();


    return 0;

}