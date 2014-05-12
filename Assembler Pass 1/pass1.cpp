#include <iostream>
#include<stdio.h>
#include<cstdio>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
	ofstream file("out.txt");
	freopen("in.txt", "r", stdin);
//	freopen("out.txt","w",stdout);
	string s;
//	cin >>s;
	getline(cin, s);
	cout << s;
	file << s;
	file.close();
}
