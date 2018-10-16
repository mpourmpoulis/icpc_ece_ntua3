#include <iostream>
#include <vector>
#include <list>
#include<climits>
#include<string>
#include<unordered_map>
using namespace std;

/* Hashmap for edges of graph, priority queue for dijkstra and
 * every element of queue has a list with previous history of visited nodes
 */


typedef struct info_route{
	int node;
	double cost;
	int limit;
	list<int> prev_node;
}route;

typedef struct{
	int v;
	int l;
}vl_value;

unordered_map<string,vl_value> LV;

void swap(route *x, route *y){
    route temp = *x;
    *x = *y;
    *y = temp;
}

// A class for Min Heap
class MinHeap
{
    route *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int cap){
        heap_size = 0;
        capacity = cap;
        harr = new route[cap];
    }

    bool isEmpty(){
    	return (heap_size==0);
    }
    // to heapify a subtree with the root at given index
    void MinHeapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && harr[l].cost < harr[i].cost)
            smallest = l;
        if (r < heap_size && harr[r].cost < harr[smallest].cost)
            smallest = r;
        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // Method to remove minimum element (or root) from min heap
    route extractMin(){
        if (heap_size <= 0){
        	route temp;
        	temp.cost = INT_MAX;
            return temp;
        }
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        // Store the minimum value, and remove it from heap
        route root = harr[0];
        harr[0] = harr[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    // Decreases value of key at index 'i' to new_val.  It is assumed that
    // new_val is smaller than harr[i].
    void decreaseKey(int i, route new_val){
        harr[i] = new_val;
        while (i != 0 && harr[parent(i)].cost > harr[i].cost)
        {
           swap(&harr[i], &harr[parent(i)]);
           i = parent(i);
        }
    }

    // Returns the minimum key (key at root) from min heap
    route getMin() { return harr[0]; }

    // This function deletes key at index i. It first reduced value to minus
    // infinite, then calls extractMin()
    void deleteKey(int i){
    	route temp;
    	temp.cost = INT_MIN;
        decreaseKey(i, temp);
        extractMin();
    }

    // Inserts a new key 'k'
    void insertKey(route k){
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)].cost > harr[i].cost)
        {
           swap(&harr[i], &harr[parent(i)]);
           i = parent(i);
        }
    }
};


vector<int> *neighboors;

list<int> navigate(int start, int starting_limit, int destination){
	route sr;
	sr.cost=0;
	sr.limit=starting_limit;
	sr.node=start;
	MinHeap pqueue(100000);
	pqueue.insertKey(sr);

	while(!pqueue.isEmpty() && pqueue.getMin().node!=destination){
		route temp = pqueue.extractMin();
		for(int i=0; i<neighboors[temp.node].size(); i++){
			string key = to_string(temp.node)+to_string(neighboors[temp.node][i]);
			int nlimit = LV[key].v;
			if (nlimit==0) nlimit = temp.limit;
			double ncost = 1.0*LV[key].l/nlimit + temp.cost;
			route ntemp;
			ntemp.cost = ncost;
			ntemp.limit = nlimit;
			ntemp.prev_node = temp.prev_node;
			ntemp.prev_node.push_back(temp.node);
			ntemp.node = neighboors[temp.node][i];
				pqueue.insertKey(ntemp);
		}

	}
	if(pqueue.isEmpty() || pqueue.getMin().node!= destination){
		list<int> emptyx;
		return emptyx;
	}
	list<int> path;
	path = pqueue.getMin().prev_node;
	path.push_back(destination);
	return path;
}

void showlist(list <int> g)
{
    list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        if(it==g.begin()) cout << *it;
        else cout << " " << *it;
    cout << '\n';
}

int main() {
	int N,M,D;
	cout << "Enter input" << endl;
	cin >> N >> M >> D;
	neighboors = new vector<int>[N];

	for(int i=0; i<M; i++){
		int a,b,v,l;
		cin >> a >> b >> v >> l;
		vl_value tvalue; tvalue.l=l; tvalue.v=v;
		LV[to_string(a)+to_string(b)]=tvalue;
		neighboors[a].push_back(b);
	}

	list <int> nav = navigate(0,70,D);
	showlist(nav);
	return 0;
}
