#include "unionTree.hpp"


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

