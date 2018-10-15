#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int sum_of_letters[10];


void precompute_sums()
{
	int power_of_26 = 1;
	sum_of_letters[0] = 0;
	for(int i=1;i<7;i++){
		power_of_26 *= 26;
		sum_of_letters[i] = sum_of_letters[i-1] + i*power_of_26;
		//HERE THERE WAS THE BUG :)
		//we have power_of_26 tuplets but the size of each tuplet varies!!!!
	}
}

int find_type_of_tuplet(int position)
{
	int total_letters = position + 1; //querries are zero indexed!
	for(int i=1;i<7;i++){
		if(total_letters <= sum_of_letters[i]) return i;
	}
	return 7;
}


int get_tuplet_number(int position, int tuplet_type)
{
	position -= sum_of_letters[tuplet_type-1];
	return position / tuplet_type;
}

int get_position_inside_tuplet(int position, int tuplet_type)
{
	position -= sum_of_letters[tuplet_type-1];
	return position % tuplet_type;
}

vector<int> get_base26_encoding_msb_to_lsb(int number,int tuplet_type)
{
	vector<int> ret;
	for(int i=0;i<tuplet_type;i++){
		ret.push_back(number % 26);
		number /=26;
	}
	reverse(ret.begin(),ret.end());
	return ret;
}

int main()
{
	int k; cin>>k;
	precompute_sums();
	int tuplet_type = find_type_of_tuplet(k);
	int tuplet_number = get_tuplet_number(k,tuplet_type);
	int position_inside_tuplet = get_position_inside_tuplet(k,tuplet_type);
	vector<int> ret = get_base26_encoding_msb_to_lsb(tuplet_number,tuplet_type);
	char output = 'A' + ret[position_inside_tuplet];
	cout<<output<<endl;
}





