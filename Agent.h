#ifndef _AGENT_H_
#define _AGENT_H_

#include <vector>

class Agent{
public:
	Agent();
	virtual std::vector<int> getCityTurn()=0;
	virtual void setCityNum(int);
	virtual void setCityWeight(std::vector<std::vector<int>> );
	virtual void setFitness(int);
protected:
	int fitness;
	std::vector<std::vector<int>> weight;
	int cityNum;
};

#endif