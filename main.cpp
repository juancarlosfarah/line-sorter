#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

/*
char line[];
char* linePtr;
char** listPtr;
*/

struct PointerArray {
	string** pointer;
	unsigned int length;
};

int GetLineCount(ifstream& ifs, const char filename[]) {
	ifs.open(filename);
	
	if (ifs.fail()) {
		cerr << "Failed to open file." << endl; 	
		exit(1);
	}

	int count = 0;
	string dummy;
	while (getline(ifs, dummy)) {
		count++;
	}
	
	ifs.close();

	return count;
}

void PrintArray(PointerArray* ptr) {
	string** tmpPtr = ptr->pointer;
	for (int i = 0; i < ptr->length; ++i) {
		cout << **tmpPtr << endl;
		tmpPtr++;
	}
	return;
}

void WriteArray(PointerArray* arr, ifstream& ifs, const char filename[]) {
	
	ifs.open(filename);
	
	if (ifs.fail()) {
		cerr << "Failed to open file." << endl; 	
		exit(1);
	}

	int index = 0;
	string line;
	while (getline(ifs, line) && index < arr->length) {
		string* ptr = new string;
		*ptr = line;
		arr->pointer[index] = ptr;
	
		/* this is to understand what is going on */	
		/*
		cout << *ptr << endl; 
		cout << ptr << endl;
		cout << &ptr << endl;
		cout << *arr->pointer[index] << endl;
		*/

		index++;
	}

	return;
}

PointerArray* ReadFile(const char filename[]) {
		
	ifstream ifs;

	unsigned int count = GetLineCount(ifs, filename);
	
	PointerArray* ptrArr = new PointerArray;
	ptrArr->pointer = new string*[count];
	ptrArr->length = count;

	WriteArray(ptrArr, ifs, filename);	

	//PrintArray(ptrArr);

	return ptrArr;
}

void WriteFile(string* arr[], ofstream& ofs, const char filename[]) {
		
}

bool Compare(const string s1, const string s2) {
	unsigned int l = s1.length();
	for (int i = 0; i < l; ++i) {
		try {
			int c1 = tolower(s1.at(i));
			int c2 = tolower(s2.at(i));
			if (c1 != c2) {
				if (c1 > c2) return true;
				return false;
			} 
		} catch (const out_of_range& oor) {
			cerr << "out of range error: "
			     << oor.what() << endl;
			return true;
		}
	} 	

	return false;
}

void Swap(string& s1, string& s2) {
	if (s1 != s2) {
		string tmp = s1;
		s1 = s2;
		s2 = tmp;
	}
	return;
}

void PutMinimum(PointerArray* ptr, int index) {

	string* ptr1 = ptr->pointer[index];
	string s1 = *ptr1;
	string* min = ptr1;

	for (unsigned int i = index + 1; i < ptr->length; ++i) {
		string* ptr2 = ptr->pointer[i];
		string s2 = *ptr2;
		if (Compare(*min, s2)) {
			min = ptr2;
		}
	}

	Swap(*ptr1, *min);

	return;
}

void SortArray(PointerArray* ptr) {

	for (unsigned int i = 0; i < ptr->length; ++i) {
		PutMinimum(ptr, i);		
	}

/*
	cout << ptr->length << endl;
	cout << "Test ab v bb: " << Compare("ab", "bb") << endl;
	cout << "Test bb v ab: " << Compare("bb", "ab") << endl;
	cout << "Test abc v bb: " << Compare("abc", "bb") << endl;
	cout << "Test bb v abc: " << Compare("bb", "abc") << endl;
	cout << "Test abc v abc: " << Compare("abc", "abc") << endl;
	cout << "Test a v b: " << Compare("a", "b") << endl;
	cout << "Test popul1231 v b231ss b: " << Compare("popul1231", "b231ss b") << endl;
*/

	return;
}

int main() {
  
	PointerArray* ptr = ReadFile("names.txt");
	
	SortArray(ptr);

	PrintArray(ptr);

	return 0;
}
