#include"sub.h"

int main( int argc, char *argv[] )
{
	
	if( !strcmp( argv[2], "-html" ) )
	{
		sub( argv[1], "  ", "&nbsp;&nbsp;" );
	}
	
	return 0;
	
}
