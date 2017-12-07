package com.company;

public class RastriginFunction {
    //obliczenie wartości funkcji rastrigin na osi z
    static double rastrigin(double x1, double x2) {
        return 10 * 2 +
                Math.pow(x1, 2) - 10 * Math.cos(2 * Math.PI * x1) +
                Math.pow(x2, 2) - 10 * Math.cos(2 * Math.PI * x2);
    }

    //normalizacja do przedziału <0; 1>
    static double normalization (double number, double rangeA, double rangeB){
        return ((number - rangeA)/(rangeB - rangeA)) * (1.0 - (0.0)) + (0.0);
    }
}
