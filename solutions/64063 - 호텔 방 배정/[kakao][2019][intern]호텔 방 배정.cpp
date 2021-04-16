// [kakao][2019][intern]호텔 방 배정
// https://programmers.co.kr/learn/courses/30/lessons/64063

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
multiset <int> s;
int solution(vector<int> stones, int k) {
	int ans = 1e9;
	
	for (int i = 0; i < k - 1; i++)
		s.insert(stones[i]);
    
	for (int i = k - 1, j = 0; i < stones.size(); i++){
		s.insert(stones[i]);
		auto x = s.end(); x--;
        cout << *x << '\n';
		ans = min(ans, *x);
		s.erase(s.find(stones[j++]));
	}

	return ans;
}