#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace::std;

 // reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< string > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier( string &sourceLine );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< string > &identifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< string > &identifiers, int pos );

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
   vector< string > program;

   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );
	for(int i=0; i<102; i++){
		cout << program[i] << endl;
	}
   vector< string > identifiers;
   string firstIdentifier;
   string null;

   for( unsigned int i = 0; i < program.size(); i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      // extracts all identifiers from program[ i ], and put them into the vector identifiers
      while( ( firstIdentifier = delFirstIdentifier( program[ i ] ) ) != null )
         identifiers.push_back( firstIdentifier );
   }
	for(int i=0; i<102; i++){
		cout << program[i] << endl;
	}
	
	/*for(int i=0; i<identifiers.size(); i++){
		cout << identifiers[i] << endl;
	}
	cout << "----------" << endl;*/
   // stores all non-keyword strings in the vector identifiers into a text file
   store( identifiers );

	system( "pause" );
}

void load( vector< string > &program ){
    ifstream test( "test.cpp", ios::in );
	char in[100];
    while( !test.eof()){
		test.getline( in, 100);
		program.push_back(in);
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
		cout << a << "    " << b << endl;
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
    int a, b, start, end;

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

void store( vector< string > &identifiers )
{
    int a, b;
    ofstream outFile("result3.txt", ios::out);

    if (!outFile){
        cout << "File could not be open!\n";
        exit(1);
    }

    for(a=0; a<identifiers.size(); a++){
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

bool duplicate( vector< string > &identifiers, int pos )
{
    int a;

    for(a=0; a<pos; a++){
        if (identifiers[pos]==identifiers[a])
            return true;
    }
    return false;
}

