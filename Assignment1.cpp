#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <climits>
#include <tuple>
#include <algorithm>

std::vector<int> make_random_vector(int size) { //generate vector of random size
    std::vector<int> input_list(size);
    for (int& x : input_list) {
        x = rand() % 10001;  // random number from 0~10^6
    }
    return input_list;
}

std::vector<int> make_ordered_vector(int size) { //generate ordered vector
    int i = 1;
    std::vector<int> input_list(size);
    for (int& x : input_list) {
        x = i;
        i++;
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

void bubble_sort(std::vector<int>& list) { 
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

void selection_sort(std::vector<int>& list) {
    int start = 0;
    while(start < list.size()) {
        int min_index = start;
        int min = INT_MAX;
        for(int i = start; i < list.size(); i++) {
            if (list[i] < min) {\
                min = list[i];      
                min_index = i;
            }
        }
        std::swap(list[start], list[min_index]);
        start++;
    }
}

void insertion_sort(std::vector<int>& list) {
    int key = 1;
    while(key < list.size()) {
        int i = key;
        while(i >= 1 && list[i] < list[i-1]) {
            std::swap(list[i], list[i-1]);
            i--;
        }
        key++;
    }
}

std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
    int i = 0, j = 0;
    std::vector<int> merged_vector;

    while(i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged_vector.push_back(left[i]);
            i++;
        }
        else {
            merged_vector.push_back(right[j]);
            j++;
        }
    }

    while(i < left.size()) {
        merged_vector.push_back(left[i]);
        i++;
    }

    while(j < right.size()) {
        merged_vector.push_back(right[j]);
        j++;
    }
    return merged_vector;
}

void merge_sort(std::vector<int>& list) {
    std::vector<int> left;
    std::vector<int> right;

    if (list.size() <= 1) {
        return;
    }

    for(int i = 0; i < list.size() ; i++) {
        if(i < list.size() / 2) {
            left.push_back(list[i]);
        }
        else {
            right.push_back(list[i]); 
        }
    }

    merge_sort(left);
    merge_sort(right);
    std::vector<int> merged_vector = merge(left, right);
    list = merged_vector;
}

std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> quick_partition(std::vector<int> list) {
    std::vector<int> small;
    std::vector<int> big;
    std::vector<int> equal;
    int pivot = list[rand() % list.size()];

    for(int& x : list) {
        if (x < pivot) {
            small.push_back(x);
        }
        else if (x > pivot) {
            big.push_back(x);
        }
        else {
            equal.push_back(x);
        }
    }
    return std::make_tuple(small, equal, big);
}

void quick_sort(std::vector<int>& list) {
    if (list.size() <= 1) {
        return;
    }
    std::vector<int> small, equal, big;
    std::tie(small, equal, big) = quick_partition(list);
    quick_sort(small);
    quick_sort(big);
    list.clear();

    for (int& x: small) {
        list.push_back(x);
    }

    for (int& x: equal) {
        list.push_back(x);
    }

    for (int& x: big) {
        list.push_back(x);
    }
}

void heapify(std::vector<int>& list, int i, int size) {
    int max_index = i;
    if (2 * i + 1 < size && list[max_index] < list[2 * i + 1]) {
        max_index = 2 * i + 1;
    }
    if (2 * i + 2  < size && list[max_index] < list[2 * i + 2]) {
        max_index = 2 * i + 2;
    }

    if(i != max_index) {
        std::swap(list[i], list[max_index]);
        heapify(list, max_index, size);
    }
}

void build_max_heap(std::vector<int>& list, int size) {
    for(int i = (size / 2) - 1 ; i >= 0; i--) {
        heapify(list, i, size);
    }
}

void heap_sort(std::vector<int>& list) {
    int size = list.size();
    build_max_heap(list, size);
    while (size > 1) {
        std::swap(list[0], list[size-1]);
        size --;
        heapify(list, 0, size);
    }
}



int main() {
    int size;
    std::cin >> size;
    std::vector<int> input = make_random_vector(size);
    auto start = std::chrono::high_resolution_clock::now();
    heap_sort(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Execution time: " << duration << " ms\n";
    is_sorted(input);
    return 0;
}
