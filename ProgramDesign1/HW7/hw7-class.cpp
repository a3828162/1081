#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

const int numTestCases = 22;
const int arraySize = 200;
#include <string.h>
#include <stdlib.h>
// HugeInt class definition
class HugeInt
{
public:
   // enable user to input a positive huge integer
   void input( istream &inFile );

   // outputs elems[ hugeInt.size - 1 .. 0 ]
   void output( ostream &outFile );

   // a recursive function that outputs elems[ last .. 0 ]
   void recursiveOutput( ostream &outFile, int last );

   // returns true if and only if the specified huge integer is zero
   bool isZero();

   // return true if and only if current object == hugeInt2
   bool equal( HugeInt &hugeInt2 );

   // a recursive function that returns true if and only if
   // elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
   // provided that size == hugeInt2.size
   bool recursiveEqual( HugeInt &hugeInt2, int last );

   // return true if and only if current object < hugeInt2
   bool less( HugeInt &hugeInt2 );

   // a recursive function that returns true if and only if
   // elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
   // provided that size == hugeInt2.size
   bool recursiveLess( HugeInt &hugeInt2, int last );

   // request the current object to reduce its array to fit its size
   void shrink_to_fit();

   // sum = current object + adder
   void addition( HugeInt &adder, HugeInt &sum );

   // difference = current object - subtrahend
   // provided that the current object is greater than or equal to the subtrahend
   void subtraction( HugeInt &subtrahend, HugeInt &difference );

   // product = current object * multiplier
   void multiplication( HugeInt &multiplier, HugeInt &product );

   // quotient = current object / divisor; remainder = current object % divisor
   // provided that the divisor is not equal to 0
   void division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder );

   // left = current object; assignment
   void assign( HugeInt &left );

   // current object /= 10
   void divideByTen();

   void reset();

   int size = 1; // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ]();  // used to store a nonnegative integer, one digit per element
}; // end class HugeInt


// enable user to input a positive huge integer
void HugeInt::input( istream &inFile )
{
   char numericString[ 200 ];

   inFile >> numericString;

   size = strlen( numericString );
   delete[] elems;
   elems = new int[ size ];
   for( int i = 0; i < size; i++ )
      elems[ i ] = numericString[ size - i - 1 ] - '0';
}

