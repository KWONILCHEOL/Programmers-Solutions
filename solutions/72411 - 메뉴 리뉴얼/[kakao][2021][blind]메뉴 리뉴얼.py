# [kakao][2021][blind]메뉴 리뉴얼
# https://programmers.co.kr/learn/courses/30/lessons/72411

from itertools import combinations
from collections import Counter

# 방법 1
def solution(orders, course):
    answer = []
    dic = {}

    for s in orders:
        for n in course:
            if n <= len(s):
                for x in combinations(s, n):
                    key = ''.join(sorted(x))
                    if key in dic:
                        dic[key] += 1
                    else:
                        dic[key] = 1

    del_list = []
    for key in dic.keys():
        if dic[key] < 2:
            del_list.append(key)

    for item in del_list:
        del dic[item]

    cnt = [0] * 11
    for key in dic.keys():
        cnt[len(key)] = max(cnt[len(key)], dic[key])

    for i in range(2, 11):
        if cnt[i] == 0:
            continue
        for key in dic.keys():
            if i == len(key) and cnt[i] == dic[key]:
                answer.append(key)

    answer.sort()
    return answer

# 방법 2
# def solution(orders, course):
#     result = []
#
#     for course_size in course:
#         order_combinations = []
#         for order in orders:
#             order_combinations += combinations(sorted(order), course_size)
#
#         most_ordered = Counter(order_combinations).most_common()
#         result += [ k for k, v in most_ordered if v > 1 and v == most_ordered[0][1] ]
#
#     return [ ''.join(v) for v in sorted(result) ]

# 방법 3
# def solution(orders, course):
#     answer = []
#     for c in course:
#         order_combinations = []
#         for order in orders:
#             order_combinations += combinations(sorted(order), c)
# 
#         counter = Counter(order_combinations)
#         if len(counter) == 0:
#             continue
# 
#         _max = max(counter.values())
#         if _max == 1:
#             continue
# 
#         answer += [''.join(f) for f in counter if counter[f] == _max]
# 
#     return sorted(answer)


print(solution(["ABCFG", "AC", "CDE", "BCFG", "ACDE", "ACDEH"], [2, 3, 4]))
print(solution(["ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"], [2, 3, 5]))
print(solution(["XYZ", "XWY", "WXA"], [2, 3, 4]))