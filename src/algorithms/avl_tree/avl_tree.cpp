#define DOCTEST_CONFIG_IMPLEMENT

#include <vector>
#include "doctest/doctest.h"

using namespace std;

// Structure that represents a node in the AVL tree.
struct Node {
  // Value of the node.
  int value;

  // Height of the node.
  int height;

  // Left child of the node.
  Node *left;

  // Right child of the node.
  Node *right;

  // Constructor.
  explicit Node(int value) : value(value), height(1), left(nullptr), right(nullptr) {}
};

// Class that implements an AVL tree.
class AVLTree {
 private:
  // Root of the tree.
  Node *root;

  // Size of the tree.
  int size;

  // Helper method for inserting a value in the tree.
  static int getHeight(Node *node) {
    // If the node is null, return 0.
    if (node == nullptr) return 0;

    // Return the height of the node.
    return node->height;
  }

  // Helper method for getting the balance factor of a node.
  static int balanceFactor(Node *node) {
    // If the node is null, return 0.
    if (node == nullptr) return 0;

    // Return the balance factor of the node.
    return getHeight(node->left) - getHeight(node->right);
  }

  // Helper method for updating the height of a node.
  static void updateHeight(Node *node) {
    // Set the height of the node to 1 plus the maximum height of its children.
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  }

  // Helper method for rotating a node to the right.
  static Node *rotateRight(Node *node) {
    // Get the new parent of the node.
    Node *newParent = node->left;

    // Set the left child of the node to the right child of the new parent.
    node->left = newParent->right;

    // Set the right child of the new parent to the node.
    newParent->right = node;

    // Update the height of the node.
    updateHeight(node);

    // Update the height of the new parent.
    updateHeight(newParent);

    // Return the new parent.
    return newParent;
  }

  // Helper method for rotating a node to the left.
  static Node *rotateLeft(Node *node) {
    // Get the new parent of the node.
    Node *newParent = node->right;

    // Set the right child of the node to the left child of the new parent.
    node->right = newParent->left;

    // Set the left child of the new parent to the node.
    newParent->left = node;

    // Update the height of the node.
    updateHeight(node);

    // Update the height of the new parent.
    updateHeight(newParent);

    // Return the new parent.
    return newParent;
  }

  // Helper method for balancing a node.
  static Node *balance(Node *node) {
    // Update the height of the node.
    updateHeight(node);

    // Get the balance factor of the node.
    int balanceFactorNode = balanceFactor(node);

    // If the balance factor is greater than 1, the node is left-heavy.
    if (balanceFactorNode > 1) {
      // If the balance factor of the left child is less than 0, the left child is right-heavy.
      if (balanceFactor(node->left) < 0) {
        // Rotate the left child to the left.
        node->left = rotateLeft(node->left);
      }

      // Rotate the node to the right.
      return rotateRight(node);
    }

    // If the balance factor is less than -1, the node is right-heavy.
    if (balanceFactorNode < -1) {
      // If the balance factor of the right child is greater than 0, the right child is left-heavy.
      if (balanceFactor(node->right) > 0) {
        // Rotate the right child to the right.
        node->right = rotateRight(node->right);
      }

      // Rotate the node to the left.
      return rotateLeft(node);
    }

    // Return the node.
    return node;
  }

  // Helper method for inserting a value in the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *insertHelper(Node *node, int value) { // NOLINT
    // If the node is null, create a new node with the value and return it.
    if (node == nullptr) {
      size++;
      return new Node(value);
    }

    // If the value is less than the value of the node, insert it in the left subtree.
    if (value < node->value) {
      node->left = insertHelper(node->left, value);
    } else if (value > node->value) {
      // If the value is greater than the value of the node, insert it in the right subtree.
      node->right = insertHelper(node->right, value);
    } else {
      // If the value is equal to the value of the node, the value is already in the tree, so return the node.
      return node;
    }

