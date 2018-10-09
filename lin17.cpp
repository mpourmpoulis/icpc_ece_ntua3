#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

int n,m;
vector<vector<int> > v,e;
vector<bool> visited;

void bfs(int node){
	queue<int> q;
	q.push(node); visited[node]=true;
	while(!q.empty()){
		int curr=q.front(); q.pop();
		for(int next : v[curr]){
			if(visited[next] == false){
				visited[next] = true;
				q.push(next);
			}
		}
	}
}

int get_rank()
{
	int rank = m;
	visited.resize(m,false);
	for(int i=0;i<n;i++){
		if(visited[i] == false){
			rank--;
			bfs(i);
		}
	}
	return rank;
}

void read_input()
{
	cin >> m >> n;
	v.resize(m);
	e.resize(n);
	for(int i=0;i<m;i++){
		int ck; cin>>ck;
		for(int j=0;j<ck;j++){
			int loc;
			cin >> loc;
			e[loc-1].push_back(i);
		}
	}

	for(int i=0;i<n;i++){
		v[e[i][0]].push_back(e[i][1]);
		v[e[i][1]].push_back(e[i][0]);
	}
}




int main()
{
	read_input();
	cout<<get_rank()<<endl;
}

























