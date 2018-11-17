#include <stdio.h>

unsigned add(unsigned a, unsigned b) {
	unsigned sum = 0;
	unsigned pos = 1;
	unsigned carry = 0;
	while(a || b) {
		if((a & 1) ^ (b & 1) ^ carry) {
			sum |= pos;
		}
		pos <<= 1;
		carry = ((a & b) | (a & carry) | (b & carry)) & 1;
		a >>= 1;
		b >>= 1;
	}
	if(carry) {
		sum |= pos;
	}
	return sum;
}

int main() {
	int errors = 0;
	for(int i = 0; i < 100; ++i) {
		for(int j = 0; j < 100; ++j) {
			int got = add(i, j);
			if(got != i + j) {
				printf("add(%d, %d) -> %d not %d\n", i, j, got, i + j);
				++errors;
				if(errors > 10) {
					puts("...");
					return 1;
				}
			}
		}
	}
	return 0;
}
