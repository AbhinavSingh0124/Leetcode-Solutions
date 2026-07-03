class Solution(object):
    def findMaxPathScore(self, edges, online, k):
        """
        :type edges: List[List[int]]
        :type online: List[bool]
        :type k: int
        :rtype: int
        """
        n = len(online)
        
        # Step 1: Build the adjacency list
        adj = [[] for _ in range(n)]
        for u, v, cost in edges:
            if online[u] and online[v]:
                adj[u].append((v, cost))
                
        # Compute in-degrees for topological sort
        in_degree = [0] * n
        for u in range(n):
            if online[u]:
                for v, c in adj[u]:
                    in_degree[v] += 1
                    
        queue = [i for i in range(n) if online[i] and in_degree[i] == 0]
        topo_order = []
        
        while queue:
            u = queue.pop(0)
            topo_order.append(u)
            for v, c in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    queue.append(v)

        # Helper function to check if a minimum edge cost of 'mid' is achievable
        def can_reach(mid):
            dp = [float('inf')] * n
            dp[0] = 0
            
            for u in topo_order:
                if dp[u] == float('inf'):
                    continue
                for v, cost in adj[u]:
                    if cost >= mid: 
                        if dp[u] + cost < dp[v]:
                            dp[v] = dp[u] + cost
                            
            return dp[n - 1] <= k

        # Step 2: Binary search on the maximum possible minimum edge cost
        low = 0
        high = max([edge[2] for edge in edges]) if edges else 0
        ans = -1
        
        while low <= high:
            mid = low + (high - low) // 2
            
            if can_reach(mid):
                ans = mid        # Found a valid path, try to maximize the score
                low = mid + 1
            else:
                high = mid - 1
                
        return ans