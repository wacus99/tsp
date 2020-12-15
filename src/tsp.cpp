// Jan Wacek , 302931
#include "tsp.hpp"

    std::vector<double> Cost_matrix::find_min_col() {
        std::vector<double> lst;
        double min, k = 1;
        for (auto i = 0; i < matrix.size(); i++ ){
            min = matrix[i][0];
            while (std::isnan(min) && k < matrix[i].size()) {
                min = matrix[i][k];
                k++;
            }
            while (k < matrix[i].size()) {
                if ( matrix[i][k] < min) {
                    min = matrix[i][k];
                }
                k++;
            }
            lst.push_back(min);
            k = 1;
        }
        return lst;
    }

    std::vector<double> Cost_matrix::find_min_row() {
        std::vector<double> lst;
        double min, k = 1;
        for (auto i = 0; i < matrix.size(); i++ ){
            min = matrix[0][i];
            while (std::isnan(min) && k < matrix.size()) {
                min = matrix[k][i];
                k++;
            }
            while (k < matrix.size()) {
                if ( matrix[k][i] < min) {
                    min = matrix[k][i];
                }
                k++;
            }
            lst.push_back(min);
            k = 1;
        }
        return lst;
    }

    bool Cost_matrix::check_zero() {
        double k = 0;
        double k1 = 0;
        double j = 0;
        double j1 = 0;
        for (auto i = 0; i < matrix.size(); i++){
            for (auto m = 0; m < matrix.size(); m++){
                if (matrix[i][m] == 0)
                    k++;
                if (std::isnan(matrix[i][m]))
                    k1++;
                if (matrix[m][i] == 0)
                    j++;
                if (std::isnan(matrix[m][i]))
                    j1++;
            }
            if (k == 0 && k1 != matrix.size())
                return false;
            if (j == 0 && j1 != matrix.size())
                return false;
            k = 0;
            j = 0;
            k1 = 0;
            j1 = 0;
        }
        return true;
    }

    void Cost_matrix::subtract_min_col() {
        std::vector<double> vec = find_min_col();
        for (auto i = 0; i < matrix.size(); i++ ){
            for (auto m = 0; m < matrix.size(); m++ ){
                if (m != i){
                    matrix[i][m] = matrix[i][m] - vec[i];
                }

            }
        }
    }

    void Cost_matrix::subtract_min_row() {
        std::vector<double> vec = find_min_row();
        for (auto i = 0; i < matrix.size(); i++ ){
            for (auto m = 0; m < matrix.size(); m++ ){
                if (m != i){
                    matrix[i][m] = matrix[i][m] - vec[m];
                }

            }
        }
    }

    double Cost_matrix::min_val_col(double col, double id) {
        std::vector<double> vec;
        double min;
        for (auto i = 0; i < matrix.size(); i++){
            for (auto m = 0; m < matrix.size(); m++){
                if (i == col && m != id && !std::isnan(matrix[m][i])) vec.push_back(matrix[m][i]);
            }
        }
        if (vec.size() == 0) return 0;

        min = vec[0];
        for (auto i = 1; i < vec.size(); i++) {
            if (vec[i] < min) min = vec[i];
        }
        return min;
    }

    double Cost_matrix::min_val_row(double row, double id){
        std::vector<double> vec;
        double min;
        for (auto i = 0; i < matrix[row].size(); i++) {
            if (i != id && !std::isnan(matrix[row][i])) {
                vec.push_back(matrix[row][i]);
            }
        }
        if (vec.size() == 0) return 0;

        min = vec[0];
        for (auto i = 1; i < vec.size(); i++) {
            if (vec[i] < min) min = vec[i];
        }
        return min;
    }

    std::vector<std::pair<std::pair<int,int>,double>> Cost_matrix::find_pairs() {
        std::vector<std::pair<std::pair<int,int>,double>> vec;
        double value = 0;
        std::pair<int,int> pa;
        for (auto i = 0; i < matrix.size(); i++) {
            for (auto m = 0; m < matrix.size(); m++) {
                if (!std::isnan(matrix[i][m]) && matrix[i][m] == 0) {
                    pa.first = i+1;
                    pa.second = m+1;
                    value = min_val_col(m,i) + min_val_row(i,m);
                    vec.push_back({pa,value});
                }
            }
        }
        return vec;
    }

    void Cost_matrix::delete_row_col(double row, double col) {
        for (auto i = 0; i < matrix.size(); i++){
            for (auto j = 0; j < matrix.size(); j++) {
                if ( i == row - 1 || j == col - 1){
                    matrix[i][j] = NAN;
                }
            }
        }
        matrix[col - 1][row - 1] = NAN;
    }


std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix) {
    Cost_matrix mat(cost_matrix);
    int n = cost_matrix.size();
    std::vector<std::pair<std::pair<int,int>,double>> vec ={};
    std::vector<std::pair<int,int>> tr;
    double max;
    int id_max;
    while (n > 2) {
        for (auto i =0; !mat.check_zero(); i++) {
            mat.subtract_min_col();
            if (!mat.check_zero()) mat.subtract_min_row();
        }
        vec = mat.find_pairs();
        max = vec[0].second;
        id_max = 0;
        for (auto i = 0; i < vec.size(); i++) {
            if ( max < vec[i].second) {
                max = vec[i].second;
                id_max = i;
            }
        }
        tr.push_back(vec[id_max].first);
        mat.delete_row_col(vec[id_max].first.first,vec[id_max].first.second);
        n--;
    }
    for (auto i = 0; !mat.check_zero(); i++) {
        mat.subtract_min_col();
        if (!mat.check_zero()) mat.subtract_min_row();
    }

    vec = mat.find_pairs();
    if (vec.size() == 2) {
        tr.push_back(vec[0].first);
        tr.push_back(vec[1].first);
    }
    else {
        if (vec[0].first.first == vec[1].first.first) {
            if (vec[2].first.second == vec[0].first.second) {
                tr.push_back(vec[1].first);
                tr.push_back(vec[2].first);
            }
            if (vec[2].first.second == vec[1].first.second) {
                tr.push_back(vec[0].first);
                tr.push_back(vec[2].first);
            }
        }
        if (vec[1].first.first == vec[2].first.first) {
            if (vec[0].first.second == vec[1].first.second) {
                tr.push_back(vec[0].first);
                tr.push_back(vec[2].first);
            }
            if (vec[0].first.second == vec[2].first.second) {
                tr.push_back(vec[0].first);
                tr.push_back(vec[1].first);
            }
        }
    }
    std::vector<int> tr_vec;
    tr_vec.push_back(tr[0].first);
    tr_vec.push_back(tr[0].second);
    for (auto m = 1; m < tr.size(); m++) {
        for (auto i = 1; i < tr.size(); i++){
            if (tr[i].first == tr_vec[m]){
                tr_vec.push_back(tr[i].second);
                break;
            }
        }
    }
    return tr_vec;
}

double get_forbidden_cost(){
    return NAN;
}