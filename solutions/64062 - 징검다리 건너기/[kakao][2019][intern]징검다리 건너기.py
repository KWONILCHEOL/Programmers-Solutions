# [kakao] 징검다리 건너기
# https://programmers.co.kr/learn/courses/30/lessons/64062
# 시간 복잡도 : O(nlogm),  m=2e8
def solution(stones, k):
  answer = 0
  left, right = 0, int(2e8)

  while left <= right:  #O(logm)
    mid = (left + right) // 2
    s = list(stones)

    for i in range(len(s)):
      s[i] -= mid

    cnt = 0
    for i in range(len(s)):
      if s[i] < 0:
        cnt += 1
        if cnt == k:
          break
      else:
        cnt = 0

    if cnt < k:
      answer = max(answer,mid)
      left = mid + 1
    else:
      right = mid - 1
  return answer

print(solution([2, 4, 5, 3, 2, 1, 4, 2, 5, 1],3))