#include <stdio.h>
#include <iostream>

#include "Perceptron.h"

using namespace std;

int main() {
	const int trainingIterations = 10;
	const int numberOfInputs = 2;
	const double trainingRate = 0.1;

	const double ZERO_ZERO[] = { 0, 0 };
	const double ZERO_ONE[] = { 0, 1 };
	const double ONE_ZERO[] = { 1, 0 };
	const double ONE_ONE[] = { 1, 1 };

	Perceptron perceptron(numberOfInputs, trainingRate);

	cout << "----------------AND - wyniki PRZED uczeniem----------------" << endl;
	cout << "Wejscie (0,0) - wynik: " << perceptron.getResult(ZERO_ZERO) << endl;
	cout << "Wejscie (0,1) - wynik: " << perceptron.getResult(ZERO_ONE) << endl;
	cout << "Wejscie (1,0) - wynik: " << perceptron.getResult(ONE_ZERO) << endl;
	cout << "Wejscie (1,1) - wynik: " << perceptron.getResult(ONE_ONE) << endl;

	for (int i = 0; i < trainingIterations; i++) {
		perceptron.train(ZERO_ZERO, 0);
		perceptron.train(ZERO_ONE, 0);
		perceptron.train(ONE_ZERO, 0);
		perceptron.train(ONE_ONE, 1);
		//cout << "Wagi: " << *perceptron.Perceptron_getWeights(perceptron) << endl;
		//cout << "Wagi: " << perceptron.Perceptron_getWeightAt(perceptron, 0) << " " 
		//<< perceptron.Perceptron_getWeightAt(perceptron, 1) << endl;
	}

	cout<< endl << "------------------AND - wyniki PO uczeniu------------------" << endl;
	cout << "Wejscie (0,0) - wynik: " << perceptron.getResult(ZERO_ZERO) << endl;
	cout << "Wejscie (0,1) - wynik: " << perceptron.getResult(ZERO_ONE) << endl;
	cout << "Wejscie (1,0) - wynik: " << perceptron.getResult(ONE_ZERO) << endl;
	cout << "Wejscie (1,1) - wynik: " << perceptron.getResult(ONE_ONE) << endl;

	system("pause");
	return 0;
}

