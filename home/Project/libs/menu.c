#include "../headers/project.h"

static int func_err = 0;

int set_sets(char *a, char *b, char *c) {

    /* Initializing variables */
    int func;
	extern int func_err;
    char *list[] = {"A =", a, "B =", b, "C =", c};
	char change[NAME];
    dialog_vars.input_menu = 1;
	dialog_vars.help_line = "Ctrl + U to clear field";
	dialog_vars.extra_button = 1;
	dialog_vars.extra_label = "Change";
	dialog_vars.cancel_label = "Quit";
	dialog_vars.defaultno = 0;

    /* I/O flow */
	dialog_vars.input_result = change;
    init_dialog(stdin, stdout);
    func = dialog_menu(TITLE, "===> Type sets: ", 0, 0, 10, 3, list);
    end_dialog();
	if (func == 1)
		return func;
	else if (!func && !func_err)
		return func;
	else if (!func && func_err) {
		str_err(ERROR_MSG);
		return 4;
	}
	if (*(change + 8) == 'A') {
		output(a, change, b, c);
	} else if (*(change + 8) == 'B') {
		output(b, change, a, c);
	} else {
		output(c, change, a, b);
	}
	
    /* Returning value */
    return func;
}

void rep_str(char *str) {

	/* Initializing variables */
	int i, j;

	/* Main part */
	for (i = 0; i < strlen(str); ++i) {
		if (isspace(*(str + i))) {
			for (j = i; j < strlen(str); ++j) {
				*(str + j) = *(str + (j + 1));
			}
			--i;
		}
	}
}

int check(char *str) {

	/* Initializing variables */
	int i, len = strlen(str);

	/* Main part */
	if (!strcmp(str, "NATURAL_ALL"))
		return 2;
	if (!strncmp(str, "NATURAL(", 8)) {
		if (strstr(str, ",") && strstr(str, ")") && strchr(str, '(') == strrchr(str, '(') && strchr(str, ',') == strrchr(str, ',') && strchr(str, ')') == strrchr(str, ')')) {
			for (i = 8; i < len - 1; ++i)
				if (!isdigit(*(str + i)) && *(str + i) != ',')
					return 0;
			return 3;
		} else
			return 0;
	}
	if (!strncmp(str, "RAND(", 5)) {
		if (strchr(str, '(') == strrchr(str, '(') && strstr(str, ")") && strchr(str, ')') == strrchr(str, ')') && str_chr_cnt(str, ',') == 2) {
			for (i = 5; i < len - 1; ++i) {
				if (!isdigit(*(str + i)) && *(str + i) != ',' && *(str + i) != '-') {
					return 0;
				}
				if ((*(str + i) == '-' && *(str + (i + 1)) == '-') || (isdigit(*(str + i)) && *(str + (i + 1)) == '-') || (*(str + i) == ',' && *(str + (i + 1)) == '-' && !isdigit(*(str + (i + 2))))) {
					return 0;
				}
			}
			return 4;
		} else
			return 0;
	}
	if (strlen(str) == 1) {
		if (!strcmp(str, "A")) {
			return 'A';
		} else if (!strcmp(str, "B")) {
			return 'B';
		} else if (!strcmp(str, "C")) {
			return 'C';
		} else {
			return 0;
		}
	}
	if (*str != '{')
		return 0;
	if (*(str + (len - 1)) != '}')
		return 0;
	if (len == 2) 
		return 1;

	for (i = 1; i < len - 1; ++i) {
		if (!isdigit(*(str + i)) && *(str + i) != ',' && *(str + i) != '-') {
			return 0;
		}
		if ((*(str + i) == '-' && *(str + (i + 1)) == '-') || (isdigit(*(str + i)) && *(str + (i + 1)) == '-') || (*(str + i) == ',' && *(str + (i + 1)) == '-' && !isdigit(*(str + (i + 2))))) {
			return 0;
		}
	}
	
	/* Returning value */
	return 1;
}

int numcmp(char *s1, char *s2) {

	/* Initializing variables */
	double v1 = atof(s1), v2 = atof(s2);

	/* Returning value */
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else 
		return 0;
}

