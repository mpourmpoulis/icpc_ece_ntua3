#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct bit {
	int cost;
	int phb;
	int a;
	int b;
} mybit[5000];

bool cmp(struct bit x, struct bit y) {
	return (x.cost < y.cost);
}

int n;



int solve() {
	sort(mybit, mybit + n, cmp);
	int total_cost = 0, i;
	for(i = n-1; i >= 0; i--)
		if(mybit[i].a == 1) total_cost+=mybit[i].cost;
	int flip_cost = 0;	
	for(i = n-1; i >= 0; i--)
		if(mybit[i].a == 1 && mybit[i].a != mybit[i].b) {
			flip_cost += total_cost - mybit[i].cost;
			total_cost -= mybit[i].cost;
		}
	for(i = 0; i < n; i++)
		if(mybit[i].a == 0 && mybit[i].a != mybit[i].b) {
			flip_cost += total_cost + mybit[i].cost;
			total_cost += mybit[i].cost;
		}
	return flip_cost;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d",&mybit[i].cost);
	char * tmp = new char[n + 5];
	
	scanf("%s", tmp);
	for(int i = 0; i < n; i++)
		if(tmp[i] == '0')
			mybit[i].a = 0;
		else mybit[i].a = 1;

	scanf("%s", tmp);
	
	for(int i = 0; i < n; i++)
		if(tmp[i] == '0')
			mybit[i].b = 0;
		else mybit[i].b = 1;
	free(tmp);
	
	
	cout << solve() << endl;
}
