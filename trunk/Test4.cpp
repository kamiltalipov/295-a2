	

void func( vector<int>& ourArray )
{
	for( vector<int>::iterator it = ourArray.begin(); it != ourArray.end(); it++ ) {
		if( *it == 5 ) {
			ourArray.erase( it );
		}
	}
}