#include <gtest/gtest.h>
#include "Lab8/MSort.h"

#include <vector>


TEST(MERGE_SORT_THREAD, NORMAL_VECTOR) {
	
    std::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::vector<int> vec2{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    merge_sort(vec1.begin(), vec1.end());
	sort_threads(vec2.begin(), vec2.end());

	
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(vec1[i], vec2[i]);
	
}

TEST(MERGE_SORT_THREAD, ONE_ELEMENT_VECTOR) {
	
    std::vector<int> vec{0};
    sort_threads(vec.begin(), vec.end());
    EXPECT_EQ(vec[0], 0);
	
}