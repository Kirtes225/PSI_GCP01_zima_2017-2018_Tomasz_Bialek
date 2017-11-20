#include "Perceptron.h"

//dla kazdej wagi perceptronu bêd¹ losowanie liczby z zakresu od 0 do 1
double Perceptron::getRandomDouble()
{
	double randValue = ((double)rand() / (double)RAND_MAX);
	return randValue;
}

//oblicza sumê wszytkich wejœcie*waga, przyjmuje indeks litery
double Perceptron::getSumOfInput(int i)
{
	double sum = 0;

	for (int j = 0; j < BITS_OF_ONE_LETTER; j++)
		sum += this->weights[j] * this->inputData[i][j];

	return sum;
}

//wczytanie danych ucz¹cych z pliku
void Perceptron::readTestData()
{
	fstream file;
	file.open("data_for_learning.txt");
	
	if (!file.good()){
		cout<< "--------- I can't open the file with learning data ---------" << endl;
		system("PAUSE");
		exit(0);
	}

	//wczytuj z pliku dopóki s¹ dane
	while (!file.eof())
		for (int i = 0; i < numberOfInputs; i++){ // i oznacza indeks litery
			for (int j = 0; j < BITS_OF_ONE_LETTER; j++) // j oznacza iloœæ bitów na dan¹ literê
				file >> this->inputData[i][j]; //wczytywanie do tablicy z wejœciami
			
			file >> this->expectedResults[i]; //wczytanie z pliku czy dana litera jest du¿a (1) lub ma³a (0)
		}

	file.close();
}

//ucz siê
void Perceptron::learn1()
{
	double sumOfInput = 0.;	//zmienna przechowuj¹ca wynik getSumOfInput(i)
	double errorOfOnePerceptron = 0.;	//b³¹d lokalny
	double globalError = 0.;	//b³¹d globalny
	double threshold = 1.5; //próg okreœlaj¹cy kiedy sieæ jet ju¿ nauczona
	int epoch = 0;	//epoka uczenia siê (na start = 0)
	double MAPE = 0., MSE = 0.;

	do{
		globalError = 0.;

		for (int i = 0; i < this->numberOfInputs; i++) //zmienna i oznacza indeks litery w tablicy
		{
			sumOfInput = getSumOfInput(i);
			errorOfOnePerceptron = this->expectedResults[i] - func(sumOfInput);

			//zmiana wag
			for (int j = 0; j < BITS_OF_ONE_LETTER; j++) { //zmienna j oznacza bity danej litery
				this->weights[j] += this->learningRate * errorOfOnePerceptron * this->inputData[i][j];
				//this->weights[j] += this->learningRate * (this->expectedResults[j] - func2(sumOfInput)) *this->inputData[i][j];
			}

			////////////////////////////////////////
			globalError += pow(errorOfOnePerceptron, 2);
			//MSE = pow(globalError, 2) / (BITS_OF_ONE_LETTER);
			//MAPE = (globalError * 10 / BITS_OF_ONE_LETTER);
			//cout << " MSE: " << MSE << "\tMAPE: " << MAPE << "%\n";
		}


		epoch++;
	} while (globalError >= threshold);  //zapêtla uczenie dopóki b³¹d nie bêdzie ni¿szy od progu
	
	cout << "Liczba epok potrzebnych do nauczenia: " << epoch << endl;
	//cout << "MSE: " << globalError << endl;
}

