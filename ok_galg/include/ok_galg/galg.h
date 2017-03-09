#ifndef GALG_H
#define GALG_H

#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <algorithm>
#include <ok_galg/indiv.h>
#include <yaml-cpp/yaml.h>

namespace ok_galg
{

// perform a single run with a random population
template<class T> T SolveSingleRun(const YAML::Node &config = YAML::Node(), const unsigned int &_t=0, const unsigned int &_run=0)
{
    // read config parameters
    int keep_best = 5;
    int iter_max = 100;
    int iter_out = 30;
    int full_population = 500;    

    if(!config.IsNull())
    {
        if(!config["keep_best"].IsNull())
            keep_best = config["keep_best"].as<double>();

        if(!config["iter_max"].IsNull())
            iter_max = config["iter_max"].as<double>();

        if(!config["iter_out"].IsNull())
            iter_out = config["iter_out"].as<double>();

        if(!config["full_pop"].IsNull())
            full_population = 2*((config["full_pop"].as<int>()+1)/2);;
    }
    const int half_population = full_population/2;

    // init first population from random individuals
    std::vector<T> population(full_population + half_population);

    std::nth_element(population.begin(), population.begin()+keep_best, population.begin()+full_population);
    T best;best.Copy(population[0]);

    // loop until exit conditions
    unsigned int i, iter=0,iter_follow=0;
    unsigned int n1,n2;
    std::string spaces = "";
    for(i=0;i<_t;++i)
        spaces += "              ";
    while(iter++ < iter_max && iter_follow< iter_out)   // max iteration and max iteration where the best is always the same
    {
        if(_t != 0)
            std::cout << spaces << _t << ":" << _run << ":" << iter << std::endl;

        // we keep the best individuals anyway
        for(i=0;i<keep_best;++i)
            population[full_population+i].Copy(population[i]);

        // selection, 1 vs 1 tournament to fill half of the population
        for(i=keep_best;i<half_population;++i)
        {
            n1 = rand_int(0,full_population);
            n2 = rand_int(0,full_population);
            while(n1 == n2)
                n2 = rand_int(0,full_population);
            if(population[n1].cost < population[n2].cost)
                population[full_population+i].Copy(population[n1]);
            else
                population[full_population+i].Copy(population[n2]);
        }

        // put new elements at front of new population
        for(i=0;i<half_population;++i)
            population[i].Copy(population[full_population+i]);

        // crossing and mutation to fill other half of the new pop
        for(i=half_population;i<full_population;++i)
        {
            n1 = rand_int(0,half_population);
            n2 = rand_int(0,half_population);
            while(n1 == n2)
                n2 = rand_int(0,half_population);
            //   std::cout << "  new " << i << " is crossing between " << n1 << " and " << n2 << std::endl;
            // cross between parents + compute cost
            population[i].CrossAndMutate(population[n1],population[n2]);
        }

        // update costs
        std::nth_element(population.begin(), population.begin()+keep_best, population.begin()+full_population);

        // check for best individual
        if(population[0] < best)
        {
            // found new best individual
            // reset counter
            iter_follow = 0;
            // update best
            best.Copy(population[0]);
        }
        else
            iter_follow += 1;   // always the same winner
    }
    return best;
}




// perform a given number of runs and returns the best one in _best
// not to be used directly
template<class T> void SolveMultiRun(const YAML::Node &config = YAML::Node(), const unsigned int &_thread_n = 0, unsigned int *_run = 0, const unsigned int &_runs = 0, T &_best = T(), bool display = false)
{
    T indiv;
    bool first = true;
    unsigned int run;
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100*_thread_n));

    while(*_run < _runs)
    {
        run = ++(*_run);

        std::cout << "Run #" << run << " in thread #" << _thread_n << std::endl;
        if(display)
            indiv.Copy(SolveSingleRun<T>(config, _thread_n, run));
        else
            indiv.Copy(SolveSingleRun<T>(config));
        if(first || indiv.cost < _best.cost)
        {
            _best.Copy(indiv);
            first = false;
        }
    }
}



// performs a given number of runs across a given number fo threads, returns the overall best result
template<class T> T SolveMultiThread(const YAML::Node &config = YAML::Node(), const unsigned int &_runs = 10, unsigned int _n_threads = 1, bool display = false)
{
    if(_n_threads > _runs)
        _n_threads = _runs;
    std::vector<std::thread> t;
    std::vector<T> bests(_n_threads);
    unsigned int run = 0;

    for(unsigned int i=0;i<_n_threads;++i)
            t.push_back(std::thread(SolveMultiRun<T>, config, i+1, &run, _runs, std::ref(bests[i]), display));

    for(unsigned int i=0;i<_n_threads;++i)
        t[i].join();

    // compare results and return best individual
    T best;
    best.Copy(bests[0]);
    for(auto &other: bests)
        if(other.cost < best.cost)
            best.Copy(other);
    return best;
}


}

#endif // GALG_H