//
//  main.cpp
//
//  Created by Taygrim on 04.03.13.
//  Copyright (c) 2013 Taygrim. All rights reserved.
//

#include <iostream>
#include <list>
#include <map>

using namespace std;

class BadCopy {
public:
	BadCopy( int val = -1 ) : value( val ) {}
    
	void SetValue( int val ) { value = val; }
	int GetValue() { return value; }
private:
	int value;
};

int main(int argc, const char * argv[])
{
    map<string, BadCopy> a;
    
    a["abcd"].SetValue(5);

    return 0;
}

