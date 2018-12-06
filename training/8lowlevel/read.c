#define SIZE 100

main() {

	int n, buf[SIZE];

	if ((n = read(0, buf, SIZE)) == '\n')
		write(1, buf, SIZE);
}