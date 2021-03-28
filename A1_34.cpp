#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

float mean(int ar[], int size);
float variance(int arr[], int size);
float mean_abs_dev(int arr[], int size);

int main(int argc, char* argv[]) 
{
	int size;
	int A[50000];
	cin >> size;
	for (int i = 0; i < size; i++)
		cin >> A[i];


	float var = variance(A, size);
	float sd = sqrt(var);
	float mad = mean_abs_dev(A, size);


	ofstream outfile("outfile.txt");
	if (outfile.is_open())
	{
		outfile << "Var = " << var << endl;
		outfile << "Stdev = " << sd << endl;
		outfile << "MAD = " << mad << endl;
		outfile.close();
	}
	else cout << "Unable to open file";
}

float mean(int ar[], int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++)
		sum += ar[i];
	return (sum / size);
}


float variance(int arr[], int size)
{
	float m = mean(arr, size);
	float s = 0;
	for (int i = 0; i < size; i++)
	{
		s += pow(arr[i] - m, 2);
	}
	return (s / (size - 1) );
}

float mean_abs_dev(int arr[], int size)
{
	float m = mean(arr, size);
	float s = 0;
	for (int i = 0; i < size; i++)
	{
		s += abs(arr[i] - m);
	}
	return (s / size);
}