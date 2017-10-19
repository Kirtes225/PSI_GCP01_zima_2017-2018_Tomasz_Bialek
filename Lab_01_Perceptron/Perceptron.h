class Perceptron {
public:
	unsigned numberOfInputs;
	double *weights;
	double learningRate;

	double getRandomDouble();

	double getValue(const double inputs[]);
	int getResult(const double inputs[]);
	double getWeightAt(unsigned index);
	const double *getWeights();
	unsigned getNumOfInputs();
	double getTrainingRate();

	void setTrainingRate(double trainingRate);
	void setWeightAt(unsigned index, double weight);
	void setWeights(const double *weights);

	void changeWeights(int actualResult, int desiredResult, const double inputs[]);
	void learn(const double inputs[], int expectedResult);

	Perceptron(unsigned numOfInputs, double trainingRate);
};
