#include "gets.h"
#include <stdio.h>
#include <stdlib.h>

main() {

	int n;
	char buf[SIZE_BUF_GETS];

	printf("Type your string: ");
	n = lgets(buf);
	/* write(1, "Your string: ", 13);
	* write(1, buf, n);
	*/
	printf("Your string: %s\n", buf);

	#ifdef _WIN32
		system("pause");
	#endif // _WIN32

}