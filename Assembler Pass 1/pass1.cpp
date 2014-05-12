#include <iostream>
#include<stdio.h>
#include<cstdio>
using namespace std;

int main(int argc, char **argv) {

	freopen("in.txt", "r", stdin);
	freopen("out.txt","w",stdout);
	string s;
//	cin >>s;
	getline(cin,s);
	cout<<s;
}
