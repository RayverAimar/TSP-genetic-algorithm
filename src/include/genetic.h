#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <string>
#include <stdlib.h>
#include <time.h>

#include "./utils.h"


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

