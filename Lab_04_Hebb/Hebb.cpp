#include "Hebb.h"

Hebb::Hebb(double learningRate){
	this->learningRate = learningRate;
	
	for(int i = 0; i<HOW_MANY_EMOTICONS; i++)
		for (int j = 0; j < HOW_MANY_BITS; j++) {
			weights[i][j] = 0;
			sumOfInput[i] = 0; 
			emoticonTest[i] = 0;
	}
}

//funkcja progowa bipolarna
int Hebb::activationFunction(double sum){
	return (sum >= 0) ? 1 : -1;
}

//losowanie wag dla kazdej z emotikon [przedzial 0;1]
void Hebb::generateWeights(){
	srand(time(NULL));
	for (int i = 0; i<HOW_MANY_BITS; i++) {
		weights[0][i] = (double)rand() / (double)RAND_MAX;			
		weights[1][i] = (double)rand() / (double)RAND_MAX;		
		weights[2][i] = (double)rand() / (double)RAND_MAX;
		weights[3][i] = (double)rand() / (double)RAND_MAX;
	}
	
}

//ustawienie sum (wejscie*waga) na wartosc poczatkowa = 0
void Hebb::resetSum(){
	int i = 0;
	for (i = 0; i<HOW_MANY_BITS; i++)
		sumOfInput[i] = 0.;
}

//wczytanie z pliku danych do nauki
void Hebb::readFromFile(){
	int whichEmoticon = 0, whichBit = 0, bit;
	fstream file;
	file.open("dane.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			//jesli wczytano juz wszystkie bity (225) danej emotikony, przejscie do wczytywania bitow kolejnej
			if (whichBit == 225) {
				whichBit = 0; whichEmoticon++;
			}
			//jesli wczytano wszystkie (4) emotikony, zakoncz wczytywanie
			if (whichEmoticon == HOW_MANY_EMOTICONS) 
				break;

			file >> bit;
			emoticons[whichEmoticon][whichBit] = bit;
			whichBit++;
		}
		file.close();
	}
}

//uczenie regula Hebba (bez zapominania)
void Hebb::learnWithoutForgetting() {
	int epoch = 0; //epoka

	double globalError = 0.; //blad globalny
	double localError = 0.; //blad lokalny
	double MSE = 0.; //blad sredniokwadratowy
	double MAPE = 0.; //blad bezwgledny

	double sum = 0.; //przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //ustawienie wartosci poczatkowych dla wektora sumOfInput
	
	generateWeights(); //losowanie wag z przedzia³u 0;1
	readFromFile(); //wczytanie do 4 wektorów wszystkich (225) bitów w celu uczenia

	do {
		cout << "Epoka: " << epoch << endl;

		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];
				sumOfInput[j] = (weights[i][j]*emoticons[i][j]);

				//aktualizacja wag
				weights[i][j] = weights[i][j] + this->learningRate*sumOfInput[j]*emoticons[i][j];

				if (localError == abs(sum - sumOfInput[j])) 
					break;
				localError = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localError, 2);

			}

			MSE = pow(globalError, 2) / HOW_MANY_BITS;
			MAPE = (globalError * 10) / HOW_MANY_BITS;
			cout << "MSE: " << MSE << "\tMAPE: " << MAPE << "%"<< endl;
		}
		epoch++;

	} while (globalError != 0 && epoch<5000);

	cout << endl << "Liczba epok uczenia [Hebb bez zapominania]: " << epoch << endl;

	test();
}

//uczenie regu³¹ Hebba (z zapominaniem)
void Hebb::learnWithForgetting() {

	int epoch = 0; //epoka
	double FORGET_RATE = 0.05; //wspolczynnik zapominania

	double globalError = 0.; //blad globalny
	double localError = 0.; //blad lokalny
	double MSE = 0.; //blad sredniokwadratowy
	double MAPE = 0.; //blad bezwgledny

	double sum = 0.; //przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //ustawienie wartosci poczatkowych dla wektora sumOfInput

	generateWeights(); //losowanie wag z przedzia³u 0;1
	readFromFile(); //wczytanie do 4 wektorów wszystkich (225) bitów w celu uczenia

	do {
		cout << "Epoka: " << epoch << endl;

		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];

				sumOfInput[j] = (weights[i][j]*emoticons[i][j]);

				//aktualizacja wag
				weights[i][j] = weights[i][j] * (1- FORGET_RATE) + this->learningRate*sumOfInput[j] * emoticons[i][j];

				if (localError == abs(sum - sumOfInput[j])) break;
				localError = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localError, 2);
			}

			MSE = pow(globalError, 2) / (HOW_MANY_BITS);
			MAPE = (globalError * 10 / HOW_MANY_BITS);
			cout << "MSE: " << MSE << "\tMAPE: " << MAPE << "%"<<endl;
			
		}

		epoch++;

	} while (globalError != 0 && epoch<5000);

	cout << endl << "Liczba epok uczenia [Hebb z zapominaniem]: " << epoch << endl;

	test();
}

