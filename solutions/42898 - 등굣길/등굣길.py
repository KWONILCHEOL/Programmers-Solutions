# https://programmers.co.kr/learn/courses/30/lessons/42898

def solution(m, n, puddles):
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    dp[1][1] = 1

    for y,x in puddles:
        dp[x][y] = -1

    for x in range(1, n+1):
        for y in range(1, m+1):
            if x == y == 1:
                continue
            if dp[x][y] == -1:
                dp[x][y] = 0
                continue
            dp[x][y] = dp[x][y-1] + dp[x-1][y]

    answer = dp[n][m] % 1000000007
    return answer

# 4방향 모두 가능한 경우
# from collections import deque
# dx = [0,1,0,-1]
# dy = [1,0,-1,0]
# def solution(m, n, puddles):
#     visit = [[False] * (m + 1) for _ in range(n + 1)]
#     dp = [[0] * (m + 1) for _ in range(n + 1)]
#     dp[1][1] = 1
#     visit[1][1] = True
# 
#     for y,x in puddles:
#         visit[x][y] = True
#     que = deque()
#     que.append((1,1))
# 
#     while que:
#         length = len(que)
#         temp = set()
#         for _ in range(length):
#             x,y = que.popleft()
#             for i in range(4):
#                 nx = x + dx[i]
#                 ny = y + dy[i]
#                 if nx < 1 or ny < 1 or nx > n or ny > m:
#                     continue
#                 if visit[nx][ny]:
#                     continue
#                 dp[nx][ny] = (dp[nx][ny] + dp[x][y])
#                 temp.add((nx,ny))
# 
#         for x,y in temp:
#             visit[x][y] = True
#             que.appendleft((x,y))
# 
#     answer = dp[n][m] % 1000000007
#     return answer

m = 4
n = 3
puddles = [[2,2]]
print(solution(m,n,puddles))    #answer 4