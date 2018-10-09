#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
	int N;
	cin >> N;
	string note;

	bool scales[12][12];
	for (int i=0; i<12; i++){
		for(int k=0; k<12; k++){
			scales[i][k]=false;

		}
		scales[i][(i+0)%12]=true;
		scales[i][(i+2)%12]=true;
		scales[i][(i+4)%12]=true;
		scales[i][(i+5)%12]=true;
		scales[i][(i+7)%12]=true;
		scales[i][(i+9)%12]=true;
		scales[i][(i+11)%12]=true;

	}
	//printf("Song 0\n");
	long int min_songs = 0;
	bool flag = true;
	bool state[12];
	bool first_song = true;
	bool first_state[12]; memset(state,true,sizeof(state));
	string nn[12];
	int notes = 0;
	nn[0]="Do";
	nn[1]="Do#";
	nn[2]="Re";
	nn[3]="Re#";
	nn[4]="Mi";
	nn[5]="Fa";
	nn[6]="Fa#";
	nn[7]="Sol";
	nn[8]="Sol#";
	nn[9]="La";
	nn[10]="La#";
	nn[11]="Si";
	char tmp[10];
	for(int i=0; i<N; i++){

		scanf("%s\n", &tmp);
		note = string(tmp);
		int note_n=0;

		while(nn[note_n] != note) note_n++;
		
		flag = false;
		for(int z=0; z<12; z++){
			state[z] = state[z] && scales[z][note_n];
			flag |= state[z];
		}

		if(!flag){
			if(first_song) {
				memcpy(first_state, state, sizeof(state));
				first_song = false;
			}
			memset(state,true,sizeof(state));
			min_songs++;
			notes=0;

			for(int z=0; z<12; z++){
				state[z] = state[z] && scales[z][note_n];
			}
		}
		notes++;
	}
	min_songs++;
	for(int z=0;z<12;z++){
		if(state[z] && first_state[z]){
			min_songs--; break;
		}
	}
	if(notes < 2) min_songs--;
	cout << min_songs << endl;

}




















/*
switch (note){
			case string("Do" : note_n=0;
			break;
			case "Do#": note_n=1;
			break;
			case "Re" : note_n=2;
			break;
			case "Re#" : note_n=3;
			break;
			case "Mi" : note_n=4;
			break;
			case "Fa" : note_n=5;
			break;
			case "Fa#" : note_n=6;
			break;
			case "Sol" : note_n=7;
			break;
			case "Sol#" : note_n=8;
			break;
			case "La" : note_n=9;
			break;
			case "La#" : note_n=10;
			break;
			case "Si" : note_n=11;
			break;

		}

		*/

