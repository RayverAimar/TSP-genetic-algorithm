#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <iostream>
#include <string>
#include <unordered_set>

#include <stdlib.h>
#include <time.h>

using std::cout;
using std::string;
using std::unordered_set;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void fast_random(unordered_set<char> &r, char beg)
{
    int random_idx;
    while (r.size() != 25)
    {
        random_idx = rand() % 26;
        if (alphabet[random_idx] != beg)
            r.insert(alphabet[random_idx]);
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
        if ((alphabet[random_idx] != beg) &&
            (individual.find(alphabet[random_idx]) == string::npos))
            individual.push_back(alphabet[random_idx]);
    }

    individual.push_back(beg);

    return individual;
}

void matching(std::string genomeA, std::string genomeB)
{
    srand ((unsigned) time(NULL));

    int random_number = rand() % MAX_RANDOM_VALUE;

    std::string matched_genomeA, matched_genomeB, missing_genomeA, missing_genomeB;

    int lsb = genomeA.size() - 2;

    matched_genomeA.push_back(genomeA[0]);
    matched_genomeB.push_back(genomeB[0]);

    std::cout << random_number << std::endl;

    for(int f = lsb, i = 1; i < genomeA.size() - 1; f--, i++){
        char to_push_genomeA = ' ', to_push_genomeB = ' ';
        int mask = 1 << f;
        if(mask & random_number){
            to_push_genomeA = genomeB[i];
            to_push_genomeB = genomeA[i];
        }
        else{
            missing_genomeA.push_back(genomeA[i]);
            missing_genomeB.push_back(genomeB[i]);
        }
        matched_genomeA.push_back(to_push_genomeA);
        matched_genomeB.push_back(to_push_genomeB);
    }

    matched_genomeA.push_back(genomeA[0]);
    matched_genomeB.push_back(genomeB[0]);

    std::cout<<matched_genomeA<<std::endl;
    std::cout<<matched_genomeB<<std::endl;

    std::cout<<missing_genomeA<<std::endl;
    std::cout<<missing_genomeB<<std::endl;

}

#endif //__GENETIC_H__
