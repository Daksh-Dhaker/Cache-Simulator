#ifndef LRU_H
#define LRU_H
#include <iostream>
#include <list>
#include <algorithm> 
#define int long long

using namespace std;

class LRU{
public:
    list<int> l;
    LRU();
    void insert(int tag_value);
    void apply_op(int tag_value);
    int pop();
};

#endif
