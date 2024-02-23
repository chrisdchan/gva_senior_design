import numpy as np
import torch
from unionFind import UnionFind

class Counter:
    def __init__(self, mask):
        self.mask = mask
        self.N, self.M = np.shape(mask)
        self.union_find = UnionFind()

    def count_cells(self):
        """ Returns a count for all islands of pixels
            input:
                mask: tensor<long>
        """
        nodes = torch.nonzero(self.mask)
        for row, col in zip(nodes[:, 0], nodes[:, 1]):
            self.process_node((row.item(), col.item()))

        return self.union_find.count_roots()

    def process_node(self, node):
        neighbors = self.get_neighbors(node)
        for neighbor in neighbors:
            self.union_find.union(node, neighbor)

    def get_neighbors(self, node):
        row, col = node
        neighbors = []

        left = (row, col-1)
        right = (row, col+1)
        top = (row-1, col)
        down = (row+1, col)

        for coord in [left, right, top, down]:
            i = coord[0]
            j = coord[1]
            if self.is_in_bounds(i, j) and self.mask[i, j]:
                neighbors.append(coord)

        return neighbors

    def is_in_bounds(self, row, col):
        row_in_bounds = 0 <= row < self.N
        col_in_bounds = 0 <= col < self.M
        return row_in_bounds and col_in_bounds


def test_count_cells():
    mask = torch.tensor([
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ])
    counter = Counter(mask)

    assert counter.count_cells() == 3

if __name__ == '__main__':
    test_count_cells()