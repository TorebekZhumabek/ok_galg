#ifndef Travel_H
#define Travel_H

#include <vector>

class Travel
{
public:
    std::vector<unsigned int> ordering_;
    static std::vector<unsigned int> base_ordering_;
    Travel() {randomize();}
    void randomize();
    Travel(std::vector<std::vector<double> > _nodes, bool _closed = false);    
    void computeCost();
    void crossAndMutate(Travel &_father, Travel &_mother);
    void print();

    inline static void waitForCosts() {}

    double cost;

protected:

    static std::vector<std::vector<double> > nodes_;    
    static unsigned int n_;
    static bool closed_;
};



#endif // Travel_H
