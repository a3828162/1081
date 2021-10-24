#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int main() {

	int a;
	cin >> a;

	char** b;
	b = new char*[a]();
	for (int i = 0; i < a; i++)
		b[i] = new char[a]();

	int* c;
	c = new int[a]();

	for (int i = 0; i < a; i++) {
		cin >> b[i];
	}
	
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			if (b[i][j] == '-')
				continue;
			else if (b[i][j] == 'W')
				c[i] += 2;
			else if (b[i][j] == 'D')
				c[i] += 1;
			else if (b[i][j] == 'L')
				c[i] += 0;
		}
	}

	int w = 0, x = 0;

	for (int i = 0; i < a; i++) {
		if (c[i] > w) {
			w = c[i];
			x = i;
		}
	}

	int W = 0, D = 0, L=0;
	for (int j = 0; j < a; j++) {
		if (b[x][j] == '-')
			continue;
		else if (b[x][j] == 'W')
			W++;
		else if (b[x][j] == 'D')
			D++;
		else if (b[x][j] == 'L')
			L++;
	}

	cout << x + 1 << " " << c[x] << " " << W << " " << D << " " << L << endl;

	
	return 0;
}
