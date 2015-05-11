#ifndef _ACOAGENT_H_
#define _ACOAGENT_H_

#include "Agent.h"
#include <stdio.h>

class AcoAgent:public Agent{
public:
	AcoAgent(const std::vector<std::vector<double> >&);
	std::vector<int> getCityTurn();
	void setCityNum(int);
	void setCityWeight(std::vector<std::vector<double> > );
	void setFitness(int);
	std::vector<int>* getRoundgo();
	~AcoAgent();
private:
	void erase(int,std::vector<int>& );
private:
	std::vector<std::vector<double> > tau;
	std::vector<std::vector<double> > eta;
	std::vector<int> roundgo;
	double alpha;
	double beta;
};

#endif