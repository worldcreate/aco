#include "AcoAgent.h"
#include "util.h"

AcoAgent::AcoAgent(const std::vector<std::vector<double> > &t){
	alpha=1.0;
	beta=0.5;
	tau=t;
}

void AcoAgent::setCityNum(int n){
	Agent::setCityNum(n);
}

void AcoAgent::setCityWeight(std::vector<std::vector<double> > cost){
	Agent::setCityWeight(cost);
	eta=std::vector<std::vector<double> >(cityNum,std::vector<double>(cityNum,0));
	for(int i=0;i<cost.size();i++){
		for(int j=0;j<cost[0].size();j++){
			if((int)cost[i][j]==0){
				eta[i][j]=0;
				continue;
			}
			eta[i][j]=1/(double)cost[i][j];
		}
	}
}

std::vector<int>* AcoAgent::getRoundgo(){
	return &roundgo;
}

std::vector<int> AcoAgent::getCityTurn(){
	std::vector<int> omega;
	for(int i=0;i<cityNum;i++){
		omega.push_back(i);
	}
	roundgo.clear();
	roundgo.push_back(omega[0]);
	erase(roundgo[0],omega);

	while(omega.size()>1){
		int i=roundgo[roundgo.size()-1];
		std::vector<double> theta(cityNum,0);
		double thetaSum=0;
		for(int k=0;k<omega.size();k++){
			int j=omega[k];
			theta[j]=(tau[i][j]*alpha)*(eta[i][j]*beta);
			thetaSum+=theta[j];
		}
		if(thetaSum!=0){
			std::vector<double> a(cityNum,0);
			std::vector<double> p(cityNum,0);
			double sum=0;
			for(int k=0;k<omega.size();k++){
				int j=omega[k];
				a[j]=theta[j]/thetaSum;
				sum+=a[j];
			}
			for(int k=0;k<omega.size();k++){
				int j=omega[k];
				p[j]=a[j]/sum*100;
			}
			double saving=0;
			int r=Util::getRand(100,0);

			for(int k=0;k<omega.size();k++){
				int j=omega[k];
				if(saving<=r && r<saving+p[j]){
					roundgo.push_back(j);
					erase(j,omega);
				}
				saving+=p[k];
			}
		}else{
			int r;
			if(omega.size()-1!=0){
				r=Util::getRand(omega.size()-1,0);
			}else{
				r=0;
			}
			roundgo.push_back(omega[r]);
			erase(omega[r],omega);
		}
	}
	roundgo.push_back(omega[0]);
	return roundgo;
}

void AcoAgent::setFitness(int fit){
	Agent::setFitness(fit);

}

void AcoAgent::erase(int n,std::vector<int> &omega){
	std::vector<int>::iterator it=omega.begin();
	for(std::vector<int>::iterator it=omega.begin();it!=omega.end();++it){
		if((*it)==n){
			omega.erase(it);
			break;
		}
	}
}

AcoAgent::~AcoAgent(){
}