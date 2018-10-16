#ifndef header_UnionFind2D_hpp
# define header_UnionFind2D_hpp

#include "unionTree.hpp"
#include <stdexcept>

class UnionFind2D{	
	public:
		UnionFind2D(int nrow,int ncol);
		bool sameRoot(int row1, int col1, int row2, int col2);
		void unite(int row1, int col1, int row2, int col2);
		int root(int row, int col);
	private:
		void check_point(int row, int col) const throw (std::logic_error);
		int num_row,num_col;
		UnionTree tree;
};















#endif




