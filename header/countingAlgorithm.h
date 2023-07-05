//
// Created by Yuxin Tang on 7/3/23.
//

#ifndef BUTTERFLY_COUNTING_COUNTINGALGORITHM_H
#define BUTTERFLY_COUNTING_COUNTINGALGORITHM_H

#include <cstdint>
#include "Bigraph.h"

class ButterflyCounting{
public:
    static uint64_t monarch(const BiGraph& b);

    static uint64_t BFC_IBS(BiGraph& b);

    static uint16_t BFC_VPS(BiGraph& b);

    static uint16_t ParButterfly(const BiGraph& b);

};



#endif //BUTTERFLY_COUNTING_COUNTINGALGORITHM_H
