typedef struct Node {
    int64_t data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int64_t data);
// Function for inserting a node in a binary tree
void insert(Node** root, int64_t data);
// Function to perform level order traversal to find the
// deepest rightmost node
Node* getDeepestRightmostNode(Node* root);
// Function for deleting deepest rightmost node in a binary
// tree
void deleteDeepestRightmostNode(Node* root, Node* dNode);
// Function to delete a node in the binary tree
void deleteNode (Node** root, int64_t data);
// Function to search for a node in the binary tree
Node* search(Node* root, int64_t data);
// function to perform inorder traversal in a binary tree
int inorderTraversal(Node* root);
