//
// Created by Yuxin Tang on 6/30/23.
//
#include "hash.h"
uint64_t fasthash(uint64_t a, uint64_t b){
    return (a > b) ? ((a << 32) | b) : ((b << 32) | a);
}