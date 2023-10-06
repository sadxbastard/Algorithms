#include <iostream>
#include <windows.h>
#include <cstdlib>
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
	int Intervals;
	int M;

	InitializerAndHandlerArray(const int _Size, const Type _Max, const Type _Min, const int _Intervals);
	~InitializerAndHandlerArray();

	// Check functions
	void PrintArray(const int _Size) const;
	bool CheckOrder(const int _Size) const;
	void PrintRuntime();


	// Filling an array with random values
	Type RandAB(const Type _Min, const Type _Max) const;
	void Rand(int Id, const int _Size);

	// Ordering an array
	void Decrease(int Id, const int _Size);
	void Increase(int Id, const int _Size);
	void Saw(int Id, const int _Size);
	void Quasi(int Id, const int _Size);
	void Stepwise(int Id, const int _Size);
	void Sinusoidal(int Id, const int _Size) const;

	// Sorting an array
	void Bubble(int Id, const int _Size);
	void ModifiedBubble(int Id, const int _Size); // using the index of the last exchange
	void QuickSortWrapper(const int _Size);
	void QuickSorting(const int Left, const int Right); // Hoare Sorting
	int QuickSortingPartition(const int Left, const int Right); // Auxiliary function for Hoare Sorting
	void ModifiedQuickSortWrapper(const int _Size);
	void ModifiedQuickSorting(const int Id, const int _Size); // An almost ordered sequence is sorted by inserts (with the size of the sections M = 10)
	void SortingByInserts(const int _Size);
};

int compare(const void* a, const void* b) {
	const double* objA = static_cast<const double*>(a);
	const double* objB = static_cast<const double*>(b);
	counter++;
	if (*objA < *objB) return -1;
	counter++;
	if (*objA > *objB) return 1;
	return 0;
}

template <typename Type>
InitializerAndHandlerArray<Type>::InitializerAndHandlerArray(const int _Size, const Type _Max, const Type _Min, const int _Intervals) {
	Size = _Size;
	/*Array = new Type[Size];*/
	Max = _Max;
	Min = _Min;
	Intervals = _Intervals;
	M = 10;
}

