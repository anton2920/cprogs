#include <iostream>
using namespace std;
 
 int main() {
     int n, k, p;
	     cin >> n >> k;
		     int person = 0;
			     for (int count = 2; count <= n; count++) person = (person + k) % count;
				     cout << person+1;
					     return 0;
						 }
