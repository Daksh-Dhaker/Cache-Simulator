#include "fifo_cache.h"

Fifo_Cache::Fifo_Cache(int set_sig,int block,int byte,bool write_alloc_sig,bool write_through_sig){
        sets = set_sig;
        lines = block;
        bytes = byte;
        write_alloc = write_alloc_sig;
        write_through = write_through_sig;
        
        
        queue<int> s;
        checker = vector<queue<int>> (sets,s);
        set<pair<int,int>> st;
        cache = vector<set<pair<int,int>>> (sets,st); 
}

void Fifo_Cache::load(int addr,int &loads,int &load_hits,int &load_misses,int &cycles){
        //int byte_offset = (addr % bytes);
        int set_no = ((addr/bytes)%sets);
        int tag = ((addr/bytes)/sets);

        auto hit = find_if(cache[set_no].begin(),cache[set_no].end(),[tag](const auto& pair){
            return pair.first == tag;
        });
        
        if (hit != cache[set_no].end()){
            loads++;         // If hit directly bring from cache to reg file
            load_hits++;
            cycles = cycles+(1);  // Ask if one cycles is required or more than one
        }else{
            if(cache[set_no].size() == static_cast<size_t>(this->lines)){
                if (write_through){
                    int to_be_removed = checker[set_no].front();
                    checker[set_no].pop();
                    auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto& pair){
                        return pair.first == to_be_removed;
                    });
                    cache[set_no].erase(it);
                    checker[set_no].push(tag);
                    cache[set_no].insert(make_pair(tag,0));
                    loads++;
                    load_misses++;
                    cycles = cycles+((bytes/4)*100)+2;
                }else{
                    int to_be_removed = checker[set_no].front();
                    checker[set_no].pop();

                    auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto &pair){
                        return pair.first == to_be_removed;
                    });
                    
                    if ((*it).second == 1){
                        cycles = cycles+((bytes/4)*100);
                    }
                    cache[set_no].erase(it);
                    checker[set_no].push(tag);
                    cache[set_no].insert(make_pair(tag,0));
                    loads++;
                    load_misses++;
                    cycles = cycles+((bytes/4)*100)+2;
                }

            }else{
                cache[set_no].insert(make_pair(tag,0));
                checker[set_no].push(tag);
                loads++;
                load_misses++;
                cycles = cycles+((bytes/4)*100)+2;
            }
        }
}

void Fifo_Cache::store(int addr,int &stores,int &store_hits,int &store_misses,int &cycles){
        //int byte_offset = (addr % bytes);
        int set_no = ((addr/bytes)%sets);
        int tag = ((addr/bytes)/sets);
        
        auto hit = find_if(cache[set_no].begin(),cache[set_no].end(),[tag](const auto& pair){
            return pair.first == tag;
        });                                     // In the book no where it is written that
        if (hit != cache[set_no].end()){                             // write back or write through uses write buffer            
            if (write_through){ 
                stores++;
                store_hits++;
                cycles = cycles+((bytes/4)*100)+1;
            }else{
                stores++;
                store_hits++;
                cache[set_no].erase(hit);
                cache[set_no].insert(make_pair(tag,1));
                cycles = cycles+(2);
            }
        }else{
            if (write_alloc){
                if (cache[set_no].size() == static_cast<size_t>(this->lines)){ // All locations are filled
                    if (write_through){
                        int to_be_removed = checker[set_no].front();
                        checker[set_no].pop();
                        auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto& pair){
                            return pair.first == to_be_removed;
                        });
                        cache[set_no].erase(it);
                        checker[set_no].push(tag);
                        cache[set_no].insert(make_pair(tag,0));
                        cycles = cycles+((bytes/4)*100);
                        cycles = cycles+2+((bytes/4)*100);
                        store_misses++;
                        stores++;
                    }else{
                        int to_be_removed = checker[set_no].front();
                        checker[set_no].pop();

                        auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto &pair){
                            return pair.first == to_be_removed;
                        });
                    
                        if ((*it).second == 1){
                            cycles = cycles+((bytes/4)*100);
                        }
                        cache[set_no].erase(it);
                        checker[set_no].push(tag);
                        cache[set_no].insert(make_pair(tag,1));
                        cycles = cycles+((bytes/4)*100)+2;
                        stores++;
                        store_misses++;
                    }
                }else{// Atleast one line is empty
                    if (write_through){
                        checker[set_no].push(tag);
                        cache[set_no].insert(make_pair(tag,0));
                        stores++;
                        store_misses++;
                        cycles = cycles+((bytes/4)*100)+2+((bytes/4)*100);
                    }else{
                        checker[set_no].push(tag);
                        cache[set_no].insert(make_pair(tag,1));
                        stores++;
                        store_misses++;
                        cycles = cycles+((bytes/4)*100)+2;
                    }
                    
                }
            }else{
                if (write_through){
                    stores++;
                    store_misses++;
                    cycles = cycles+((bytes/4)*100)+1;
                }else{
                    stores++;
                    store_misses++;
                    cycles = cycles+((bytes/4)*100)+1;
                }
            }
        }
}


