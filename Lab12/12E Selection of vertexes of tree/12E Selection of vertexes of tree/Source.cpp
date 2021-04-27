#include<iostream>
#include<vector>

class Tree {
public:
	Tree(int vertexSize) :
		graph(vertexSize),
		dp(vertexSize, { -1, -1 })
	{}

	void addEdge(int parent, int child) {
		graph[parent].push_back(child);
	}

	int getMaxAllowableSetSize(int root) {
		findMaxAllowableSetsSizes(root);
		return std::max(dp[root].first, dp[root].second);
	}

private:
	std::vector<std::vector<int>> graph;
	std::vector<std::pair<int, int>> dp; //first - doesn't include, second - include

	void findMaxAllowableSetsSizes(int root) {
		if (dp[root] != std::pair<int, int>{ -1, -1 }) {
			return;
		}
		dp[root] = { 0, 1 };
		for (int i(0); i < graph[root].size(); ++i) {
			int child = graph[root][i];
			findMaxAllowableSetsSizes(child);
			dp[root].first += std::max(dp[child].first, dp[child].second);
			dp[root].second += dp[child].first;
		}
	}
};

int main() {
	int n;
	std::cin >> n;
	Tree tree(n);
	int root;
	for (int i(0); i < n; ++i) {
		int parent;
		std::cin >> parent;
		if (parent == 0) {
			root = i;
		}
		else {
			tree.addEdge(parent - 1, i);
		}
	}
	std::cout << tree.getMaxAllowableSetSize(root);

	return 0;
}