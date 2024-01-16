#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int add(int a, int b) {
	return a+b;
}

int multiply(int a, int b) {
	return a*b;
}

int sequential_compute(char filepath[], int(*f)(int, int)) {
	int result, N = 0;
	FILE *fh = fopen(filepath, "r");
	if(fh == NULL) {
		perror("Unable to open the file");
		exit(1);
	}
	else {
		int arr[1000];
		while (!feof(fh)) {
			fscanf(fh, "%d", &arr[N]);
			N++;
		}
		fclose(fh);
		int i;
		if(N > 1) {
			if(f == add) {
				result = add(arr[N-2], arr[N-1]);
				for(i = N-3; i >= 0; i--) {
					result = add(result, arr[i]);
				}
			}
			else if(f == multiply) {
				result = multiply(arr[N-2], arr[N-1]);
				for(i = N-3; i >= 0; i--) {
					result = multiply(result, arr[i]);
				}	
			}
		}
		else if(N == 1) {
			if(f == add) {
				result = 0;
				result = add(result, arr[N-1]);
			}
			else if(f == multiply) {
				result = 1;
				result = multiply(result, arr[N-1]);
			}
		}
		return result;
	}
}

int main(int argc, char* argv[]) {
	char filepath[] = "numbers.txt";
	int (*f[])(int, int) = {add, multiply};
	printf("%d\n", sequential_compute(filepath, f[0]));
	return 0;
}
