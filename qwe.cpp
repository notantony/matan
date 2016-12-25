#include <string>
#include <stdio.h>
#include <cstdio>

#pragma warning(disable : 4996)

using namespace std;

void print(char* s, int length) {
	printf("(");
	for (int i = 0; i < length; i++) {
		printf("%c", s[i]);
	}
	printf(")");
}

void parse0(char* s, int length);       ///func
void parse1(char* s, int length);       ///**
void parse2(char* s, int length);       ///*,/
void parse3(char* s, int length);       ///+,-

void parse0(char* s, int length) {
	for (int i = 0; i < length; i++) {
		if (s[i] == '(') {
			if (i == 0) {
				parse3(s + 1, length - 2);
			}
			else if (i == 2){
				if (memcmp(s, "tg", 2 * sizeof(char)) == 0) {
					printf("(");
					parse3(s + 3, length - 4);
					printf("/cos");
					print(s + 3, length - 4);
					printf("**2)");
				}
				if (memcmp(s, "ln", 2 * sizeof(char)) == 0) {
					printf("(");
					parse3(s + 3, length - 4);
					printf("/");
					print(s + 3, length - 4);
					printf(")");
				}
			}
			else if (i == 3) {
				if (memcmp(s, "sin", 3 * sizeof(char)) == 0) {
					printf("(");
					parse3(s + 4, length - 5);
					printf("*cos");
					print(s + 4, length - 5);
					printf(")");
				}
				if (memcmp(s, "cos", 3 * sizeof(char)) == 0) {
					printf("(-");
					parse3(s + 4, length - 5);
					printf("*sin");
					print(s + 4, length - 5);
					printf(")");
				}
				if (memcmp(s, "ctg", 3 * sizeof(char)) == 0) {
					printf("(-");
					parse3(s + 4, length - 5);
					printf("/sin");
					print(s + 4, length - 5);
					printf("**2)");
				}
			}
			else if (i == 5){
				if(memcmp(s, "arctg", 5 * sizeof(char)) == 0) {
					printf("(");
					parse3(s + 6, length - 7);
					printf("/(1+");
					print(s + 6, length - 7);
					printf("**2))");
				}
			}
			else if (i == 6){
				if(memcmp(s, "arcsin", 6 * sizeof(char)) == 0) {
					printf("(");
					parse3(s + 7, length - 8);
					printf("/(1-");
					print(s + 7, length - 8);
					printf("**2)**(1/2))");
				}
			}
			return;
		}
	}
	parse3(s, length);
}




void parse1(char* s, int length) {
	int balance = 0;
	for (int i = 0; i < length; ++i) {
		if (balance == 0 && s[i] == '*') {
			printf("(");
			print(s, length);
			printf("*(");
			printf("ln");
			print(s, i);
			printf("*");
			parse1(s + i + 2, length - i - 2);
			printf("+");
			parse1(s, i);
			printf("/");
			print(s, i);
			printf("*");
			print(s + i + 2, length - i - 2);
			printf("))");
			return;
		}
		if (s[i] == '('){
			++balance;
		}
		if (s[i] == ')'){
			--balance;
		}
	}
	parse0(s, length);
}

void parse2(char* s, int length) {
	int balance = 0;
	for (int i = length - 1; i >= 0; i--) {
		if (balance == 0 && s[i] == '*' && s[i + 1] != '*' && s[i - 1] != '*') {
			printf("(");
			parse2(s, i);
			printf("*");
			print(s + i + 1, length - i - 1);
			printf("+");
			print(s, i);
			printf("*");
			parse2(s + i + 1, length - i - 1);
			printf(")");
			return;
		}

		if (balance == 0 && s[i] == '/') {
			printf("((");
			parse2(s, i);
			printf("*");
			print(s + i + 1, length - i - 1);
			printf("-");
			print(s, i);
			printf("*");
			parse2(s + i + 1, length - i - 1);
			printf(")/");
			print(s + i + 1, length - i - 1);
			printf("**2");
			printf(")");
			return;
		}
		if (s[i] == '('){
			++balance;
		}
		if (s[i] == ')'){
			--balance;
		}
	}
	parse1(s, length);
}



void parse3(char* s, int length) {
	if (length == 1 && s[0] == 'x') {
		printf("1");
		return;
	}
	int balance = 0, digits = 0;
	for (int i = 0; i < length; i++) {
		if (balance == 0 && (s[i] == '+' || s[i] == '-')) {
			printf("(");
			parse3(s, i);
			printf("%c", s[i]);
			parse3(s + i + 1, length - i - 1);
			printf(")");
			return;
		}
		if (s[i] == '('){
			++balance;
		}
		if (s[i] == ')'){
			--balance;
		}
		digits += isdigit(s[i]) ? 1 : 0;
	}
	if (digits == length) {
		printf("0");
		return;
	}
	parse2(s, length);
}


char c[10000007];

int main() {
	//freopen("input.txt","rt",stdin);
	//freopen("output.txt","wt",stdout);
	freopen("deriv.in","rt",stdin);
	freopen("deriv.out","wt",stdout);
	//while(scanf("%s", c)!=EOF){
	while(gets(c)){
		int len=((string)c).size();
		int j=0;
		for(int i=0;i<len;i++){
			if(c[i]!=' '){
				c[j]=c[i];
				j++;
			}
		}
		parse3(c, j);
		printf("\n");
	}
	return 0;
}
