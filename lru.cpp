#include "lru.h"

LRU::LRU(){}


void LRU::insert(int tag_value){
        l.push_back(tag_value);
}

void LRU::apply_op(int tag_value){
        if (l.size() ==0){
        	cout<<"empty lru"<<endl;
        }else{
        	auto it = std::find(l.begin(),l.end(),tag_value);
        	if(it !=l.end()){
        		l.erase(it);
        		l.push_back(tag_value);
        	}
        }
}

int LRU::pop(){   
        if(l.size()==0){
        	return -1;
        }else{
        	int ans = l.front();
        	l.pop_front();
        	return ans;
        }
}


