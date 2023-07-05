#include <chrono>
#include "Bigraph.h"
#include "countingAlgorithm.h"

int main(){
    BiGraph b;
    b.loadFromFile("in.in");

    // begin to count butterflies.

    auto begin = std::chrono::high_resolution_clock::now();

    std::cout << ButterflyCounting::monarch(b) << std::endl;

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Time of monarch: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count() << " secs.\n\n\n";


    begin = std::chrono::high_resolution_clock::now();

    std::cout << ButterflyCounting::BFC_IBS(b) << std::endl;

    end = std::chrono::high_resolution_clock::now();

    std::cout << "Time of BFC_IBS: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count() << " secs.\n\n\n";

    begin = std::chrono::high_resolution_clock::now();

    std::cout << ButterflyCounting::BFC_VPS(b) << std::endl;

    end = std::chrono::high_resolution_clock::now();

    std::cout << "Time of BFC_VPS: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count() << " secs.\n\n\n";

    return 0;
}