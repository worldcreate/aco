#include "AcoAgent.h"
#include "util.h"

AcoAgent::AcoAgent(){
	alpha=1.0;
	beta=5.0;
	rho=0.5;
	Q=100;
	minFitness=INT_MAX;
	fp=fopen("test.csv","w");
}

void AcoAgent::setCityNum(int n){
	Agent::setCityNum(n);
	tau=std::vector<std::vector<double>>(cityNum,std::vector<double>(cityNum,0));
}

void AcoAgent::setCityWeight(std::vector<std::vector<int>> cost){
	Agent::setCityWeight(cost);
	eta=std::vector<std::vector<double>>(cityNum,std::vector<double>(cityNum,0));
	for(int i=0;i<cost.size();i++){
		for(int j=0;j<cost[0].size();j++){
			if(cost[i][j]==0){
				eta[i][j]=0;
				continue;
			}
			eta[i][j]=1/(double)cost[i][j];
		}
	}
}

std::vector<int> AcoAgent::getCityTurn(){
	fprintf(stdout,"start\n");
	std::vector<int> omega;
	for(int i=0;i<cityNum;i++){
		omega.push_back(i);
	}
	roundgo.clear();
	roundgo.push_back(Util::getRand(cityNum-1,0));
	erase(roundgo[0],omega);

	while(omega.size()>1){
		fprintf(fp,"%d\n",omega.size());
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
				fprintf(fp,"%lf,",theta[j]);
			}
			fprintf(fp,"\n");
			for(int k=0;k<omega.size();k++){
				int j=omega[k];
				p[j]=a[j]/sum*100;
			}
			double saving=0;
			int r=Util::getRand(100,0);

			fprintf(fp,"p\n");
			for(int k=0;k<cityNum;k++){
				fprintf(fp,"%lf,",p[k]);
			}
			fprintf(fp,"\n");
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
	fprintf(fp,"roundgo\n");
	for(int i=0;i<roundgo.size();i++){
		fprintf(fp,"%d,",roundgo[i]);
	}
	fprintf(fp,"\n");
	return roundgo;
}

void AcoAgent::setFitness(int fit){
	Agent::setFitness(fit);
	std::vector<std::vector<double>> delta(cityNum,std::vector<double>(cityNum,0));
	fprintf(fp,"fitness=%d\n",fit);
	for(int i=0;i<roundgo.size()-1;i++){
		int j=roundgo[i];
		int k=roundgo[i+1];
		delta[j][k]=Q/fit;
		delta[k][j]=delta[j][k];
	}
	for(int i=0;i<cityNum;i++){
		for(int j=0;j<cityNum;j++){
			tau[i][j]=tau[i][j]*rho+delta[i][j];
			fprintf(fp,"%lf,",tau[i][j]);
		}
		fprintf(fp,"\n");
	}
	if(minFitness>fit){
		solution=roundgo;
	}
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

void AcoAgent::printSolution(){
	printf("solution\n");
	for(int i=0;i<solution.size();i++){
		printf("%d,",solution[i]);
	}
	printf("\n");
}

AcoAgent::~AcoAgent(){
	fclose(fp);
}