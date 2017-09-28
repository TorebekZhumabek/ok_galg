#include <iostream>
#include <ok_galg/galg.h>
#include <travel.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include <chrono>

using namespace std;
using namespace ok_galg;

void printSummary(std::chrono::time_point<std::chrono::system_clock> start,
                  Travel t,
                  std::string legend)
{
    std::chrono::duration<double> elapsed_seconds =
            std::chrono::system_clock::now()-start;
    cout << legend << " in " << elapsed_seconds.count() << " s" << std::endl;
    t.print();
    cout << endl;
}

int main(int argc, char ** argv)
{
    std::srand(std::time(0));


    // load configuration for genetic algorithm
    YAML::Node config = YAML::LoadFile("../config.yaml");

    // load travel cost from YAML

    std::string path = "../tsp.yaml";
    if(argc > 1)
        path = std::string(argv[1]);
    YAML::Node data = YAML::LoadFile(path);
    YAML::Node cities = data["cities"];
    const unsigned int N = cities.size();
    std::vector<std::vector<double> > nodes(N);
    for(unsigned int i=0;i<N;++i)
    {
        nodes[i].resize(N);
        for(unsigned int j=0;j<N;++j)
            nodes[i][j] = data[i][j].as<double>();
    }

    Travel t(nodes, true);    

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    // single-run solver
    ok_galg::solveSingleRun(t, config);
    printSummary(start, t, "Single run solution");


    // 50 runs without threading
    start = std::chrono::system_clock::now();
    ok_galg::solveMultiRun(t, 100, config, false);
    printSummary(start, t, "Multi run solution");

    // 200 runs in 4 threads
    start = std::chrono::system_clock::now();
    ok_galg::solveMultiThread(t, 200, 4, config, false);
    printSummary(start, t, "Multi run x multi thread solution");

    // detail solution
    cout << "Detailed solution" << endl;
    for(unsigned int i=0;i<t.ordering_.size();++i)
        cout << cities[t.ordering_[i]].as<string>() << " -> ";
    cout << cities[t.ordering_[0]].as<string>() << endl;
    cout << endl;

    t.randomize();
    cout << "Random solution" << endl;
    t.print();
    for(unsigned int i=0;i<t.ordering_.size();++i)
        cout << cities[t.ordering_[i]].as<string>() << " -> ";
    cout << cities[t.ordering_[0]].as<string>() << endl;
    cout << endl;

    YAML::Node solution = data["solution"];
    if(!solution.IsNull() && argc > 1)
        cout << "Best known solution: " << solution << endl;
}
