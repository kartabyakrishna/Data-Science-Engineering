#include<iostream>
#include<queue>
#include<stack>
using namespace std;
int main(){
	queue<int> q;
	stack<int> s;
	
	cout<< "enter the numbers of integers to put in : ";
	int n;
	cin>>n;
	
	for(int i=0;i<n;i++){
		int p;
		cin>>p;
		q.push(p);
	}
	cout<<"before reverse" <<endl;;
	for(int i=0;i<n;i++){
		s.push(q.front());
		cout<<q.front() << " ";
		q.pop();
	}

	for(int i=0;i<n;i++){
		q.push(s.top());
		s.pop();
	}
	
	cout<<endl;
	
	cout<<"after reverse "<<endl;
	for(int i=0;i<n;i++){
		cout<< q.front()<< " ";
		q.pop();
	}
}
