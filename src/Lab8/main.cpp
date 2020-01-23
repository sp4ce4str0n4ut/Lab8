#include <cstdlib>
#include <vector>
#include "Sort.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;



int main() {
    std::vector<long> yGraphicMultiThreading, yGraphicConsistent, xGraphics;

    for (int sz = 10; sz < 1000000; sz *= 10) {

        std::vector<int> vector(sz);

        for (int i = 0; i < sz; i++) {
            vector[i] = rand();
        }

        xGraphics.push_back(sz);
		
        yGraphicMultiThreading.push_back(sort_threads(vector));
		
        yGraphicConsistent.push_back(sort_consistent(vector));
    }

    plt::named_plot("multiple threads", xGraphics, yGraphicMultiThreading);
    plt::named_plot("consistent", xGraphics, yGraphicConsistent );
	
    plt::xlabel("vector elements");
    plt::ylabel("time, ms");
	
    plt::legend();
    plt::show();

    return 0;
}
