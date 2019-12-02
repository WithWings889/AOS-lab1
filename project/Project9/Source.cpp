#include "Header.h"

int main()
{
	int n1, n2, n3;
	ifstream fin("Number.txt");
	fin >> n1 >> n2 >> n3;
	vector<double> answer;
	result((double)11.0, (double)7.0, (double)3.0, n1, answer);
	result((float)11.0, (float)7.0, (float)3.0, n1, answer);
	result((long)11, (long)7, (long)3, n2, answer);
	result('a', 'b', 'c', n3, answer);
	result((int)11, (int)7, (int)3, n2, answer);

	print(answer);

	system("pause");
}
