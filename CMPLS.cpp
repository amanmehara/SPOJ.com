// Copyright 2019 Aman Mehara
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

class divided_differences {
  public:
    divided_differences(const std::vector<std::pair<double, double>>& points);
    double interpolate(double x);

  private:
    std::vector<std::pair<double, double>> points_;
    std::vector<std::vector<double>> table_;
};

divided_differences::divided_differences(const std::vector<std::pair<double, double>>& points) {
    points_ = points;
    size_t size = points_.size();
    table_ = std::vector<std::vector<double>>(size, std::vector<double>());
    for (auto point : points_) {
        table_[0].push_back(point.second);
    }
    for (size_t difference = 1; difference < size; difference++) {
        for (size_t i = 0; i < size - difference; i++) {
            double numerator = table_[difference - 1][i + 1] - table_[difference - 1][i];
            double denominator = points[i + difference].first - points[i].first;
            table_[difference].push_back(numerator / denominator);
        }
    }
}

double divided_differences::interpolate(double x) {
    double y = table_[0][0];
    for (size_t difference = 1; difference < table_.size(); difference++) {
        double coefficient = table_[difference][0];
        for (size_t i = 0; i < difference; i++) {
            coefficient *= (x - points_[i].first);
        }
        y += coefficient;
    }
    return y;
}

std::vector<int> compute_remaining_terms(std::vector<int> given_terms, int remaining_count) {
    std::vector<std::pair<double, double>> points;
    for (size_t i = 1; i <= given_terms.size(); i++) {
        points.push_back(std::make_pair(i, given_terms[i - 1]));
    }
    divided_differences divided_differences(points);

    std::vector<int> remaining_terms;
    for (size_t x = given_terms.size() + 1; x <= given_terms.size() + remaining_count; x++) {
        remaining_terms.push_back(std::round(divided_differences.interpolate(x)));
    }
    return remaining_terms;
}

int main() {
    int number;
    std::cin >> number;
    while (number--) {
        int given_count, remaining_count;
        std::cin >> given_count >> remaining_count;
        std::vector<int> given_terms(given_count);
        for (size_t i = 0; i < given_count; i++) {
            std::cin >> given_terms[i];
        }
        auto remaining_terms = compute_remaining_terms(given_terms, remaining_count);
        for (size_t i = 0; i < remaining_terms.size(); i++) {
            std::cout << remaining_terms[i] << " ";
        }
        std::cout << std::endl;
    }
}
