#include<iostream>
using namespace std;
int fibo(int n){
	if(n<=1){
		return n;
	}else {
		return fibo(n-1)+fibo(n-2);
	}
}
void printFibo(int n){
	if(n>0){
		for(int i=0;i<n;i++){
			cout<<fibo(i)<<" ";
		}
	}else{
		cout<<"pls enter +ve n";
	}

}
int main(){
	int n ;
	cout<< "enter n : ";
	cin>>n ;
	printFibo(n);
}
