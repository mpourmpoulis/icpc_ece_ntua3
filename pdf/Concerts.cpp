#include <iostream>
using namespace std;

char *order;
char *festival;
unsigned long long int **dp;
int main() {
	int K,N;
	cin >> K >> N;
	int H[26];
	for (int i=0; i<26; i++) cin >> H[i];
	order = new char [K+4];
	cin >> order;
	festival = new char[N+4];
	cin >> festival;


	dp = new unsigned long long int* [K];
	for (int i=0; i<K; i++){
		dp[i] = new unsigned long long int [N];

	}

	long int total=0;
	for (int z=N-1; z>=0; z--){
			//cout << festival[z] <<endl;
			//cout << order[K-1] << endl;
			if(festival[z]==order[K-1]) total++;
			dp[0][z] = total;
	}


	for (int i=1; i<K; i++){
		total=0;
		for (int z=N-1; z>=0; z--){
			dp[i][z]=total;
			if(festival[z]==order[K-i-1]){
				if(z+H[festival[z]-65]+1<N) total += dp[i-1][z+H[festival[z]-65]+1];
				total = total%(1000000000+7);
				dp[i][z] = total;
			}

		}
	}

	unsigned long long int sum=0;

	sum=dp[K-1][0]%(1000000000+7);
	cout << "Total combinations = " << sum << endl;

	return 0;
}
