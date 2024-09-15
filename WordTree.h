#include <iostream>
#include <string>
using namespace std;
        
  
struct WordNode {
    
    WordNode(string s) {
        data = s;
        left = right = nullptr;
        count = 1;
    }
    
    ~WordNode() {
        cout << "Deleting " << data << endl; 
    }
    
    string data;
    WordNode *left;
    WordNode *right;
    int count;
};
        
class WordTree {
            
private:
    WordNode *root;

   void Insert(WordNode*& node, string str) {
        if (node == nullptr) {
            node = new WordNode(str);
        } else if (str == node->data) {
            node->count++;
        } else if (str < node->data) {
            Insert(node->left, str);
        } else {
            Insert(node->right, str);
        }
    }

    // helper for find occurance
    int findOccurrencesHelper(WordNode* node, string str){
        if (node == nullptr){
             return 0;
        }
        if (str == node->data){ 
            return node->count;
        }
        if (str < node->data){
            return findOccurrencesHelper(node->left, str);
        }
        return findOccurrencesHelper(node->right, str);
        }

    void freetree(WordNode* node){
        if (node == nullptr){
            return;
        }
        freetree(node->left);
        freetree(node->right);
        delete node;
    }

    int CountTotalWordsHelper(const WordNode* node) const{
        if (node == nullptr){
            return 0;
        }
        return node->count + CountTotalWordsHelper(node->left) + CountTotalWordsHelper(node->right);
    }

    int CountDistinctWordsHelper(const WordNode *Node) const{
        if(Node == nullptr){
            return 0;
        }
        return 1 + CountDistinctWordsHelper(Node->left) + CountDistinctWordsHelper(Node->right);
    }

    WordNode* DeleteItem(WordNode* Node, string str){
        if(Node == nullptr){
            return nullptr;
        }
        if(str < Node->data){
           Node->left = DeleteItem(Node->left, str);
        } else if(str > Node->data){
           Node->right = DeleteItem(Node->right, str);
        } else {
            Node->count--;
            if(Node->count == 0){
                if(Node->left == nullptr){
                     WordNode* temp = Node->right;
                    delete Node;
                    return temp;
                } else if (Node->right == nullptr) {
                    WordNode* temp = Node->left;
                    delete Node;
                    return temp;
                }
                    WordNode* temp = findLargest(Node->left);
                    Node->data = temp->data;
                    Node->count = temp->count;
                    Node->left = DeleteItem(Node->left, temp->data);
            }
        }
        return Node;
    }

WordNode* findLargest(WordNode* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

   
public:
        
    // default constructor            
    WordTree() { 
        root = nullptr;  // Yay!  I actually wrote this method for you.  You're welcome.
    }
    
    // Destroys all the dynamically allocated memory in the tree.
    // Delete using a post-order traversal
    ~WordTree() {
        freetree(root);
    }
    
    // Return the count for a given string
    int findOccurrences(string str) {
        return findOccurrencesHelper(root, str);
    }

    // insert str into the WordTree    
    void add(string str) {
        Insert(root, str);
    }

    // Remove the string (decrease the count by 1).  If the count goes to 0, remove the node.
    // For consistancy with the test cases, if you are removing a node with 2 children, search the left child.
    void remove(string str) {
        root = DeleteItem(root, str);
    }

    // Returns the number of distinct words in the tree 
    // You must traverse the tree to calculate this, no external counters!  
    int distinctWords() const {
        return CountDistinctWordsHelper(root);
    }
    
    // Returns the total number of words inserted, including duplicate values
    // You must traverse the tree to calculate this, no external counters!
    int totalWords() const {
        return CountTotalWordsHelper(root);
    }

    // Prints the BST in alphabetical order
    // Print each node on its own line with the string followed by the occurrance count in parentheses
    // Like:   word(count)
   void inOrder(WordNode* curr){
        if(curr == nullptr){
            return;
        } else {
            inOrder(curr->left);
            cout << curr->data <<  "(" << findOccurrences(curr->data) << ")" << endl;
            inOrder(curr->right);
        }
    }

    // Implement a function to print the contents of the BST using in-order traversal
    void print() {
        inOrder(root);
    }

};

