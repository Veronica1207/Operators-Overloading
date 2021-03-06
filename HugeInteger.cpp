//HugeInt class definitions
// Veronica
//2021-04-21

#include "HugeInteger.h"

#include <iostream>
#include<iomanip>
using namespace std;

// ctor converts a long long into a HugeInteger
HugeInteger::HugeInteger( long long value )
{
	// set all MaxDigit digits to zero to start
	this->negative = false;
	if (value < 0LL){ // 0LL is constant literal 0 of type long long
		this->negative = true;
		value = - value; // make the value positive	                
	}

	for( unsigned int i = 0; i < hugeInt.size(); i++ )
	{
		this->hugeInt[i] = 0;
	}

	// convert individual digits of input value into a HugeInteger
	for( unsigned int j = hugeInt.size()-1; j >= 0 && value != 0LL; j-- )
	{
		this->hugeInt[j] = value % 10;
		value /= 10;
	}

	// test to make sure that HugeInteger was able to contain value

	if (value != 0LL){
		*this = 0LL; // set to -0, to signal overflow
	    this->negative = true; //   Possibly should increase value assigned
	}                          //   to MaxDigit to fix this problem.
}

// converts string into a HugeInteger object
HugeInteger::HugeInteger( const char *str )
{
	this->input( str ); //See HugeInteger::input() method below
}

// converts string into HugeInteger and then invokes
//    HugeInteger::addInto(const HugeInteger & )
HugeInteger HugeInteger::operator +(const char* str) const
{
	HugeInteger temp = *this;
	return temp += HugeInteger(str);
}

// converts long long into HugeInteger and then invokes
//    HugeInteger::addInto(const HugeInteger & )
HugeInteger HugeInteger::operator +( long long value ) const
{
	HugeInteger temp = *this;
	return temp += HugeInteger( value );
}

