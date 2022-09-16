#include <iostream>
#include "./include/utils.h"
#include "./include/genetic.h"

FLOAT_MATRIX distances = get_distances_matrix();

int main(){
    std::string a = "ABECDA";
    std::string b = "ADBCEA";

    matching(a,b);
}