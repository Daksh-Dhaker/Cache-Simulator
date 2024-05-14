#include "lru_cache.h"


Lru_Cache::Lru_Cache(int set_sig,int block,int byte,bool write_alloc_sig,bool write_through_sig){
        this->sets = set_sig;
        this->lines = block;
        this->bytes = byte;
        this->write_alloc = write_alloc_sig;
        this->write_through = write_through_sig;
        
        
        
        LRU l = LRU();
        
        this->checker = vector<LRU> (this->sets,l);
        set<pair<int,int>> st;
        this->cache = vector<set<pair<int,int>>> (this->sets,st);
        
}

void Lru_Cache::load(int addr,int &loads,int &load_hits,int &load_misses,int &cycles){
        //int byte_offset = (addr % bytes);
        int set_no = ((addr/bytes)%sets);
        int tag = ((addr/bytes)/sets);
        
        
        auto hit = find_if(cache[set_no].begin(),cache[set_no].end(),[tag](const auto& pair){
            return pair.first == tag;
        });
        if(hit !=cache[set_no].end()){
            
            checker[set_no].apply_op(tag);
            loads++;
            load_hits++;
            cycles = cycles+1;
        }else{
            
            if(cache[set_no].size() == static_cast<size_t>(this->lines)){
            	
                if(write_through){
                	
                    int to_be_removed = checker[set_no].pop();
                    auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto& pair){
                        return pair.first == to_be_removed;
                    });
                    cache[set_no].erase(it);
                    checker[set_no].insert(tag);
                    cache[set_no].insert(make_pair(tag,0));
                    loads++;
                    load_misses++;
                    cycles = cycles+((bytes/4)*100)+2;
                }else{
                    
                    int to_be_removed = checker[set_no].pop();
                    
                    auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto &pair){
                        return pair.first == to_be_removed;
                    });
                    
                    if ((*it).second == 1){
                        cycles = cycles+((bytes/4)*100);
                    }
                    cache[set_no].erase(it);
                    checker[set_no].insert(tag);
                    cache[set_no].insert(make_pair(tag,0));
                    loads++;
                    load_misses++;
                    cycles = cycles+((bytes/4)*100)+2;
                }
            }else{
            	
                cache[set_no].insert(make_pair(tag,0));
                checker[set_no].insert(tag);
                loads++;
                load_misses++;
                cycles = cycles+((bytes/4)*100)+2;
            }
        }
}

void Lru_Cache::store(int addr,int &stores,int &store_hits,int &store_misses,int &cycles){
        //int byte_offset = (addr % bytes);
        int set_no = ((addr/bytes)%sets);
        int tag = ((addr/bytes)/sets);
        
        auto hit = find_if(cache[set_no].begin(),cache[set_no].end(),[tag](const auto& pair){
            return pair.first == tag;
        });
        if(hit !=cache[set_no].end()){
            // cout<<"store hit"<<endl;
            if(write_through){
                checker[set_no].apply_op(tag);
                stores++;
                store_hits++;
                cycles = cycles+((bytes/4)*100)+1;
            }else{
                stores++;
                store_hits++;
                checker[set_no].apply_op(tag);
                cache[set_no].erase(hit);
               
                cache[set_no].insert(make_pair(tag,1));
                cycles = cycles+(2);
            }
        }else{
            // cout<<"store miss"<<endl;
            if(write_alloc){
                if(cache[set_no].size() == static_cast<size_t>(this->lines)){
                    if (write_through){
                        int to_be_removed = checker[set_no].pop();
                        auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto& pair){
                            return pair.first == to_be_removed;
                        });
                        cache[set_no].erase(it);
                        checker[set_no].insert(tag);
                        cache[set_no].insert(make_pair(tag,0));
                        cycles = cycles+((bytes/4)*100);
                        cycles = cycles+2+((bytes/4)*100);
                        store_misses++;
                        stores++;
                    }else{
                        int to_be_removed = checker[set_no].pop();
                        auto it = find_if(cache[set_no].begin(),cache[set_no].end(),[to_be_removed](const auto &pair){
                            return pair.first == to_be_removed;
                        });
                    
                        if ((*it).second == 1){
                            cycles = cycles+((bytes/4)*100);
                        }
                        cache[set_no].erase(it);
                        checker[set_no].insert(tag);
                      
                        cache[set_no].insert(make_pair(tag,1));
                        cycles = cycles+((bytes/4)*100)+2;
                        stores++;
                        store_misses++;
                    }
                }else{
                    if (write_through){
                        checker[set_no].insert(tag);
                        cache[set_no].insert(make_pair(tag,0));
                        stores++;
                        store_misses++;
                        cycles = cycles+((bytes/4)*100)+2+((bytes/4)*100);
                    }else{
                        checker[set_no].insert(tag);
                      
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


