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

#endif