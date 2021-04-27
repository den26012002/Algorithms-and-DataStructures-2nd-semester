#include<iostream>
#include<string>
#include<vector>

std::vector<int> findPrefixFunc(std::string str) {
	std::vector<int> pi(str.size(), 0);
	int k;
	for (int i(1); i < str.size(); ++i) {
		k = pi[i - 1];
		while (k > 0 && str[i] != str[k]) {
			k = pi[k - 1];
		}
		if (str[i] == str[k]) {
			++k;
		}
		pi[i] = k;
	}
	return pi;
}

std::vector<std::vector<int>> findKMPAuthomat(std::string str, int alphabetSize) {
	std::vector<int> pi = findPrefixFunc(str);
	std::vector<std::vector<int>> delta(str.size() + 1, std::vector<int>(alphabetSize, 0));
	delta[0][str[0] - 'a'] = 1;
	for (int i(1); i < str.size() + 1; ++i) {
		for (int j(0); j < alphabetSize; ++j) {
			if ('a' + j == str[i]) {
				delta[i][j] = i + 1;
			} else {
				delta[i][j] = delta[pi[i - 1]][j];
			}
		}
	}
	return delta;
}

int main() {
	int n;
	std::string str;
	std::cin >> n >> str;
	auto ans = findKMPAuthomat(str, n);
	for (int i(0); i < ans.size(); ++i) {
		for (int j(0); j < ans[i].size(); ++j) {
			std::cout << ans[i][j] << ' ';
		}
		std::cout << '\n';
	}


	return 0;
}