    // Balance the node.
    return balance(node);
  }

  // Helper method for getting the minimum value in the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *getMinHelper(Node *node) { // NOLINT
    // If the node is null, return null.
    if (node == nullptr) return nullptr;

    // If the left child is null, the node is the minimum, so return it.
    if (node->left == nullptr) return node;

    // Return the minimum value in the left subtree.
    return getMinHelper(node->left);
  }

  // Helper method for getting the maximum value in the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *getMaxHelper(Node *node) { // NOLINT
    // If the node is null, return null.
    if (node == nullptr) return nullptr;

    // If the right child is null, the node is the maximum, so return it.
    if (node->right == nullptr) return node;

    // Return the maximum value in the right subtree.
    return getMaxHelper(node->right);
  }

  // Helper method for deleting a value from the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *deleteHelper(Node *node, int value) { // NOLINT
    // If the node is null, return null.
    if (node == nullptr) return nullptr;

    // If the value is less than the value of the node, delete it from the left subtree.
    if (value < node->value) {
      node->left = deleteHelper(node->left, value);
    } else if (value > node->value) {
      // If the value is greater than the value of the node, delete it from the right subtree.
      node->right = deleteHelper(node->right, value);
    } else {
      // If the value is equal to the value of the node, delete the node.
      if (node->left == nullptr) {
        Node *rightChild = node->right;
        delete node;
        return rightChild;
      } else if (node->right == nullptr) {
        // If the node has only one child, return the child.
        Node *leftChild = node->left;
        delete node;
        return leftChild;
      } else {
        // If the node has two children, get the successor of the node.
        Node *successor = getMinHelper(node->right);
        node->value = successor->value;
        node->right = deleteHelper(node->right, successor->value);
      }

      // Decrement the size of the tree.
      size--;
    }

    // Balance the node.
    return balance(node);
  }

  // Helper method for searching a value in the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *searchHelper(Node *node, int value) { // NOLINT
    // If the node is null, return null.
    if (node == nullptr) return nullptr;

    // If the value is less than the value of the node, search in the left subtree.
    if (value < node->value) {
      return searchHelper(node->left, value);
    } else if (value > node->value) {
      // If the value is greater than the value of the node, search in the right subtree.
      return searchHelper(node->right, value);
    } else {
      // If the value is equal to the value of the node, return the node.
      return node;
    }
  }

  // Helper method for getting the predecessor of a value in the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *getPredecessorHelper(Node *node, int value) { // NOLINT
    // If the node is null, return null.
    if (node == nullptr) return nullptr;

    // If the value is less than the value of the node, get the predecessor in the left subtree.
    if (value <= node->value) {
      return getPredecessorHelper(node->left, value);
    } else {
      // If the value is greater than the value of the node, get the predecessor in the right subtree.
      Node *rightChild = getPredecessorHelper(node->right, value);

      // If the right child is null, the node is the predecessor, so return it.
      if (rightChild == nullptr) {
        return node;
      } else {
        // Otherwise, return the right child.
        return rightChild;
      }
    }
  }

  // Helper method for getting the successor of a value in the tree.
  // NOLINT is used to disable the linting for the recursive methods.
  Node *getSuccessorHelper(Node *node, int value) { // NOLINT
    // If the node is null, return null.
    if (node == nullptr) return nullptr;

    // If the value is greater than the value of the node, get the successor in the right subtree.
    if (value >= node->value) {
      return getSuccessorHelper(node->right, value);
    } else {
      // If the value is less than the value of the node, get the successor in the left subtree.
      Node *leftChild = getSuccessorHelper(node->left, value);
      if (leftChild == nullptr) {
        // If the left child is null, the node is the successor, so return it.
        return node;
      } else {
        // Otherwise, return the left child.
        return leftChild;
      }
    }
  }

  // Helper method for traversing the tree in order.
  // NOLINT is used to disable the linting for the recursive methods.
  void traverseInorderHelper(Node *node, vector<int> &nodes) { // NOLINT
    // If the node is null, return.
    if (node == nullptr) return;

    // Traverse the left subtree, visit the node, and traverse the right subtree.
    traverseInorderHelper(node->left, nodes);
    nodes.push_back(node->value);
    traverseInorderHelper(node->right, nodes);
  }

  // Helper method for traversing the tree in preorder.
  // NOLINT is used to disable the linting for the recursive methods.
  void traversePreorderHelper(Node *node, vector<int> &nodes) { // NOLINT
    // If the node is null, return.
    if (node == nullptr) return;

    // Visit the node, traverse the left subtree, and traverse the right subtree.
    nodes.push_back(node->value);
    traversePreorderHelper(node->left, nodes);
    traversePreorderHelper(node->right, nodes);
  }

  // Helper method for traversing the tree in postorder.
  // NOLINT is used to disable the linting for the recursive methods.
  void traversePostorderHelper(Node *node, vector<int> &nodes) { // NOLINT
    // If the node is null, return.
    if (node == nullptr) return;

    // Traverse the left subtree, traverse the right subtree, and visit the node.
    traversePostorderHelper(node->left, nodes);
    traversePostorderHelper(node->right, nodes);
    nodes.push_back(node->value);
  }

 public:
  // Constructor to initialize the tree.
  AVLTree() : root(nullptr), size(0) {}

  // Method to insert a value into the tree.
  void insert(int value) {
    root = insertHelper(root, value);
  }

  // Method to delete a value from the tree.
  void deleteNode(int value) {
    root = deleteHelper(root, value);
  }

  // Method to search for a value in the tree.
  Node *search(int value) {
    return searchHelper(root, value);
  }

  // Method to get the minimum value in the tree.
  Node *getMin() {
    return getMinHelper(root);
  }

  // Method to get the maximum value in the tree.
  Node *getMax() {
    return getMaxHelper(root);
  }

  // Method to get the predecessor of a value in the tree.
  Node *getPredecessor(int value) {
    return getPredecessorHelper(root, value);
  }

  // Method to get the successor of a value in the tree.
  Node *getSuccessor(int value) {
    return getSuccessorHelper(root, value);
  }

  // Method to traverse the tree in order.
  vector<int> traverseInorder() {
    vector<int> nodes;
    traverseInorderHelper(root, nodes);
    return nodes;
  }

  // Method to traverse the tree in preorder.
  vector<int> traversePreorder() {
    vector<int> nodes;
    traversePreorderHelper(root, nodes);
    return nodes;
  }

  // Method to traverse the tree in postorder.
  vector<int> traversePostorder() {
    vector<int> nodes;
    traversePostorderHelper(root, nodes);
    return nodes;
  }

  // Getter for the height of the tree.
  int getHeight() {
    return getHeight(root);
  }

  // Getter that returns whether the tree is empty.
  [[nodiscard]] bool isEmpty() const {
    return size == 0;
  }

  // Getter for the size of the tree.
  [[nodiscard]] int getSize() const {
    return size;
  }
};

