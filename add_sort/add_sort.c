#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define RANGE1 1000
#define RANGE2 10000
#define RANGE3 100000


#define SWAP(tmp,x,y) ((tmp)=(x), (x)=(y), (y)=(tmp))

int min_arr[RANGE3], mid_arr[RANGE3], tmp[RANGE3];
int cnt = 0;
int zero_val = 0;

time_t time_start, time_end;

void val_making(int rand_val, int rev_val);
double bubble(int *p, int rand_val, int rev_val);
double selection(int *p, int rand_val, int rev_val);
double insertion(int *p, int rand_val, int rev_val);
void merge_sort(int *p, int start, int end);
void merge(int *p, int start, int mid, int end);
double merge_time(int *p, int rand_val, int rev_val);
void quick_sort(int *p, int start, int end, int pivot);
int partition_ver1(int *p, int start, int end);
int partition_ver2(int *p, int start, int end);
int partition_ver3(int *p, int start, int end);
double quick_time(int *p, int rand_val, int rev_val, int pivot);
void print();
void print_bubble();
void print_select();
void print_insert();
void print_merge();
void print_quick();
void print_heap();
void print_lib();
void swap_arr(int *p, int a, int b);
void max_heapify(int *p, int a, int i);
void build_maxHeap(int *p, int size);
void heap_sort(int *p, int size);
int cmp(const void *a, const void *b);
double heap_time(int *p, int rand_val, int rev_val);
double lib_time(int *p, int rand_val, int rev_val);


int main(void) {

	print();
	getchar();

	return 0;
}

void val_making(int rand_val, int rev_val) {
	int save_val;

	if (rand_val != 0) {
		cnt = rand_val;
		for (int j = 0; j < rand_val; j++) {
			save_val = rand() % (rand_val + 1);
			min_arr[j] = save_val;
		}
	}
	if (rev_val != 0) {
		cnt = rev_val;
		save_val = rev_val;

		for (int i = 0; i < rev_val; i++)
			mid_arr[i] = save_val--;
	}
}

double bubble(int *p, int rand_val, int rev_val) {

	val_making(rand_val, rev_val);
	time_start = clock();
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = 0; j < cnt - 1 - j; j++) {
			if (p[j] > p[j + 1]) {
				zero_val = p[j];
				p[j] = p[j + 1];
				p[j + 1] = zero_val;
			}
		}
	}
	time_end = clock();
	return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
}

double selection(int *p, int rand_val, int rev_val) {

	int min;

	val_making(rand_val, rev_val);
	time_start = clock();
	for (int i = 0; i < cnt - 1; i++) {
		min = i;
		for (int j = i + 1; j < cnt; j++) {
			if (p[j] < p[min])
				min = j;
		}
		swap_arr(p, p[min], p[i]);
	}

	time_end = clock();

	return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
}

double insertion(int *p, int rand_val, int rev_val) {

	int i, j, tmp;

	val_making(rand_val, rev_val);
	time_start = clock();

	for (i = 1; i < cnt; i++) {
		tmp = p[(j = i)];
		while (--j >= 0 && tmp < p[j]) {
			SWAP(tmp, p[j], p[j + 1]);

		}
	}
	time_end = clock();
	return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
}

void merge_sort(int *p, int start, int end) {
	int mid;
	if (start < end) {
		mid = (start + end) / 2;
		merge_sort(p, start, mid);
		merge_sort(p, mid + 1, end);
		merge(p, start, mid, end);
	}
}

void merge(int *p, int start, int mid, int end) {

	int i, j, k, l;
	i = start;
	j = mid + 1;
	k = start;

	while (i <= mid && j <= end) {
		if (p[i] <= p[j])
			tmp[k++] = p[i++];
		else
			tmp[k++] = p[j++];
	}
	if (i > mid) {
		for (l = j; l <= end; l++)
			tmp[k++] = p[l];
	}
	else {
		for (l = i; l <= mid; l++)
			tmp[k++] = p[l];
	}
	for (l = start; l <= end; l++)
		p[l] = tmp[l];
}

double merge_time(int *p, int rand_val, int rev_val) {
	val_making(rand_val, rev_val);
	time_start = clock();
	merge_sort(p, 0, cnt - 1);
	time_end = clock();
	return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
}
void quick_sort(int *p, int start, int end, int stadus) {
	int q;
	if (start < end) {
		if (stadus == 1) {
			q = partition_ver1(p, start, end);

		}
		else if (stadus == 2) {
			q = partition_ver2(p, start, end);
		}
		else if (stadus == 3)
			q = partition_ver3(p, start, end);

		quick_sort(p, start, q - 1, stadus);
		quick_sort(p, q + 1, end, stadus);
	}
}

int partition_ver1(int *p, int start, int end) {
	int x = p[end];
	int i = start - 1;

	for (int j = start; j < end; j++) {
		if (p[j] <= x) {

			i++;

			swap_arr(p, i, j);
		}
	}

	swap_arr(p, i + 1, end);

	return i + 1;
}

