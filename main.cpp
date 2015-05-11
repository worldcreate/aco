#include "Environment.h"
#include "AcoControl.h"
#include "progress.h"
#include "Agent.h"
#include "AcoAgent.h"

int main(void){
	Environment env("city_position.csv");
	AcoControl ac(env.getCitynum());
	for(int j=0;j<10000;j++){
		std::vector<AcoAgent*>* agents=ac.getAgents();
		for(int i=0;i<100;i++){
			env.setAgent((*agents)[i]);
			env.simulate();
			progress(j*100+i,(100-1)*(10000-1));
		}
		ac.renew();
	}
	env.printFitness();
	return 0;
}