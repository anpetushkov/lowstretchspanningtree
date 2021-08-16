// lsst.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>


class Node {
	int id_ = 0;
	int parentId_ = -1;
	std::vector<int> children_;
public:
	Node(int id) {
		id_ = id;
	}
	void print() const {
		std::cout << "Id: " << id_ << ", Parent: " << parentId_ << "\n";
		std::cout << "Children: {";
		for (int n : children_) {
			std::cout << n << ",";
		}
		std::cout << "}\n";
	}
	friend class Tree;
};

class Tree {
	std::vector<Node> nodes_;
	int root_ = -1;
public:
	void init(int numNodes, int rootIndex);
	void addEdge(int parent, int child);
	void print() const;
};

void Tree::init(int numNodes, int rootIndex) {
	nodes_.clear();
	for (int i = 0; i < numNodes; i++) {
		nodes_.push_back(Node(i));
	}
	root_ = rootIndex;
}

void Tree::addEdge(int parent, int child) {
	nodes_[parent].children_.push_back(child);
	nodes_[child].parentId_ = parent;
}

void Tree::print() const {
	std::cout << "Number of nodes: " << nodes_.size() << "\n";
	std::cout << "Root index: " << root_ << "\n";
	for (const auto& n : nodes_) {
		n.print();
	}
}

class Vertex {
	int id_ = 0;
	std::vector<int> neighbors_;
public:
	Vertex(int id) {
		id_ = id;
	}

	Vertex(Vertex&&) = default;
	void addNeighbor(int neighbor) {
		neighbors_.push_back(neighbor);
	}
	int getId() const { return id_;  }
	void print() const {
		std::cout << "Vertex id: " << id_ << "\nNeighbors: {";
		for (int n : neighbors_) {
			std::cout << n << ",";
		}
		std::cout << "}\n";
	}
	const std::vector<int>& getNeighbors() const { return neighbors_; }
};

class Graph {
	std::vector<Vertex> vertices_;
public:
	void init(int num_vertices, std::vector<std::pair<int, int>> edges);
	void print() const;
	Tree spanningTree() const;
};


void Graph::init(int num_vertices, std::vector<std::pair<int, int>> edges) {
	vertices_.clear();
	for (int i = 0; i < num_vertices; i++) {
		vertices_.push_back(Vertex(i));
	}
	for (const auto& item : edges) {
		if (item.first >= num_vertices || item.second >= num_vertices) {
			std::abort();
		}
		auto& left = vertices_[item.first];
		auto& right = vertices_[item.second];
		left.addNeighbor(item.second);
		right.addNeighbor(item.first);
	}
}

void Graph::print() const {
	std::cout << "Graph vertices count: " << vertices_.size() << "\n";
	for (const auto& v : vertices_) {
		v.print();
	}
}

Tree Graph::spanningTree() const {
	Tree result;
	int root = std::rand() % vertices_.size();
	result.init(vertices_.size(), root);
	std::vector<bool> visited(vertices_.size(), false);
	std::queue<int> nodesToConsider;
	nodesToConsider.push(root);
	visited[root] = true;
	while (!nodesToConsider.empty()) {
		int currentNode = nodesToConsider.front();
		nodesToConsider.pop();
		if (visited[currentNode]) {
			//continue;
		}
		const auto& v = vertices_[currentNode];
		visited[currentNode] = true;
		for (int n : v.getNeighbors()) {
			if (visited[n]) { continue; }
			result.addEdge(currentNode, n);
			nodesToConsider.push(n);
			visited[n] = true;
		}
	}
	return result;
}

int main()
{
    std::cout << "Hello World!\n";
	Graph g;
	g.init(6, { {0,1},{0,2},{0,3},{2,3},{3,4},{3,5},{4,5},{1,5} });
	g.print();
	Tree t = g.spanningTree();
	t.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
