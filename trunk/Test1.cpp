#include <iostream>

class Test1 {
public:
	Test1( int i ) : value( i ) {}

	Test1( const Test1& other )
	{
		std::cout << "Copy constructor called.\n";
		operator = ( other );
	}

	Test1 operator = ( const Test1& other )
	{
		std::cout << "Assigment operator called.\n";
		value = other.value;
		return *this;
	}

	int Get() const { return value; }
	void Set( int i ) { value = i; }

private:
	int value;
};

int main(int argc, char* argv[])
{
	Test1 t1( 10 );
	Test1 t2( t1 );
	return 0;
}

