from time import time
from BFS_search import breadth_first_search
from Astar_search import Astar_search
from RBFS_search import recursive_best_first_search
from puzzle import Puzzle


state=[1, 3, 4,8, 6, 2,7, 0, 5]


Puzzle.num_of_instances=0
t0=time()
bfs=breadth_first_search(state)
t1=time()-t0
print('BFS:', bfs)
print('space:',Puzzle.num_of_instances)
print('time:',t1)
print()

Puzzle.num_of_instances = 0
t0 = time()
astar = Astar_search(state)
t1 = time() - t0
print('A*:',astar)
print('space:', Puzzle.num_of_instances)
print('time:', t1)
print()

Puzzle.num_of_instances = 0
t0 = time()
RBFS = recursive_best_first_search(state)
t1 = time() - t0
print('RBFS:',RBFS)
print('space:', Puzzle.num_of_instances)
print('time:', t1)
print()