//uczenie regu³¹ Oji
void Hebb::learnOjiRegule() {

	int epoch = 0; //epoka

	double globalError = 0.; //blad globalny
	double localError = 0.; //blad lokalny
	double MSE = 0.; //blad sredniokwadratowy
	double MAPE = 0.; //blad bezwgledny

	double sum = 0.; //przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //ustawienie wartosci poczatkowych dla wektora sumOfInput

	generateWeights(); //losowanie wag z przedzia³u 0;1
	readFromFile(); //wczytanie do 4 wektorów wszystkich (225) bitów w celu uczenia

	do {
		cout << "Epoka: " << epoch << endl;

		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];

				sumOfInput[j] = (weights[i][j]*emoticons[i][j]);

				//aktualizacja wg
				weights[i][j] = weights[i][j] + (this->learningRate*sumOfInput[j] * (emoticons[i][j] - sumOfInput[j] * weights[i][j]));

				if (localError == abs(sum - sumOfInput[j])) break;
				localError = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localError, 2);
			}

			MSE = pow(globalError, 2) / (HOW_MANY_BITS);
			MAPE = (globalError * 10 / HOW_MANY_BITS);
			cout << "MSE: " << MSE << "\tMAPE: " << MAPE << "%" <<endl;
		}

		epoch++;

	} while (globalError != 0 && epoch<5000);

	cout << endl << "Liczba epok uczenia [Oji]: " << epoch << endl;

	test();
}

//przetestowanie nauczenia danej emotikony (do test sluza zmodyfikowane w 20% emotikony)
void Hebb::test() {
	fstream file;
	file.open("test.txt", ios::app);

	double globalError = 0.;
	double localError = 0.;
	double MSE = 0.;
	double MAPE = 0.;
	double sum = 0.;
	int epoch = 0;

	generateTestInputs();

	cout << endl << "Do testu emotikona SMIECH" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i]*inputSmiech80pr[i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localError = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localError, 2);
		}

		MSE = pow(globalError, 2) / (HOW_MANY_BITS);
		MAPE = (globalError * 10 / HOW_MANY_BITS);

		//cout << "Uczenie: MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;

		file << "MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;
	} while (globalError != 0 && epoch<1);

	file.close();

	compare();
}

//sprawdzenie w ilu procentach siec rozpoznaje dana emotikone
void Hebb::compare() {
	fstream file;
	file.open("compare.txt", ios::app);
	int tmp[HOW_MANY_EMOTICONS];

	for (int i = 0; i<HOW_MANY_EMOTICONS; i++) 
		tmp[i] = 0;

	for (int i = 0; i<HOW_MANY_BITS; ++i) {
		if (emoticonTest[i] == emoticons[0][i]) tmp[0]++;
		if (emoticonTest[i] == emoticons[1][i]) tmp[1]++;
		if (emoticonTest[i] == emoticons[2][i]) tmp[2]++;
		if (emoticonTest[i] == emoticons[3][i]) tmp[3]++;
	}

	cout << "------- PODOBIENSTWO [ZMODYFIKOWANE W 20%] -------" << endl;
	cout << "Smiech: " << (double(tmp[0]) / 225.0)*100.0 << endl;
	cout << "Usmiech: " << (double(tmp[1]) / 225.0)*100.0 << endl;
	cout << "Serce: " << (double(tmp[2]) / 225.0)*100.0<< endl;
	cout << "Placz: " << (double(tmp[3]) / 225.0)*100.0 << endl;

	file << "Smiech: " << (double(tmp[0]) / 225.0)*100.0 << endl;
	file << "Usmiech: " << (double(tmp[1]) / 225.0)*100.0 << endl;
	file << "Serce: " << (double(tmp[2]) / 225.0)*100.0 << endl;
	file << "Placz: " << (double(tmp[3]) / 225.0)*100.0 << endl;

	file.close();
}

void Hebb::generateTestInputs() {
	srand(time(NULL));

	//przepisanie bitow do danych testujacych
	for (int i = 0; i<HOW_MANY_BITS; i++) {							
		inputSmiech80pr[i] = emoticons[0][i];
		inputUsmiech80pr[i] = emoticons[1][i];
		inputSerce80pr[i] = emoticons[2][i];
		inputPlacz80pr[i] = emoticons[3][i];
	}

	int wrongBits = 45; // (1 - 0.8) * 225
	int j;

	//zdefermowanie danych testujacych o 20%
	for (int i = 0; i<wrongBits; i++) {
		j = rand() % 225;
		inputSerce80pr[j] = !inputSerce80pr[j];
		j = rand() % 225;
		inputSmiech80pr[j] = !inputSmiech80pr[j];
		j = rand() % 225;
		inputUsmiech80pr[j] = !inputUsmiech80pr[j];
		j = rand() % 225;
		inputPlacz80pr[j] = !inputPlacz80pr[j];
	}
}