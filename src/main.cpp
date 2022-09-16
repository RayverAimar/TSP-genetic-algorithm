#include <iostream>
#include <vector>

#include "./include/utils.h"
#include "./include/genetic.h"

int main()
{
    std::vector<string> population;
    
    for (int i = 0; i < INITIAL_POPULATION; ++i)
        population.push_back(get_individual('A'));
    
    cout << "Size: " << population.size() << '\n';
    
    std::string a = "ABECDA";
    std::string b = "ADBCEA";

    matching(a,b);
    return 0;
}