#include <travel.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

inline unsigned int rand_int(const unsigned int &_start, const unsigned int &_length)
{
    return rand()%_length+_start;
}

// static variables
std::vector<std::vector<double> > Travel::nodes_ = std::vector<std::vector<double> >();
unsigned int Travel::n_ = 0;
std::vector<unsigned int> Travel::base_ordering_ = std::vector<unsigned int>();
bool Travel::closed_ = false;


// constructor with static init
Travel::Travel(std::vector<std::vector<double> > _nodes, bool _closed)
{
    nodes_ = _nodes;
    n_ = nodes_.size();
    base_ordering_.resize(n_);
    for(unsigned int i=0;i<n_;++i)
        base_ordering_[i] = i;
    closed_ = _closed;
}

// randomize
void Travel::randomize()
{
    ordering_ = base_ordering_;
    std::random_shuffle(ordering_.begin(),ordering_.end());
    computeCost();
}

void Travel::computeCost()
{
    cost = 0;
    for(unsigned int i=1;i<n_;++i)
        cost += nodes_[ordering_[i-1]][ordering_[i]];
    if(closed_)
        cost += nodes_[ordering_[n_-1]][ordering_[0]];
}

void Travel::crossAndMutate(Travel &_father, Travel &_mother)
{
    // crossing
    unsigned int n = rand_int(2, n_-3);
    ordering_.clear();
    ordering_.reserve(n_);
    unsigned int i;
    for(i=0;i<n;++i)
        ordering_.push_back(_father.ordering_[i]);
    // index of last element in mother
    std::vector<unsigned int>::iterator it;
    unsigned int idx = std::distance(_mother.ordering_.begin(), std::find(_mother.ordering_.begin(),_mother.ordering_.end(),ordering_[n-1]));

        for(it=_mother.ordering_.begin()+idx;it!=_mother.ordering_.end();++it)
        {
            if(std::find(ordering_.begin(),ordering_.end(),*it) == ordering_.end())
            {
                ordering_.push_back(*it);
            }
        }

        for(it=_mother.ordering_.begin();it!=_mother.ordering_.begin()+idx;++it)
        {
            if(std::find(ordering_.begin(),ordering_.end(),*it) == ordering_.end())
            {
                ordering_.push_back(*it);
             //   cout << *it << " ";
            }
        }

    // mutation: switch 2 elements
    n = rand_int(0,n_-1);
    unsigned int n2 = rand_int(0,n_-1);
    while(n2 == n)
        n2 = rand_int(0,n_-1);

    unsigned int tmp = ordering_[n];
    ordering_[n] = ordering_[n2];
    ordering_[n2] = tmp;
    computeCost();
}

void Travel::print()
{
    cout << "cost: " << cost << endl;
    cout << "ordering: ";
    for(unsigned int i=0;i<ordering_.size();++i)
        cout << ordering_[i] << " ";
    cout << endl;
}
