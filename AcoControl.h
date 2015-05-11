#ifndef _ACOCONTROL_H_
#define _ACOCONTROL_H_

#include <vector>

class AcoAgent;

class AcoControl{
public:
	AcoControl(int);
	std::vector<AcoAgent*>* getAgents();
	void renew();
private:
	double rho;
	double Q;
	std::vector<std::vector<double> >tau;
	std::vector<AcoAgent*> agents;
	int cityNum;
};

#endif