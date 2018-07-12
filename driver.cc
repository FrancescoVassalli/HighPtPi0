#include "PionPythiaGen.h"

using namespace std;

int main(int argc, char const *argv[]){
  string fileOut = string(argv[1]);
  string pTHat = string(argv[2]);
  float gammaCut= strtod(argv[3],NULL);
  long nEvents =strtol(argv[4],NULL,10);  // 5000000;
	PionPythiaGen generator(fileOut);
	generator.init(pTHat);
	generator.run(nEvents,gammaCut);
}
