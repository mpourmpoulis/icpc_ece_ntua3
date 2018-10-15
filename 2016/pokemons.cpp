#include  <iostream>
#include <cstdio>

using namespace std;

int n;
double money;
double price[1100000];
double selling_price[1100000];

int main(void)
{
	cin>>money;
	cin>>n;
	for(int i=0;i<n;i++) cin>>price[i];

	double max_price = price[n-1];
	for(int i=n-2; i>=0; i--){
		if(max_price < price[i]) max_price = price[i];
		selling_price[i] = max_price;
	}
	//cout<<endl<<endl;
	//for(int i=0;i<n;i++) cout<<price[i]<<" "<<selling_price[i]<<endl;

	double max_ratio = selling_price[0] / price[0];
	for(int i=0;i<n-1;i++){
		if((selling_price[i] / price[i]) > max_ratio) max_ratio = (selling_price[i]/price[i]);
	}
	cout<<(max_ratio-1) * money<<endl;
}