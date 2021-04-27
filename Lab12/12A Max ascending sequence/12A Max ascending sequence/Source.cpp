#include<iostream>
#include<vector>
#include<algorithm>

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i(0); i < n; ++i) {
		std::cin >> a[i];
	}
	std::vector<int> dp(n, 1);
	std::vector<int> parents(n, -1);
	for (int i(1); i < n; ++i) {
		for (int j(i); j >= 0; --j) {
			if (a[i] > a[j]) {
				if (dp[i] < dp[j] + 1) {
					dp[i] = dp[j] + 1;
					parents[i] = j;
				}
			}
		}
	}
	int ans = dp[0];
	int ansPos = 0;
	for (int i(1); i < n; ++i) {
		if (dp[i] > ans) {
			ans = dp[i];
			ansPos = i;
		}
	}
	std::vector<int> ansArr;
	while (ansPos != -1) {
		ansArr.push_back(a[ansPos]);
		ansPos = parents[ansPos];
	}
	std::reverse(ansArr.begin(), ansArr.end());
	std::cout << ans << '\n';
	for (int i(0); i < ansArr.size(); ++i) {
		std::cout << ansArr[i] << ' ';
	}

	return 0;
}