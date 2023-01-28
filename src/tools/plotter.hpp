/**
 * @file    plotter.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


#include "gplot++.h"


namespace scipp::tools {


    class plotter {


        public: 

            plotter() noexcept : 

                plt{} {}


            template <unit_base UB1, unit_base UB2>
            void plot(const std::vector<measurement<UB1>>& x, 
                      const std::vector<measurement<UB2>>& y,
                      const std::string& label = "",
                      const unit<UB1>& x_unit = unit<UB1>(), 
                      const unit<UB2>& y_unit = unit<UB2>()) {

                assert(x.size() == y.size()); 
                std::vector<scalar> x_(x.size()), y_(y.size()); 

                for (std::size_t i{}; i < x.size(); ++i) {

                    x_[i] = x[i].value_as(x_unit); 
                    y_[i] = y[i].value_as(y_unit); 

                }


                plt.plot(x_, y_, label); 
                plt.show(); 


            }

            template <unit_base UB1, unit_base UB2, unit_base UB3>
            void plot3d(const std::vector<measurement<UB1>>& x, 
                        const std::vector<measurement<UB2>>& y,
                        const std::vector<measurement<UB3>>& z,
                        const std::string& label = "",
                        const unit<UB1>& x_unit = unit<UB1>(), 
                        const unit<UB2>& y_unit = unit<UB2>(),
                        const unit<UB3>& z_unit = unit<UB3>()) {

                assert(x.size() == y.size() && y.size() == z.size()); 
                std::vector<scalar> x_(x.size()), y_(y.size()), z_(z.size()); 

                for (std::size_t i{}; i < x.size(); ++i) {

                    x_[i] = x[i].value_as(x_unit); 
                    y_[i] = y[i].value_as(y_unit); 
                    z_[i] = z[i].value_as(z_unit); 

                }


                plt.plot3d(x_, y_, z_, label, Gnuplot::LineStyle::POINTS); 
                plt.show(); 


            }


        private:

            Gnuplot plt; 


    }; // class plotter


} // namespace scipp::tools