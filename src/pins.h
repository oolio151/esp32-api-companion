#pragma once

const int digitalPins[] = {4, 5, 16, 17, 18, 19, 21, 22, 23};

const int adcPins[] = {32, 33, 34, 35, 36, 39}; //using adc1 since wifi can cause conflicts with adc2, 
const int inputOnlyPins[] = {34, 35, 36, 39};

const int touchPins[] = {4, 0, 2, 15, 13, 12, 14, 27, 33, 32};
                       //T0 T1 T2 T3  T4  T5  T6  T7  T8  T9 
const int dacPins[] = {25, 26};

const int spiPins[] = {18, 19, 23, 5};
const int i2cPins[] {21, 22};

