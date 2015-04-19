#include "Environment.h"
#include "Agent.h"

Environment::Environment(){
	cityNum=4;
	int c[4][4]={
		{0,3,2,1},
		{3,0,6,3},
		{2,6,0,4},
		{1,3,4,0},
	};
	cost=std::vector<std::vector<int>>(cityNum,std::vector<int>(cityNum,0));
	for(int i=0;i<cityNum;i++){
		for(int j=0;j<cityNum;j++){
			cost[i][j]=c[i][j];
		}
	}
}

void Environment::setAgent(Agent* agent){
	this->agent=agent;
	agent->setCityNum(cityNum);
	agent->setCityWeight(cost);
}

void Environment::simulate(){
	std::vector<int> array=agent->getCityTurn();

	for(int i=0;i<array.size();i++){
		printf("%d ",array[i]);
	}
	printf("\n");

	int sum=0;
	for(int i=0;i<array.size()-1;i++){
		sum+=cost[array[i]][array[i+1]];
	}
	printf("fitness=%d\n",sum);
	agent->setFitness(sum);
}