#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <climits>
#include <tuple>

std::vector<int> make_random_vector(int size) { //generate vector of random size
    std::vector<int> input_list(size);
    for (int& x : input_list) {
        x = rand() % 1000001;  // random number from 0~10^6
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
            if (list[i] < min) {
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

/* pseudocode of cocktail_shaker_sort

    to be filled
*/
void cocktail_shaker_sort(std::vector<int>& list) { 
    bool is_swapped = true;
    int start = 0;
    int end = list.size() - 1;
    int times = 1;
    while(is_swapped == true) {
        is_swapped = false;
        if(times % 2 == 1) {
            for(int i = start; i < end; i++) {
                if (list[i] > list[i+1]) {
                    std::swap(list[i], list[i+1]);
                    is_swapped = true;
                }
            }
            times++;
            end--;
        }
        else {
            for(int i = end; i > start; i--) {
                if(list[i] < list[i-1]) {
                    std::swap(list[i], list[i-1]);
                    is_swapped = true;
                }
            }
            times++;
            start++;
        }    
    }
} 


/*pseudocode of comb_sort

to be filled


*/
void comb_sort(std::vector<int>& list) {
    int gap = list.size();
    double shrink_factor = 1.3;
    bool is_swapped = true;

    while(gap > 1 || is_swapped == true) {
        is_swapped = false;
        for(int i = 0; i + gap < list.size(); i += gap) {
            if(list[i] > list[i + gap]) {
                std::swap(list[i], list[i + gap]);
                is_swapped = true;
            }
        }
        gap = gap / shrink_factor;
        if(gap < 1) {
            gap = 1;
        }
    }
}

int find_insert_position(const std::vector<int>& big_list, int value) {
    int low = 0;
    int high = big_list.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int actual_mid = mid;

        if (big_list[mid] == INT_MIN) {
            int left = mid - 1;
            int right = mid + 1;
            bool found = false;

            while (left >= low || right <= high) {
                if (left >= low && big_list[left] != INT_MIN) {
                    actual_mid = left;
                    found = true;
                    break;
                }
                if (right <= high && big_list[right] != INT_MIN) {
                    actual_mid = right;
                    found = true;
                    break;
                }
                left--;
                right++;
            }

            if (found == false) {
                break; 
            }
        }

        if (value < big_list[actual_mid]) {
            high = actual_mid - 1;
        } else {
            low = actual_mid + 1;
        }
    }
    return low;
}

std::pair<std::string, int> find_nearest_empty(const std::vector<int>& big_list, int insert_idx) {
    int left = insert_idx - 1;
    int right = insert_idx + 1;

    while (left >= 0 || right < big_list.size()) {
        if (right < big_list.size() && big_list[right] == INT_MIN){
            return std::make_pair("right", right);

        }

        if (left >= 0 && big_list[left] == INT_MIN) {
            return std::make_pair("left", left);
        }

        left--;
        right++;
    }
    return std::make_pair("none", -1);
}


std::vector<int> library_sort(std::vector<int>& list) {
    double space_factor = 2.0;
    std::vector<int> big_list((int)(space_factor * list.size()), INT_MIN);
    int insert_index = find_insert_position(big_list, list[0]);
    big_list[insert_index] = list[0];

    for (int i = 1; i < list.size(); i++) {
        int index = find_insert_position(big_list, list[i]);
        if (big_list[index] == INT_MIN) {
            big_list[index] = list[i];
        }
        else {
            std::pair<std::string, int> result = find_nearest_empty(big_list, index);
            std::string direction = result.first;
            int empty_idx = result.second;

            if (result.first == "none") {
                std::cerr << "Failed to insert element: no space left\n";
                continue;
            }

            if (direction == "right") {
                for (int j = empty_idx; j > index; j--) {
                    big_list[j] = big_list[j - 1];
                }
                big_list[index] = list[i];
            }

            else if (direction == "left") {
                for(int j = empty_idx; j < index; j++) {
                    big_list[j] = big_list[j + 1];
                }
                big_list[empty_idx] = list[i];
            }
        }
    }

    std::vector<int> result;
    for (int x : big_list) {
        if (x != INT_MIN) {
            result.push_back(x);
        }
    }
    return result;
}

std::vector<int> build_tree(std::vector<int>& list) {
    std::vector<int> tree(2 * list.size() - 1);
    for (int i = 0; i < list.size(); i++) {
        tree[list.size() - 1 + i] = list[i];   
    }

    for (int i = list.size() - 2; i >= 0; i--) {
        tree[i] = std::min(tree[2 * i + 1], tree[2 * i + 2]);
    }
    return tree;
} 

std::vector<int> tournament_sort(std::vector<int>& list) {
    std::vector<int> tree = build_tree(list);
}
int main() {
    int size;
    std::cin >> size;
    std::vector<int> input = make_random_vector(size);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = library_sort(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Execution time: " << duration << " ms\n";
    is_sorted(result);

    return 0;
}
