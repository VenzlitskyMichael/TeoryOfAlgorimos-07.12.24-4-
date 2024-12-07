#include <iostream>
using namespace std;

template <typename T>
class Tree {
private:
    struct Node {
        T data;         
        Node* left;     
        Node* right;    
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    Node* root; 

    Node* copy(Node* current) {
        if (!current) return nullptr;
        Node* newNode = new Node(current->data);
        newNode->left = copy(current->left);
        newNode->right = copy(current->right);
        return newNode;
    }

    void clear(Node* current) {
        if (current) {
            clear(current->left);
            clear(current->right);
            delete current;
        }
    }

    void printInOrder(Node* current) const {
        if (current) {
            printInOrder(current->left);
            std::cout << current->data << " ";
            printInOrder(current->right);
        }
    }

    Node* erase(Node* current, const T& key) {
        if (!current) return nullptr;

        if (key < current->data) {
            current->left = erase(current->left, key);
        }
        else if (key > current->data) {
            current->right = erase(current->right, key);
        }
        else {
            if (!current->left) {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            else if (!current->right) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            Node* temp = findMin(current->right);
            current->data = temp->data;
            current->right = erase(current->right, temp->data);
        }
        return current;
    }

    Node* findMin(Node* current) const {
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        clear(root);
    }

    Tree(const Tree& other) : root(nullptr) {
        root = copy(other.root);
    }

    Tree& operator=(const Tree& other) {
        if (this == &other) return *this; 
        clear(root); 
        root = copy(other.root); 
        return *this;
    }

    void add(const T& value) {
        root = add(root, value);
    }

    Node* add(Node* current, const T& value) {
        if (!current) return new Node(value);
        if (value < current->data) {
            current->left = add(current->left, value);
        }
        else {
            current->right = add(current->right, value);
        }
        return current;
    }

    void print() const {
        if (!root) {
            cout << "Tree is empty." << endl;
        }
        else {
            printInOrder(root);
            cout << endl;
        }
    }

    void erase(const T& key) {
        root = erase(root, key);
    }
};

int main() {
    Tree<int> tree;
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);
    tree.add(7);
    tree.add(12);
    tree.add(18);

    cout << "Original Tree: ";
    tree.print();

    Tree<int> treeCopy = tree;
    cout << "Copied Tree: ";
    treeCopy.print();

    tree.erase(10);
    cout << "Tree after erasing 10: ";
    tree.print();

    Tree<int> treeAssigned;
    treeAssigned = treeCopy;
    cout << "Assigned Tree: ";
    treeAssigned.print();

    return 0;
}