// Adds into the HugeInteger pointed to by the "this" pointer 
//   the HugeInteger op.
//   Then the calculated result is returned
HugeInteger& HugeInteger::operator += (const HugeInteger& op)
{
	// if the signs of the 2 numbers are opposites, we need to do subtraction
	//     remember that x + y  ==  x - (-y)
	if ((this->negative && !(op.negative)) || (!(this->negative) && op.negative)){
		return *this -= (-op);
	}

	// NOTE: From here on, we know the two operands are the same sign

	int carry = 0;
	for (int i = hugeInt.size() - 1; i >= 0; i-- )
	{
		this->hugeInt[i] = this->hugeInt[i] + op.hugeInt[i] + carry;
		if (this->hugeInt[i] > 9 ){
			this->hugeInt[i] -= 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}

	// test for overflow
	if (carry == 1){
		*this = 0LL; // just set to -0 (LL is for type long long)
		this->negative = true;  // to signal that an overflow occurred
	}

	return *this;
}

// converts string into HugeInteger and then invokes
//    HugeInteger::subInto(const HugeInteger & )
HugeInteger HugeInteger::operator -( const char *str ) const
{
	HugeInteger temp = *this;
	return temp -= HugeInteger( str );
}

// converts long long into HugeInteger and then invokes
//    HugeInteger::subInto(const HugeInteger & )
HugeInteger HugeInteger::operator -( long long value ) const
{
	HugeInteger temp = *this;
	return temp -= HugeInteger( value );
}

// Subracts from the HugeInteger pointed to by the "this" pointer
//   the HugeInteger op
//   Then the calculated value is returned.
HugeInteger & HugeInteger::operator -=( const HugeInteger &op )
{
	// if the signs of the 2 numbers are opposites, we need to do addition
	//     remember that x - y  ==  x + (-y)
	if ((this->negative && !(op.negative)) || (!(this->negative) && op.negative)){
		return *this += (-op);
	}

	// NOTE: From here on, we know the two operands are the same sign

	HugeInteger bigger, smaller;  // used to make code easier to understand

	if (*this == op){ // Are the values equal ?
		*this = 0LL;             // then just return 0
		this->negative = false;
		return *this;

	} else if ( (~op) < (~(*this))){ // is magnitude of LHS > RHS

		bigger = *this;
		smaller = op;

	} else { // magnitude of RHS > LHS

		smaller = *this;
		bigger = op;
		*this = -(*this); // result needs to be negated
	}

	// subtract smaller (in magnitude) from biggger (in magnitude)
	int borrow = 0;
	short top, bottom, result;
	for ( int i = hugeInt.size()-1; i >= 0; i-- )
	{
		top = bigger.hugeInt[i];
		bottom = smaller.hugeInt[i];

		if (borrow == 1)
		{
			top -= 1;
			borrow = 0;
		}

		result  = top-bottom;
		if ( result < 0) //if true, we need to borrow
		{
			this->hugeInt[i] = (10+top)-bottom; // or result + 10;
			borrow = 1;
		}
		else
		{
			this->hugeInt[i] = result;
		}
	}

	return *this;
}

HugeInteger HugeInteger::operator -(void) const
{
	HugeInteger temp = *this;
	temp.negative = !temp.negative;
	return temp;
}

// computes and returns absolute value of operand
HugeInteger HugeInteger::operator ~(void) const
{
	HugeInteger temp = *this;
	temp.negative = false;
	return temp;
}

bool HugeInteger::operator ==( const HugeInteger &op ) const
{
	if (this->negative != op.negative){  // if not the same sign
		return false;                    //   they are not equal
	}

	for( unsigned int i = 0; i < hugeInt.size(); i++ )
	{
		if (this->hugeInt[i] != op.hugeInt[i])
		{
			return false;
		}
	}
	return true;
}

bool HugeInteger::operator <( const HugeInteger &op ) const
{
	if (this->negative && !(op.negative)){ // if LHS < 0, and RHS is not < 0
		return true;  // then LHS must be less than RHS
	}

	if (!(this->negative) && op.negative){ // if LHS >= 0, and RHS < 0
		return false;  // then LHS must NOT be less than RHS
	}

	// NOTE: From here on, we know the two operands are the same sign
	for(unsigned int i = 0; i < hugeInt.size(); i++ )
	{
		if (this->hugeInt[i] < op.hugeInt[i])
		{
			if ( !(this->negative)){ // if both numbers are positive
				return true;
			}
			else { // if both numbers are negative
				return false;
			}
		}
		else if (this->hugeInt[i] > op.hugeInt[i])
		{
			if ( !(this->negative)){ // if both numbers are positive
				return false;
			}
			else { // if both numbers are negative
				return true;
			}
		}
	}
	return false;
}

// Is_Zero operator
bool HugeInteger::operator !()const
{
	for (int i = hugeInt.size()-1; i >= 0; --i)
	{
		if ( this->hugeInt[ i ] != 0 )
		{
			return false;
		}
	}
	return true;
}


//prefix increment operator
HugeInteger& HugeInteger::operator++() {
	*this += 1;
	return *this;
}


//postfix increment operator
HugeInteger HugeInteger::operator++(int) {
	HugeInteger temp = *this;
	*this += 1;
	return temp;
}


//prefix decrement operator
HugeInteger& HugeInteger::operator--() {
	*this -= 1;
	return *this;
}


//postfix decrement operator
HugeInteger HugeInteger::operator--(int) {
	HugeInteger temp = *this;
	*this -= 1;
	return temp;
}


// overload typecast to double
HugeInteger::operator double(void)const {

	double temp = 0;
	
	for (int i = 0; i < hugeInt.size(); ++i) {
		temp *= 10;
		temp += hugeInt[i];			
	}

	if (negative) {
		return -(temp);
	}
	
	return temp;
	
}


void HugeInteger::input( const char *str )
{
	// assume positive for now
	this->negative = false;

	// init. to all zeros first
	for( unsigned int i = 0; i < hugeInt.size(); i++ )
	{
		this->hugeInt[i] = 0;
	}

	int len = static_cast<int>(strlen( str ));
	int k = 0;

	// if sign part of string, we need to process
	// if + sign, we ignore since we start with assumption that 
	//     input string represents a positive number
	if ((str[k] == '-') || (str[k] == '+')){ 
		if (str[k] == '-'){ // if negative, set negative member to true
			this->negative = true;
		}

		++k; // go to next char in string "str"
		--len; // length of number is one less
	}
		
	for( unsigned int j = hugeInt.size() - len; j < hugeInt.size(); j++, k++ )
	{
		if (isdigit(str[k])){
			this->hugeInt[j] = str[k] - '0';
		}
		else  // a problem with the string input !!!
		{
			*this = 0LL; // just set to -0 (LL is for type long long)
			this->negative = true;  // to signal there was a problem
			break;     //   and go home
		}
	}
}

//overloads the "<<" operator through a global friend function, NOT inline
std::ostream& operator << (std::ostream& output, const HugeInteger& object) {
	// find first non-zero digit
	unsigned int i = 0;
	while (i < object.hugeInt.size()) {
		if (object.hugeInt[i] != 0) {
			break;
		}
		++i;
	}

	// if all zeros, just output a single 0
	if (i == object.hugeInt.size())
	{
		output << "0";
		return output;
	}

	// check if we need to ouput a negative sign
	if (object.negative) {
		output << '-';
	}

	// output remaining digits
	for (; i < object.hugeInt.size(); ++i)
	{
		output << static_cast<short> (object.hugeInt[i]);
	}

	return output;
}

//overloads the ">>" operator through a global friend function, NOT inline
std::istream& operator >> (std::istream& input, HugeInteger& object) {
	char input_string[1002];  // assume user never enters in a 
	//   number > 1000 digits
	input >> input_string;
	object.input(input_string);
	return input;
}


