#include <iostream>
#include <windows.h>

using namespace std;


template<typename T>
class FillingArray {
public:
	T *Array;
	int Size;
	T Max;
	T Min;
	int Intervals;

	T RandAB(T _Min, T _Max); // ability to generate a number from a larger range
	void Rand(int Id, int _Size); // fills the array with random numbers
	void Decrease(int Id, int _Size); // sorts the array from max to min
	void Increase(int Id, int _Size); // sorts the array from min to max
	void Saw();
	void Quasi();
	void Stepwise();
	void Sinusoidal();
};

template<typename T>
T FillingArray<T>::RandAB(T _Min, T _Max) {
	return (T)((rand() << 15) | rand()) / (RAND_MAX << 15 | RAND_MAX) * (_Max - _Min) + _Min;
}

template<typename T>
void FillingArray<T>::Rand(int Id, int _Size)
{
	for (; Id < _Size; Id++)
		Array[Id] = RandAB(Min, Max);
}

template<typename T>
void FillingArray<T>::Decrease(int Id, int _Size)
{
	double step = (double(Min - Max)) / _Size;
	for (; Id < _Size; Id++)
		Array[Id] = step * Id + Max;
}

template<typename T>
void FillingArray<T>::Increase(int Id, int _Size)
{
	double step = (double(Max - Min)) / _Size;
	for (; Id < _Size; Id++)
		Array[Id] = step * Id + Min;
}

template<typename T>
void FillingArray<T>::Saw()
{
	int Length = Size / Intervals;
	int Remainder = Size % Intervals;
	for (int i = 0; i < Intervals; i++)
	{
		Rand(i * Length, Length + i * Length);
		Increase(i * Length, Length + i * Length);
	}
	if (Remainder != 0)
	{
		Rand(Size - Remainder, Size);
		Increase(Size - Remainder, Size);
	}
}

template<typename T>
void FillingArray<T>::Quasi()
{
	Rand(0, Size);
	Increase(0, Size);
	int Length = Size / Intervals;
	T temp;
	for (int i = Length; i < Size; i += Length)
	{
		temp = Array[i];
		Array[i] = Array[i - 1];
		Array[i - 1] = temp;
	}
}

template<typename T>
void FillingArray<T>::Stepwise()
{
	T Step = Max / Intervals;
	int Length = Size / Intervals;
	int Remainder = Size % Intervals;
	for (int i = 0; i < Intervals; i++)
	{
		Max = Min + Step;
		Rand(i * Length, Length + i * Length);
		Min += Step;
	}
	if (Length * Intervals < Size)
	{
		Min += Step;
		Max = Min + Step;
		Rand(Size - Remainder, Size);
	}
}

template<typename T>
void FillingArray<T>::Sinusoidal()
{
	int Length = Size / Intervals;
	int Remainder = Size % Intervals;
	for(int i = 0; i < Intervals; i++)
	{
		Rand(i * Length, Length + i * Length);
		Decrease(i * Length, i * Length + Length / 2);
		Increase(i * Length + Length / 2, Length + i * Length);
	}
	if(Remainder != 0)
	{
		Rand(Size - Remainder, Size);
		Decrease(Size - Remainder, Size);
	}
}

int main() {
	FillingArray<int> Array;

	Array.Size = 100000000;
	Array.Array = new int[Array.Size];
	int Step = Array.Size / 10;
	int t1, t2, T = 0;
	int Trials = 10;

	Array.Min = 0;

	for(int N = Step; N <= Array.Size; N += Step)
	{
		T = 0;
		for (int i = 0; i < Trials; i++)
		{
			t1 = GetTickCount();
			Array.Max = 2 * N;
			Array.Rand(0, N);
			t2 = GetTickCount();
			T += (t2 - t1);
		}
		cout << N << " " << T / Trials << endl;
	}

	//for (int N = Step; N <= Array.Size; N += Step)
	//{
	//	//T = 0;
	//	for (int i = 0; i < Trials; i++)
	//	{
	//		t1 = GetTickCount();
	//		Array.Max = 2 * N;
	//		Array.Rand(0, N);
	//		t2 = GetTickCount();
	//	}
	//	cout << N << " " << t2 - t1 << endl;
	//}

	/*Array.Rand(0, Array.Size);
	Array.Decrease(0, Array.Size);

	Array.Rand(0, Array.Size);
	Array.Increase(0, Array.Size);

	Array.Saw();

	Array.Quasi();

	Array.Stepwise();

	Array.Sinusoidal();*/

	/*cout << "Array: " << endl;
	for (int i = 0; i < Array.Size; i++) {
		cout << i + 1 << ") " << Array.Array[i] << endl;
	}*/
	delete Array.Array;


	/*Array.Min = 0;
	Array.Max = 20;
	Array.Intervals = 5;*/

	
	return 0;
}
