#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <type_traits>

using namespace std;

///////////////////////////////////// Divide and Conquer /////////////////////////////////////
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

/////////////////////////////// Recursive and Dynamic Prgramming /////////////////////////////
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

///////////////////////////////////// Trees and Graphs ///////////////////////////////////////
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
	(root->left) = (new BNode(2));
	(root->right) = (new BNode(34));
	(root->left->left) = (new BNode(15));
	(root->left->right) = (new BNode(20));
	(root->right->left) = (new BNode(30));
	(root->right->right) = (new BNode(40));
	(root->left->left->left) = (new BNode(25));
	(root->left->left->right) = (new BNode(50));
}

class Graph {
public:
	Graph(int n): adj_list_vector(n) //without knowing the graph connectivity or its size 
	{
		adj_list_vectorr = new vector<Node>[n];
	}
	~Graph() {
		delete[] adj_list_vectorr;
		delete[] adj_list_mapp;
	}
	void addEdge(int v, int u);
	void addEdge(Node v, Node u);

	//virtual void addEdge() = 0;
	//virtual ~Graph() {}

	//Graph and its representations
	//(1) Adjacency Matrix
	//Pros: Insert, Remove, Check_if_edge_exist: O(1), is the most optimized for edge search
	//Cons: Large Space O(v^2), Adding a vertex: O(V), BFS/DFS become costly as we can’t quickly get all adjacent of a node.
	//vector<Node, vector<Node>> adj_matrix_vector; //better to do vector<Node, Node>* adj_matrix_vectorr; and new/delete
	//unordered_map<Node, vector<Node>> adj_matrix_map;//	better to do unordered_map<Node, Node>* adj_matrix_mapp; and new/delete

	//(2) Adjacency List
	//Pros: Saves space O(|V|+|E|) . In the worst case, there can be C(V, 2) number of edges in a graph thus consuming O(V^2) space. Adding a vertex is easier.
	//Cons: Queries like edge search can be done O(V).
	vector<      Node>* adj_list_vectorr; //vector<      vector<Node>> adj_list_vector;
	vector<      vector<Node>> adj_list_vector;
	//IDK HOW TO handle this:
	map<Node, Node>* adj_list_mapp; //map<Node, vector<Node>> adj_list_map;



	// summary (both directed or undirected graphs)
	// always use adj_list e.g. traversing, dfs, bfs,... (use vector if node are tagged by numbers, use map (ordered) if labled and not numbered)
	// unless ONLY u need to check quickly connectivities between x and y, use adj_matrix (use unordered_map)
};
void Graph::addEdge(int v, int u)
{
	adj_list_vector[v].push_back(u);
	adj_list_vector[u].push_back(v);
}
void Graph::addEdge(Node v, Node u)
{
	//adj_list_map[v].push_back(u);
	//adj_list_map[u].push_back(v);
}

/*class Int_Graph : public Graph { //node with integer label
public:
	int X;
	void addEdge();
};

void Int_Graph::addEdge(int v, int u, double w)
{

}
void addEdge(Graph* t)
{
	return t->addEdge();
}
*/



void build_graph() {
	Graph *G = new Graph(5);
	G->addEdge(0,1);
	G->addEdge(1,2);
	G->addEdge(2,3);
	G->addEdge(2,4);
	G->addEdge(4,4);

	//G->my_function<int>(1,2,3);

	/*
	

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
	*/
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
	//BNode * root = new BNode(20);
	//build_binary_tree(root);
	//inOrderTraverseB(root);
	
	build_graph();
	
	char c; cin >> c;
	return 0;
}