int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

// Tests
TEST_CASE("AVLTree::insert") {
  AVLTree tree;

  SUBCASE("Inserting a single value") {
    tree.insert(42);
    CHECK(tree.search(42) != nullptr);
  }

  SUBCASE("Inserting multiple values") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.search(42) != nullptr);
    CHECK(tree.search(10) != nullptr);
    CHECK(tree.search(99) != nullptr);
  }

  SUBCASE("Inserting a duplicate value") {
    tree.insert(42);
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.search(42) != nullptr);
    CHECK(tree.search(10) != nullptr);
    CHECK(tree.search(99) != nullptr);
  }
}

TEST_CASE("AVLTree::deleteNode") {
  AVLTree tree;

  SUBCASE("Deleting a single value") {
    tree.insert(42);
    tree.deleteNode(42);

    CHECK(tree.search(42) == nullptr);
  }

  SUBCASE("Deleting a non-existent value") {
    tree.deleteNode(42);

    CHECK(tree.search(42) == nullptr);
  }

  SUBCASE("Deleting multiple values") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);
    tree.deleteNode(10);
    tree.deleteNode(99);

    CHECK(tree.search(42) != nullptr);
    CHECK(tree.search(10) == nullptr);
    CHECK(tree.search(99) == nullptr);
  }
}

TEST_CASE("AVLTree::search") {
  AVLTree tree;

  SUBCASE("Searching for a single value") {
    tree.insert(42);

    CHECK(tree.search(42) != nullptr);
  }

  SUBCASE("Searching for a non-existent value") {
    CHECK(tree.search(42) == nullptr);
  }

  SUBCASE("Searching for multiple values") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.search(42) != nullptr);
    CHECK(tree.search(10) != nullptr);
    CHECK(tree.search(99) != nullptr);
  }
}

TEST_CASE("AVLTree::getMin") {
  AVLTree tree;

  SUBCASE("Getting the minimum value of a single-node tree") {
    tree.insert(42);

    CHECK(tree.getMin()->value == 42);
  }

  SUBCASE("Getting the minimum value of a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.getMin()->value == 10);
  }

  SUBCASE("Getting the minimum value of an empty tree") {
    CHECK(tree.getMin() == nullptr);
  }
}

TEST_CASE("AVLTree::getMax") {
  AVLTree tree;

  SUBCASE("Getting the maximum value of a single-node tree") {
    tree.insert(42);

    CHECK(tree.getMax()->value == 42);
  }

  SUBCASE("Getting the maximum value of a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.getMax()->value == 99);
  }

  SUBCASE("Getting the maximum value of an empty tree") {
    CHECK(tree.getMax() == nullptr);
  }
}

