#include "AcoControl.h"
#include "AcoAgent.h"

AcoControl::AcoControl(int cityNum){
	tau=std::vector<std::vector<double> >(cityNum,std::vector<double>(cityNum,0));
	Q=1000;
	rho=0.8;
	this->cityNum=cityNum;
}

std::vector<AcoAgent*>* AcoControl::getAgents(){
	for(int i=0;i<100;i++){
		agents.push_back(new AcoAgent(tau));
	}
	return &agents;
}

void AcoControl::renew(){
	std::vector<std::vector<double> > delta(cityNum,std::vector<double>(cityNum,0));
	std::vector<int>* roundgo;
	for(int m=0;m<100;m++){
		roundgo=(agents[m])->getRoundgo();
		for(int i=0;i<roundgo->size()-1;i++){
			int j=(*roundgo)[i];
			int k=(*roundgo)[i+1];
			delta[j][k]+=Q/agents[m]->getFitness();
			delta[k][j]=delta[j][k];
		}
	}
	for(int i=0;i<cityNum;i++){
		for(int j=0;j<cityNum;j++){
			tau[i][j]=tau[i][j]*rho+delta[i][j];
		}
	}
}