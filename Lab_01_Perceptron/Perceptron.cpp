//#include <stdlib.h>
//#include <time.h>

#include <iostream>
#include <ctime>

#include "Perceptron.h"

//zwraca: suma wszytkich wej�cie*waga
double Perceptron::getValue(const double inputs[]){
	double sum = 0;

	for (int i = 0; i < this->numberOfInputs; i++)
		sum += this->weights[i] * inputs[i];

	return sum;
}

//ustaw: wsp�czynnik uczenia
void Perceptron::setTrainingRate(double learningRate) {
	this->learningRate = learningRate;
}

//ucz si�
void Perceptron::learn(const double inputs[], int expectedResult){
	int result = getResult(inputs);
	if (result == expectedResult)
		return;
	changeWeights(result, expectedResult, inputs);
}

//zwraca: wynik ko�cowy dla pojedynczego wej�cia <por�wnuje warto�� wej�cia z funkcj� binarn� z progiem>
int Perceptron::getResult(const double inputs[]){
	return (getValue(inputs) > 1) ? 1 : 0;
}

//zwraca: waga dla pojedynczego wej�cia
double Perceptron::getWeightAt(unsigned index){
	return this->weights[index];
}

//zwraca: waga wszystkich wej��
const double * Perceptron::getWeights(){
	return this->weights;
}

//zwraca: ilo�� wej��
unsigned Perceptron::getNumOfInputs(){
	return this->numberOfInputs;
}

//zwraca: wsp�czynnik uczenia
double Perceptron::getTrainingRate(){
	return this->learningRate;
}

//ustaw: waga dla danego wej�cia
void Perceptron::setWeightAt(unsigned index, double weight){
	this->weights[index] = weight;
}

//ustaw: wagi dla wszystkich wej��
void Perceptron::setWeights(const double * weights){
	unsigned i;
	for (i = 0; i < this->numberOfInputs; i++)
		this->weights[i] = weights[i];
}

//funkcja losuj�ca dla wag
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