#pragma once
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

#define HOW_MANY_LETTERS 20
#define BITS_OF_ONE_LETTER 35

class Perceptron
{
	double * weights;	//przechowuje wagi dla ka�dego wej�cia perceptronu
	double learningRate;	//wsp�czynnik uczenia
	int inputData[HOW_MANY_LETTERS][BITS_OF_ONE_LETTER];  //tablica przechowuj�ca litery i ich reprezentacje bitowe
	int expectedResults[HOW_MANY_LETTERS];	//tablica zawiera oczekiwane wyniki (1 - du�a litera lub 0 - ma�a litera) dla danych ucz�cych
	int numberOfInputs;	//ilosc wej��
	bool resultOfTest;	//przechowuje wynik testu (1 - du�a litera lub 0 - ma�a litera)

public:
	
	void learn1();	//funkcja ucz�ca <sigmoidalna>
	void learn2();  //funkcja ucz�ca <progowa unipolarna>
	void test(int tab[]);	//funkcja przeznaczona do testu (tab[] - reprezentacja bitowa litery do testowania)
	void readTestData();	//wczytanie danych do nauki z pliku

	double getRandomDouble();	// losowanie wag z przedzia�u <0; 1>
	double getSumOfInput(int i); //funkcja sumuj�ca perceptronu (i - indeks litery)
	double func(double sum); //funkcja sigmoidalna (przyjmuje getSumOfInput)
	double der(double sum); //pochodna func
	
	double func2(double sum); //funkcja progowa unipolarna (przyjmuje getSumOfInput)

	Perceptron(unsigned numOfInputs, double trainingRate);
	~Perceptron();

};