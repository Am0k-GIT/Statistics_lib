// Библиотека для статистической обработки массивов данных

#pragma once

#include <Arduino.h>

void swapValues(float& a, float& b);                                                               // меняет местами значения
void swapValues(int& a, int& b);

bool ascending(float a, float b);                                                                  // параметр сортировки по возрастанию
bool ascending(int a, int b);

bool descending(float a, float b);                                                                 // параметр сортировки по убыванию
bool descending(int a, int b);

void copyArray(float* array, float* copy, uint16_t length);                                         // создание копии массива
void copyArray(int* array, int* copy, uint16_t length);

void sortArray(float* array, uint16_t length, bool (*comparisonFcn)(float, float));                 // сортировка массива
void sortArray(int* array, uint16_t length, bool (*comparisonFcn)(int, int));

float averageValue(float* array, uint16_t length);                                                  // нахождение усредненного значения в массиве
float averageValue(int* array, uint16_t length);

float medianValue(float* array, uint16_t length);                                                   // нахождение медианного значения в массиве
float medianValue(int* array, uint16_t length);

float filterValue(float* array, uint16_t length, float (*referenceFcn)(float* array, uint16_t length), uint16_t maxDiffPercent);     // нахождение отфильтрованного значения
float filterValue(int* array, uint16_t length, float (*referenceFcn)(int* array, uint16_t length), uint16_t maxDiffPercent);