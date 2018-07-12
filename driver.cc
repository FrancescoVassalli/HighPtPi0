#include "PionPythiaGen.h"


int main(){
	PionPythiaGen generator("PionPythiaGenpT5");
	generator.init("5");
	generator.run(1,10);
}
