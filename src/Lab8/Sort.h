#include <iterator>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <algorithm>



using namespace std::chrono;
auto THREAD_MAX = std::thread::hardware_concurrency();
std::mutex mutex;
std::vector<std::thread> threads{THREAD_MAX};



template<typename T>
void sort_threads(T first, T last) {
    int sz = last - first;


    if (first == last || sz == 1) {
        return;
    }

    T middle = std::next(first, sz/2);

    unsigned int j = THREAD_MAX;
    unsigned int i = THREAD_MAX;

    if (sz >= 100) {
        std::lock_guard<std::mutex> locked(mutex);
        i = 0;

        while (i < THREAD_MAX) {
            if (!threads[i].joinable()) {
                threads[i] = std::thread{sort_threads<T>, first, middle};
                break;
            }
            i++;
        }

        j = 0;
        while (j < THREAD_MAX) {
            if (!threads[j].joinable()) {
                threads[j] = std::thread{sort_threads<T>, middle, last};
                break;
            }
            j++;
        }
    }

    (i == THREAD_MAX) ? sort_threads(first, middle) : threads[i].join();
    (j == THREAD_MAX) ? sort_threads(middle, last) : threads[j].join();
    std::inplace_merge(first, middle, last);
}



template<class Iterator>
void merge_sort(Iterator first, Iterator last) {
    if (last - first > 1) {
        Iterator middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}

long sort_threads(std::vector<int> &vec) {
    auto start = system_clock::now();
    sort_threads(vec.begin(), vec.end());
    auto end = system_clock::now();
    milliseconds elapsed = duration_cast<milliseconds>(end - start);
    return elapsed.count();
}


long sort_consistent(std::vector<int> &vec) {
    auto start = system_clock::now();
    merge_sort(vec.begin(), vec.end());
    auto end = system_clock::now();
    milliseconds elapsed = duration_cast<milliseconds>(end - start);
    return elapsed.count();
}
