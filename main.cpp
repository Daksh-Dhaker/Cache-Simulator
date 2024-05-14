#include <string>
#include <queue>
#include "lru_cache.h"
#include "fifo_cache.h"

#define int long long
using namespace std;   

#undef int
signed main(int argc,char*argv[]){
#define int long long  
		
    	int loads=0;
    	int stores=0;
    	int load_hits=0;
   	int store_hits=0;
   	int load_misses=0;
   	int store_misses=0;
    	int cycles=0;
    	
    	int aa = argc;
    	argc = aa;
    
   	int size_cache = std::stoi(argv[1]);
    	int blocks = std::stoi(argv[2]);
    	int bytes = std::stoi(argv[3]);
    	bool write_allocate = (std::string(argv[4])=="write-allocate");
    	bool write_through = (std::string(argv[5])=="write-through");
    	
    	if(std::string(argv[6]) == "lru"){
    		Lru_Cache cache = Lru_Cache(size_cache,blocks,bytes,write_allocate,write_through);
        	string p;
        	string q;
        	string r;
        	while(cin>>p>>q>>r){
        	    int address = std::stoll(q,0,16);
        	    if (p == "l"){
        	    	
        	        cache.load(address,loads,load_hits,load_misses,cycles);
        	    }else{
        	    	
        	        cache.store(address,stores,store_hits,store_misses,cycles);
        	    }
        	}
        	if (write_through == false){
        	for(int i=0;static_cast<size_t>(i)<cache.cache.size();i++){
        		for(auto it = cache.cache[i].begin(); it != cache.cache[i].end();++it){
        			if(it->second == 1){
        				cycles = cycles+((bytes/4)*100);
        			}
        		}
        	}
        		
        	}
    	}else{
    		Fifo_Cache cache = Fifo_Cache(size_cache,blocks,bytes,write_allocate,write_through);
        	string p;
        	string q;
        	string r;
        	while(cin>>p>>q>>r){
        	    long long address = std::stoll(q,0,16);
        	    if (p == "l"){
        	        cache.load(address,loads,load_hits,load_misses,cycles);
        	    }else{
        	        cache.store(address,stores,store_hits,store_misses,cycles);
        	    }
        	}
        	
        	if (write_through == false){
        	for(int i=0;static_cast<size_t>(i)<cache.cache.size();i++){
        		for(auto it = cache.cache[i].begin(); it != cache.cache[i].end();++it){
        			if(it->second == 1){
        				cycles = cycles+((bytes/4)*100);
        			}
        		}
        	}}
    	}
    	cout<<"Total loads: "<<loads<<endl;
        cout<<"Total stores: "<<stores<<endl;
        cout<<"Load hits: "<<load_hits<<endl;
        cout<<"Load misses: "<<load_misses<<endl;
        cout<<"Store hits: "<<store_hits<<endl;
        cout<<"Store misses: "<<store_misses<<endl;
        cout<<"Total cycles: "<<cycles<<endl;
    	
    		
    
}
