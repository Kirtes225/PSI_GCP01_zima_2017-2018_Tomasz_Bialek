#include "Include.h"

class Hebb {
public:
	// dane uczace:  
	int emoticons[4][225];
	//0 - smiech
	//1 - usmiech
	//2 - serce 
	//3 - placz

	double learningRate; //wspolczynnik uczenia

	//cztery zdeformowane emotikony testujace
	int inputSmiech80pr[225];
	int inputUsmiech80pr[225];
	int inputSerce80pr[225];
	int inputPlacz80pr[225];	

	double weights[4][225]; //wagi 
	double sumOfInput[225]; //suma: wagi * dane uczace
	double emoticonTest[225]; //wyniki dla danych testuj¹cych (przechowuje wynik z funkcji aktywacji)

	int activationFunction(double); //funkcja aktywacji (progowa bipolarna)

	void generateWeights(); //losowanie wag z zakresu <0;1>
	void generateTestInputs(); //stworzenie czterech zdeformowanych emotikon testujacych
	void resetSum(); //ustawienie sum na 0
	void readFromFile(); //wczytanie z pliku bitow danych uczacych i zapisanie do zmiennych
	
	void learnWithoutForgetting(); //uczenie Hebb'em bez zapominania
	void learnWithForgetting(); //uczenie Hebb'em z zapominaniem
	void learnOjiRegule(); //uczenie regula Oji

	void test(); //przetestowanie zdeformowanych emotikon
	void compare(); //w ilu % siec rozpoznala dobrze dana emotikone

	Hebb(double); //konstruktor
};