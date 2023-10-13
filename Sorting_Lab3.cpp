#include <iostream>
#include <cmath>
#define Number 1000000

using namespace std;

long long int counter = 0;

template <typename Type>
class InitializerAndHandlerArray {
public:
	Type* Array;
	int Size;
	Type Max;
	Type Min;

	InitializerAndHandlerArray(const int _Size, const Type _Max, const Type _Min);
	~InitializerAndHandlerArray();

	void PrintResults();

	// Filling an array with random values
	Type RandAB(const Type _Min, const Type _Max) const;
	void Rand(const int _Size);
	void Increase(const int _Size);

	// Searching for an element by key
	int SequentialSearch(int id, const int _Size, const int key);
	int SingleLevelJumpSearch(const int _Size, const int key);
	int BinarySearch(const int _Size, const int key);
};


template <typename Type>
InitializerAndHandlerArray<Type>::InitializerAndHandlerArray(const int _Size, const Type _Max, const Type _Min) {
	Size = _Size;
	Max = _Max;
	Min = _Min;
}

template <typename Type>
InitializerAndHandlerArray<Type>::~InitializerAndHandlerArray() {
	delete Array;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::PrintResults() {
	const int Trials = 100;
	int Step = Size / 10;
	int key, ans;

	for (int N = Step; N <= Size; N += Step)
	{
		int i = 0;
		while (true) {
			if (i >= Trials) {
				Array = new Type[1];
				break;
			}

			Max = 2 * N;
			Array = new Type[N];

			//Rand(N);
			//Increase(N);

			//key = Array[RandAB(0, N)];
			//key = Array[RandAB(0, N)] + 1;
			
			//SequentialSearch(0, N, key);
			//SingleLevelJumpSearch(N, key);
			//BinarySearch(N, key);
			
			delete[] Array;
			i++;
		}
		cout << N << " " << counter / Trials << " " << endl;
		counter = 0;
	}
}

template <typename Type>
Type InitializerAndHandlerArray<Type>::RandAB(const Type _Min, const Type _Max) const {
	return (double)((rand() << 15) | rand()) / (RAND_MAX << 15 | RAND_MAX) * (_Max - _Min) + _Min;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Rand(const int _Size)
{
	for (int i = 0; i < _Size; i++)
		Array[i] = RandAB(Min, Max);
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Increase(const int _Size)
{

	double step = (double(Max - Min)) / _Size;
	for (int i = 0; i < _Size; i++)
		Array[i] = step * i + Min;
}

template <typename Type>
int InitializerAndHandlerArray<Type>::SequentialSearch(int id, const int _Size, const int key) {
	for (; id < _Size; id++) {
		counter++;
		if (key == Array[id])
			return id;
	}
	return -1;
}

template <typename Type>
int InitializerAndHandlerArray<Type>::SingleLevelJumpSearch(const int _Size, const int key) {
	int step = (int)(sqrt(_Size)); 
	int prev = 0;
	counter++;
	while (Array[min(step, _Size) - 1] < key) {
		prev = step;
		step += (int)(sqrt(_Size));
		counter++;
		if (prev >= _Size) {
			return -1;
		}
	}
	counter++;
	while (Array[prev] < key) {
		prev++;
		counter++;
		if (prev == min(step, _Size)) {
			return -1;
		}
	}
	counter++;
	if (Array[prev] == key) {
		return prev;
	}
	return -1;
}

template <typename Type>
int InitializerAndHandlerArray<Type>::BinarySearch(const int _Size, const int key) {
	int left = 0, right = _Size - 1, pos = right / 2;
	counter++;
	for (; left <= right; pos = (left + right) / 2) {
		counter++;
		if (key < Array[pos])
			right = pos - 1;
		else {
			counter++;
			if (key > Array[pos])
				left = pos + 1;
			else return pos;
		}
	}
	return -1;
}

int main() {
	InitializerAndHandlerArray<int> Array(Number, 0, 0); // (Size, Max, Min)
	Array.PrintResults();
	return 0;
}
