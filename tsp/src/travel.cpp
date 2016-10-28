#include <travel.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using namespace ok_galg;

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
void Travel::Randomize()
{
    ordering_ = base_ordering_;
    std::random_shuffle(ordering_.begin(),ordering_.end());
    ComputeCost();
}

void Travel::ComputeCost()
{
    cost = 0;
    for(unsigned int i=1;i<n_;++i)
        cost += nodes_[ordering_[i-1]][ordering_[i]];
    if(closed_)
        cost += nodes_[ordering_[n_-1]][ordering_[0]];
}

void Travel::CrossAndMutate(Travel &_father, Travel &_mother)
{
    // crossing
    unsigned int n = rand_int(2, n_-3);
  //  Print("    crossing between ", ordering_);
  //  Print("                 and ", _other.ordering_);    
    ordering_.clear();
    ordering_.reserve(n_);
    unsigned int i;
    for(i=0;i<n;++i)
        ordering_.push_back(_father.ordering_[i]);
    // index of last element in mother
    std::vector<unsigned int>::iterator it;
    unsigned int idx = std::distance(_mother.ordering_.begin(), std::find(_mother.ordering_.begin(),_mother.ordering_.end(),ordering_[n-1]));
   // cout << "    crossing at " << n;
  //  cout << ", is at " << idx << " in other" << endl;
   // //Print("    starting from ", new_ordering);

    // append ending of other ordering if not already in it
    //if(idx !=_mother.ordering_.end())
    {
      //  cout << "    adding ending of other: ";
        for(it=_mother.ordering_.begin()+idx;it!=_mother.ordering_.end();++it)
        {
            if(std::find(ordering_.begin(),ordering_.end(),*it) == ordering_.end())
            {
                ordering_.push_back(*it);
           //     cout << *it << " ";
            }
        }
      //  cout << endl;
    }
    // append beginning of other ordering if not already
   // if(idx != _mother.ordering_.begin())
    {
      //  cout << "    adding beginning of other: ";
        for(it=_mother.ordering_.begin();it!=_mother.ordering_.begin()+idx;++it)
        {
            if(std::find(ordering_.begin(),ordering_.end(),*it) == ordering_.end())
            {
                ordering_.push_back(*it);
             //   cout << *it << " ";
            }
        }
       // cout << endl;
    }
  //  Print("                        final: ", new_ordering);

    // mutation: switch 2 elements
    n = rand_int(0,n_-1);
    unsigned int n2 = rand_int(0,n_-1);
    while(n2 == n)
        n2 = rand_int(0,n_-1);

    unsigned int tmp = ordering_[n];
    ordering_[n] = ordering_[n2];
    ordering_[n2] = tmp;
    ComputeCost();
}

void Travel::Print()
{
    cout << "cost: " << cost << endl;
    cout << "ordering: ";
    for(unsigned int i=0;i<ordering_.size();++i)
        cout << ordering_[i] << " ";
    cout << endl;
}
