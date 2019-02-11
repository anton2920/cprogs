/* 
SetsCalc — powerful sets calculator
Copyright © 2018 Anton

This file is part of SetsCalc.

SetsCalc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

SetsCalc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SetsCalc. If not, see <https://www.gnu.org/licenses/>.
*/

#include "../headers/project.h"

char *sum(const char *a, const char *b, const int exl) {
	
	/* Initializing variables */
	/* exl — zero if inclusive, 1 if exclusive A, 2 if exclusive B */
	char a_cp[NAME], b_cp[NAME], res[NAME] = "", *res_p;
	strcpy(a_cp, a);
	*(a_cp + strlen(a_cp) - 1) = ',';
	strcpy(b_cp, b + 1);

	/* Main part */
	if (!strcmp(a, INT_ALL) || !strcmp(b, INT_ALL)) {
		strcpy(res, INT_ALL);
	} else if (!strcmp(a, "{}")) {
		strcpy(res, b);
	} else if (!strcmp(b, "{}")) {
		strcpy(res, a);
	} else {
		strcat(res, a_cp);
		strcat(res, b_cp);
		fix_str_rpt(res);
	}
	
	if (exl) {
		to_neg(res);
	}

	res_p = res;

	/* Returning value */
	return res_p;
}

void to_neg(char *str) {

	/* Initializing variables */
	char str2[NAME] = "";

	/* Main part */
	if (*str == '-') {
		strcpy(str2, str + 1);
	} else {
		strcat(str2, "-");
		strcat(str2, str);
	}

	strcpy(str, str2);
}

void to_opp(char *str, int param) {

	/* Initializing variables */
	int i, str_int[NAME], j;
	char *pstr = str;

	/* Main part */
	if (param) {
		if (!strcmp(str, "-{}")) {
			strcpy(str, INT_ALL);
			return;
		}
		pstr += 2;
		for (i = 0; ; ++i) {
			if (*(pstr - 1) == '}') {
				break;          
			}   
			*(str_int + i) = str_get_num(pstr);
			pstr += numlen(*(str_int + i)) + 1;
		}
		strcpy(str, "");
		strcat(str, "{x ∈ N | ");
		for (j = 0; j < i; ++j) {
			strcat(str, "x ≠ ");
			strcat(str, get_elem(str_int + j));
			if (j != i - 1) {
				strcat(str, ", ");
			} else {
				strcat(str, "}");
			}
		}
	} else {
		pstr += 11;
		for (i = 0; ; ++i) {
			if (*(pstr - 2) == '}') {
				break;
			}
			*(str_int + i) = str_get_num(pstr);
			pstr += numlen(*(str_int + i)) + 8;
		}
		strcpy(str, "");
		strcat(str, "{");
		for (j = 0; j < i; ++j) {
			strcat(str, get_elem(str_int + j));
			if (j != i - 1) {
				strcat(str, ",");
			} else {
				strcat(str, "}");
			}
		}
	}
}

char *mul(char *a, char *b, int exl) {

	/* Initializing variables */
	int i, a_int[NAME], b_int[NAME], j, k, res_int[NAME], count = 0;
	/* exl — zero if inclusive, 1 if exclusive A, 2 if exclusive B */
	char res[NAME] = "", *res_p, *p = a + 1;

	/* Main part */
	if (!strcmp(a, INT_ALL)) {
		strcpy(res, b);
	} else if (!strcmp(b, INT_ALL)) {
		strcpy(res, a);
	} else if (!strcmp(a, "{}") || !strcmp(b, "{}")) {
		strcpy(res, "{}");
	} else {
		for (i = 0; ; ++i) {
			if (*(p - 1) == '}') {
				break;          
			}   
			*(a_int + i) = str_get_num(p);
			p += numlen(*(a_int + i)) + 1;
		}
		p = b + 1;
		for (j = 0; ; ++j) {
			if (*(p - 1) == '}') {
				break;
			}
			*(b_int + j) = str_get_num(p);
			p += numlen(*(b_int + j)) + 1;
		}
		for (k = 0; k < j; ++k) {
			if (bsearch((int *) b_int + k, (int *) a_int, (int) i, sizeof(int), num_cmp)) {
				*(res_int + count) = *(b_int + k);
				++count;
			}
		}
		get_set(res, res_int, &count);
	}

	if (exl) {
		to_neg(res);
	}
	res_p = res;

	/* Returning value */
	return res_p;
}

char *sub(char *a, char *b, int exl) {

	/* Initializing variables */
	int i, a_int[NAME], b_int[NAME], j, k, res_int[NAME], count = 0;
	/* exl — zero if inclusive, 1 if exclusive A, 2 if exclusive B */
	char res[NAME] = "", *res_p, *p = a + 1;

	/* Main part */
	if (!strcmp(a, INT_ALL)) {
		strcpy(res, b);
		to_neg(res);
	} else if (!strcmp(b, INT_ALL)) {
		strcpy(res, "{}");
	} else if (!strcmp(a, "{}")) {
		strcpy(res, "{}");
	} else if (!strcmp(b, "{}")) {
		strcpy(res, a);
	} else {
		for (i = 0; ; ++i) {
			if (*(p - 1) == '}') {
				break;          
			}   
			*(a_int + i) = str_get_num(p);
			p += numlen(*(a_int + i)) + 1;
		}
		p = b + 1;
		for (j = 0; ; ++j) {
			if (*(p - 1) == '}') {
				break;
			}
			*(b_int + j) = str_get_num(p);
			p += numlen(*(b_int + j)) + 1;
		}
		for (k = 0; k < i; ++k) {
			if (!bsearch((int *) a_int + k, (int *) b_int, (int) j, sizeof(int), num_cmp)) {
				*(res_int + count) = *(a_int + k);
				++count;
			}
		}
		get_set(res, res_int, &count);
	}

	if (exl) {
		to_neg(res);
	}
	res_p = res;

	/* Returning value */
	return res_p;
}
