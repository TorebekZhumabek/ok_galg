#include <iostream>
#include <ok_galg/galg.h>
#include <travel.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include <time.h>

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


    // single-run solver
    //t.Copy(ok_galg::SolveSingleRun<Travel>(config, 0, 0));

    // multi-run in threads
    t.Copy(ok_galg::SolveMultiThread<Travel>(config, 200, 5, false));

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



}
