# Basic templated genetic algorithm in C++ 

# Available calls to genetic algorithm solver

The ok_galg project just consists in 1 header file, which is the genetic algorithm with 3 templated functions

1. solveSingleRun(T &indiv, YAML::Node config)  

Runs 1 genetic algorithm based on the T class and optional configuration. 

1. solveMultiRun(T &indiv, int _runs = 0, YAML::Node config, bool display)  

Runs <_runs> GA based on T class and optional configuration or display.

1. solveMultiThread(T &indiv, int _runs, int _n_threads, YAML::Node config, bool display)  

Runs several GA's across several threads with optional configuration or display.

At the end of any of these functions, indiv is the best found solution.



The tsp project gives an example for the classical TSP problem.
