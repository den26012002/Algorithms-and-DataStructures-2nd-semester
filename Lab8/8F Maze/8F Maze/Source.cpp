#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Position {
	int x;
	int y;
};

Position operator+(const Position& pos1, const Position& pos2) {
	return Position{ pos1.x + pos2.x, pos1.y + pos2.y };
}

Position operator-(const Position& pos1, const Position& pos2) {
	return Position{ pos1.x - pos2.x, pos1.y - pos2.y };
}

struct Direction {
	Position pos;
	char dir;
};

const Direction MOVES[4] = { {1, 0, 'D'}, {-1, 0, 'U'}, {0, 1, 'R'}, {0, -1, 'L'} };

class Maze {
public:
	std::pair<int, std::vector<char>> getWay() {
		bfs(startPos);
		return restoreWay(finishPos);
	}

	Maze(int _height, int _width) {
		height = _height;
		width = _width;
		arr.resize(_height);
		for (int i(0); i < _height; ++i) {
			arr[i].resize(_width);
		}
	}

	Maze() {
		height = 0;
		width = 0;
	}
private:
	std::vector<std::vector<char>> arr;
	int height;
	int width;
	Position startPos;
	Position finishPos;

	bool correctPosition(Position& pos) {
		return (pos.x >= 0 && pos.x < height && pos.y >= 0 && pos.y < width);
	}

	void bfs(Position& startPos) {
		std::queue<Position> q;
		q.push(startPos);
		while (!q.empty()) {
			Position v = q.front();
			q.pop();
			for (int i(0); i < 4; ++i) {
				Position u = v + MOVES[i].pos;
				if (correctPosition(u) && (arr[u.x][u.y] == '.' || arr[u.x][u.y] == 'T')) {
					arr[u.x][u.y] = MOVES[i].dir;
					q.push(u);
				}
			}
		}
	}

	std::pair<int, std::vector<char>> restoreWay(Position& finishPos) {
		std::vector<char> ans;
		int ansLenght = 0;
		if (arr[finishPos.x][finishPos.y] == 'T') {
			ansLenght = -1;
		}
		while (arr[finishPos.x][finishPos.y] != 'S' && arr[finishPos.x][finishPos.y] != 'T') {
			ans.push_back(arr[finishPos.x][finishPos.y]);
			++ansLenght;
			switch (arr[finishPos.x][finishPos.y]) {
				case 'D':
					finishPos = finishPos - MOVES[0].pos;
					break;
				case 'U':
					finishPos = finishPos - MOVES[1].pos;
					break;
				case 'R':
					finishPos = finishPos - MOVES[2].pos;
					break;
				case 'L':
					finishPos = finishPos - MOVES[3].pos;
					break;
			}
		}
		std::reverse(ans.begin(), ans.end());
		return make_pair(ansLenght, ans);
	}

	friend std::istream& operator>>(std::istream&, Maze&);
};

std::istream& operator>>(std::istream& cin, Maze& maze) {
	for (int i(0); i < maze.height; ++i) {
		for (int j(0); j < maze.width; ++j) {
			cin >> maze.arr[i][j];
			if (maze.arr[i][j] == 'S') {
				maze.startPos = { i, j };
			}
			else if (maze.arr[i][j] == 'T') {
				maze.finishPos = { i, j };
			}
		}
	}
	return cin;
}

std::ostream& operator<<(std::ostream& cout, std::pair<int, std::vector<char>>& pair) {
	cout << pair.first << '\n';
	for (int i(0); i < pair.second.size(); ++i) {
		cout << pair.second[i];
	}
	return cout;
}

int main() {
	int n, m;
	fin >> n >> m;
	Maze maze(n, m);
	fin >> maze;
	std::pair<int, std::vector<char>> ans = maze.getWay();
	fout << ans;

	return 0;
}