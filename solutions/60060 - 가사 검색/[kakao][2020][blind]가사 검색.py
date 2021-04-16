# [Ch15] 30 가사 검색
# https://programmers.co.kr/learn/courses/30/lessons/60060
# 시간 복잡도 : O(mlogn)

from bisect import bisect_left, bisect_right

def count_by_range(a, left_value, right_value):
  left_index = bisect_left(a,left_value)
  right_index = bisect_right(a,right_value)
  return right_index - left_index

def solution(words, queries):
  answer = []
  
  arr = [[] for _ in range(10001)]
  rev_arr = [[] for _ in range(10001)]

  for x in words:
    arr[len(x)].append(x)
    rev_arr[len(x)].append(x[::-1])

  for i in range(10001):
    arr[i].sort()
    rev_arr[i].sort()

  for q in queries:
    if q[0] == '?':
      res = count_by_range(rev_arr[len(q)], q[::-1].replace('?','a'), q[::-1].replace('?','z'))
    else:
      res = count_by_range(arr[len(q)], q.replace('?','a'), q.replace('?','z'))
      
    answer.append(res)
  
  return answer

words = ["frodo", "front", "frost", "frozen", "frame", "kakao"]
queries = ["fro??", "????o", "fr???", "fro???", "pro?"]
result = solution(words, queries)
print(result)