// output the specified huge integer
void HugeInt::output( ostream &outFile )
{
   recursiveOutput( outFile, size - 1 );
   outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void HugeInt::recursiveOutput( ostream &outFile, int last )
{
 	if(last>=0){
		outFile << elems[last];
		return recursiveOutput( outFile , last-1);
	}
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero()
{
   if( size == 1 && elems[ 0 ] == 0 )
      return true;
   return false;
}

// return true if and only if current object == hugeInt2
bool HugeInt::equal( HugeInt &hugeInt2 )
{
   if( size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt2, size - 1 );
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveEqual( HugeInt &hugeInt2, int last )
{
    if (last>=0){
        if (elems[last] != hugeInt2.elems[last])
            return false;
    }
    else
        return true;

    return recursiveEqual(hugeInt2, last-1);
}

// returns true if and only if current object < hugeInt2
bool HugeInt::less( HugeInt &hugeInt2 )
{
   if( size < hugeInt2.size )
      return true;
   if( size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt2, size - 1 );
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveLess( HugeInt &hugeInt2, int last )
{
	if(elems[last]<hugeInt2.elems[last])
		return true;
	else if(elems[last]>hugeInt2.elems[last])
		return false;

	if(last>0){
        recursiveLess( hugeInt2, last - 1);
	}else{
	    return false;
	}
}

// request the current object to reduce its array to fit its size
void HugeInt::shrink_to_fit()
{
   int *buffer = new int[ size ];
   for( int i = 0; i < size; i++ )
      buffer[ i ] = elems[ i ];
   delete [] elems;
   elems = buffer;
}

// sum = current object + adder
void HugeInt::addition( HugeInt &adder, HugeInt &sum )
{
   sum.size = ( size >= adder.size ) ? size + 1 : adder.size + 1;

   delete[] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < size; i++ )
      sum.elems[ i ] = elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   for( int i = 0; i < sum.size - 1; i++ )
      if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.elems[ i ] -= 10; // reduce to 0-9
         sum.elems[ i + 1 ]++;
      }

   if( sum.elems[ sum.size - 1 ] == 0 )
   {
      sum.size--;
      sum.shrink_to_fit();
   }
}

// difference = current object - subtrahend
// provided that the current object is greater than or equal to the subtrahend
void HugeInt::subtraction( HugeInt &subtrahend, HugeInt &difference )
{
	difference.size = ( size >= subtrahend.size ) ? size : subtrahend.size ;

	delete[] difference.elems;
	difference.elems = new int[difference.size]();



    for( int i = 0; i < size; i++ )
    	difference.elems[ i ] = elems[ i ];


    for( int i = size; i < difference.size; i++ ){
    	difference.elems[ i ] = 0;
    }


	for( int i = 0; i < subtrahend.size; i++ )
    	difference.elems[ i ] -= subtrahend.elems[ i ];



    for( int i = 0; i < difference.size; i++ ){
       if( difference.elems[ i ] < 0 && i+1!=difference.size)
    	{
        	difference.elems[ i ] += 10;
        	difference.elems[ i + 1 ]--;
    	}

    }

	for(int i=difference.size; difference.elems[i-1]==0 && i-1>0;i--){
        difference.size--;
        difference.shrink_to_fit();
	}

}

// product = current object * multiplier
void HugeInt::multiplication( HugeInt &multiplier, HugeInt &product )
{
	product.size = size + multiplier.size;

   	delete[] product.elems;
   	product.elems = new int[ product.size ]();

    if( isZero( )){
        product.size = 1;
        product.elems[0] = 0;
        return;
    }
    if( multiplier.isZero()){
        product.size = 1;
        product.elems[0] = 0;
        return;
    }

	for( int i=0; i<product.size; i++)
		product.elems[i] = 0;

	for( int i=0; i<size; i++){
		for( int j=0; j<multiplier.size; j++){
			product.elems[i+j] += elems[i]*multiplier.elems[j];
		}
	}

	for( int i=0; i<product.size; i++){
		int j;
		for( j=product.elems[i]; j>9; j-=10){
			product.elems[i+1]++;
		}
		product.elems[i]=j;
	}

	for( int i=product.size; product.elems[i-1] == 0; i--){
        product.size--;
        product.shrink_to_fit();
	}
}

// quotient = current object / divisor; remainder = current object % divisor
// provided that the divisor is not equal to 0
void HugeInt::division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder )
{
   if( isZero( ) )
   {
    	quotient.reset();
        remainder.reset();
        quotient.size = 1;
        remainder.size = 1;
        quotient.elems[0] = 0;
        remainder.elems[0] = 0;
        return;
   }else if(equal( divisor )){
    	quotient.reset();
        remainder.reset();
        quotient.size = 1;
        quotient.elems[0] = 1;
        remainder.size = 1;
        remainder.elems[0] = 0;
        return;
   }else if(less( divisor )){
        quotient.size = 1;
        remainder.size = size;
        //delete[] quotient;
        //delete[] remainder;
        quotient.elems = new int[quotient.size]();
        remainder.elems = new int[remainder.size]();
        quotient.elems[0] = 0;
        for( int i=size-1; i>=0; i--)
            remainder.elems[i]=elems[i];
        return;
   }else{
	    int n;
		n = size-divisor.size;
		HugeInt buffer;
	    buffer.size = divisor.size+n;
	    buffer.elems= new int[ buffer.size ]();

	 	remainder.size = size;
	    //delete[] remainder;
	    remainder.elems = new int[remainder.size]();
	 	for(int i=0; i<remainder.size; i++){
			remainder.elems[i] = elems[i];
		}

		for(int i=0; i<n; i++)
	        buffer.elems[i] = 0;
		for(int i=divisor.size; i>0; i--){
			buffer.elems[n+i-1]=divisor.elems[i-1];
		}
		quotient.size = size-divisor.size;

		if(less( buffer )){
			buffer.divideByTen();
		}else{
			quotient.size++;
			quotient.shrink_to_fit();
		}
		HugeInt temp;
        temp.size=remainder.size;
		quotient.elems = new int[quotient.size]();
		for( int k=quotient.size-1; k>=0; k--){
			while(buffer.less(remainder) || buffer.equal(remainder)){
		        delete[] temp.elems;
		        temp.elems = new int[temp.size]();
		        remainder.subtraction( buffer, temp);
		        //delete[] remainder;
		        //remainder.elems = new int[temp.size]();
				//remainder.size = temp.size;
	            //for(int l=temp.size-1; l>=0; l--)
	               // remainder.elems[l] = temp.elems[l];
               //temp.assign(remainder);
		        //if (remainder.size==0)
                    //remainder.reset();
                temp.assign(remainder);
				quotient.elems[k]++;
		        if( remainder.isZero() ){
		            return;
		        }
			}

			buffer.divideByTen();
		}
		delete []buffer.elems;
		return;
	}

}

// left = current object; assignment
void HugeInt::assign( HugeInt &left )
{
   left.size = size;
   delete[] left.elems;
   left.elems = new int[ left.size ];
   for( int i = 0; i < left.size; i++ )
      left.elems[ i ] = elems[ i ];
}

// current object /= 10
void HugeInt::divideByTen()
{
   if( size == 1 )
      elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         elems[ i - 1 ] = elems[ i ];

      size--;
      elems[ size ] = 0;
      shrink_to_fit();
   }
}

void HugeInt::reset()
{
   size = 1;
   delete[] elems;
   elems = new int[ 1 ]();
}


void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
                                HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   hugeInt1.output( outFile );
   hugeInt2.output( outFile );

   hugeInt1.addition( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   hugeInt3.output( outFile );
   hugeInt3.reset();

   if( hugeInt1.less( hugeInt2 ) )
   {
      outFile << '-';
      hugeInt2.subtraction( hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      hugeInt3.output( outFile );
   }
   else
   {
      hugeInt1.subtraction( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      hugeInt3.output( outFile );
   }
   hugeInt3.reset();

   hugeInt1.multiplication( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   hugeInt3.output( outFile );
   hugeInt3.reset();

   if( hugeInt2.isZero() )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
      hugeInt1.division( hugeInt2, hugeInt3, hugeInt4 );
      hugeInt3.output( outFile );
      hugeInt4.output( outFile );
      hugeInt3.reset();
      hugeInt4.reset();
   }

   outFile << endl;
}

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   HugeInt hugeInt1;
   HugeInt hugeInt2;
   HugeInt hugeInt3;
   HugeInt hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      hugeInt1.input( inFile );
      hugeInt2.input( inFile );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      hugeInt1.reset();
      hugeInt2.reset();
   }

   delete[] hugeInt1.elems;
   delete[] hugeInt2.elems;
   delete[] hugeInt3.elems;
   delete[] hugeInt4.elems;

   inFile.close();
   outFile.close();

   system( "pause" );
}
