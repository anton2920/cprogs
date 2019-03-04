#pragma warning ( disable : 4996 )
#include <iostream> 

int const N = 10000; 

int formula(int n, int *x) 
{ 
	int i,f1=x[n-1],f2=x[n-1];

	for(i=1;i<n;i++) 
	{ 
		f1=f1+x[n-i-1]; 
		f2=f2*f1; 
	}
	return f2; 
} 

int main() 
{ 
	int n, x[N]; 

	do 
	{ 
		printf("Enter the number of elements in the array: "); 
		scanf("%d", &n); 
	} while(n <= 0); 
	
	for (int i = 0; i < n; i++)
	{
		printf("Enter %d element of array: ", i+1);
		scanf("%d", &x[i]);
	}
	
	int f = formula(n, x); 
	
	printf("Formula for an array of %d elements = %d\n", n, f); 
	
	system("pause"); 
	return 0; 
}
