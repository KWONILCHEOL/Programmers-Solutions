/*
	[kakao][2019][blind]후보키
	https://programmers.co.kr/learn/courses/30/lessons/42890
*/
#include <string>
#include <vector>
#include <set>
using namespace std;
#pragma warning(disable: 4996)
	
bool bits[9];
void getBits(int x) {
	for (int i = 1; i <= 8; i++, x /= 2)
		bits[i] = (x % 2);
}

int solution(vector<vector<string>> relation) {
	int answer = 0;
	int rows = relation.size();
	int cols = relation[0].size();
	bool check[256] = { false, };	//(8bit)
		
	vector<int> vAnswer;
	for (int i = 1; i < (1 << cols); i++) {
		getBits(i);
		
		vector<string> v(rows);
		for (int j = 0; j < rows; j++) 
			for (int k = 1; k <= 8; k++) 
				if (bits[k])
					v[j] += relation[j][k - 1];

		set<string> s;
		for (int j = 0; j < rows; j++)
			s.insert(v[j]);

		if (v.size() == s.size())
			vAnswer.push_back(i);
	}

	for (int i = 0; i < vAnswer.size(); i++) {
		int a = vAnswer[i];
		if (check[a])
			continue;
		for (int j = i + 1; j < vAnswer.size(); j++) {
			int b = vAnswer[j];
			if ((a&b) == a)
				check[b] = true;
			
			// if ((b-a) == (a^b)) 
				// check[b] = true;
		}
		//check[vAnswer] false가 후보키
		if (check[a] == false)
			answer++;
	}

	return answer;
}

int main()
{
	vector<vector<string>> relation;
	vector<string> v1 = { "100","ryan","music","2" };
	vector<string> v2 = { "200","apeach","math","2" };
	vector<string> v3 = { "300","tube","computer","3" };
	vector<string> v4 = { "400","con","computer","4" };
	vector<string> v5 = { "500","muzi","music","3" };
	vector<string> v6 = { "600","apeach","music","2" };

	relation.push_back(v1);
	relation.push_back(v2);
	relation.push_back(v3);
	relation.push_back(v4);
	relation.push_back(v5);
	relation.push_back(v6);
	printf("%d", solution(relation));
}
