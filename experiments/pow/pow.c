#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define LOOP (1000000)

extern double lpow(double, double);

int main(int argc, const char *argv[]) {

	/* Initializing variables */
	register int i;
	double a = 1024, b = 0.5, c = 0;
	struct timeval stop, start;

	/* Main part */
	if (**(argv + 1) == '1') {
		gettimeofday(&start, NULL);
		for (i = 0; i < LOOP; ++i) {
			c += pow(a, b);
		}
		gettimeofday(&stop, NULL);
	} else if (**(argv + 1) == '2') {
		gettimeofday(&start, NULL);
		for (i = 0; i < LOOP; ++i) {
			c += lpow(a, b);
		}
		gettimeofday(&stop, NULL);
	}

	double time_in_mill = 
         (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;

	double time_in_mill2 = 
         (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;

	/* Final output */
	printf("Time: %lf\n", time_in_mill2 - time_in_mill);
	printf("%lf\n", c);

	/* Returning value */
	return 0;
}