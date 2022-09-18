#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "./utils.h"

using std::cout;
using std::string;
using std::unordered_set;

FLOAT_MATRIX distances = get_distances_matrix();

void fast_random(unordered_set<char> &r, char beg)
{
    int random_idx;
    while (r.size() != 25)
    {
        random_idx = rand() % 26;
        if (get_node_name(random_idx) != beg)
            r.insert(get_node_name(random_idx));
    }
}

string get_individual(char beg)
{
    string individual;

    int random_idx;

    individual.push_back(beg);

    while (individual.size() != 26)
    {
        random_idx = rand() % 26;
        if ((get_node_name(random_idx) != beg) &&
            (individual.find(get_node_name(random_idx)) == string::npos))
            individual.push_back(get_node_name(random_idx));
    }

    individual.push_back(beg);

    return individual;
}

std::vector<std::string> get_initial_population()
{
    std::vector<std::string> population;
    
    for (int i = 0; i < INITIAL_POPULATION; ++i)
    {
        population.push_back(get_individual('A'));
    }

    return population;
}

std::vector<std::string> refill_population(const std::vector<std::string> &selected_genomes)
{
    std::vector<std::string> full_population;

    for(int i = 0; i < selected_genomes.size(); i++){
        full_population.push_back(get_individual('A'));
        full_population.push_back(selected_genomes[i]);
    }

    return full_population;
}


void insert_missing_cromosomes(std::string &matched_genomeA, const std::string &missing_genomeA){
    int cur_id = 0;

    for(int i = 0;  i < matched_genomeA.size(); i++)
    {
        if(matched_genomeA[i] == ' ')
        {
            matched_genomeA[i] = missing_genomeA[cur_id];
            cur_id++;
        }
    }
}

void crossover(std::string &genomeA, std::string &genomeB) //Missing full implementation
{
    int lsb;
    std::string matched_genomeA, matched_genomeB, missing_genomeA, missing_genomeB;

    int random_number = rand() % MAX_RANDOM_VALUE;
    lsb = genomeA.size() - 2;

    matched_genomeA.push_back(genomeA[0]);
    matched_genomeB.push_back(genomeB[0]);

    std::cout << "Random number chosen: " << random_number << std::endl;

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
            missing_genomeB.push_back(genomeA[i]);
            missing_genomeA.push_back(genomeB[i]);
        }
        matched_genomeA.push_back(to_push_genomeA);
        matched_genomeB.push_back(to_push_genomeB);
    }

    matched_genomeA.push_back(genomeA[0]);
    matched_genomeB.push_back(genomeB[0]);

    insert_missing_cromosomes(matched_genomeA, missing_genomeA);
    insert_missing_cromosomes(matched_genomeB, missing_genomeB);

    std::cout << "matched_genomeA: " << matched_genomeA << std::endl;
    std::cout << "matched_genomeB: " << matched_genomeB << std::endl;
    
    genomeA = matched_genomeA;
    genomeB = matched_genomeB;

}

float get_fitness_value(const std::string &genome)
{
    float total_distance = 0;
    for(int i = 0; i < genome.size() - 1; i++){
        int from, to;
        from = get_node_id(genome[i]);
        to = get_node_id(genome[i + 1]);
        total_distance = distances[from][to];
    }
    return total_distance;
}

void generate_two_random_numbers(int &first_number, int &second_number, int lower_value, int upper_value){
    first_number = (rand() % upper_value) + lower_value;
    do{
        second_number = (rand() % upper_value) + lower_value;
    }while(second_number == first_number);
}

void swap_characters(string &genomeA, int first_idx, int second_idx)
{
    char temp = genomeA[first_idx];
    genomeA[first_idx] = genomeA[second_idx];
    genomeA[second_idx] = temp;
}

std::vector<std::string> population_selection(const std::vector<std::string> &population)
{
    
    std::vector<std::string> selected_genomes;
    
    for(int i = 0; i < population.size(); i+=2)
    {
        float value_first_genome, value_second_genome;
        value_first_genome = get_fitness_value(population[i]);
        value_second_genome = get_fitness_value(population[i + 1]);
        
        string selected_genome = population[i];
        
        if(value_first_genome < value_second_genome)
            selected_genome = population[i + 1];
        
        selected_genomes.push_back(selected_genome);
    }

    return selected_genomes;

}

void population_crossover(std::vector<std::string>& selected_genomes)
{
    for(int i = 0; i < selected_genomes.size(); i+=2)
    {
        crossover(selected_genomes[i], selected_genomes[i + 1]);
    }
    
}

void population_mutation(std::vector<std::string>& selected_genomes){
    //According to a mutation rate

    for(int i = 0; i < selected_genomes.size(); i++)
    {
        
        bool mutation = (rand() % 100) < (100 * MUTATION_RATE);

        if(!mutation) continue;

        int first_random_idx, second_random_idx;

        generate_two_random_numbers(first_random_idx, second_random_idx, 1, N_NODES - 2);

        swap_characters(selected_genomes[i], first_random_idx, second_random_idx);
    }

}




#endif //__GENETIC_H__
