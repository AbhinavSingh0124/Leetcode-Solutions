from collections import deque

class Solution:
    def minScore(self, n, roads):
        graph = {i: [] for i in range(1, n + 1)}
        for u, v, w in roads:
            graph[u].append((v, w))
            graph[v].append((u, w))
        
        min_score = float('inf')
        queue = deque([1])
        visited = {1}
        
        while queue:
            node = queue.popleft()
            for neighbor, weight in graph[node]:
                min_score = min(min_score, weight)
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
                    
        return min_score
     