#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( string *program, int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier( string &sourceLine );

// stores all non-keyword strings in the array identifiers into a text file
void store( string *identifiers, int numIdentifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( string *identifiers, int pos );

const string keywords[] = { "auto", "break", "case", "char", "const",
                            "continue", "default", "define","do", "double",
                            "else", "enum", "extern", "float", "for",
                            "goto", "if", "int", "long", "register",
                            "return", "short", "signed", "sizeof",
                            "static", "struct", "switch", "typedef",
                            "union", "unsigned", "void", "volatile",
                            "while", "bool", "catch", "class",
                            "const_cast", "delete", "dynamic_cast",
                            "explicit", "false", "friend", "inline",
                            "mutable", "namespace", "new", "operator",
                            "private", "protected", "public",
                            "reinterpret_cast", "static_cast", "template",
                            "this", "throw", "true", "try", "typeid",
                            "typename", "using", "virtual", "include" };


int main()
{
   string *program = new string[ 500 ]();
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );
	cout << numLines;
	for(int i=0; i<numLines; i++){
		cout << program[i] << endl;
	}
   string *identifiers = new string[ 500 ]();
   string firstIdentifier;
   string null;
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]
	
      // extracts all identifiers from program[ i ], and put them into the array identifiers
      while( ( firstIdentifier = delFirstIdentifier( program[ i ] ) ) != null ){
         identifiers[ numIdentifiers ] = firstIdentifier;
         //cout << identifiers[ numIdentifiers ] << endl;
         numIdentifiers++;
     }
   }

	/*for(int i=0; i<102; i++){
		cout << program[i] << endl;
	}*/
	cout << numIdentifiers << endl;
	cout << "-------" << endl;
	cout << identifiers[2] << endl;
	cout << "-------" << endl;
    //stores all non-keyword strings in the array identifiers into a text file
    store( identifiers, numIdentifiers );
	delete []program;
	delete []identifiers;
	system( "pause" );
}

void load( string *program, int &numLines ){
    ifstream test( "test.cpp", ios::in );
    while( !test.eof()){
		getline(test, program[numLines]);
		numLines++;
    }
}

void delComment( string &sourceLine ){
	if(sourceLine!=" "){
		for(int i=0; i<sourceLine.size(); i++){
			if(sourceLine[i]-'/'==0 && sourceLine[i+1]-'/'==0){
				sourceLine.erase(sourceLine.begin()+i,sourceLine.end());
				break;
			}
		}
	}
}

void delStrConsts( string &sourceLine ){
	int a=0, b=0;
	if(sourceLine!=" "){
		for(int i=0; i<sourceLine.size(); i++){
			if(sourceLine[i]-'"'==0){
				a = i;
				break;
			}
		}
		for(int j=sourceLine.size()-1; j>=0; j--){
			if(sourceLine[j]-'"'==0){
				b = j;
				break;
			}
		}
		//cout << a << "    " << b << endl;
		if(a!=0 && b!=0){
			sourceLine.erase(sourceLine.begin()+a-1, sourceLine.begin()+b+1);
		}
	}
}

void delCharConsts( string &sourceLine ){
	int a=0, b=0;
	if(sourceLine!=" "){
		for(int i=0; i<sourceLine.size(); i++){
			if(sourceLine[i]-' \' '==0){
				a = i;
				break;
			}
		}
		for(int j=sourceLine.size()-1; j>=0; j--){
			if(sourceLine[j]-' \' '==0){
				b = j;
				break;
			}
		}
		if(a!=0 && b!=0){
			sourceLine.erase(sourceLine.begin()+a-1, sourceLine.begin()+b+1);
		}
	}
}

string delFirstIdentifier( string &sourceLine )
{
    int start, end;

    if (sourceLine=="")
        return sourceLine;
    else{
        for(int i=0; i<sourceLine.size(); i++){
            start=-1;
            end=-1;
            for(int j=i; j<sourceLine.size(); j++){
                if(sourceLine[j]=='_' || (sourceLine[j]>='a'&&sourceLine[j]<='z') || (sourceLine[j]>='A'&&sourceLine[j]<='Z')){
                    if (start==-1)
                        start=j;
                }
                else if(sourceLine[j]=='_' || (sourceLine[j]>='0'&&sourceLine[j]<='9') || (sourceLine[j]>='a'&&sourceLine[j]<='z') || (sourceLine[j]>='A'&&sourceLine[j]<='Z'))
                    continue;
                else{
                    if (start!=-1)
                        end=j;
                    break;
                }
            }

            if (start!=-1 && end!=-1){
                string re(sourceLine.begin()+start, sourceLine.begin()+end);
                sourceLine.erase(sourceLine.begin()+start, sourceLine.begin()+end);
                //cout << re << endl;
                return re;
            }
        }
        return "";
    }

}

void store( string *identifiers, int numIdentifiers )
{
	int a;
    ofstream outFile("result2.txt", ios::out);

    if (!outFile){
        cout << "File could not be open!\n";
        exit(1);
    }

    for(a=0; a<numIdentifiers; a++){
        if (!keyword(identifiers[a]) && !duplicate(identifiers, a)){
            cout << identifiers[a] << endl;
            outFile << identifiers[a] << endl;
        }
    }
}

bool keyword( string str )
{
    int a;

    for(a=0; a<sizeof(keywords)/sizeof(keywords[0]); a++){
        if (str==keywords[a])
            return true;
    }
    return false;
}

bool duplicate( string *identifiers, int pos )
{
    int a;

    for(a=0; a<pos; a++){
        if (identifiers[pos]==identifiers[a])
            return true;
    }
    return false;
}
