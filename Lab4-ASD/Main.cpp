#include <iostream>
#include "windows.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <ctime>
#include "List.h"

using namespace std;

class Sort {
private:
	int* Array;
	vector<int> buf_vector;
	unsigned int start_time = 0, end_time = 0;
	unsigned long long Compare_number = 0, Swap_number = 0;
	void Create_Random(int n) {
		Array = new int[n];
		for (int i = 0; i < n; i++) {
			buf_vector.push_back(rand());
			Array[i] = buf_vector[i];
		}
	}
	void Create_Sort(int n) {
		Create_Random(n);
		sort(buf_vector.begin(), buf_vector.end());
		for (int i = 0; i < n; i++) {
			Array[i] = buf_vector[i];
		}
	}
	void Create_Sort_Inv(int n) {
		Create_Sort(n);
		reverse(buf_vector.begin(), buf_vector.end());
		for (int i = 0; i < n; i++) {
			Array[i] = buf_vector[i];
		}
	}
	void Swap(int ind_i, int ind_j) {
		int buf = Array[ind_i];
		Array[ind_i] = Array[ind_j];
		Array[ind_j] = buf;
	}
	void Output_Array(int n) {
		for (int i = 0; i < n; i++) {
			cout << ' ' << Array[i];
		}
		cout << endl;
	}
	void Sort_Choice(int n) {
		//Compare_number = 0, Swap_number = 0;
		start_time = clock();
		int min_index;
		for (int i = 0; i < n - 1; i++) {
			min_index = i;
			for (int j = i + 1; j < n; j++) {
			//	Compare_number++;
				if (Array[j] < Array[min_index]) { 
					min_index = j; 
				}
			}
			if (min_index != i) {
				Swap(i, min_index);
			//	Swap_number++;
			}
		}
		end_time = clock();
		cout << "Time of running sort: " << end_time - start_time << " ms." << endl;
		//cout << "Compare: " << Compare_number << endl;
		//cout << "Swap: " << Swap_number << endl;
	}
	void Sort_By_Inserts(int n) {
		//Compare_number = 0, Swap_number = 0;
		start_time = clock();
		int min;
		for (int i = 1; i < n; i++) {
			min = Array[i];
			int j = i;
			//Compare_number++;
			while (j > 0 && Array[j - 1] > min) {
			//	Compare_number++;
				Array[j] = Array[j - 1];
			//	Swap_number++;
				j--;
			//	if(j <= 0) Compare_number--; //ןנמגונÿעü מעהוכüםמ גנולÿ
			}
			Array[j] = min;
			//Swap_number++;
		}
		end_time = clock();
		cout << "Time of running sort: " << end_time - start_time << " ms." << endl;
		//cout << "Compare: " << Compare_number << endl;
		//cout << "Swap: " << Swap_number << endl;
	}
	void Bubble_Sort(int n) {
		//Compare_number = 0, Swap_number = 0;
		start_time = clock();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				//Compare_number++;
				if (Array[j + 1] <= Array[j]) {
					Swap(j, j + 1);
				//	Swap_number++;
				}
			}
		}
		end_time = clock();
		cout << "Time of running sort: " << end_time - start_time << " ms." << endl;
		//cout << "Compare: " << Compare_number << endl;
		//cout << "Swap: " << Swap_number << endl;
	}
	void Recursion_Quick_Sort(int left, int right) {
		int i = left;
		int j = right;
		int x = Array[(left + right) / 2];
		while (i <= j) {
			Compare_number++;
			while (Array[i] < x) { 
				i++; 
				Compare_number++;
			}
			Compare_number++;
			while (Array[j] > x) {
				j--;
				Compare_number++;
			}
			if (i <= j) {
				Swap(i, j);
				Swap_number++;
				i++;
				j--;
			}
		}
		if(left < j) Recursion_Quick_Sort(left, j);
		if(i < right) Recursion_Quick_Sort(i, right);
	}
	void Quick_Sort(int n) {
		Compare_number = 0, Swap_number = 0;
		start_time = clock();
		Recursion_Quick_Sort(0, n - 1);
		end_time = clock();
		cout << "Time of running sort: " << end_time - start_time << " ms." << endl;
		cout << "Compare: " << Compare_number << endl;
		cout << "Swap: " << Swap_number << endl;
	}

	void Insertin_list_sort(int n) {
		Compare_number = 0, Swap_number = 0;
		start_time = clock();
		vector<int> sort = { -1 };
		for (int i = 0; i < n; i++) {
			sort.push_back(Array[i]);
		}
		List list_for_sort(n);
		list_for_sort.push_back(0);
		int p, q, K;
		int list_size_test = sort.size() + 1;
		List::Iterator it, it_prev;
		vector<int>::iterator it_v = sort.begin();
		for (int j = n - 1; j > 0; j--) {
			it_prev = list_for_sort.begin();
			it = list_for_sort.begin();
			p = *it; // L2
			q = 0;
			K = *(it_v + j);
		L3:
			Compare_number++;
			if (K <= *(it_v + p)) { // L3
				if (q == 0) {// L5
					list_for_sort.add_begin(j);
				}
				else
					list_for_sort.insert(it_prev, j);
			}
			else {
				q = p; // L4
				it_prev = it;
				it++;
				p = *it;
				if (p > 0) goto L3;
				else {
					list_for_sort.insert(it_prev, j);//L5
				}
			}
		}
		it = list_for_sort.begin();
		for (int i = 0; i < n; i++) {
			Array[i] = sort[*it];
			it++;
		}
		end_time = clock();
		cout << "Time of running sort: " << end_time - start_time << " ms." << endl;
		cout << "Compare: " << Compare_number << endl;
		cout << "Swap: " << Swap_number << endl;
	}

