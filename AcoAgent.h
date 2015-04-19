#ifndef _ACOAGENT_H_
#define _ACOAGENT_H_

#include "Agent.h"
#include <stdio.h>

class AcoAgent:public Agent{
public:
	AcoAgent();
	std::vector<int> getCityTurn();
	void setCityNum(int);
	void setCityWeight(std::vector<std::vector<int>> );
	void setFitness(int);
	~AcoAgent();
private:
	void erase(int,std::vector<int>& );
private:
	std::vector<std::vector<double>> tau;
	std::vector<std::vector<double>> eta;
	std::vector<int> roundgo;
	double alpha;
	double beta;
	double Q;
	double rho;
	FILE *fp;
};

#endif