#include <iostream>

class Tree
{
	private:
		int data;
		Tree* left_node {nullptr};
		Tree* right_node {nullptr};
		
	public:
		Tree(const int& d) : data(d) 
		{
			
		}
	
		void setLeftSubTree( Tree& left_sub_tree)
		{
			left_node = &left_sub_tree;
		}
		
		void setRightSubTree( Tree& right_sub_tree)
		{
			right_node = &right_sub_tree ;
		}
	
		Tree * getSubTreeWithMaxSum()
		{
 			int sum_of_left_subtree = 0;
			int sum_of_right_subtree = 0;
			
			getSumOfAllNodesOfTree(left_node,sum_of_left_subtree) ;
			getSumOfAllNodesOfTree(right_node,sum_of_right_subtree);
			return sum_of_left_subtree > sum_of_right_subtree ? left_node : right_node;
		}
		
		private:
		void getSumOfAllNodesOfTree(Tree* tree, int& sum)
		{
			if (!tree)
				return;
				
			sum += tree->data;
			std::cout << sum << " " << std::endl;
			
			getSumOfAllNodesOfTree(tree->left_node,sum);
			getSumOfAllNodesOfTree(tree->right_node,sum);
		}
	
};



int main()
{
	Tree root(0);
	Tree t1(100);
	Tree t2(2);
	Tree t3(3);
	Tree t4(4);
	
	root.setLeftSubTree(t1);
	root.setRightSubTree(t2);
	t1.setLeftSubTree(t3);
	t2.setLeftSubTree(t4);
	
	
	Tree *subtree_with_max_sum = root.getSubTreeWithMaxSum();
	
	if (subtree_with_max_sum == &t2 )
		std::cout << "It worked";
		
	
	
}
