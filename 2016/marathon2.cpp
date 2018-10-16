#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class UnionTree{
	public:
		void init(int numb);
		bool sameRoot(int x,int y);
		void unite(int x,int y);
		int  treePathCompression(int x);
	private:
		int n;
		std::vector<int> parent,numberOfChildren;
};


typedef  pair<double,double> TimePlace;
#define InvalidTimePlace make_pair(-1.0,-1.0)


bool cmp_pair_double(const pair<double,double> &one, const pair<double,	double> &two)
{
	return one.second < two.second;
}

class Meeting {
public:
	int id_one,id_two;
	TimePlace tp;
	bool operator < (const Meeting & other) const
	{
		return tp.first > other.tp.first;
	}
	friend ostream & operator << (ostream &out, const Meeting &m) {
		out<<"Meeting"<<endl;
		out<<m.id_one<<" "<<m.id_two<<endl;
		out<<m.tp.first<<" "<<m.tp.second <<endl;
	} 
};




class GroupDataStructure{
	public:
		int  current_group(int id)
		{
			return utree.treePathCompression(id);
		}
		int get_next_group(int id)
		{
			id = current_group(id);
			return current_group(next_group[id]);
		}
		int get_back_group(int id)
		{
			id = current_group(id);
			return current_group(back_group[id]);
		}

		TimePlace compute_colision_t_and_x_raw(double x1, double v1, double t1, double x2, double v2, double t2)
		{
			if(v1 == v2) return make_pair(-1,-1);
			double rhs = x2 - x1 + v1*t1 - v2*t2;
			double lhs = v1 - v2; //bug here before
			double tcol = rhs / lhs;
			double xcol = x1 + v1 * (tcol-t1);
			if(tcol < max(t1,t2) - 0.00000001) return InvalidTimePlace;
			return make_pair(tcol,xcol);
		}

		TimePlace compute_colision(int id_one, int id_two)
		{
			id_one = current_group(id_one);
			id_two = current_group(id_two);
			if(id_one >=1649 && id_one <= 1651 && id_two >=1649 && id_two <= 1651) cout <<"id "<<id_one <<" "<<id_two<<endl;
			if(id_one == id_two) return InvalidTimePlace;
			return compute_colision_t_and_x_raw(x[id_one],v[id_one],t[id_one],x[id_two],v[id_two],t[id_two]);
		}

		Meeting compute_meeting(int id_one, int id_two)
		{
			Meeting m;
			m.id_one = current_group(id_one);
			m.id_two = current_group(id_two);
			m.tp = compute_colision(id_one,id_two);
			return m;
		}

		void apply_meeting(const Meeting &m)
		{
			int id_one = current_group(m.id_one);
			int id_two = current_group(m.id_two);
			int next_group_new = max(get_next_group(id_one),get_next_group(id_two));
			int back_group_new = min(get_back_group(id_one),get_back_group(id_two));
			utree.unite(id_one,id_two);
			int new_group = utree.treePathCompression(id_one);
			k[new_group] = k[id_one] + k[id_two];
			t[new_group] = m.tp.first;
			x[new_group] = m.tp.second;
			v[new_group] = 100 / k[new_group];
			next_group[new_group] = next_group_new;
			back_group[new_group] = back_group_new;
		}

		bool valid_meeting(const Meeting &m)
		{
			if(m.tp == InvalidTimePlace) return false;
			int id_one = current_group(m.id_one);
			int id_two = current_group(m.id_two);
			TimePlace tmp = compute_colision(id_one,id_two);
			return (m.tp == tmp);
		}

		void read_input(int n)
		{
			utree.init(n);
			t.resize(n,0.0);
			x.resize(n);
			v.resize(n);
			k.resize(n);
			vector<pair<double,double>> tmp;
			tmp.resize(n);
			for(int i=0;i<n;i++){
				cin>>tmp[i].first; cin>>tmp[i].second;
			}
			sort(tmp.begin(),tmp.end(),cmp_pair_double);
			for(int i=0;i<n;i++){
				k[i] = tmp[i].first;
				x[i] = tmp[i].second;
				v[i] = 100/k[i];
			}
			for(int i=0;i<n;i++){
				next_group.push_back(i+1);
				back_group.push_back(i-1);
			}
			back_group[0] = 0;
			next_group[n-1] = n-1;
		}

		vector<int> next_group,back_group;
		vector<double> t,x,v,k;
		UnionTree utree;
};





int main()
{
	GroupDataStructure g;
	priority_queue<Meeting, vector<Meeting>> q;
	int n; cin>>n;
	g.read_input(n);
	for(int i=0;i<n;i++){
		Meeting m;
		m = g.compute_meeting(i,g.get_next_group(i));
	    if(i == 1651) cout<<"group 1649" << m<<endl;
		if(g.valid_meeting(m)) q.push(m);

	}
	//cout<<"queue"<<endl;
	while(!q.empty()){
		Meeting m = q.top(); q.pop();
	//	cout<<m<<endl;
	//	cout<<"next is "<<g.get_next_group(1)<<endl;
		if(g.valid_meeting(m)) {
			g.apply_meeting(m);
			Meeting mnext, mback;
			mnext = g.compute_meeting(m.id_one,g.get_next_group(m.id_one));
			mback = g.compute_meeting(m.id_one,g.get_back_group(m.id_one));
			if(m.id_one == 1649 || m.id_two == 1649) cout<<"menxt and mback"<<endl<<mnext<<mback<<endl;
			//if(g.valid_meeting(mnext) && g.valid_meeting(mback)) q.push(min(mnext,mback));
			 if(g.valid_meeting(mnext)) q.push(mnext);
			 if(g.valid_meeting(mback)) q.push(mback);
		}
	}
	//Meeting mm = g.compute_meeting(1649,8221);
	//cout<<mm; //with an endl we have segmentation fault :D
	//cout<<g.t[1649]<<endl<<g.t[8221]<<endl<<g.v[1649]<<endl<<g.v[8221]<<endl<<g.x[1649]<<endl<<g.x[8221]<<endl;
	vector<int> groups;
	for(int i=0;i<n;i++){
		if(g.current_group(i) == i) {
			groups.push_back(g.k[i]);
	//		cout << "surviving is " << i <<" with next group being " << g.get_next_group(i)<<endl;
		}
	}

	cout<<groups.size()<<endl;
	for(int i=0;i<groups.size()-1;i++) cout<<groups[i]<<" ";
	cout<<groups.back()<<endl;	
}







void UnionTree::init(int numb)
{
	int i;
	n=numb;
	parent.clear();
	numberOfChildren.clear();
	parent.resize(n);
	numberOfChildren.resize(n);
	for(i=0;i<n;i++){
		parent[i]=i;
		numberOfChildren[i]=1;
	}
}


bool UnionTree::sameRoot(int x,int y)
{
	return treePathCompression(x)==treePathCompression(y);
}

int UnionTree::treePathCompression(int x)
{
	if(parent[x]!=x) parent[x]=treePathCompression(parent[x]);
	return parent[x];
}



void UnionTree::unite(int x,int y)
{
	if(sameRoot(x,y)) return;
	int py,px;
	py=treePathCompression(y);
	px=treePathCompression(x);
	if(numberOfChildren[py]>numberOfChildren[px]){
		numberOfChildren[py]+=numberOfChildren[px];
		parent[px]=py;
	}
	else{
		numberOfChildren[px]+=numberOfChildren[py];
		parent[py]=px;
	}
}