public:
	void Sorting_Choice(int n) { // T = O(n^2);
		if (n < 2) {
			cout << "Error! Incorrect size of Array." << endl;
			return;
		}
		Create_Random(n);
		//cout << "Basic random array:";
		//Output_Array(n);
		Sort_Choice(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort(n);
		//cout << "Basic sort array:";
		//Output_Array(n);
		Sort_Choice(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort_Inv(n);
		//cout << "Basic sort inverse array:";
		//Output_Array(n);
		Sort_Choice(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;
	}
	void Sorting_Inserts(int n) { // T = O(n^2);
		if (n < 2) {
			cout << "Error! Incorrect size of Array." << endl;
			return;
		}
		Create_Random(n);
		cout << "Basic random array:";
		Output_Array(n);
		Sort_By_Inserts(n);
		cout << "Sort array:";
		Output_Array(n);
		delete[] Array;

		Create_Sort(n);
		//cout << "Basic sort array:";
		//Output_Array(n);
		Sort_By_Inserts(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort_Inv(n);
		//cout << "Basic sort inverse array:";
		//Output_Array(n);
		Sort_By_Inserts(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;
	}
	void Sorting_Bubble(int n) { // T = O(n^2);
		if (n < 2) {
			cout << "Error! Incorrect size of Array." << endl;
			return;
		}
		Create_Random(n);
		cout << "Basic random array:";
		Output_Array(n);
		Bubble_Sort(n);
		cout << "Sort array:";
		Output_Array(n);
		delete[] Array;

		Create_Sort(n);
		//cout << "Basic sort array:";
		//Output_Array(n);
		Bubble_Sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort_Inv(n);
		//cout << "Basic sort inverse array:";
		//Output_Array(n);
		Bubble_Sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;
	}
	void Sorting_Quick(int n) { //T = O(nlogn);
		if (n < 2) {
			cout << "Error! Incorrect size of Array." << endl;
			return;
		}
		Create_Random(n);
		cout << "Basic random array:";
		Output_Array(n);
		Quick_Sort(n);
		cout << "Sort array:";
		Output_Array(n);
		delete[] Array;

		Create_Sort(n);
		//cout << "Basic sort array:";
		//Output_Array(n);
		Quick_Sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort_Inv(n);
		//cout << "Basic sort inverse array:";
		//Output_Array(n);
		Quick_Sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;
	}
	void Sorting_List(int n) {// T = O(n^3);
		if (n < 2) {
			cout << "Error! Incorrect size of Array." << endl;
			return;
		}
		Create_Random(n);
		//cout << "Basic random array:";
		//Output_Array(n);
		Insertin_list_sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort(n);
		//cout << "Basic sort array:";
		//Output_Array(n);
		Insertin_list_sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;

		Create_Sort_Inv(n);
		//cout << "Basic sort inverse array:";
		//Output_Array(n);
		Insertin_list_sort(n);
		//cout << "Sort array:";
		//Output_Array(n);
		delete[] Array;
	}
};
int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int n = 1, exit = 1;
	while (exit == 1) {
		int sort = 0;
		Sort S;
		cout << "1.Sorting by choice" << endl << "2.Sorting by inserts" << endl << "3.Bubble sort" << endl << "4.Quick sorting" << endl << "5.Sort by inserting into a list" << endl <<  "6.Exit" << endl << "Choose a way:" << endl;
		cin >> sort;
		switch (sort)
		{
		case 1:
			cout << "Input size of Array:" << endl << "n = ";
			cin >> n;
			S.Sorting_Choice(n);
			break;
		case 2:
			cout << "Input size of Array:" << endl << "n = ";
			cin >> n;
			S.Sorting_Inserts(n);
			break;
		case 3:
			cout << "Input size of Array:" << endl << "n = ";
			cin >> n;
			S.Sorting_Bubble(n);
			break;
		case 4:
			cout << "Input size of Array:" << endl << "n = ";
			cin >> n;
			S.Sorting_Quick(n);
			break;
		case 5:
			cout << "Input size of Array:" << endl << "n = ";
			cin >> n;
			S.Sorting_List(n);
			break;
		case 6:
			exit = 0;
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "This sort does not exist" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}
