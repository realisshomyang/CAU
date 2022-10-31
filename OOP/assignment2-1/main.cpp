#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int c("1111");
	inf_int d("2");
	inf_int a = c + d;

	cout << a;

	return 0;
}
