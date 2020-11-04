#include<iostream>
#include<chrono>
#include<fstream>
using namespace std;
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}
//In each of the five sorting functions I first note the time and at the end of sorting I againg note the time
//Then calculate there difference in nanoseconds and type cast it in double data type
//Then I convert it into seconds and return it
double wrongSel_sort(int arr[], const int& n) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0;i < n - 1;i++) {
		for (int j = i + 1;j < n;j++) {
			if (arr[j] < arr[i]) {
				swap(arr[i], arr[j]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	double time_elapsed = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
	return time_elapsed / 1e9;
}
double rightSel_sort(int arr[], const int& n) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0;i < n - 1;i++) {
		int min_ind = arr[i];
		for (int j = i + 1;j < n;j++) {
			if (arr[j] < min_ind) {
				min_ind = j;
			}
		}
		if(i!=min_ind)
			swap(arr[i], arr[min_ind]);
	}
	auto end = chrono::high_resolution_clock::now();
	double time_elapsed = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
	return time_elapsed / 1e9;
}
double bubble_sort(int arr[], const int& n) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < (n - i); j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	double time_elapsed = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
	return time_elapsed / 1e9;
}
double flagBubble_sort(int arr[], const int& n) {
	auto start = chrono::high_resolution_clock::now();
	bool swapped = true;
	int top = 1;
	while (swapped) {
		swapped = false;
		for (int j = n - 1;j >= top;j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
				swapped = true;
			}
		}
		top++;
	}
	auto end = chrono::high_resolution_clock::now();
	double time_elapsed = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
	return time_elapsed / 1e9;
}
double ins_sort(int arr[], const int& n) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 1;i < n;i++) {
		int to_place = arr[i];
		int j = i - 1;
		while (j >= 0 && to_place < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = to_place;
	}
	auto end = chrono::high_resolution_clock::now();
	double time_elapsed = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
	return time_elapsed / 1e9;
}
int main() {
	const int n = 100000;
	int A[n];
	//variables to store sums and avgs of execution times for each function
	double us_ws_sum = 0, us_ws_avg = 0, us_rs_sum = 0, us_rs_avg = 0, us_b_sum = 0, us_b_avg = 0, us_fb_sum = 0, us_fb_avg = 0, us_i_sum = 0, us_i_avg = 0, s_ws_sum = 0, s_ws_avg = 0, s_rs_sum = 0, s_rs_avg = 0, s_b_sum = 0, s_b_avg = 0, s_fb_sum = 0, s_fb_avg = 0, s_i_sum = 0, s_i_avg = 0;
	for (int j = 1;j <= 10;j++) {
		for (int i = 0;i < n;i++) {
			A[i] = (rand() % 1000000) + 1; //to generate and store a random value at ith position
		}
		us_ws_sum += wrongSel_sort(A, n); //passing random array to the function
		s_ws_sum += wrongSel_sort(A, n); // once the upper function sorts that random array so passing it as a sorted array
	}
	us_ws_avg = us_ws_sum / 10.0;
	s_ws_avg = s_ws_sum / 10.0;
	//Following loops do the same for the rest of algorithms
	for (int j = 1;j <= 10;j++) {
		for (int i = 0;i < n;i++) {
			A[i] = (rand() % 1000000) + 1;
		}
		us_rs_sum += rightSel_sort(A, n);
		s_rs_sum += rightSel_sort(A, n);
	}
	us_rs_avg = us_rs_sum / 10.0;
	s_rs_avg = s_rs_sum / 10.0;
	for (int j = 1;j <= 10;j++) {
		for (int i = 0;i < n;i++) {
			A[i] = (rand() % 1000000) + 1;
		}
		us_b_sum += bubble_sort(A, n);
		s_b_sum += bubble_sort(A, n);
	}
	us_b_avg = us_b_sum / 10.0;
	s_b_avg = s_b_sum / 10.0;
	for (int j = 1;j <= 10;j++) {
		for (int i = 0;i < n;i++) {
			A[i] = (rand() % 1000000) + 1;
		}
		us_fb_sum += flagBubble_sort(A, n);
		s_fb_sum += flagBubble_sort(A, n);
	}
	us_fb_avg = us_fb_sum / 10.0;
	s_fb_avg = s_fb_sum / 10.0;
	for (int j = 1;j <= 10;j++) {
		for (int i = 0;i < n;i++) {
			A[i] = (rand() % 1000000) + 1;
		}
		us_i_sum += ins_sort(A, n);
		s_i_sum += ins_sort(A, n);
	}
	us_i_avg = us_i_sum / 10.0;
	s_i_avg = s_i_sum / 10.0;
	//After calculating the avg times of all of five functions, writing them on the excel sheet
	ofstream thefile("data.csv");
	if (thefile.is_open()) {
		thefile << "Algorithm,Array Size,Array Type,Number of Runs,Avg. Time Taken(s)" << endl;
		thefile << "Wrong Selection Sort," << n << ",Unsorted,10," << us_ws_avg << endl;
		thefile << "Wrong Selection Sort," << n << ",Sorted,10," << s_ws_avg << endl;
		thefile << "Right Selection Sort," << n << ",Unsorted,10," << us_rs_avg << endl;
		thefile << "Right Selection Sort," << n << ",Sorted,10," << s_rs_avg << endl;
		thefile << "Bubble Sort without Flag," << n << ",Unsorted,10," << us_b_avg << endl;
		thefile << "Bubble Sort without Flag," << n << ",Sorted,10," << s_b_avg << endl;
		thefile << "Flagged Bubble Sort," << n << ",Unsorted,10," << us_fb_avg << endl;
		thefile << "Flagged Bubble Sort," << n << ",Sorted,10," << s_fb_avg << endl;
		thefile << "Insertion Sort," << n << ",Unsorted,10," << us_i_avg << endl;
		thefile << "Insertion Sort," << n << ",Sorted,10," << s_i_avg << endl;
		thefile.close();
	}
	return 0;
}