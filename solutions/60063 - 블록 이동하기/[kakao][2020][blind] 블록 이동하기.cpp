/*
	[kakao][2020][blind] 블록 이동하기
	https://programmers.co.kr/learn/courses/30/lessons/60063
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct NODE {
	int x1, y1, x2, y2;
	bool ro = false;	//false(행 +-1) true(열+-1)
};
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
queue<NODE> q;
bool visit[100][100][100][100];
int solution(vector<vector<int>> board) {
	int answer = 0, r, c;
	r = board.size();
	c = board[0].size();
	q.push({ 0,0,0,1,false});
	visit[0][0][0][1] = true;
	visit[0][1][0][0] = true;
	while (!q.empty()) {
		answer++;
		int size = q.size();
		for (int i = 0; i < size; i++) {
			NODE node = q.front();
			int x1 = node.x1, y1 = node.y1, x2 = node.x2, y2 = node.y2;
			bool ro = node.ro;
			q.pop();
			
			//상하좌우
			for (int j = 0; j < 4; j++) {
				int nx1 = x1 + dx[j];
				int ny1 = y1 + dy[j];
				int nx2 = x2 + dx[j];
				int ny2 = y2 + dy[j];

				if (nx1 < 0 || ny1 < 0 || nx2 < 0 || ny2 < 0 || nx1 == r || ny1 == c || nx2 == r || ny2 == c)
					continue;
				if (visit[nx1][ny1][nx2][ny2])
					continue;
				if (board[nx1][ny1] == 0 && board[nx2][ny2] == 0) {
					if ((nx1 == r - 1 && ny1 == c - 1) || (nx2 == r - 1 && ny2 == c - 1))
						return answer;
					q.push({ nx1,ny1,nx2,ny2,ro });
					visit[nx1][ny1][nx2][ny2] = true;
					visit[nx2][ny2][nx1][ny1] = true;
				}
			}

			//회전
			if (ro == false) {
				if (x1 - 1 >= 0) {
					if (board[x1 - 1][y1] == 0 && board[x2 - 1][y2] == 0) {
						if (visit[x1][y1][x1 - 1][y1] == false) {
							q.push({ x1,y1,x1 - 1,y1,!ro });
							visit[x1][y1][x1 - 1][y1] = true;
							visit[x1 - 1][y1][x1][y1] = true;
						}
						if (visit[x2][y2][x2 - 1][y2] == false) {
							q.push({ x2,y2,x2 - 1,y2,!ro });
							visit[x2][y2][x2 - 1][y2] = true;
							visit[x2 - 1][y2][x2][y2] = true;
						}
					}
				}
				if (x1 + 1 < r) {
					if (board[x1 + 1][y1] == 0 && board[x2 + 1][y2] == 0) {
						if (x1 + 1 == r - 1 && (y1 == c - 1 || y2== c - 1))
							return answer;

						if (visit[x1][y1][x1 + 1][y1] == false) {
							q.push({ x1,y1,x1 + 1,y1,!ro });
							visit[x1][y1][x1 + 1][y1] = true;
							visit[x1 + 1][y1][x1][y1] = true;
						}
						if (visit[x2][y2][x2 + 1][y2] == false) {
							q.push({ x2,y2,x2 + 1,y2,!ro });
							visit[x2][y2][x2 + 1][y2] = true;
							visit[x2 + 1][y2][x2][y2] = true;
						}
					}
				}
			}
			else{
				if (y1 - 1 >= 0) {
					if (board[x1][y1 - 1] == 0 && board[x2][y2 - 1] == 0) {
						if (y1 == c - 1 && (x1 + 1 == r - 1 || x2 + 1 == r - 1))
							return answer;

						if (visit[x1][y1][x1][y1 - 1] == false) {
							q.push({ x1,y1,x1,y1 - 1,!ro });
							visit[x1][y1][x1][y1 - 1] = true;
							visit[x1][y1 - 1][x1][y1] = true;
						}
						if (visit[x2][y2][x2][y2 - 1] == false) {
							q.push({ x2,y2,x2,y2 - 1,!ro });
							visit[x2][y2][x2][y2 - 1] = true;
							visit[x2][y2 - 1][x2][y2] = true;
						}
					}
				}
				if (y1 + 1 < c) {
					if (board[x1][y1 + 1] == 0 && board[x2][y2 + 1] == 0) {
						if (y1 + 1 == c - 1 && (y1 == r - 1 || x2 == r - 1))
							return answer;

						if (visit[x1][y1][x1][y1 + 1] == false) {
							q.push({ x1,y1,x1,y1 + 1,!ro });
							visit[x1][y1][x1][y1 + 1] = true;
							visit[x1][y1 + 1][x1][y1] = true;
						}
						if (visit[x2][y2][x2][y2 + 1] == false) {
							q.push({ x2,y2,x2,y2 + 1,!ro });
							visit[x2][y2][x2][y2 + 1] = true;
							visit[x2][y2 + 1][x2][y2] = true;
						}
					}
				}
			}
		}
	}
	return answer;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vector<vector<int>> board(7);
	board[0].push_back(0);
	board[0].push_back(0);
	board[0].push_back(0);
	board[0].push_back(0);
	board[0].push_back(0);
	board[0].push_back(0);
	board[0].push_back(1);

	board[1].push_back(1);
	board[1].push_back(1);
	board[1].push_back(1);
	board[1].push_back(1);
	board[1].push_back(0);
	board[1].push_back(0);
	board[1].push_back(1);

	board[2].push_back(0);
	board[2].push_back(0);
	board[2].push_back(0);
	board[2].push_back(0);
	board[2].push_back(0);
	board[2].push_back(0);
	board[2].push_back(0);

	board[3].push_back(0);
	board[3].push_back(0);
	board[3].push_back(1);
	board[3].push_back(1);
	board[3].push_back(1);
	board[3].push_back(1);
	board[3].push_back(0);

	board[4].push_back(0);
	board[4].push_back(1);
	board[4].push_back(1);
	board[4].push_back(1);
	board[4].push_back(1);
	board[4].push_back(1);
	board[4].push_back(0);

	board[5].push_back(0);
	board[5].push_back(0);
	board[5].push_back(0);
	board[5].push_back(0);
	board[5].push_back(0);
	board[5].push_back(1);
	board[5].push_back(1);

	board[6].push_back(0);
	board[6].push_back(0);
	board[6].push_back(1);
	board[6].push_back(0);
	board[6].push_back(0);
	board[6].push_back(0);
	board[6].push_back(0);

	cout << solution(board);
}