#include <iostream>


class Tree
{
    private:
        int data;
        std::shared_ptr<Tree> left;
        std::shared_ptr<Tree> right;

    public:
        void setLeftSubTree(std::shared_ptr<Tree>& left_tree) {
            left = left_tree;
        }

        void setRightSubTree(std::shared_ptr<Tree>& right_tree) {
            right = right_tree;
        }

        Tree(int d) : data(d) { }

};


int main()
{
    Tree root(0);
    Tree left_node(1);
    Tree right_node(2);
    

}
