package com.company;

import org.neuroph.core.NeuralNetwork;
import org.neuroph.core.data.DataSet;
import org.neuroph.core.data.DataSetRow;
import org.neuroph.nnet.MultiLayerPerceptron;
import org.neuroph.nnet.learning.BackPropagation;
import org.neuroph.util.TransferFunctionType;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {

    private static double zMAX = Double.MIN_VALUE;
    private static double zMIN = Double.MAX_VALUE;
    private static double xyMAX = 2.0;
    private static double xyMIN = -2.0;

    public static void main(String[] args) throws IOException {
        //uworzeine danych testowych
        DataSet trainingData = new DataSet(2, 1);
        trainingData.setLabel("TrainingData");

        //określenie minimum i maximum funkcji Rastrigin na przedziale <-2.0; 2.0>
        double tmp;
        for (double i = -2.0; i <= 2.0; i += 0.1) {
            for (double j = -2.0; j <= 2.0; j += 0.1) {
                tmp = RastriginFunction.rastrigin(i, j);
                if (zMAX <= tmp)
                    zMAX = tmp;
                if (zMIN >= tmp)
                    zMIN = tmp;
            }
        }

        File newFile = new File("learningDataSet.txt");
        FileWriter fileWriter = new FileWriter(newFile);

        //wypisanie danych uczących (przed normalizacją) [40*40 danych]
        double x, y, z;
        for (double i = -2.0; i <= 2.0; i += 0.1)
            for (double j = -2.0; j <= 2.0; j += 0.1) {
                x = i;
                y = j;
                z = RastriginFunction.rastrigin(i, j);
                System.out.println("x = " + i + "\ty = " + j + "\tz = " + z);
                fileWriter.write(x + ";" + y + ";" + z + "\n");
            }

        fileWriter.close();

        //wczytanie danych wejściowcyh z pliku
        Scanner in = new Scanner(newFile);
        String[] result;
        do {
            String line = in.nextLine();
            result = line.split(";");
            //dane do normalizacji danych wejściowych  i wyjściowych
            System.out.println("Normalization: x = " + RastriginFunction.normalization(Double.parseDouble(result[0]), xyMIN, xyMAX)
                    + " y = " + RastriginFunction.normalization(Double.parseDouble(result[1]), xyMIN, xyMAX)
                    + " z = " + RastriginFunction.normalization(Double.parseDouble(result[2]), zMIN, zMAX));
            //dodanie rzędu danych uczących
            trainingData.addRow(new DataSetRow(new double[]{
                    RastriginFunction.normalization(Double.parseDouble(result[0]), xyMIN, xyMAX),
                    RastriginFunction.normalization(Double.parseDouble(result[1]), xyMIN, xyMAX)
            }, new double[]{RastriginFunction.normalization(Double.parseDouble(result[2]), zMIN, zMAX)}));
        } while (in.hasNext());

        //wybranie metody backPropagation i ustawienie maksymalnego błędu i współczynnika uczenia
        BackPropagation backPropagation = new BackPropagation();
        backPropagation.setMaxError(0.015);
        backPropagation.setLearningRate(0.04);

        //utworzenie sieci wielowarstwowej i ustalenie ilości warstw ukrytych
        MultiLayerPerceptron multiLayerPerceptron = new MultiLayerPerceptron(TransferFunctionType.SIGMOID, 2, 20, 10, 5, 1);
        multiLayerPerceptron.setLabel("MultiLayerPerceptron");
        multiLayerPerceptron.setLearningRule(backPropagation);

        System.out.println("Teaching: " + multiLayerPerceptron.getLabel() + ", LearningData: " + trainingData.getLabel());
        System.out.println("Using algorithm BackPropagation with configuration:");
        System.out.println("Max Error: " + backPropagation.getMaxError());
        System.out.println("Learning Rate: " + backPropagation.getLearningRate());

        //losowanie wstępnych wag i rozpoczęcie uczenia
        multiLayerPerceptron.randomizeWeights();
        multiLayerPerceptron.learn(trainingData);

        System.out.println("Teaching is finished:");
        //wyświetlenie liczby iteracji oraz całkowitego błędu uczenia w sieci neuronowej
        System.out.println("Number of iterations: " + backPropagation.getCurrentIteration());
        System.out.println("Total error: " + backPropagation.getErrorFunction().getTotalError());
        //zapis sieci do pliku .nnet
        multiLayerPerceptron.save("mlp.nnet");

        //testowanie utworzonej sieci
        NeuralNetwork neuralNetwork = NeuralNetwork.createFromFile("mlp.nnet");
        int iteration = 1;
        for (DataSetRow dataSetRow : trainingData.getRows()) {
            double[] input = dataSetRow.getInput();
            System.out.println("Set " + iteration + ": x = " + input[0] + " y = " + input[1]);

            double[] desiredOutput = dataSetRow.getDesiredOutput();
            neuralNetwork.setInput(dataSetRow.getInput());
            neuralNetwork.calculate();
            double[] output = neuralNetwork.getOutput();
            System.out.println("Desired output: " + desiredOutput[0]);
            System.out.println("Output: " + output[0]);
            System.out.println();
            iteration++;
        }
    }
}