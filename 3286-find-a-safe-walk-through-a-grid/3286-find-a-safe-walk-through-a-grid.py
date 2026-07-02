from collections import deque

class Solution(object):
    def findSafeWalk(self, grid, health):
        """
        :type grid: List[List[int]]
        :type health: int
        :type rtype: bool
        """
        m, n = len(grid), len(grid[0])
        
        # dist[r][c] stores the minimum health lost to reach (r, c)
        dist = [[float('inf')] * n for _ in range(m)]
        
        dq = deque()
        
        # Initialize the starting cell
        dist[0][0] = grid[0][0]
        dq.append((0, 0))
        
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        while dq:
            r, c = dq.popleft()
            
            # Early exit if we reached the destination
            if r == m - 1 and c == n - 1:
                break
                
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < m and 0 <= nc < n:
                    weight = grid[nr][nc]
                    # If a shorter path to (nr, nc) is found
                    if dist[r][c] + weight < dist[nr][nc]:
                        dist[nr][nc] = dist[r][c] + weight
                        if weight == 0:
                            dq.appendleft((nr, nc))
                        else:
                            dq.append((nr, nc))
        
        # We need to reach the end with at least 1 health left
        return dist[m - 1][n - 1] < health

