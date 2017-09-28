# Basic templated genetic algorithm in C++ 

This project proposes a single header with 3 possible ways to call a genetic algorithm

## Available calls to genetic algorithm solver

### solveSingleRun(T &indiv, YAML::Node config)  

+ Runs 1 instance of genetic algorithm based on the T class and optional configuration. 

### solveMultiRun(T &indiv, int _runs = 0, YAML::Node config, bool display)  

+ Runs several GA's based on T class and optional configuration or display.

### solveMultiThread(T &indiv, int _runs, int _n_threads, YAML::Node config, bool display)  

+ Runs several GA's across several threads with optional configuration or display.

At the end of any of these functions, indiv is the best found solution.


## Yaml configuration

An example of YAML file configuration is shown in the tsp example. It consists in 4 variables:
- full_pop: size of the population considered in the GA.
- iter_max: the GA stops after this number of iterations.
- iter_out: the GA stops if the same individual is always the same during this number of iterations.
- keep_best: number of best individuals that will be automatically kept from one generation to another.

## Example and required interface 

The tsp project gives an example for the classical Traveling Salesman Problem.
A custom class describes an individual in TSP, that is a particular ordering of the cities. 

New problems can be instanciated as long as the individual class is defined with the following interface, assuming the class is called Indiv:
- 

