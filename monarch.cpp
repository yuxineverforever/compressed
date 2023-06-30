#include <chrono>
#include "Bigraph.h"

int main(){
    BiGraph b;
    b.loadFromFile("in.in");

    auto begin = std::chrono::high_resolution_clock::now();

    std::cout << b.monarch() << std::endl;

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Time of monarch: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count() << " secs." << std::endl;

    begin = std::chrono::high_resolution_clock::now();

    std::cout << b.BFC_IBS() << std::endl;

    end = std::chrono::high_resolution_clock::now();

    std::cout << "Time of BFC_IBS: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count() << " secs." << std::endl;

    return 0;
}