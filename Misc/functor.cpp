#include <iostream>
using namespace std;

template <class T> struct compare {
	compare() {}
	bool operator() (const T& v1,const T& v2) const {
		return v1 < v2;
	}
};

template <typename T> void sort (T A[], int sz , compare<T> co) {
	for(int i=0;i<sz;i++) {
		int j=i;;
		T t = A[i];
		for(;j >0 ;j--) {
			if(!(co(t,A[j-1]))) {
				break;
			}
			A[j] = A[j-1];
		}
		A[j] = t;
	}
}

int main() {
	int nums[10] = {10,12,1,2,9,7,3,5,1,17};
	string names[3] = {"foo","names","abc"};
	float f[3] = {1.1,8.9,2.2};
	compare<int> co;
	sort(nums,10,co);
	compare<string> co1;
	sort(names,3,co1);
	compare<float> co2;
	sort(f,3,co2);
	for(int i=0;i<10;i++) {
		cout<<nums[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<3;i++) {
		cout<<names[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<3;i++) {
		cout<<f[i]<<" ";
	}
	cout<<endl;
	return 0;
}