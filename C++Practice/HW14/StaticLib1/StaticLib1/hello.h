#ifndef HELLO_H
#define HELLO_H
#include <iostream>
#define MAXWORDLENGTH 255

struct dictionary {
	char word[MAXWORDLENGTH];
	unsigned int count;
};
using namespace std;
bool change(dictionary a, dictionary b);
void countnumber();
#endif
