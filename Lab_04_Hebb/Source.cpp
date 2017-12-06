#include "Hebb.h"

int main() {
	
	double LEARNING_RATE = 0.1;
	

	//Hebb hebbWithoutForgetting(LEARNING_RATE);
	//hebbWithoutForgetting.learnWithoutForgetting();

	//Hebb  hebbWithForgetting(LEARNING_RATE);
	//hebbWithForgetting.learnWithForgetting();
	
	Hebb hebbOjiRule(LEARNING_RATE);
	hebbOjiRule.learnOjiRegule();

	cout << endl << "Wspolczynnik uczenia: " << LEARNING_RATE << endl << endl;

	system("pause");

	return 0;
}