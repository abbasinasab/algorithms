#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


float power_ali(float x, int y) {
	if (y == 0) return 1.0;
	
	float temp=power_ali(x, y / 2);
	
	//Devide and Conquor
	if (! y % 2)  temp*temp;
	else 
		if(y>0)	return x * temp * temp;
		else	return temp * temp / x;
}
//FASTEST: F2n = (Fn-1 + Fn+1)Fn with memo
int mem[100000];
int M[2][2] = { { 1,1 },{ 1,0 } };
int F[2][2] = { { 1,1 },{ 1,0 } };

void fib_multiply(int M[2][2])
{
	int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
	int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
	int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
	int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = z;
	F[1][1] = w;
}



int fib(int n){

	if (mem[n]) return mem[n];
	if (n == 0)	return 0;
	if (n == 1 || n == 2) return (mem[n] = 1);
	//Time: O(n) , Space: O(n)
	//return (mem[n] = fib(n-1)+fib(n-2));

	//Time: O(logn) , Space: O(n) 
	//int k = (n & 1) ? (n + 1) / 2 : n / 2;
	//return (mem[n] = (n & 1) ? (fib(k)*fib(k) + fib(k - 1)*fib(k - 1)) : (2 * fib(k - 1) + fib(k))*fib(k)); //https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/

	//Time: O(logn) , Space: O(1)
	for (int i = 2; i <= n; i++) // n - 1 times multiply the matrix to {{1,0},{0,1}} 
		fib_multiply(M);

	return F[0][0];
}

class Node {
public:
	int id;
	vector<Node*> child;

	Node(int name) {
		id = name;
	}

};
class BNode {
public:
	int id;
	BNode *left;
	BNode *right;

	BNode(int name) {
		id = name;
		left = NULL;
		right = NULL;

	}

};
class Tree {
public:
	Node root;
};
class Graph {
	//Graph and its representations
	//(1) Adjacency Matrix:
	//Pros: Insert, Remove, Check_if_edge_exist: O(1), is the most optimized for edge search
	//Cons: Large Space O(v^2), Adding a vertex: O(V), BFS/DFS become costly as we can’t quickly get all adjacent of a node.

	vector<Node*> node;
};


void build_tree(Node * root) {
	(root->child).push_back(new Node(2));
	(root->child).push_back(new Node(34));
	(root->child).push_back(new Node(50));
	(root->child).push_back(new Node(60));
	(root->child).push_back(new Node(70));
	(root->child[0]->child).push_back(new Node(15));
	(root->child[0]->child).push_back(new Node(20));
	(root->child[1]->child).push_back(new Node(30));
	(root->child[2]->child).push_back(new Node(40));
	(root->child[2]->child).push_back(new Node(100));
	(root->child[2]->child).push_back(new Node(20));
	(root->child[0]->child[1]->child).push_back(new Node(25));
	(root->child[0]->child[1]->child).push_back(new Node(50));
}

void build_binary_tree(BNode * root) {
	(root->left)=(new BNode(2));
	(root->right)=(new BNode(34));
	(root->left->left)=(new BNode(15));
	(root->left->right)=(new BNode(20));
	(root->right->left)=(new BNode(30));
	(root->right->right)=(new BNode(40));
	(root->left->left->left)=(new BNode(25));
	(root->left->left->right)=(new BNode(50));
}

void inOrderTraverseB(BNode* node) {
	if (node != NULL) {
		inOrderTraverseB(node->left);
		cout << node->id << endl;
		inOrderTraverseB(node->right);
	}
}


int main() {
	//cout << power_ali(2, -3) << endl;
	//cout << fib(11) << endl;
	BNode * root = new BNode(20);
	build_binary_tree(root);
	inOrderTraverseB(root);

	char c; cin >> c;
	return 0;
}