int partition_ver2(int *p, int start, int end) {

	int tmp[3] = { start, (start + end) / 2,end };
	int val;

	for (int i = 0; i < 2; i++) {
		for (int j = i + 1; j < 3; j++) {
			if (p[tmp[i]] > p[tmp[j]]) {
				SWAP(val, tmp[i], tmp[j]);
			}
		}
	}

	swap_arr(p, end, tmp[1]);

	int x = p[end];
	int i = start - 1;

	for (int j = start; j < end; j++) {
		if (p[j] <= x) {
			i++;
			swap_arr(p, i, j);
		}
	}
	swap_arr(p, i + 1, end);

	return i + 1;
}

int partition_ver3(int *p, int start, int end) {
	int tmp = (rand() % (end - start + 1)) + start;
	swap_arr(p, end, tmp);

	int x = p[end];
	int i = start - 1;

	for (int j = start; j < end; j++) {
		if (p[j] <= x) {
			i++;
			swap_arr(p, i, j);
		}
	}
	swap_arr(p, i + 1, end);

	return i + 1;
}

double quick_time(int *p, int rand_val, int rev_val, int stadus) {
	val_making(rand_val, rev_val);
	time_start = clock();
	quick_sort(p, 0, cnt - 1, stadus);
	time_end = clock();

	return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
}


void print() {

	printf("----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\tRandom1000\tReverse1000\tRandom10000\tReverse10000\tRandom100000\tReverse100000\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");
	/*
	print_bubble();
	print_select();
	print_insert();
	print_merge();
	print_quick();
	*/
	print_heap();
	print_lib();

}
void print_bubble() {

	printf("Bubble\t\t");

	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			int *a = min_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", bubble(a, b, 0));
			b = b * 10;
		}
		else {
			int *a = mid_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", bubble(a, 0, b));
			b = b * 10;
		}
	}
	printf("\n");
}
void print_select() {

	printf("Select\t\t");

	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			int *a = min_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", selection(a, b, 0));
			b = b * 10;
		}
		else {
			int *a = mid_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", selection(a, 0, b));
			b = b * 10;
		}
	}
	printf("\n");
}
void print_insert() {

	printf("Insert\t\t");

	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			int *a = min_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", insertion(a, b, 0));
			b = b * 10;
		}
		else {
			int *a = mid_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", insertion(a, 0, b));
			b = b * 10;
		}
	}
	printf("\n");
}
void print_merge() {

	printf("Merge\t\t");
	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			int *a = min_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", merge_time(a, b, 0));
			b = b * 10;
		}
		else {
			int *a = mid_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", merge_time(a, 0, b));
			b = b * 10;
		}
	}
	printf("\n");
}
void print_quick() {
	for (int i = 1; i < 4; i++) {
		printf("Quick%d\t\t", i);
		for (int j = 0; j < 6; j++) {

			if (j % 2 == 0) {
				int *a = min_arr;
				static int b = RANGE1;
				printf("%.3lf\t\t", quick_time(a, b, 0, i));
				b = b * 10;
			}
			else {
				int *a = mid_arr;
				static int b = RANGE1;
				printf("%.3lf\t\t", quick_time(a, 0, b, i));
				b = b * 10;
			}
		}
		printf("\n");
	}

}

void print_heap() {

	printf("Heap \t\t");

	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			int *a = min_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", merge_time(a, b, 0));
			b = b * 10;
		}
		else {
			int *a = mid_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", merge_time(a, 0, b));
			b = b * 10;
		}
	}
	printf("\n");
}

void print_lib() {

	printf("lib  \t\t");

	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			int *a = min_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", lib_time(a, b, 0));
			b = b * 10;
		}
		else {
			int *a = mid_arr;
			static int b = RANGE1;
			printf("%.3lf\t\t", lib_time(a, 0, b));
			b = b * 10;
		}
	}
	printf("\n");

}

void swap_arr(int *p, int a, int b) {

	int tmp;
	tmp = p[a];
	p[a] = p[b];
	p[b] = tmp;
}

void max_heapify(int *p, int a, int i) {

	int left = i * 2;
	int right = (i * 2) + 1;
	int size_val = i;

	if (left<a && p[left]>p[size_val]) {
		size_val = left;
	}
	if (right<a && p[right]>p[size_val]) {
		size_val = right;
	}
	if (size_val != i) {

		swap_arr(p, size_val, i);
		max_heapify(p, a, size_val);
	}
}

void build_maxHeap(int *p, int size) {
	for (int i = size / 2; i >= 0; i--) {
		max_heapify(p, size, i);
	}
}

void heap_sort(int *p, int size) {

	build_maxHeap(p, size);

	for (int i = size - 1; i >= 0; i--) {
		swap_arr(p, i, 0);
		max_heapify(p, i, 0);
	}
}

double heap_time(int *p, int rand_val, int rev_val) {

	val_making(rand_val, rev_val);
	time_start = clock();
	heap_sort(p, 0);
	time_end = clock();

	return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
}

int cmp(const void *a, const void *b) {
	return (*(int *)a) - (*(int *)b);
}

double lib_time(int *p, int rand_val, int rev_val) {
	int x = rand_val;
	int y = rev_val;

	if (rev_val == 0) {
		val_making(rand_val, rev_val);
		time_start = clock();
		qsort(p, rand_val, 4, cmp);
		time_end = clock();
		return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
	}
	else {
		val_making(rand_val, rev_val);
		time_start = clock();
		qsort(p, rev_val, 4, cmp);
		time_end = clock();
		return (double)(time_end - time_start) / (CLOCKS_PER_SEC);
	}

}