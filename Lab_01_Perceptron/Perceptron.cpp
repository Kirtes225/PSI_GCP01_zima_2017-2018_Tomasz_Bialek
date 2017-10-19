//#include <stdlib.h>
//#include <time.h>

#include <iostream>
#include <ctime>

#include "Perceptron.h"

//zwraca: suma wszytkich wejœcie*waga
double Perceptron::getValue(const double inputs[]){
	double sum = 0;

	for (int i = 0; i < this->numberOfInputs; i++)
		sum += this->weights[i] * inputs[i];

	return sum;
}

//ustaw: wspó³czynnik uczenia
void Perceptron::setTrainingRate(double learningRate) {
	this->learningRate = learningRate;
}

//ucz siê
void Perceptron::learn(const double inputs[], int expectedResult){
	int result = getResult(inputs);
	if (result == expectedResult)
		return;
	changeWeights(result, expectedResult, inputs);
}

//zwraca: wynik koñcowy dla pojedynczego wejœcia <porównuje wartoœæ wejœcia z funkcj¹ binarn¹ z progiem>
int Perceptron::getResult(const double inputs[]){
	return (getValue(inputs) > 1) ? 1 : 0;
}

//zwraca: waga dla pojedynczego wejœcia
double Perceptron::getWeightAt(unsigned index){
	return this->weights[index];
}

//zwraca: waga wszystkich wejœæ
const double * Perceptron::getWeights(){
	return this->weights;
}

//zwraca: iloœæ wejœæ
unsigned Perceptron::getNumOfInputs(){
	return this->numberOfInputs;
}

//zwraca: wspó³czynnik uczenia
double Perceptron::getTrainingRate(){
	return this->learningRate;
}

//ustaw: waga dla danego wejœcia
void Perceptron::setWeightAt(unsigned index, double weight){
	this->weights[index] = weight;
}

//ustaw: wagi dla wszystkich wejœæ
void Perceptron::setWeights(const double * weights){
	unsigned i;
	for (i = 0; i < this->numberOfInputs; i++)
		this->weights[i] = weights[i];
}

//funkcja losuj¹ca dla wag
double Perceptron::getRandomDouble(){
	double randValue = ((double)rand() / (double)RAND_MAX);
	return randValue;
}

//funkcja - zmienia wagi
void Perceptron::changeWeights(int actualResult, int desiredResult, const double inputs[]){
	for (int i = 0; i < this->numberOfInputs; i++)
		this->weights[i] += this->learningRate * (desiredResult - actualResult) * inputs[i];
}

//konstruktor
Perceptron::Perceptron(unsigned numOfInputs, double trainingRate){
	srand(time(NULL));
	this->learningRate = trainingRate;

	this->numberOfInputs = numOfInputs;
	if (this->numberOfInputs <= 0)
		this->numberOfInputs = 1;

	this->weights = new double[numberOfInputs];
	for (int i = 0; i < this->numberOfInputs; i++)
		this->weights[i] = getRandomDouble();

}