void output (char *str, const char *change, const char *str1, const char *str2) {

	/* Initializing variables */
	extern int func_err;
	char x[NAME] = "", y[NAME] = "", temp[NAME] = "";
	int ch;
	func_err = 0;

	/* I/O flow */
	strcpy(str, change + 12);
	rep_str(str);
	if (!strncmp(str, "FILE(\"", 6)) {
		file_get_str(str, change);
		if (func_err) {
			str_err(ERROR_MSG_FILE);
			return;
		}
	}
    if (!(ch = check(str))) {
		str_err(ERROR_MSG);
    } else if (ch == 2) {
        strcpy(str, NATURAL_ALL);
    } else if (ch == 3) {
        strncpy(x, strstr(str, "(") + 1, (strstr(str, ",") - (strstr(str, "(") + 1)));
        strncpy(y, strstr(str, ",") + 1, (strstr(str, ")") - (strstr(str, ",") + 1)));
        if (numcmp(x, y) > 0) {
    	    strcpy(temp, y);
            strcpy(y, x);
            strcpy(x, temp);
        }   
        strcpy(str, "");
        strcat(str, "{x ∈ N | ");
        strcat(str, strcat(x, " < x < "));
        strcat(str, strcat(y, " }"));
	} else if (ch == 'A') {
		if (*(change + 8) == 'B' || *(change + 8) == 'C') {
			strcpy(str, str1);
		} else {
			str_err(ERROR_MSG);
		}
	} else if (ch == 'B') {
		if (*(change + 8) == 'A') {
			strcpy(str, str1);
		} else if (*(change + 8) == 'C') {
			strcpy(str, str2);
		} else {
			str_err(ERROR_MSG);
		}
	} else if (ch == 'C') {
		if (*(change + 8) == 'A' || *(change + 8) == 'B') {
			strcpy(str, str2);
		} else {
			str_err(ERROR_MSG);
		}
	} else if (ch == 4) {
		rand_get_str(str);
		if (func_err) {
			str_err(ERROR_MSG);
		}
	}


}

void str_err(const char *str) {

	/* Initializing variables */
	extern int func_err;
	dialog_vars.extra_button = 0;

	/* Main part */
	init_dialog(stdin, stdout);
    dialog_msgbox(TITLE, str, 0, 0, 1);
	func_err = 1;
	end_dialog();

	dialog_vars.extra_button = 1;
}

void file_get_str(char *str, const char *change) {

	/* Initializing variables */
	extern func_err;
	FILE *inputs = NULL;
	char name[NAME] = "", str2[NAME];
	func_err = 0;
	
	/* I/O flow */
	if (*(str + (strlen(str) - 1)) == ')') {
		if (*(strstr(str, ")") - 1) == '\"' && (strchr(strchr(str, '(') + 2, '\"') == strrchr(str, '\"'))) {
			strncpy(name, strstr(str, "(") + 2, (strstr(str, ")") - 1) - (strstr(str, "(") + 2));
		}
	}
	if (strlen(name)) {
		if ((inputs = fopen(name, "r"))) {
			if (*(change + 8) == 'A') {
				if (find_str(inputs, "A = {", NONE_STR, NONE_STR)) {
					strcpy(str, find_str(inputs, "A = {", NONE_STR, NONE_STR));
				} else if (find_str(inputs, "{", "B = {", "C = {")) {
					strcpy(str, find_str(inputs, "{", "B = {", "C = {"));
				} else {
					func_err = 1;
				}
			} else if (*(change + 8) == 'B') {
				if (find_str(inputs, "B = {", NONE_STR, NONE_STR)) {
					strcpy(str, find_str(inputs, "B = {", NONE_STR, NONE_STR));
				} else if (find_str(inputs, "{", "A = {", "C = {")) {
					strcpy(str, find_str(inputs, "{", "A = {", "C = {"));
				} else {
					func_err = 1;
				}
			} else {
				if (find_str(inputs, "C = {", NONE_STR, NONE_STR)) {
					strcpy(str, find_str(inputs, "C = {", NONE_STR, NONE_STR));
				} else if (find_str(inputs, "{", "A = {", "B = {")) {
					strcpy(str, find_str(inputs, "{", "A = {", "B = {"));
				} else {
					func_err = 1;
				}
			}
		} else {
			func_err = 1;
		}
	}
	
	rep_str(str);
	if (*(str) != '{' && !func_err && strlen(name)) {
		strcpy(str2, str);
		strcpy(str, str2 + 2);
		if (*(str + (strlen(str) - 1)) == '\n') { 
			*(str + (strlen(str) - 1)) = '\0';
		}
	}

	if (inputs)
		fclose(inputs);

}

