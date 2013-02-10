#include <string.h>
#include <memory.h>
#include <iostream>

class Test2 {
public:
	Test2( const char* str )
	{
		data = copyString( str );
	}
	~Test2()
	{
		delete[] data;
	}

	operator const char*() const { return data; }

	const Test2& operator = ( const Test2& other )
	{
		char* newData = copyString( other );
		char* oldData = data;
		data = newData;
		delete[] oldData;
	}

private:
	char* data;

	char* copyString( const char* str )
	{
		if( str == 0 ) {
			str = "";
		}

		int len = strlen( str ) + 1;
		char* data = new char[len];
		memcpy( data, str, len * sizeof( data[0] ) );
		return data;
	}
};

void dump( Test2 value )
{
	std::cout << value << '\n';
}

int main(int argc, char* argv[])
{
	Test2 t( "The mother washed the frame." );
	dump( t );
	return 0;
}

