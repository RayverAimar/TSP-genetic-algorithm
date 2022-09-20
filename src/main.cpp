#include "./include/genetic.h"

int main()
{
    srand((unsigned int) time(NULL));

    POPULATION population, selected_genomes;
    std::pair<float, GENOME> best_genome_last_generation, best_genome_cur_generation;
    FLOAT_VECTOR means, best_fitness_values;
    float mean_fitness_value = 0.0f;

    population = get_initial_population();
    best_genome_last_generation = get_best_genome(population);
    std::cout << "[Before] Best path length " << best_genome_last_generation.first << "\n[Before] Best genome: "<< best_genome_last_generation.second << std::endl;

    for(int i = 0; i < MAX_ITERATIONS; i++)
    {
        selected_genomes = population_selection(population, mean_fitness_value);
        means.push_back(mean_fitness_value);
        best_fitness_values.push_back(best_genome_last_generation.first);
        population_crossover(selected_genomes);
        population_mutation(selected_genomes);
        best_genome_cur_generation = get_best_genome(selected_genomes);
        elitism_handler(best_genome_last_generation, best_genome_cur_generation, selected_genomes);     
        population = refill_population(selected_genomes);
    }
    
    std::cout << "[After] Best path length " << best_genome_cur_generation.first << "\n[After] Best genome: "<< best_genome_cur_generation.second << std::endl;
    std::cout << "[Delta] Means: " << means[0] << " -> " << means[means.size() - 1] << std::endl;
    std::cout << "[Delta] Best Fitness Value: " << best_fitness_values[0] << " -> " << best_fitness_values[best_fitness_values.size() - 1] << std::endl;

    export_float_vector(means, "means");
    export_float_vector(best_fitness_values, "best_fitness_values");

    return 0;
}