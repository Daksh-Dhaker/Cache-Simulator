#ifndef FIFO_CACHE_H
#define FIFO_CACHE_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#define int long long

using namespace std;

class Fifo_Cache{
public:
    int sets;
    int lines;
    int bytes;
    bool write_alloc;
    bool write_through;
    
    vector<queue<int>> checker;
    vector<set<pair<int,int>>> cache; // only contains tags and dirty bits

    Fifo_Cache(int set_sig,int block,int byte,bool write_alloc_sig,bool write_through_sig);

    void load(int addr,int &loads,int &load_hits,int &load_misses,int &cycles);

    void store(int addr,int &stores,int &store_hits,int &store_misses,int &cycles);
};

#endif

