class Perceptron {
public:
	unsigned numberOfInputs;
	double *weights;
	double threshold;
	double trainingRate;

	double getValue(const double inputs[]);
	void setTrainingRate(double trainingRate);
	void train(const double inputs[], int expectedResult);
	int getResult(const double inputs[]);
	double getWeightAt(unsigned index);
	const double *getWeights();
	unsigned getNumOfInputs();
	double getThreshold();
	double getTrainingRate();
	void setWeightAt(unsigned index, double weight);
	void setWeights(const double *weights);
	void setThreshold(double threshold);

	double getRandomDouble();
	void changeWeights(int actualResult, int desiredResult, const double inputs[]);
	Perceptron(unsigned numOfInputs, double trainingRate);
};