template <typename Type>
InitializerAndHandlerArray<Type>::~InitializerAndHandlerArray() {
	delete Array;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::PrintArray(const int _Size) const {
	for (int i = 0; i < _Size; i++)
		cout << i + 1 << ") " << Array[i] << endl;
}

template <typename Type>
bool InitializerAndHandlerArray<Type>::CheckOrder(const int _Size) const {
	for (int i = 0; i < _Size - 1; i++) {
		if (Array[i] > Array[i + 1])
			return false;
	}
	return true;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::PrintRuntime() {
	const int RatioStep = 10;
	const int Trials = 20;
	int Step = Size / RatioStep;
	Type* pointer;
	long long int FullCounter = 0;

	for (int N = Step; N <= Size; N += Step)
	{
		int i = 0;
		while(true){
			if (i >= Trials) {
				Array = new Type[1];
				break;
			}

			Max = 2 * N;
			Array = new Type[N];
			pointer = Array;

			//Increase(0, N);
			//Rand(0, N);
			//Decrease(0, N);
			Saw(0, N);

			//Bubble(0, N);
			//ModifiedBubble(0, N);
			//QuickSortWrapper(N);
			//ModifiedQuickSortWrapper(N);
			qsort(pointer, N, sizeof(Array[0]), compare);

			FullCounter += counter;
			counter = 0;
			delete[] Array;
			i++;
		}
		cout << N << " ";
		//cout << "Array sorted: " << (CheckOrder(N) ? "Yes" : "No") << endl;
		cout /*<< "Counter operations: "*/ << FullCounter / Trials << endl /*<< endl*/;
		//PrintArray(N);
	}
}

template <typename Type>
Type InitializerAndHandlerArray<Type>::RandAB(const Type _Min, const Type _Max) const{
	return (double)((rand() << 15) | rand()) / (RAND_MAX << 15 | RAND_MAX) * (_Max - _Min) + _Min;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Rand(int Id, const int _Size)
{
	for (; Id < _Size; Id++)
		Array[Id] = RandAB(Min, Max);
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Decrease(int Id, const int _Size)
{
	double step = (double(Min - Max)) / _Size;
	for (; Id < _Size; Id++)
		Array[Id] = step * Id + Max;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Increase(int Id, const int _Size)
{
	double step = (double(Max - Min)) / _Size;
	for (; Id < _Size; Id++)
		Array[Id] = step * Id + Min;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Saw(int Id, const int _Size)
{
	int Length = _Size / Intervals;
	int Remainder = _Size % Intervals;
	for (; Id < Intervals; Id++)
	{
		Increase(Id * Length, Length + Id * Length);
	}
	if (Remainder != 0)
	{
		Increase(_Size - Remainder, _Size);
	}
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Quasi(int Id, const int _Size)
{
	Increase(Id, _Size);
	int Length = _Size / Intervals;
	for (Id += Length; Id < _Size - 1; Id += Length)
	{
		Type temp = Array[Id];
		Array[Id] = Array[Id - 1];
		Array[Id - 1] = temp;
	}
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Stepwise(int Id, const int _Size)
{
	Type Step = Max / Intervals;
	int Length = _Size / Intervals;
	int Remainder = _Size % Intervals;
	for (; Id < Intervals; Id++)
	{
		Max = Min + Step;
		Rand(Id * Length, Length + Id * Length);
		Min += Step;
	}
	if (Length * Intervals < _Size)
	{
		Min += Step;
		Max = Min + Step;
		Rand(_Size - Remainder, _Size);
	}
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Sinusoidal(int Id, const int _Size) const
{
	int Length = _Size / Intervals;
	int Remainder = _Size % Intervals;
	for (; Id < Intervals; Id++)
	{
		Decrease(Id * Length, Id * Length + Length / 2);
		Increase(Id * Length + Length / 2, Length + Id * Length);
	}
	if (Remainder != 0)
	{
		Decrease(_Size - Remainder, _Size);
	}
}

template <typename Type>
void InitializerAndHandlerArray<Type>::Bubble(int Id, const int _Size) {
	for (; Id < _Size - 1; Id++)
		for (int j = Id + 1; j < _Size; j++) {
			counter++;
			if (Array[Id] > Array[j])
				swap(Array[Id], Array[j]);
		}
			
}

template <typename Type>
void InitializerAndHandlerArray<Type>::ModifiedBubble(int Id, const int _Size) {
	int IndexOfChanged, Low = 0;
	while (Low < _Size - 1) {
		for (IndexOfChanged = Id = _Size - 1; Id > Low; Id--) {
			counter++;
			if (Array[Id - 1] > Array[Id]) {
				swap(Array[Id], Array[Id - 1]);
				IndexOfChanged = Id;
			}
		}
		Low = IndexOfChanged;
	}
}

template <typename Type>
void InitializerAndHandlerArray<Type>::QuickSortWrapper(const int _Size){
	QuickSorting(0, _Size - 1);
}

template <typename Type>
void InitializerAndHandlerArray<Type>::QuickSorting(const int Left, const int Right){
	int PartitionIndex;
	if (Right - Left <= 0)
		return;
	PartitionIndex = QuickSortingPartition(Left, Right);
	QuickSorting(Left, PartitionIndex - 1);
	QuickSorting(PartitionIndex + 1, Right);
}

template <typename Type>
int InitializerAndHandlerArray<Type>::QuickSortingPartition(const int Left, const int Right) {
	Type V = Array[Right];
	int i = Left - 1;
	int j = Right;
	while (true) {
		while (V > Array[++i])
			counter++;
		while (V < Array[--j]) {
			counter++;
			if (j == Left)
				break;
		}
		counter++;
		if (i >= j)
			break;	
		swap(Array[i], Array[j]);
	}
	swap(Array[Right], Array[i]);
	return i;
}

template <typename Type>
void InitializerAndHandlerArray<Type>::ModifiedQuickSortWrapper(const int _Size) {
	QuickSorting(0, _Size - 1);
	SortingByInserts(_Size);
}

template <typename Type>
void InitializerAndHandlerArray<Type>::ModifiedQuickSorting(const int Left, const int Right) {
	int PartitionIndex;
	if (Right - Left <= M)
		return;
	swap(Array[(Left + Right) / 2], Array[Right - 1]);
	counter++;
	if (Array[Left] > Array[Right - 1])
		swap(Array[Left], Array[Right - 1]);
	counter++;
	if (Array[Left] > Array[Right])
		swap(Array[Left], Array[Right]);
	counter++;
	if (Array[Right - 1] > Array[Right])
		swap(Array[Right - 1], Array[Right]);
	PartitionIndex = QuickSortingPartition(Left + 1, Right - 1);
	ModifiedQuickSorting(Left, PartitionIndex - 1);
	ModifiedQuickSorting(PartitionIndex + 1, Right);
}

template <typename Type>
void InitializerAndHandlerArray<Type>::SortingByInserts(const int _Size) {
	int i, j;
	Type V;
	for (i = _Size - 1; i > 0; i--) {
		counter++;
		if (Array[i - 1] > Array[i])
			swap(Array[i], Array[i - 1]);
	}
	for (i = 2; i < _Size; i++) {
		V = Array[i];
		for (j = i; Array[j - 1] > V; j--) {
			counter++;
			Array[j] = Array[j - 1];
		}
		Array[j] = V;
	}
}

int main() {
	InitializerAndHandlerArray<double> Array(Number, 0, 0, 10); // (Size, Max, Min, Intervals)
	Array.PrintRuntime();
	return 0;
}