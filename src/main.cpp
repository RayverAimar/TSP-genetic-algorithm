#include <iostream>
#include <vector>

#include "./include/utils.h"
#include "./include/genetic.h"


int main()
{
    std::vector<std::string> population, selected_genomes;
    
    population = get_initial_population();
    
    for(int i = 0; i < MAX_ITERATIONS; i++)
    {
        selected_genomes = population_selection(population);
        //Missing some elitism function
        population_crossover(selected_genomes);
        population_mutation(selected_genomes);
        population = refill_population(selected_genomes);
    }

    return 0;
}