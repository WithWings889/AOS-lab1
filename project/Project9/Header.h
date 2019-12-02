#pragma once
#pragma optimize("", off)

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;


template <typename T> void Cycle(int N, T a, T b, T c)
{
	T d;
	for (int i = 0; i < N; ++i)
	{
		d = a;
		c = b;
		a = d;
		b = a;
		d = a;
		c = b;
	}
}

template <typename T> void Sum(int N, T a, T b, T c)
{
	T d;
	for (int i = 0; i < N; ++i)
	{
		d = a + b;
		a = b + c;
		b = d + b;
		c = a + c;
		d = a + b;
		a = b + c;
	}
}

template <typename T> void Multiplication(int N, T a, T b, T c)
{
	T d;
	for (int i = 0; i < N; ++i)
	{
		d = a * b;
		a = b * c;
		c = d * b;
		b = a * c;
		d = a * b;
		a = b * c;
	}
}

template <typename T> void Difference(int N, T a, T b, T c)
{
	T d;
	for (int i = 0; i < N; ++i)
	{
		d = a - b;
		a = b - c;
		b = d - b;
		c = a - c;
		d = a - b;
		a = b - c;
	}

}
template <typename T> void Division(int N, T a, T b, T c)
{
	T d;
	for (int i = 0; i < N; ++i)
	{
		d = a / b;
		c = c / b;
		a = d / b;
		d = a / b;
		d = a / b;
		c = c / b;
	}
}

template <typename T> double times(int N, void(*operation)(int N, T a, T b, T c), T a, T b, T c, double time_cycle = 0)
{
	chrono::time_point<std::chrono::system_clock> start, end;
	start = chrono::system_clock::now();
	operation(N, a, b, c);
	end = chrono::system_clock::now();
	double elapsed_seconds = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count()) *(double)1e-9;
	//cerr << elapsed_seconds << '\n';
	if (time_cycle == 0)
		return elapsed_seconds;
	else
		return (6.0*double(N) / (elapsed_seconds - time_cycle));
}

int Percent(double time_min, double mytime)
{
	return int(mytime * 100.0 / time_min);
}

template <typename T> void result(T a, T b, T c, int n, vector<double> &answer)
{
	double times_cycle = times(n, Cycle, a, b, c);
	answer.push_back(times(n, Sum, a, b, c, times_cycle));
	answer.push_back(times(n, Difference, a, b, c, times_cycle));
	answer.push_back(times(n, Multiplication, a, b, c, times_cycle));
	answer.push_back(times(n, Division, a, b, c, times_cycle));
}

string printX(int n)
{
	string x = "";
	for (int i = 0; i < n / 2; ++i)
		x = x + "X";
	return x;
}

void print(vector<double> &answer)
{
	double cur_min = *max_element(answer.begin(), answer.end());
	string print[5] = { "double", "float", "long", "char", "int" };
	cout << left;
	cout << setw(6) << "Oprtn" << setw(15) << "Type" << setw(20) << "Frequency" << setw(60) << "Diagram" << setw(4) << "Percent" << endl;
	for (int i = 0; i < 5; ++i)
	{
		int percent_sum = Percent(cur_min, answer[i * 4]);
		int percent_difference = Percent(cur_min, answer[i * 4 + 1]);
		int percent_multiplication = Percent(cur_min, answer[i * 4 + 2]);
		int percent_division = Percent(cur_min, answer[i * 4 + 3]);
		cout << setw(6) << "+" << setw(15) << print[i] << setw(20) << answer[i * 4] << setw(60) << printX(percent_sum) << setw(4) << percent_sum << "%" << endl;
		cout << setw(6) << "-" << setw(15) << print[i] << setw(20) << answer[i * 4 + 1] << setw(60) << printX(percent_difference) << setw(4) << percent_difference << "%" << endl;
		cout << setw(6) << "*" << setw(15) << print[i] << setw(20) << answer[i * 4 + 2] << setw(60) << printX(percent_multiplication) << setw(4) << percent_multiplication << "%" << endl;
		cout << setw(6) << "/" << setw(15) << print[i] << setw(20) << answer[i * 4 + 3] << setw(60) << printX(percent_division) << setw(4) << percent_division << "%" << endl;
	}
}