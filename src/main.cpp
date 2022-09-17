#include <iostream>
#include <vector>

#include "./include/utils.h"
#include "./include/genetic.h"


int main()
{
    std::vector<string> population;
    
    for (int i = 0; i < INITIAL_POPULATION; ++i)
    {
        population.push_back(get_individual('A'));
        //std::cout << population[i] << std::endl;
    }
    
    cout << "Size: " << population.size() << '\n';
    
    std::string a = "ABGEFHCDA";
    std::string b = "ADHBCGEFA";

    crossover(a,b);


    std::cout << get_fitness_value(b);

    return 0;
}