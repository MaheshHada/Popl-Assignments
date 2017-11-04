#include <bits/stdc++.h>
using namespace std;

int summation(int st,int fin) {
	int acc = 0;
	for(int i=st;i<=fin;i++) {
		acc += st;
		st++;
	}
	return acc;
}

//This recursive function at line 15 is not Tail Recursive
//Tail Recursion is used for space optimization on stack of the program the compiler need not save the stack frame
// as the return statement is the final statement int that function definition.
int summRecur(int st,int fin) {
	if(st == fin)
		return st;
	return st+summRecur(st+1,fin);
}

//Tail Recursive version
int sumHelper(int st,int fin,int acc) {
	if(st == fin) return acc + st;
	return sumHelper(st+1,fin,acc + st);
}

int summationTailRecursive(int st,int fin) {
	return sumHelper(st,fin,0);
}

int fib(int n) {
	if(n == 0 || n == 1) {
		return n;
	}
	return fib(n-1) + fib(n-2);
}

int fib_helper(int n,int a,int b) {
	if(n == 1) return b;
	return fib_helper(n-1,b,a+b);
}

int fib1(int n) {
	return fib_helper(n,0,1);
}

int fact(int n) {
	if(n == 0 || n == 1)
		return 1;
	return n*fact(n-1);
}

int factTailRechelper(int n,int ans) {
	if(n == 0)
		return ans;
	return factTailRechelper(n-1,n*ans);
}

int factTail(int n) {
	return factTailRechelper(n,1);
}

int fibg() {
	static int x = 0,y = 1;
	int u = x;
	x -= u;
	x += y;
	y += u;
	return x;
}

int main(){
	// cout<<summation(2,6)<<endl;
	// cout<<summRecur(2,6)<<endl;
	// cout<<summationTailRecursive(2,6)<<endl;
	// cout<<fib(7)<<endl;
	// cout<<fib1(7)<<endl;
	// cout<<fact(5)<<endl;
	// cout<<factTail(5)<<endl;
	int n = 8;
	int ans;
	for(int i=0;i<n;i++) {
		ans = fibg();
	}
	cout<<ans<<endl;
	return 0;
}