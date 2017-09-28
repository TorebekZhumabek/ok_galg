# Basic templated genetic algorithm in C++ 

This project proposes a single header with 3 possible ways to call a genetic algorithm

## Available calls to genetic algorithm solver

### solveSingleRun(T &indiv, YAML::Node config)  

Runs 1 instance of genetic algorithm based on the T class and optional configuration. 

### solveMultiRun(T &indiv, int _runs = 0, YAML::Node config, bool display)  

Runs several GA's based on T class and optional configuration or display.

### solveMultiThread(T &indiv, int _runs, int _n_threads, YAML::Node config, bool display)  

Runs several GA's across several threads with optional configuration or display.

At the end of any of these functions, indiv is the best found solution.



The tsp project gives an example for the classical TSP problem.