char *find_str(FILE *f, char *ch, const char *exl, const char *exl2) {

	/* Initializing variables */
	char str[NAME], *pstr = NULL, *ppstr = NULL;
	rewind(f);

	/* I/O flow */
	do {
		;
	} while (!strstr((ppstr = (pstr = fgets(str, NAME, f)) ? pstr : ch), ch) || strstr(ppstr, exl) || strstr(ppstr, exl2));

	/* Returning value */
	return pstr;
}

void rand_get_str(char *str) {
	
	/* Initializing variables */
	int n, a, b, i, temp;
	char str2[NAME] = "";
	int set[NAME] = {0};
	extern int func_err;
	func_err = 0;

	/* I/O flow */
	rep_str(str);
	strcpy(str2, str + 4);
	n = str_get_num(str2);
	if (n <= 0) {
		func_err = 1;
		return;
	}
	strcpy(str, str2 + numlen_int(n) + 2);
	a = str_get_num(str);
	strcpy(str2, str + numlen_int(a) + 1 + (numlen(a) - numlen_int(a)));
	b = str_get_num(str2);
	if (a > b) {
		temp = b;
		b = a;
		a = temp;
	}
	for (i = 0; i < n; ++i) {
		*(set + i) = (a == b) ? a : (rand() % (b - a + 1)) + a;
	}
	
	qsort((int *) set, n, sizeof (int), num_cmp);
	get_set(str, set, &n);
}

int str_chr_cnt(const char *str, const char ch) {

	/* Initializing variables */
	int i, count = 0;

	/* Main part */
	for (i = 0; i < strlen(str); ++i) {
		if (*(str + i) == ch) {
			++count;
		}
	}

	/* Returning valur */
	return count;
}

int str_get_num(const char *str) {
	
	/* Initializing variables */
	int res = 0, sign = 1, i;

	/* Main part */
	for (i = 0; i < strlen(str) && *(str + i) != ','; ++i) {
		if (*(str + i) == '-') {
			sign = -1;
			continue;
		}
		if (isdigit(*(str + i))) {
			res = (res * 10) + (*(str + i) - '0');
		}
	}
	
	/* Returning value */
	return res * sign;
}

int numlen(int num) {
	
	/* Initializing variables */
	int len;

	/* Main part */
	for (len = (num < 0) ? 1 : 0; num; ++len)
		num /= 10;

	/* Returning value */
	return len;
}

void get_set(char *str, const int *set, const int *n) {
	
	/* Initializing variables */
	strcpy(str, "");
	int i;

	/* Main part */
	strcat(str, "{");
	for (i = 0; i < *n; ++i, ++set) {
		strcat(str, get_elem(set));
		if (i != *n - 1) {
			strcat(str, ",");
		}
	}

	strcat(str, "}");
}

int num_cmp(const void *a, const void *b) {
	
	/* Returning value */
	return (*(int *) a == *(int *) b) ? 0 : (*(int *) a > *(int *) b) ? 1 : -1;
}

char *get_elem(const int *num) {
	
	/* Initializing variables */
	int i, len = numlen(*num);
	int dnum = ABS(*num);
	char elem[NAME], *pelem = elem;

	/* Main part */
	*(elem) = '-';
	if (!dnum) {
		*(elem) = '0';
		*(elem + 1) = '\0';

	} else {
		for (i = len - 1; i >= 0 && dnum; --i) {
			*(elem + i) = (dnum % 10) + '0';
			dnum /= 10;
		}
		*(elem + len) = '\0';

	}
	/* Returning value */
	return pelem;
}

int numlen_int(int num) {
	
	/* Initializing variables */
	int len;
	num = ABS(num);

	/* Main part */
	for (len = 0; num; ++len) {
		num /= 10;
	}

	/* Returning value */
	return len;
}