TEST_CASE("AVLTree::getPredecessor") {
  AVLTree tree;

  SUBCASE("Getting the predecessor of a single-node tree") {
    tree.insert(42);

    CHECK(tree.getPredecessor(42) == nullptr);
  }

  SUBCASE("Getting the predecessor of a non-existent value") {
    CHECK(tree.getPredecessor(42) == nullptr);
  }

  SUBCASE("Getting the predecessor of a value with no left child") {
    tree.insert(42);
    tree.insert(99);

    CHECK(tree.getPredecessor(99)->value == 42);
  }

  SUBCASE("Getting the predecessor of a value with a left child") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.getPredecessor(99)->value == 42);
  }

  SUBCASE("Getting the predecessor of the root value") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.getPredecessor(42)->value == 10);
  }
}

TEST_CASE("AVLTree::getSuccessor") {
  AVLTree tree;

  SUBCASE("Getting the successor of a single-node tree") {
    tree.insert(42);

    CHECK(tree.getSuccessor(42) == nullptr);
  }

  SUBCASE("Getting the successor of a non-existent value") {
    CHECK(tree.getSuccessor(42) == nullptr);
  }

  SUBCASE("Getting the successor of a value with no right child") {
    tree.insert(42);
    tree.insert(10);

    CHECK(tree.getSuccessor(10)->value == 42);
  }

  SUBCASE("Getting the successor of a value with a right child") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.getSuccessor(42)->value == 99);
  }

  SUBCASE("Getting the successor of the root value") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.getSuccessor(99) == nullptr);
  }
}

TEST_CASE("AVLTree::traverseInorder") {
  AVLTree tree;

  SUBCASE("Traversing an empty tree") {
    CHECK(tree.traverseInorder() == std::vector<int>{});
  }

  SUBCASE("Traversing a single-node tree") {
    tree.insert(42);

    CHECK(tree.traverseInorder() == std::vector<int>{42});
  }

  SUBCASE("Traversing a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.traverseInorder() == std::vector<int>{10, 42, 99});
  }
}

TEST_CASE("AVLTree::traversePreorder") {
  AVLTree tree;

  SUBCASE("Traversing an empty tree") {
    CHECK(tree.traversePreorder() == std::vector<int>{});
  }

  SUBCASE("Traversing a single-node tree") {
    tree.insert(42);

    CHECK(tree.traversePreorder() == std::vector<int>{42});
  }

  SUBCASE("Traversing a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.traversePreorder() == std::vector<int>{42, 10, 99});
  }
}

TEST_CASE("AVLTree::traversePostorder") {
  AVLTree tree;

  SUBCASE("Traversing an empty tree") {
    CHECK(tree.traversePostorder() == std::vector<int>{});
  }

  SUBCASE("Traversing a single-node tree") {
    tree.insert(42);

    CHECK(tree.traversePostorder() == std::vector<int>{42});
  }

  SUBCASE("Traversing a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);

    CHECK(tree.traversePostorder() == std::vector<int>{10, 99, 42});
  }
}

TEST_CASE("AVLTree::getHeight") {
  AVLTree tree;

  SUBCASE("Getting the height of an empty tree") {
    CHECK(tree.getHeight() == 0);
  }

  SUBCASE("Getting the height of a single-node tree") {
    tree.insert(42);

    CHECK(tree.getHeight() == 1);
  }

  SUBCASE("Getting the height of a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);
    tree.insert(5);
    tree.insert(15);
    tree.insert(90);

    CHECK(tree.getHeight() == 3);
  }
}

TEST_CASE("AVLTree::isEmpty") {
  AVLTree tree;

  SUBCASE("Checking if an empty tree is empty") {
    CHECK(tree.isEmpty() == true);
  }

  SUBCASE("Checking if a non-empty tree is empty") {
    tree.insert(42);

    CHECK(tree.isEmpty() == false);
  }
}

TEST_CASE("AVLTree::getSize") {
  AVLTree tree;

  SUBCASE("Getting the size of an empty tree") {
    CHECK(tree.getSize() == 0);
  }

  SUBCASE("Getting the size of a single-node tree") {
    tree.insert(42);

    CHECK(tree.getSize() == 1);
  }

  SUBCASE("Getting the size of a multi-node tree") {
    tree.insert(42);
    tree.insert(10);
    tree.insert(99);
    tree.insert(5);
    tree.insert(15);
    tree.insert(90);

    CHECK(tree.getSize() == 6);
  }
}
