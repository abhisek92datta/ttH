#include<iostream>
#include<stdio.h>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include<vector>

using namespace std;

void select( int start, int end, std::vector<int> & prev, int group, int & count, std::vector< std::vector<int> > & group_list){

	int size = end - start + 1;

	if(group == size){
		std::vector<int> group_prelim;
		group_prelim.clear();
		for(unsigned int j=0; j<prev.size(); j++ ){
			//std::cout<<prev[j]<<"  ";
			group_prelim.push_back(prev[j]);
		}
		for(int i=start; i<=end; i++){
			//std::cout<<i<<"  ";
			group_prelim.push_back(i);
		}
		//std::cout<<"\n";
		group_list.push_back(group_prelim);
		count++;
		return;
	}

	else if(group == 1){
		std::vector<int> group_prelim;
		for(int i=start; i<=end; i++){
			group_prelim.clear();
			for(unsigned int j=0; j<prev.size(); j++ ){
				//std::cout<<prev[j]<<"  ";
				group_prelim.push_back(prev[j]);
			}
			//std::cout<<i<<"\n";
			group_prelim.push_back(i);
			group_list.push_back(group_prelim);
			count++;
		}
		return;
	}

	prev.push_back(start);
	start++;
	select(start,end,prev,group-1, count, group_list);

	prev.pop_back();
	select(start, end, prev, group, count, group_list);

	return;
}



int main(){

	int N;
	int M;
	std::cout<<"Enter N and M : ";
	std::cin>>N>>M;
	std::cout<<"\n";

	int count = 0;
	int n_groups = 0;
	std::vector< std::vector<int> > group_list;
	std::vector< std::vector<int> > group_rest_list;
	group_list.clear();
	group_rest_list.clear();

	int i=0;
	int rem_size = N-i;
	std::vector<int> prev;
	prev.clear();

	if(M!=0)
		select(i,N-1,prev,M,count, group_list);

	/*
	while( rem_size >= M ){

		if(M == 0)
			break;

		prev.clear();
		select(i,N-1,prev,M,count, group_list);

		if(M==1)
			break;

		i++;
		rem_size = N-i;
	}
	*/

	if(group_list.size()==0){
		std::vector<int> group_rest_prelim;
		for(int z=0; z<N; z++){
			group_rest_prelim.push_back(z);
		}
		group_rest_list.push_back(group_rest_prelim);
	}

	for(unsigned int x=0; x<group_list.size(); x++){
		std::vector<int> group_rest_prelim;
		for(int z=0; z<N; z++){
			int match = 0;
			for(unsigned int y=0; y<group_list[x].size(); y++){
				if(z == group_list[x][y]){
					match = 1;
					break;
				}
			}
			if(match==0)
				group_rest_prelim.push_back(z);
		}
		group_rest_list.push_back(group_rest_prelim);
	}


	if(group_list.size()==0){
		std::cout<<"  ,  ";
		for(unsigned int y=0; y<group_rest_list[0].size(); y++){
			std::cout<<group_rest_list[0][y]<<"  ";
		}
		std::cout<<"\n";
	}

	for(unsigned int x=0; x<group_list.size(); x++){
		for(unsigned int y=0; y<group_list[x].size(); y++){
			std::cout<<group_list[x][y]<<"  ";
		}
		std::cout<<"  ,  ";
		for(unsigned int y=0; y<group_rest_list[x].size(); y++){
			std::cout<<group_rest_list[x][y]<<"  ";
		}
		std::cout<<"\n";
	}

	if(M !=0)
		n_groups = group_list.size();
	else
		n_groups = 1;

	std::cout<<"\nNumber of groups : "<<n_groups<<"\n\n";
	return 0;
}
