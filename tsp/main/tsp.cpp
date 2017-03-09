#include <iostream>
#include <ok_galg/galg.h>
#include <travel.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include <chrono>

using namespace std;
using namespace ok_galg;

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
    //ok_galg::SolveSingleRun(t, config, 1, 1);

    // multi-run in threads
    ok_galg::SolveMultiThread(t, config, 200, 4, false);

    end = std::chrono::system_clock::now();

    cout << "Final" << endl;
    t.Print();
    for(unsigned int i=0;i<t.ordering_.size();++i)
        cout << cities[t.ordering_[i]].as<string>() << " -> ";
    cout << cities[t.ordering_[0]].as<string>() << endl;
    cout << endl;

    t.Randomize();
    cout << "Random" << endl;
    t.Print();
    for(unsigned int i=0;i<t.ordering_.size();++i)
        cout << cities[t.ordering_[i]].as<string>() << " -> ";
    cout << cities[t.ordering_[0]].as<string>() << endl;
    cout << endl;

    YAML::Node solution = data["solution"];
    if(!solution.IsNull() && argc > 1)
        cout << "Best known solution: " << solution << endl;

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";



}
