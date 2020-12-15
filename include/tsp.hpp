// Jan Wacek , 302931
#ifndef TSP_HPP
#define TSP_HPP

#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

class Cost_matrix{
public:
    Cost_matrix(std::vector<std::vector<double>> matrix_): matrix(matrix_) {}

    std::vector<double> find_min_col();

    std::vector<double> find_min_row();

    bool check_zero();

    void subtract_min_col();

    void subtract_min_row();

    double min_val_col(double col, double id);

    double min_val_row(double row, double id);

    std::vector<std::pair<std::pair<int,int>,double>> find_pairs();

    void delete_row_col(double row, double col);

private:
    std::vector<std::vector<double>> matrix;

};

std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);

double get_forbidden_cost();

#endif //TSP_HPP
