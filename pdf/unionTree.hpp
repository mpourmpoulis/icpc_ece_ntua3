#ifndef header_uniontree_hpp
# define header_uniontree_hpp


# include <vector>


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



# endif
