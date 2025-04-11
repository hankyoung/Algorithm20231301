#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <chrono>

std::vector<int> make_vector(int size) { //generate vector of random size
    std::vector<int> input_list(size);
    for (int& x : input_list) {
        x = rand() % 10001;  // random number from 0~10^6
    }
    return input_list;
}

bool is_sorted(std::vector<int>& list) {
    for(int i = 0; i < list.size() - 1; i++) {
        if (list[i] > list[i+1]) {
            std::cout << "error" << std::endl;
            return false;
        }
    }
    std::cout << "sorted!" << std::endl;
    return true;
}

void bubble_sort(std::vector<int>& list) { //bubble_sort implementaion
    bool is_swapped = false;
    for(int times = 0; times < list.size()-1; times++) {
        for(int i = 0; i < list.size() - 1; i++) {
            if(list[i] > list[i+1]) {
                std::swap(list[i], list[i+1]);
                is_swapped = true;
            }
        }
        if(is_swapped == false) {
            break;
        }
    }

} 




int main() {
    int size;
    std::cin >> size;
    std::vector<int> input = make_vector(size);
    auto start = std::chrono::high_resolution_clock::now();
    bubble_sort(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Execution time: " << duration << " ms\n";
    is_sorted(input);
    return 0;
}
