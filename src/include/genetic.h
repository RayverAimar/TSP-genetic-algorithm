#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include <utility>
#include <algorithm>

#include "./utils.h"

FLOAT_MATRIX distances = get_distances_matrix();

void fast_random(std::unordered_set<char> &r, char beg)
{
    int random_idx;
    while (r.size() != 25)
    {
        random_idx = rand() % 26;
        if (get_node_name(random_idx) != beg)
            r.insert(get_node_name(random_idx));
    }
}

GENOME get_individual(char beg)
{
    GENOME individual;

    int random_idx;

    individual.push_back(beg);

    while (individual.size() != 26)
    {
        random_idx = rand() % 26;
        if ((get_node_name(random_idx) != beg) &&
            (individual.find(get_node_name(random_idx)) == GENOME::npos))
            individual.push_back(get_node_name(random_idx));
    }

    individual.push_back(beg);

    return individual;
}

POPULATION get_initial_population()
{
    POPULATION population;
    
    for (int i = 0; i < INITIAL_POPULATION; ++i)
    {
        population.push_back(get_individual('A'));
    }

    return population;
}

POPULATION refill_population(const POPULATION &selected_genomes)
{
    POPULATION full_population;

    for(int i = 0; i < selected_genomes.size(); i++){
        full_population.push_back(get_individual('A'));
        full_population.push_back(selected_genomes[i]);
    }

    return full_population;
}


void insert_missing_cromosomes(GENOME &genome, GENOME &matched_genome, std::vector<bool> &missing){

    for(int i = 0;  i < matched_genome.size(); i++)
    {
        if(matched_genome[i] == ' ')
        {
            for(int j = 0; j < genome.size(); j++)
            {
                if (missing[get_node_id(genome[j])])
                {
                    matched_genome[i] = genome[j];
                    missing[get_node_id(genome[j])] = false;
                    break;
                }
            }
        }
    }
}

void crossover(GENOME &genomeA, GENOME &genomeB)
{
    int lsb;
    GENOME matched_genomeA, matched_genomeB;
    std::vector<bool> missing_cromosomes_A(N_NODES, 0);
    std::vector<bool> missing_cromosomes_B(N_NODES, 0);

    int random_number = rand() % MAX_RANDOM_VALUE;
    lsb = genomeA.size() - 2;

    matched_genomeA.push_back(genomeA[0]);
    matched_genomeB.push_back(genomeB[0]);

    for(int f = lsb, i = 1; i < genomeA.size() - 1; f--, i++)
    {
        char to_push_genomeA = ' ', to_push_genomeB = ' ';
        int mask = 1 << f;
        if(mask & random_number)
        {
            to_push_genomeA = genomeB[i];
            to_push_genomeB = genomeA[i];
        }
        else
        {
            missing_cromosomes_A[get_node_id(genomeB[i])] = true;
            missing_cromosomes_B[get_node_id(genomeA[i])] = true;
        }
        matched_genomeA.push_back(to_push_genomeA);
        matched_genomeB.push_back(to_push_genomeB);
    }

    matched_genomeA.push_back(genomeA[0]);
    matched_genomeB.push_back(genomeB[0]);

    insert_missing_cromosomes(genomeA, matched_genomeA, missing_cromosomes_A);
    insert_missing_cromosomes(genomeB, matched_genomeB, missing_cromosomes_B);

    genomeA = matched_genomeA;
    genomeB = matched_genomeB;
}

float get_fitness_value(const GENOME &genome)
{
    float total_distance = 0;
    for(int i = 0; i < genome.size() - 1; i++){
        int from, to;
        from = get_node_id(genome[i]);
        to = get_node_id(genome[i + 1]);
        total_distance += distances[from][to];
    }
    return total_distance;
}

void generate_two_random_numbers(int &first_number, int &second_number, int lower_value, int upper_value){
    first_number = (rand() % upper_value) + lower_value;
    do{
        second_number = (rand() % upper_value) + lower_value;
    }while(second_number == first_number);
}

void swap_characters(GENOME &genomeA, int first_idx, int second_idx)
{
    char temp = genomeA[first_idx];
    genomeA[first_idx] = genomeA[second_idx];
    genomeA[second_idx] = temp;
}

POPULATION population_selection(const POPULATION &population, float &mean_fitness_value)
{
    mean_fitness_value = 0.0f;
    POPULATION selected_genomes;
    for(int i = 0; i < population.size(); i+=2)
    {
        float value_first_genome, value_second_genome;
        value_first_genome = get_fitness_value(population[i]);
        value_second_genome = get_fitness_value(population[i + 1]);
        mean_fitness_value += value_first_genome;
        mean_fitness_value += value_second_genome;
        GENOME selected_genome = population[i];
        if(value_first_genome > value_second_genome)
            selected_genome = population[i + 1];
        selected_genomes.push_back(selected_genome);
    }

    mean_fitness_value /= population.size();

    return selected_genomes;

}

void population_crossover(POPULATION& selected_genomes)
{
    for(int i = 0; i < selected_genomes.size(); i+=2)
    {
        crossover(selected_genomes[i], selected_genomes[i + 1]);
    }
}

void population_mutation(POPULATION& selected_genomes){

    for(int i = 0; i < selected_genomes.size(); i++)
    { 
        int random_number = (rand() % 100);
        bool mutation = random_number < (100 * MUTATION_RATE);
        if(!mutation) continue;
        int first_random_idx, second_random_idx;
        generate_two_random_numbers(first_random_idx, second_random_idx, 1, N_NODES - 1);
        swap_characters(selected_genomes[i], first_random_idx, second_random_idx);
    }
    
}

ELITE_VECTOR get_best_genomes(const POPULATION &selected_genomes)
{
    ELITE_VECTOR elite;
    float cur_genome_fitness_value;

    for(int i = 0; i < selected_genomes.size(); i++)
    {
        cur_genome_fitness_value = get_fitness_value(selected_genomes[i]);
        elite.push_back(std::make_pair(cur_genome_fitness_value, selected_genomes[i]));
    }

    std::sort(elite.begin(), elite.end());
    
    return ELITE_VECTOR (elite.begin(), elite.begin() + MAX_ELITISM);
}

void elitism_handler(   ELITE_VECTOR& best_genome_last_generation,
                        ELITE_VECTOR& best_genome_cur_generation,
                        POPULATION& selected_genomes
                    )
{
    ELITE_VECTOR all_elite(best_genome_last_generation);
    all_elite.insert(all_elite.end(), best_genome_cur_generation.begin(), best_genome_cur_generation.end());

    std::sort(all_elite.begin(), all_elite.end());

    best_genome_last_generation.clear();

    best_genome_last_generation.insert(best_genome_last_generation.begin(), all_elite.begin(), all_elite.begin() + MAX_ELITISM);

    for (int i = 0, j = 0; i < MAX_ELITISM; ++i, ++j)
        selected_genomes[j] = best_genome_last_generation[i].second;
}

#endif //__GENETIC_H__