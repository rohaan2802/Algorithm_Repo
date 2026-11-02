# Binary Tree Traversals (Inorder, Preorder, Postorder)

| Traversal | Order |
|---|---|
| Inorder | Left → Root → Right |
| Preorder | Root → Left → Right |
| Postorder | Left → Right → Root |

## C++
```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

void inorder(Node* r)   { if (!r) return; inorder(r->left);  cout << r->data << " "; inorder(r->right); }
void preorder(Node* r)  { if (!r) return; cout << r->data << " "; preorder(r->left);  preorder(r->right); }
void postorder(Node* r) { if (!r) return; postorder(r->left); postorder(r->right); cout << r->data << " "; }

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);          //        1
    root->right = new Node(3);         //       / \
    root->left->left = new Node(4);    //      2   3
    root->left->right = new Node(5);   //     / \   \
    root->right->right = new Node(6);  //    4   5   6
    inorder(root);   cout << endl;     // 4 2 5 1 3 6
    preorder(root);  cout << endl;     // 1 2 4 5 3 6
    postorder(root); cout << endl;     // 4 5 2 6 3 1
}
```

## Dry run of inorder
The key point: after a call finishes, control returns to the line just after that call in the **caller**, which is still waiting on the stack.

| Step | Call stack (top last) | Action | Output so far |
|---|---|---|---|
| 1 | in(1) | go left | |
| 2 | in(1), in(2) | go left | |
| 3 | in(1), in(2), in(4) | left null, print 4, right null, return | 4 |
| 4 | in(1), in(2) | left done → print 2, go right | 4 2 |
| 5 | in(1), in(2), in(5) | left null, print 5, right null, return | 4 2 5 |
| 6 | in(1), in(2) | right done → in(2) ends, returns to in(1) | 4 2 5 |
| 7 | in(1) | left done → print 1, go right | 4 2 5 1 |
| 8 | in(1), in(3) | left null, print 3, go right | 4 2 5 1 3 |
| 9 | in(1), in(3), in(6) | print 6, return | 4 2 5 1 3 6 |
| 10 | – | in(3) and in(1) end | 4 2 5 1 3 6 |

So after printing 5, node 2 has nothing left to do; its frame is popped and execution continues in node 1's frame at "print root", which prints 1.

Each traversal visits every node once: O(n) time, O(h) stack space (h = tree height).
