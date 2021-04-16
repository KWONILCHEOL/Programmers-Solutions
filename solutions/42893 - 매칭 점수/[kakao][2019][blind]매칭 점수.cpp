/*
	[kakao][2019][blind]매칭 점수
	https://programmers.co.kr/learn/courses/30/lessons/42893
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
map<string, int> contentIdx;
vector<vector<string>> link(20);
float point[20];
int basePoint[20];

char Lower(char c) {
	return c <= 'Z' ? c - 'A' + 'a' : c;
}
bool isAlpha(char c) {
	return 'a' <= c && c <= 'z';
}
int solution(string word, vector<string> pages) {
	int wordLen = word.size();
	for (char& c : word)
		c = Lower(c);

	int pagesSize = pages.size();
	for (int i = 0; i < pagesSize; i++) {
		
		//stream으로 짜르는법
		/*string stringBuffer;
		istringstream ssPages(pages[i]);
		while (getline(ssPages, stringBuffer, '\n')) {
			if (stringBuffer.find("  <meta property=\"og:url\" content=\"") == 0) {
				contentIdx[stringBuffer.substr(35, stringBuffer.size() - 38)] = i;
			}
			else if (stringBuffer.find("<a href=\"") == 0) {
				int last = stringBuffer.find("\">");
				link[i].push_back(stringBuffer.substr(9, last - 9));
			}
		}*/

		string metaString = pages[i];
		//테스트케이스 9번 <meta property=\"og:url\" 이거로 통과
		int ogurlStart = metaString.find("<meta property=\"og:url\"");
		metaString = metaString.substr(ogurlStart);
		int startMeta = metaString.find("https://");
		metaString = metaString.substr(startMeta);
		int lastMeta = metaString.find("\"/>");
		contentIdx[metaString.substr(0, lastMeta)] = i;

		string linkString = pages[i];
		while (true) {
			int startLink = linkString.find("<a href=");
			if (startLink == -1)
				break;
			linkString = linkString.substr(startLink);
			int lastLink = linkString.find(">");
			link[i].push_back(linkString.substr(9, lastLink - 10));
			linkString = linkString.substr(lastLink);
		}

		int startBody = pages[i].find("<body>") + 6;
		int lastBody = pages[i].find("</body>");

		string bodyString = pages[i].substr(startBody, lastBody - startBody);
		for (char& c : bodyString)
			c = Lower(c);

		for (int j = 1; j < lastBody - startBody - wordLen; j++) {
			if (isAlpha(bodyString[j - 1]) || isAlpha(bodyString[j + wordLen]))
				continue;
			if (bodyString.substr(j, wordLen) == word) {
				basePoint[i]++;
				point[i]++;
			}
		}
	}

	//링크점수 = 링크가 오는 페이지의 (기본점수 / 외부링크)
	//link[n]은 n번째 page의 링크, link[n][0~m]이 각 링크 이름이 되는데
	//map[link[n][0~m]]으로 index를 구할 수 있음

	for (int i = 0; i < pagesSize; i++) {
		int linkSize = link[i].size();
		for (int j = 0; j < linkSize; j++) {
			if (contentIdx.find(link[i][j]) != contentIdx.end()) {
				int idx = contentIdx[link[i][j]];
				point[idx] += (float(basePoint[i]) / linkSize);
			}
		}
	}

	float fMax = 0;
	int answer = 0;
	for (int i = 0; i < pagesSize; i++) {
		if (fMax < point[i]) {
			fMax = point[i];
			answer = i;
		}
	}

	return answer;
}

int main()
{
	solution("Muzi", { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" });
}
