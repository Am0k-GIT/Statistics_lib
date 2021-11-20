// Библиотека для статистической обработки массивов данных

#pragma once

#include <Arduino.h>

template <typename T>
void swapValues(T& a, T& b);                                                   // меняет местами значения

template <typename T>
bool ascending(T a, T b);                                                      // параметр сортировки по возрастанию

template <typename T>
bool descending(T a, T b);                                                     // параметр сортировки по убыванию

template <typename T>
void copyArray(T* array, T* copy, uint16_t length);                            // создание копии массива

template <typename T>
void sortArray(T* array, uint16_t length, bool (*comparisonFcn)(T, T));        // сортировка массива

template <typename T>
float averageValue(T* array, uint16_t length);                                 // нахождение усредненного значения в массиве

template <typename T>
float medianValue(T* array, uint16_t length);                                  // нахождение медианного значения в массиве

template <typename T>
float filterValue(T* array, uint16_t length, float (*referenceFcn)(T* array, uint16_t length), uint16_t maxDiffPercent);       // нахождение отфильтрованного значения