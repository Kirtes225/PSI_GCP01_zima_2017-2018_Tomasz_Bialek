#include <iostream>
#include "Perceptron.h"

using namespace std;

int main() {
	
	const double 
		ONE_ONE[] = { 1, 1, 1 }, 
		ZERO_ONE[] = {1, 0, 1 },
		ONE_ZERO[] = {1, 1, 0 },
		ZERO_ZERO[] = { 1, 0, 0 };

	int startEpoch = 0;
	int numberOfEpochs = 15;
	int numberOfInputs = 3;
	double learningRate = 0.1;

	Perceptron perceptron(numberOfInputs, learningRate);

	cout << "----------------AND - wyniki PRZED uczeniem----------------" << endl;
	cout << "Wejscie (0,0) - wynik: " << perceptron.getResult(ZERO_ZERO) << endl;
	cout << "Wejscie (0,1) - wynik: " << perceptron.getResult(ZERO_ONE) << endl;
	cout << "Wejscie (1,0) - wynik: " << perceptron.getResult(ONE_ZERO) << endl;
	cout << "Wejscie (1,1) - wynik: " << perceptron.getResult(ONE_ONE) << endl;

	while (startEpoch < numberOfEpochs) {
		perceptron.learn(ZERO_ZERO, 0);
		perceptron.learn(ZERO_ONE, 0);
		perceptron.learn(ONE_ZERO, 0);
		perceptron.learn(ONE_ONE, 1);

		//cout << "Wagi: " << *perceptron.getWeights() << endl;
		//cout << "Wagi: " << perceptron.getWeightAt(0) << " " << perceptron.getWeightAt(1) << endl;

		startEpoch++;
	}


	cout<< endl << "------------------AND - wyniki PO uczeniu------------------" << endl;
	cout << "Wejscie (0,0) - wynik: " << perceptron.getResult(ZERO_ZERO) << endl;
	cout << "Wejscie (0,1) - wynik: " << perceptron.getResult(ZERO_ONE) << endl;
	cout << "Wejscie (1,0) - wynik: " << perceptron.getResult(ONE_ZERO) << endl;
	cout << "Wejscie (1,1) - wynik: " << perceptron.getResult(ONE_ONE) << endl;

	system("pause");
	return 0;
}

