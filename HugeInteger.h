
// HugeInteger class declaration.
//Veronica 
//2021-04-21

#include <array>
#include <iostream>

class HugeInteger
{
	friend std::ostream& operator << (std::ostream & output, const HugeInteger & object);
	friend std::istream& operator >> (std::istream & input, HugeInteger & object);

public:
	//ctor that converts a "long long" into a HugeInteger
	HugeInteger( long long value = 0LL ); //0LL is constant literal value 0
	                                      //   of type long long
	//ctor that converts a string into a HugeInteger
	HugeInteger( const char *str );

	//adds RHS into LHS (the object pointed to by the "this" pointer) and returns result
	HugeInteger& operator += (const HugeInteger& RHS);


	//adds a "long long" (RHS) and LHS and puts result into a temp HugeInteger
	//   and returns result
	HugeInteger operator +(long long RHS) const;


	//adds a string (which will be converted into a HugeInteger) with LHS into a temp 
	//       HugeInteger and returns result
	HugeInteger operator +(const char* RHS) const;


	//subtracts RHS from LHS (the object pointed to by the "this" pointer) and returns result
	HugeInteger& operator -= (const HugeInteger& RHS);


	//subtracts a "long long" (RHS) from LHS and puts result into a temp HugeInteger 
	//    and returns result
	HugeInteger operator -(long long RHS) const;


	//subtracts a string (which will be converted into a HugeInteger) from LHS 
	//    and puts result into a temp HugeInteger and returns result
	HugeInteger operator -(const char* RHS) const;


	//calculates the negation of the object pointed to by the this pointer and returns result
	HugeInteger operator -(void) const;


	//calculates the absolute value of the object pointed to by the this pointer and returns result
	HugeInteger operator ~(void) const;


	//Is LHS (the object pointed to by the "this" pointer) equal to RHS
	bool operator==(const HugeInteger& RHS) const;


	//Is LHS (the object pointed to by the "this" pointer) less than RHS
	bool operator <(const HugeInteger& RHS) const;


	//Is the object pointed to by the "this" pointer equal to zero
	bool operator !() const;


	//prefix increment operator
	HugeInteger& operator++();


	//postfix increment operator
	HugeInteger operator++(int); 
	

	//prefix decrement operator
	HugeInteger& operator--();


	//postfix decrement operator
	HugeInteger operator--(int);


	//Convert a string into a HugeInteger
	void input(const char* str);


	// overload typecast to double
	operator double(void)const;


private:
	bool negative;  // will be true if number is negative
	std::array<unsigned short,40> hugeInt; // each element in the array represents 
	                           //    one digit of the number
};

//Is LHS not equal to RHS
inline bool operator!=(const HugeInteger & LHS, const HugeInteger& RHS) {
	return !(LHS == RHS);
}

//Is LHS greater than RHS
inline bool operator > (const HugeInteger& LHS, const HugeInteger& RHS) {
	//return RHS < LHS;
	return !(LHS < RHS || LHS ==RHS);
}

//Is LHS less than or equal to RHS
inline bool operator <=(const HugeInteger& LHS, const HugeInteger& RHS) {
	//return !(RHS < LHS);
	return (LHS < RHS || LHS == RHS);
}

//Is LHS greater than or equal to RHS
inline bool operator >=(const HugeInteger& LHS, const HugeInteger& RHS) {
	return !(LHS < RHS);
}

//Is the object not equal to zero
inline bool operator+(const HugeInteger& obj) {
	return obj;
}


//overloads the "<<" operator through a global friend function, NOT inline
std::ostream& operator << (std::ostream& output, const HugeInteger& object);

//overloads the ">>" operator through a global friend function, NOT inline
std::istream& operator >> (std::istream& input, HugeInteger& object);

