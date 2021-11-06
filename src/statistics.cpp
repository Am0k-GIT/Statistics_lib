#include <Arduino.h>
#include "statistics.h"

void swapValues(float& a, float& b) {
	float c = a;
	a = b;
	b = c;
}

void swapValues(int& a, int& b) {
	float c = a;
	a = b;
	b = c;
}

bool ascending(float a, float b)
{
	return a > b;
}

bool ascending(int a, int b)
{
	return a > b;
}

bool descending(float a, float b)
{
	return a < b;
}

bool descending(int a, int b)
{
	return a < b;
}

void copyArray(float* array, float* copy, uint16_t length)
{
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		copy[currentIndex] = array[currentIndex];
	}
}

void copyArray(int* array, int* copy, uint16_t length)
{
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		copy[currentIndex] = array[currentIndex];
	}
}

void sortArray(float* array, uint16_t length, bool (*comparisonFcn)(float, float))
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

void sortArray(int* array, uint16_t length, bool (*comparisonFcn)(int, int))
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

float averageValue(float* array, uint16_t length)
{
	float average = 0;
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		average += array[currentIndex];
	}
	return (average / length);
}

float averageValue(int* array, uint16_t length)
{
	float average = 0;
	for (uint16_t currentIndex = 0; currentIndex < length; currentIndex++)
	{
		average += array[currentIndex];
	}
	return (average / length);
}

float medianValue(float* array, uint16_t length)
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

float medianValue(int* array, uint16_t length)
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
		int* copy = new int[length];
		copyArray(array, copy, length);
		sortArray(copy, length, ascending);
		int result;
		while (currentIndex >= 0 && currentIndex < length)
		{
			int leftSum = 0;
			int rightSum = 0;
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

float filterValue(float* array, uint16_t length, float (*referenceFcn)(float* array, uint16_t length), uint16_t maxDiffPercent)
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

float filterValue(int* array, uint16_t length, float (*referenceFcn)(int* array, uint16_t length), uint16_t maxDiffPercent)
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