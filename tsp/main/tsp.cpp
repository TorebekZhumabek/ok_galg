#include <iostream>
#include <ok_galg/galg.h>
#include <travel.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include <time.h>

using namespace std;
using namespace ok_galg;

int main(void)
{
    std::srand(std::time(0));


    // load configuration for genetic algorithm
    YAML::Node config = YAML::LoadFile("../config.yaml");

    // load city cost from YAML
    YAML::Node data = YAML::LoadFile("../tsp.yaml");
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
    t.Copy(ok_galg::SolveMultiThread<Travel>(config, 40, 4, false));

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



}
