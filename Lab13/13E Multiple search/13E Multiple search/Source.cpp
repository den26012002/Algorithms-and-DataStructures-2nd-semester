#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::ifstream fin("search4.in");
std::ofstream fout("search4.out");

class AhoCorasickTrie {
public:
	struct Node {
		int to[26];
		short isTerminated;
		int parent;
		int parentSymb;
		int suf;
		std::vector<int> terminatedStringNumbs;

		Node() :
			isTerminated(0),
			parent(-1),
			parentSymb(-1),
			suf(-1)
		{
			for (int i(0); i < 26; ++i) {
				to[i] = -1;
			}
		}
	};

public:
	AhoCorasickTrie() :
		nodes(1),
		dictSize(0)
	{}

	void addString(std::string str) {
		int curNodeNumb = 0;
		for (int i(0); i < str.size(); ++i) {
			if (nodes[curNodeNumb].to[str[i] - 'a'] == -1) {
				nodes.push_back(Node());
				nodes.back().parent = curNodeNumb;
				nodes.back().parentSymb = str[i] - 'a';
				nodes[curNodeNumb].to[str[i] - 'a'] = nodes.size() - 1;
			}
			curNodeNumb = nodes[curNodeNumb].to[str[i] - 'a'];
		}
		nodes[curNodeNumb].isTerminated = 1;
		nodes[curNodeNumb].terminatedStringNumbs.push_back(dictSize);
		++dictSize;
	}

	std::vector<bool> checkString(std::string str) {
		nodes[0].isTerminated = -1;
		std::vector<bool> isSubstrings(dictSize, false);
		int curState = 0;
		for (int i(0); i < str.size(); ++i) {
			curState = to(curState, str[i] - 'a');
			if (isTerminated(curState) == 1) {
				for (int strNumb : nodes[curState].terminatedStringNumbs) {
					isSubstrings[strNumb] = true;
				}
				nodes[curState].isTerminated = -1;
			}
			int sufState = suf(curState);
			while (sufState != 0 && isTerminated(sufState) == 1) {
				for (int strNumb : nodes[sufState].terminatedStringNumbs) {
					isSubstrings[strNumb] = true;
				}
				nodes[sufState].isTerminated = -1;
				sufState = suf(sufState);
			}
		}
		return isSubstrings;
	}

private:
	std::vector<Node> nodes;
	int dictSize;

	int suf(int nodeNumb) {
		if (nodes[nodeNumb].suf == -1) {
			if (nodes[nodeNumb].parent == 0 || nodeNumb == 0) {
				nodes[nodeNumb].suf = 0;
			} else {
				int newNodeNumb = suf(nodes[nodeNumb].parent);
				nodes[nodeNumb].suf = to(newNodeNumb, nodes[nodeNumb].parentSymb);
			}
		}
		return nodes[nodeNumb].suf;
	}

	int to(int nodeNumb, int symb) {
		if (nodes[nodeNumb].to[symb] == -1) {
			if (nodeNumb == 0) {
				nodes[nodeNumb].to[symb] = 0;
			} else {
				nodes[nodeNumb].to[symb] = to(suf(nodeNumb), symb);
			}
		}
		return nodes[nodeNumb].to[symb];
	}

	int isTerminated(int nodeNumb) {
		if (nodes[nodeNumb].isTerminated == 0) {
			nodes[nodeNumb].isTerminated = isTerminated(suf(nodeNumb));
			for (int strNumb : nodes[suf(nodeNumb)].terminatedStringNumbs) {
				nodes[nodeNumb].terminatedStringNumbs.push_back(strNumb);
			}
		}
		return nodes[nodeNumb].isTerminated;
	}
};

int main() {
	int n;
	fin >> n;
	AhoCorasickTrie trie;
	for (int i(0); i < n; ++i) {
		std::string s;
		fin >> s;
		trie.addString(s);
	}
	std::string t;
	fin >> t;
	std::vector<bool> ans = trie.checkString(t);
	for (int i(0); i < ans.size(); ++i) {
		fout << (ans[i] ? "YES" : "NO") << '\n';
	}

	return 0;
}