#include <iostream>
#include <algorithm>

template <typename Type>
struct TreeNode {
    Type value;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Type val) : value(val), height(1), left(nullptr), right(nullptr) {}
};

template <typename Type>
class Tree {
private:
    TreeNode<Type>* root;

    int getHeight(TreeNode<Type>* node) { return node ? node->height : 0; }
    int getBalance(TreeNode<Type>* node) { return node ? getHeight(node->left) - getHeight(node->right) : 0; }
    void updateHeight(TreeNode<Type>* node) {
        if (node) node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    TreeNode<Type>* rightRotate(TreeNode<Type>* y) {
        TreeNode<Type>* x = y->left;
        TreeNode<Type>* t = x->right;
        x->right = y;
        y->left = t;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    TreeNode<Type>* leftRotate(TreeNode<Type>* x) {
        TreeNode<Type>* y = x->right;
        TreeNode<Type>* t = y->left;
        y->left = x;
        x->right = t;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    TreeNode<Type>* insertRec(TreeNode<Type>* node, Type val) {
        if (!node) return new TreeNode<Type>(val);
        if (val < node->value)
            node->left = insertRec(node->left, val);
        else if (val > node->value)
            node->right = insertRec(node->right, val);
        else return node;  // Нет дублей

        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && val < node->left->value) return rightRotate(node);
        if (balance > 1 && val > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && val > node->right->value) return leftRotate(node);
        if (balance < -1 && val < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    TreeNode<Type>* searchRec(TreeNode<Type>* node, Type val) {
        if (!node) return nullptr;
        if (node->value == val) return node;
        if (val < node->value) return searchRec(node->left, val);
        return searchRec(node->right, val);
    }

    static void printInorder(TreeNode<Type>* node) {
        if (!node) return;
        printInorder(node->left);
        std::cout << node->value << " ";
        printInorder(node->right);
    }

    static void deleteTree(TreeNode<Type>* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    Tree(Type val) : root(new TreeNode<Type>(val)) {}
    ~Tree() { deleteTree(root); }
    void insert(Type val) { root = insertRec(root, val); }
    TreeNode<Type>* search(Type val) { return searchRec(root, val); }
    void printInorder() { printInorder(root); std::cout << std::endl; }
};