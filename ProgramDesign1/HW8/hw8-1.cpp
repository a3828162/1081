#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
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
   char ( *program )[ 100 ] = new char[ 500 ][ 100 ]();
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );
    for( int i=0; i<numLines; i++){
   		cout << program[i] << endl;
    }	
	
   char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ]();
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }
	for(int i=0; i<numLines; i++){
		cout << program[i] << endl;
	}
	cout << "----------" << endl;
	/*for(int i=0; i<numIdentifiers; i++){
		cout << identifiers[i] << endl;
	}*/
   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );
	delete []identifiers;
	delete []program;
	
	system( "pause" );
}

void load( char( *program )[ 100 ], int &numLines ){
    ifstream test( "test.cpp", ios::in );
    while( !test.eof()){
		test.getline(program[numLines], 100);
		numLines++;
    }	
}

void delComment( char sourceLine[] ){
	int size = strlen(sourceLine);

	if(sourceLine!=" "){
		for(int i=0; i<size; i++){
			if(sourceLine[i]-'/'==0 && sourceLine[i+1]-'/'==0){
				for(int j=i; j<size; j++){
					sourceLine[j] = ' ';
				}
				break;
			}
		}
	}
	
	cout << sourceLine << endl;
}

void delStrConsts( char sourceLine[] ){
	
	int size = strlen(sourceLine);
	int a=0, b=0;
	if(sourceLine!=" "){
		for(int i=0; i<size; i++){
			if(sourceLine[i]-'"'==0){
				a = i;
				break;
			}
		}
		for(int j=size-1; j>=0; j--){
			if(sourceLine[j]-'"'==0){
				b = j;
				break;
			}
		}
		cout << a << "    " << b << endl;
		if(a!=0 && b!=0){
			for(int i=a; i<=b; i++){
				sourceLine[i] = ' ';
			}
		}
	}	
}

void delCharConsts( char sourceLine[] ){
	int size = strlen(sourceLine);
	int a=0, b=0;
	if(sourceLine!=" "){
		for(int i=0; i<size; i++){
			if(sourceLine[i]-'\''==0){
				a = i;
				break;
			}
		}
		for(int j=size-1; j>=0; j--){
			if(sourceLine[j]-'\''==0){
				b = j;
				break;
			}
		}
		cout << a << "    " << b << endl;
		if(a!=0 && b!=0){
			for(int i=a; i<=b; i++){
				sourceLine[i] = ' ';
			}
		}
	}	
}

void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers ){
	int size = strlen(sourceLine);
	int start, end;
	int i=0;
	
		if (sourceLine=="")
        	return;
    	else{
        	for(int a=0; a<size; a++){
            	start=-1;
            	end=-1;
	            for(int  j=a; j<size; j++){
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
	            	int check=0;
	                for(int k=start; k<end; k++){
	                	identifiers[numIdentifiers][check] = sourceLine[k];
	                	check++;
					}
					numIdentifiers++;
					a= end;
	                //cout << re << endl;
	            }
        	}
    	}	
}

void store( char ( *identifiers )[ 32 ], int numIdentifiers ){
	
	int a;
    ofstream outFile("result1.txt", ios::out);

    if (!outFile){
        cout << "File could not be open!\n";
        exit(1);
    }

    for(a=0; a<numIdentifiers; a++){
        if (keyword(identifiers[a]) && duplicate(identifiers, a)){
            cout << identifiers[a] << endl;
            outFile << identifiers[a] << endl;
        }
    }
}	

bool keyword( char str[] ){
	
	/*int b=strlen(str);
	cout << str << endl;
	cout << b << endl;*/
	
    int a;
    int b=strlen(str);
    int c;
	
    for(a=0; a<sizeof(keywords)/sizeof(keywords[0]); a++){
        c=strlen(keywords[a]);
        if(b==c){
        	int d=0;
        	for(int i=0; i<b; i++){
        		if(str[i]-keywords[a][i]==0){
        			d++;
				}
			}
			if(d==b){
				return false;
			}
		}
    }
    return true;
    /*for(a=0; a<sizeof(keywords)/sizeof(keywords[0]); a++){
        if (str==keywords[a])
            return false;
    }
    return true;*/
}

bool duplicate( char ( *identifiers )[ 32 ], int pos ){

    int a;
    int b=strlen(identifiers[pos]);
    int c;
	
    for(a=0; a<pos; a++){
        c=strlen(identifiers[a]);
        if(b==c){
        	int d=0;
        	for(int i=0; i<b; i++){
        		if(identifiers[pos][i]-identifiers[a][i]==0){
        			d++;
				}
			}
			if(d==b){
				return false;
			}
		}
    }
    return true;

    /*int a;

    for(a=0; a<pos; a++){
        if (identifiers[pos]==identifiers[a])
            return false;
    }
    return true;*/
}

