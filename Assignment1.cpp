#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <climits>
#include <tuple>

std::vector<std::pair<int, int>> make_random_vector(int size) { //generate vector of random size
    std::vector<std::pair<int, int>> input_list(size);
    for (int i = 0; i < size; i++) {
        int value = rand() % 1000001;
        input_list[i] = {value, i};  
    }
    return input_list;
}

std::vector<std::pair<int, int>> make_ordered_vector(int size) { //generate ordered vector
    int i = 1;
    std::vector<std::pair<int, int>> input_list(size);
    for (int i = 0; i < size; i++) {
        int value = rand() % 1000001;
        input_list[i] = {value, 0};  
    }
    return input_list;
}

void bubble_sort(std::vector<std::pair<int, int>>& list) { 
    bool is_swapped = false;
    for(int times = 0; times < list.size()-1; times++) {
        for(int i = 0; i < list.size() - 1; i++) {
            if(list[i].first > list[i+1].first) {
                std::swap(list[i], list[i+1]);
                is_swapped = true;
            }
        }
        if(is_swapped == false) {
            break;
        }
    }
} 

void selection_sort(std::vector<std::pair<int, int>>& list) {
    for (int start = 0; start < list.size() - 1; start++) {
        int min_index = start;
        for (int i = start + 1; i < list.size(); i++) {
            if (list[i].first < list[min_index].first) {
                min_index = i;
            }
        }
        if (min_index != start) {
            std::swap(list[start], list[min_index]);
        }
    }
}

void insertion_sort(std::vector<std::pair<int, int>>&  list) {
    for (int key = 1; key < list.size(); key++) {
        int i = key - 1;
        std::pair<int, int> value = list[key];

        while(i >= 0 && list[i].first > value.first) {
            list[i + 1] = list[i];
            i--;
        }
        list[i + 1] = value; 
    }
}

std::vector<std::pair<int, int>> merge(std::vector<std::pair<int, int>> left, std::vector<std::pair<int, int>> right) {
    int i = 0, j = 0;
    std::vector<std::pair<int, int>> merged_vector;

    while(i < left.size() && j < right.size()) {
        if (left[i].first < right[j].first || (left[i].first == right[j].first && left[i].second < right[j].second)) {
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

void merge_sort(std::vector<std::pair<int, int>>& list) {
    std::vector<std::pair<int, int>> left;
    std::vector<std::pair<int, int>> right;

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
    std::vector<std::pair<int, int>> merged_vector = merge(left, right);
    list = merged_vector;
}

std::tuple<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> quick_partition(std::vector<std::pair<int, int>> list) {
    std::vector<std::pair<int, int>> small;
    std::vector<std::pair<int, int>> big;
    std::vector<std::pair<int, int>> equal;
    int pivot = list[rand() % list.size()].first;

    for(std::pair<int, int>& x : list) {
        if (x.first < pivot) {
            small.push_back(x);
        }
        else if (x.first > pivot) {
            big.push_back(x);
        }
        else {
            equal.push_back(x);
        }
    }
    return std::make_tuple(small, equal, big);
}

void quick_sort(std::vector<std::pair<int, int>>& list) {
    if (list.size() <= 1) {
        return;
    }
    std::vector<std::pair<int, int>> small, equal, big;
    std::tie(small, equal, big) = quick_partition(list);
    quick_sort(small);
    quick_sort(big);
    list.clear();

    for (std::pair<int, int>& x: small) {
        list.push_back(x);
    }

    for (std::pair<int, int>& x: equal) {
        list.push_back(x);
    }

    for (std::pair<int, int>& x: big) {
        list.push_back(x);
    }
}

void heapify(std::vector<std::pair<int, int>>& list, int i, int size) {
    int max_index = i;
    if (2 * i + 1 < size && list[max_index].first < list[2 * i + 1].first) {
        max_index = 2 * i + 1;
    }
    if (2 * i + 2  < size && list[max_index].first < list[2 * i + 2].first) {
        max_index = 2 * i + 2;
    }

    if(i != max_index) {
        std::swap(list[i], list[max_index]);
        heapify(list, max_index, size);
    }
}

void build_max_heap(std::vector<std::pair<int, int>>& list, int size) {
    for(int i = (size / 2) - 1 ; i >= 0; i--) {
        heapify(list, i, size);
    }
}

void heap_sort(std::vector<std::pair<int, int>>& list) {
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

void remove_winner(std::vector<int>& tree) {
    int winner = tree[0];
    int start = (tree.size() + 1) / 2 - 1;
    int index = INT_MIN;

    for(int i = start; i < tree.size(); i++) {
        if(tree[i] == winner) {
            tree[i] = INT_MAX;
            index = i;
            break;
        }
    }

    if(index == INT_MIN) {
        return;
    }

    while (index > 0) {
        int parent = (index - 1) / 2;
        tree[parent] = std::min(tree[2 * parent + 1], tree[2 * parent + 2]);
        index = parent;
    }
} 

std::vector<int> tournament_sort(std::vector<int>& list) {
    std::vector<int> tree = build_tree(list);
    std::vector<int> result;

    for (int i = 0; i < list.size(); i++) {
        result.push_back(tree[0]);     
        remove_winner(tree);          
    }

    return result;
}

void tim_insertion_sort(std::vector<int>& list, int start, int end) {
    for (int i = start + 1; i < end; i++) {
        int key = list[i];
        int j = i - 1;
        while (j >= start && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

std::vector<std::pair<int, int>> extract_runs(const std::vector<int>& arr, int minrun) {
    std::vector<std::pair<int, int>> runs;
    int i = 0;
    while (i < arr.size()) {
        int start = i;
        int end = i + 1;

        if (end < arr.size() && arr[end] < arr[start]) {
            while (end < arr.size() && arr[end] < arr[end - 1]) {
                end++;
            }

        } 
        
        else {
            // 오름차순 run
            while (end < arr.size() && arr[end] >= arr[end - 1]) {
                end++;
            }
        }

        int run_len = end - start;

        // run이 MINRUN보다 짧으면 늘리기 (삽입 정렬 대상)
        if (run_len < minrun) {
            int new_end = std::min(start + minrun, (int)arr.size());
            // 삽입 정렬: insertion_sort(arr, start, new_end);
            end = new_end;
        }

        // run 기록
        runs.push_back({start, end});

        // 다음 run 시작 지점
        i = end;
    }

    return runs;
}


bool is_sorted(std::vector<std::pair<int, int>>& list) {
    for(int i = 0; i < list.size() - 1; i++) {
        if (list[i].first > list[i+1].first) {
            std::cout << "error" << std::endl;
            return false;
        }
    }
    std::cout << "sorted!" << std::endl;
    return true;
}

bool is_stable(std::vector<std::pair<int, int>>& list) {
    for(int i = 0; i < list.size() - 1; i++) {
        if(list[i].first == list[i+1].first) {
            if (list[i].second > list[i+1].second) {
                std::cout << "not stable" << std::endl;
                return false;
            }
        }
    }
    std::cout << "stable" << std::endl;
    return true;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<std::pair<int, int>> input = make_random_vector(size);

    auto start = std::chrono::high_resolution_clock::now();
    heap_sort(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Execution time: " << duration << " ms\n";
    is_sorted(input);
    is_stable(input);

    return 0;
}
