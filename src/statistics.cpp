#include <Arduino.h>
#include "statistics.h"

template <typename T>
void swapValues(T& a, T& b) 
{
	T c = a;
	a = b;
	b = c;
}

template <typename T>
bool ascending(T a, T b)
{
	return a > b;
}

template <typename T>
bool descending(T a, T b)
{
	return a < b;
}

template <typename T>
void copyArray(T* array, T* copy, uint16_t length)
{
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		copy[currentIndex] = array[currentIndex];
	}
}

template <typename T>
void sortArray(T* array, uint16_t length, bool (*comparisonFcn)(T, T))
{
	for (uint16_t startIndex = 0; startIndex < length; ++startIndex)
	{
		uint16_t bestIndex = startIndex;
		for (uint16_t currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			if (comparisonFcn(array[bestIndex], array[currentIndex]))
				bestIndex = currentIndex;
		}
		swapValues(array[startIndex], array[bestIndex]);
	}
}

template <typename T>
float averageValue(T* array, uint16_t length)
{
	float average = 0;
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		average += array[currentIndex];
	}
	return (average / length);
}

template <typename T>
float medianValue(T* array, uint16_t length)
{
	float diffValue = 0;
	float newDiffValue = 0;
	uint16_t currentIndex = length / 2;
	uint16_t medianIndex = currentIndex;
	if (length < 3)
	{
		return averageValue(array, length);
	}
	else
	{
		float* copy = new float[length];
		copyArray(array, copy, length);
		sortArray(copy, length, ascending);
		float result;
		while (currentIndex >= 0 && currentIndex < length)
		{
			float leftSum = 0;
			float rightSum = 0;
			for (uint16_t leftIndex = 0; leftIndex < currentIndex; leftIndex++)
			{
				leftSum += copy[currentIndex] - copy[leftIndex];
			}
			for (uint16_t rightIndex = currentIndex + 1; rightIndex < length; rightIndex++)
			{
				rightSum += copy[rightIndex] - copy[currentIndex];
			}
			newDiffValue = rightSum - leftSum;
			if (newDiffValue == 0)
			{
				result = copy[currentIndex];
				delete[] copy;
				return (result);
			}
			if (newDiffValue + diffValue == 0)
			{
				result = copy[medianIndex];
				delete[] copy;
				return (result);
			}
			if (newDiffValue < 0)
			{
				if (abs(newDiffValue) <= abs(diffValue) || diffValue == 0)
				{
					medianIndex = currentIndex;
					currentIndex--;
					diffValue = newDiffValue;
				}
				else
				{
					result = copy[medianIndex];
					delete[] copy;
					return (result);
				}
			}
			else
			{
				if (newDiffValue <= abs(diffValue) || diffValue == 0)
				{
					medianIndex = currentIndex;
					currentIndex++;
					diffValue = newDiffValue;
				}
				else
				{
					result = copy[medianIndex];
					delete[] copy;
					return (result);
				}
			}
		}
		delete[] copy;
		return 0;
	}
}

template <typename T>
float filterValue(T* array, uint16_t length, float (*referenceFcn)(T* array, uint16_t length), uint16_t maxDiffPercent)
{
	float summ = 0;
	uint16_t members = 0;
	float referenceData = referenceFcn(array, length);
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		float diff = abs(array[currentIndex] - referenceData);
		if (diff < referenceData * maxDiffPercent / 100)
		{
			summ += array[currentIndex];
			members++;
		}
	}
	if (members != 0)
		return (summ / members);
	else
		return referenceData;
}