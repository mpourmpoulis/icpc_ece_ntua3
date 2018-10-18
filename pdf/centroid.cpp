#include <vector>

vector<vector<int> > v;
vector<int> &num_children;
vector<bool> visited;



int dfs_count_children(int root)
{
	int sum = 0;
	visited[root] = true;
	for(int node : v[root]){
		if(!visited[node]) sum += dfs_count_children(node);
	}
	num_children[root] = sum + 1;
	return sum + 1;
}

int find_centroid()
{
	int root = 0; bool centroid_found = false;
	dfs_count_children(root);
	while(!centroid_found){
		centroid_found = true;
		for(int node : v[root]){
			if(num_children[node] > v.size()/2){
				centroid_found = false;
				root = node; break;
			}
		} 
	}
}


 


















