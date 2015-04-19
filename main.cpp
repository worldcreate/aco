#include "Environment.h"
#include "AcoAgent.h"

int main(void){
	Environment env;
	AcoAgent agent;
	env.setAgent(&agent);
	for(int j=0;j<300;j++){
		env.simulate();
	}
	agent.printSolution();
	return 0;
}