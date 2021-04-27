#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class TwoBitsVector {
public:
	TwoBitsVector(int _size = 0, int _defaultValue = 0) :
		vector((_size + 3) / 4, _defaultValue)
	{}

	void setValue(int pos, int value) {
		int vectorPos = pos / 4;
		int bitsPos = pos % 4;
		vector[vectorPos] &= ~(3 << (bitsPos * 2));
		vector[vectorPos] |= (value << (bitsPos * 2));
	}

	int getValue(int pos) {
		int vectorPos = pos / 4;
		int bitsPos = pos % 4;
		return ((vector[vectorPos] & (3 << (bitsPos * 2))) >> (bitsPos * 2));
	}

private:
	std::vector<char> vector;
};

int main() {
	std::string str1, str2;
	std::cin >> str1 >> str2;
	str1 = ' ' + str1;
	str2 = ' ' + str2;
	if (str1.size() < str2.size()) {
		std::swap(str1, str2);
	}
	std::vector<int> dp[2];
	for (int i(0); i < 2; ++i) {
		dp[i].resize(str2.size() + 1, 0);
	}
	std::vector<TwoBitsVector> prevDp(str1.size() + 1, TwoBitsVector(str2.size() + 1)); // value: 1 - влево, 2 - вверх, 3 - диагональ
	for (int i(1); i <= str1.size(); ++i) {
		for (int j(1); j <= str2.size(); ++j) {
			if (str1[i] == str2[j]) {
				dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1;
				prevDp[i].setValue(j, 3);
			} else {
				if (dp[(i - 1) % 2][j] > dp[i % 2][j - 1]) {
					dp[i % 2][j] = dp[(i - 1) % 2][j];
					prevDp[i].setValue(j, 2);
				} else {
					dp[i % 2][j] = dp[i % 2][j - 1];
					prevDp[i].setValue(j, 1);
				}
			}
		}
	}
	int n = str1.size() - 1;
	int m = str2.size() - 1;
	std::string ans = "";
	while (n * m > 0) {
		switch (prevDp[n].getValue(m)) {
		case 1:
			--m;
			break;
		case 2:
			--n;
			break;
		case 3:
			ans += str1[n];
			--m;
			--n;
			break;
		default:
			break;
		}
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << ans;

	return 0;
}