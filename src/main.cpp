#include <iostream>
#include <vector>

#include "./include/utils.h"
#include "./include/genetic.h"


int main()
{
    srand((unsigned int) time(NULL));

    std::vector<std::string> population, selected_genomes;
    std::pair<float, std::string> best_genome;

    population = get_initial_population();

    for(int i = 0; i < 1; i++)
    {
        selected_genomes = population_selection(population);
        best_genome = get_best_genome(selected_genomes);
        //Missing some elitism function
        population_crossover(selected_genomes);
        population_mutation(selected_genomes);
        population = refill_population(selected_genomes);
        std::cout << "Best path length " << best_genome.first << "\nBest genome: "<< best_genome.second;
        best_genome = get_best_genome(selected_genomes);
        std::cout << "\n-----------Crossover & mutation-----------\n";
        std::cout << "Best path length " << best_genome.first << "\nBest genome: "<< best_genome.second;
    }

    std::cout << std::endl;

    return 0;
}