//ucz siê
void Perceptron::learn2()
{
	double sumOfInput = 0.;	//zmienna przechowuj¹ca wynik getSumOfInput(i)
	double errorOfOnePerceptron = 0.;	//b³¹d lokalny
	double globalError = 0.;	//b³¹d globalny
	double threshold = 1.5; //próg okreœlaj¹cy kiedy sieæ jet ju¿ nauczona
	int epoch = 0;	//epoka uczenia siê (na start = 0)
	double MAPE = 0., MSE = 0.;

	do {
		globalError = 0.;

		for (int i = 0; i < this->numberOfInputs; i++) //zmienna i oznacza indeks litery w tablicy
		{
			sumOfInput = getSumOfInput(i);
			errorOfOnePerceptron = this->expectedResults[i] - func2(sumOfInput);

			//zmiana wag
			for (int j = 0; j < BITS_OF_ONE_LETTER; j++) { //zmienna j oznacza bity danej litery
				this->weights[j] += this->learningRate * errorOfOnePerceptron * this->inputData[i][j];
				//this->weights[j] += this->learningRate * (this->expectedResults[j] - func2(sumOfInput)) *this->inputData[i][j];
			}

			////////////////////////////////////////
			globalError += pow(errorOfOnePerceptron, 2);
			//MSE = pow(globalError, 2) / (BITS_OF_ONE_LETTER);
			//MAPE = (globalError * 10 / BITS_OF_ONE_LETTER);
			//cout << " MSE: " << MSE << "\tMAPE: " << MAPE << "%\n";
		}


		epoch++;
	} while (globalError >= threshold);  //zapêtla uczenie dopóki b³¹d nie bêdzie ni¿szy od progu

	cout << "Liczba epok potrzebnych do nauczenia: " << epoch << endl;
	//cout << "MSE: " << globalError << endl;
}

//funkcja testuj¹ca czy podane bity tworz¹ ma³¹ czy du¿¹ literê
void Perceptron::test(int tab[])
{
	double sum = 0.;
	double errorOfOnePerceptron = 0.;
	double globalError = 0.;
	double threshold = 1.5;
	double MAPE = 0., MSE = 0.;
	for (int i = 0; i < BITS_OF_ONE_LETTER; i++)
	{
		sum += tab[i] * this->weights[i]; //oblicza sume dla zadanego elementu
		
		//MAPE += ((fabs(tab[i] * this->weights[i] - tab[i])*(tab[i] * this->weights[i]) * 100) / (tab[i] * this->weights[i]);
		//MSE += pow((tab[i] * weights[i]), 2);MSE = pow(globalError,2)/(SIZE);
	}
	errorOfOnePerceptron = 1 - sum; //b³¹d lokalny
	globalError = pow(2, errorOfOnePerceptron);	//b³¹d globalny

	if (globalError >= threshold)
		this->resultOfTest = true; //podana litera jest ma³a
	else
		this->resultOfTest = false; //podana litera jest du¿a

	//cout << "MAPE: " <<MAPE << endl;
	//cout << "MSE: " << MSE << endl;

	//wypisanie w konsoli ostatecznego wyniku testu
	if (this->resultOfTest == true)
		cout << "Wynik testu: mala litera" << endl << endl;
	else
		cout << "Wynik testu: duza litera" << endl << endl;
}

Perceptron::Perceptron(unsigned numberOfInputs, double learningRate)
{
	srand(time(NULL));

	this->numberOfInputs = numberOfInputs;
	this->learningRate = learningRate;

	//stworzenie dynamicznej tablicy wag i losowanie wag dla ka¿dego wejœcia
	this->weights = new double[BITS_OF_ONE_LETTER];
	for (int i = 0; i < BITS_OF_ONE_LETTER; i++)
		this->weights[i] = getRandomDouble();

	//wczytanie danych z pliku tekstowego
	readTestData();
}

Perceptron::~Perceptron()
{
	delete weights;
}

//wykorzystywane przy aktualizacji wag <funkcja sigmoidalna>
double Perceptron::func(double sum)
{	    
		return 1 / (1 + exp(-0.5*sum)); //wspó³czynnik beta = 0.5
}
//wykorzystywane przy aktualizacji wag <funkcja progowa unipolarna>
double Perceptron::func2(double sum)
{
	return (sum > 0)? 1 : 0;
}

//pochodna func
double Perceptron::der(double sum)
{
	return (0.5*exp(-0.5*sum))/(pow(exp(-0.5*sum)+1, 2));
}