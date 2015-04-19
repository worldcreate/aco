#include "util.h"
#include <time.h>
#include <stdlib.h>

int Util::getRand(int max,int min){
	static int init=0;
	if(init==0){
		init=1;
		srand((unsigned)time(NULL));
	}
	int r=(rand()%(max-min))+min+1;
	return r;
}