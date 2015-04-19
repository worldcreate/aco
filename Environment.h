#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <utility>
#include <vector>

class Agent;

class Environment{
public:
	Environment();
	void setAgent(Agent*);
	void simulate();
private:
	std::vector<std::vector<int>> cost;
	Agent* agent;
	int cityNum;
};

#endif