class UnionFind():
    def __init__(self):
        self.parent = {} # Store tree structure
        self.rank = {} # Store size of the tree
        self.count = 0

    def _add_node(self, node):
        self.parent[node] = node
        self.rank[node] = 0

    def find(self, node):
        '''
        Returns the root of a given node in O(log n) time
        '''
        if node not in self.parent: 
            self._add_node(node)
            return node

        current_node = node
        # Traverse up the tree until a root is found
        while self.parent[current_node] != current_node:
            current_node = self.parent[current_node]
        return current_node

    def union(self, node1, node2):
        '''
        Combine two disjoint sets to all share the same root.
        '''
        root1 = self.find(node1)
        root2 = self.find(node2)

        if root1 != root2:
            # Choose the root of the larger tree to be the new root
            # This ensures that the tree is balanced and ensures log(n) look up times
            if self.rank[root1] < self.rank[root2]:
                self.parent[root1] = root2
            elif self.rank[root1] > self.rank[root2]:
                self.parent[root2] = root1
            else:
                # If the tree sizes are the same, arbitrarily pick root1 to be the new root
                self.parent[root2] = root1
                self.rank[root1] += 1

    def count_roots(self):
        """ Returns the number of roots in O(nlogn) time
        """
        nodes = set()
        for node in self.parent:
            root = self.find(node)
            nodes.add(root)

        return len(nodes)

