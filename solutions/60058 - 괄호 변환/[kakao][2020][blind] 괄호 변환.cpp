/*
	[kakao][2020][blind] 괄호 변환
	https://programmers.co.kr/learn/courses/30/lessons/60058
*/
#include<iostream>
using namespace std;

bool correct(string p) {
	int l = 0;
	for (int i = 0; i < p.length(); i++) {
		l += p[i] == '(' ? 1 : -1;
		if (l < 0)
			return false;
	}
	return true;
}

string solution(string p) {
	if (correct(p))
		return p;

	string u, v;
	int l = 0;
	for (int i = 0; i < p.length(); i++) {
		l += p[i] == '(' ? 1 : -1;
		if (l == 0) {
			u = p.substr(0, i + 1);
			v = p.substr(i + 1);
			break;
		}
	}
	
	if (correct(u)) 
		return u + solution(v);
	
	string answer = "(" + solution(v) + ")";
	u = u.substr(1, u.length() - 2);
	for (int i = 0; i < u.length(); i++)
		u[i] = u[i] == '(' ? ')' : '(';
	
	return answer + u;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//cout << solution("(()())()") << '\n';
	//cout << solution(")(") << '\n';
	cout << solution("()))((()") << '\n';
}