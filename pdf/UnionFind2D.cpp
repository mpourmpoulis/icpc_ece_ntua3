#include "UnionFind2D.hpp"
#include <cstdio>
UnionFind2D::UnionFind2D(int nrows,int ncols)
{
	num_row=nrows;
	num_col=ncols;
	tree.init(num_row * num_col);
	
}
	
bool UnionFind2D::sameRoot(int row1,int col1, int row2, int col2)
{
	check_point(row1,col1);
	check_point(row2,col2);
	return tree.sameRoot(row1 * num_col + col1, row2 * num_col + col2);
}

void UnionFind2D::unite(int row1, int col1, int row2, int col2)
{
	check_point(row1,col1);
	check_point(row2,col2);
	tree.unite(row1 * num_col +col1, row2 * num_col + col2);
}


void UnionFind2D::check_point(int row, int col) const throw (std::logic_error)
{
	if(row < 0 || row >= num_row || col < 0 || col >= num_col){
		fprintf(stderr,"Error:\nTried to access point (%d,%d) in an instance of UnionFind2D"
			" with (num_row=%d, num_col=%d)\n",row,col,num_row,num_col);
		throw(std::logic_error("out of bounds in UnionFind2D\n"));
	}
}

int UnionFind2D::root(int row, int col)
{
	check_point(row,col);
	return tree.treePathCompression(row * num_col + col);
}



