 
from collections import deque
import heapq
import numpy as np
import random
import sys
 
N = 3
 
def Manhattan(s1, s2):
  dist = 0
  for i1, d in enumerate(s1):
    i2 = s2.index(d)
    x1 = i1 % N
    y1 = i1 // N
    x2 = i2 % N
    y2 = i2 // N
    dist += abs(x1 - x2) + abs(y1 - y2)
  return dist
 
def Hamming(s1, s2):
  return sum(x != y for x, y in zip(s1, s2))
 
class Node:
  dirs = [0, -1, 0, 1, 0]
  def __init__(self, state, parent = None, h = 0):
    self.state = state
    self.parent = parent
    self.g = parent.g + 1 if parent else 0
    self.h = h
    self.f = self.g + self.h
 
  def getMoves(self):
    moves = []
    index = self.state.index(0)
    x = index % N
    y = index // N
    for i in range(4):
      tx = x + Node.dirs[i]
      ty = y + Node.dirs[i + 1]
      if tx < 0 or ty < 0 or tx == N or ty == N:
        continue
      i = ty * N + tx
      move = list(self.state)
      move[index] = move[i]
      move[i] = 0
      moves.append(tuple(move))
    return moves
 
  def print(self):
    print(np.reshape(self.state, (N, N)))
 
  def __lt__(self, other):
    return self.f < other.f
 
def AStarSearch(start_state, end_state, heuristic):
  def h(s):
    return heuristic(s, end_state)
  q = []
  s = Node(start_state, h=h(start_state))
  heapq.heappush(q, s)
  opened = {s.state : s.f}
  closed = dict()
  while q:
    n = heapq.heappop(q)
    if n.state == end_state:
      return n, len(opened), len(closed)
    if n.state in closed: continue
    closed[n.state] = n.f
    for move in n.getMoves():
      node = Node(move, n, h(move))
      if move in opened and opened[move] <= node.f: continue
      opened[node.state] = node.f
      heapq.heappush(q, node)
  return None, len(opened), len(closed)
 
def BFS(start_state, end_state):
  q = deque()
  q.append(Node(start_state))
  opened = set(start_state)
  closed = 0
  while q:
    n = q.popleft()
    if n.state == end_state:
      return n, len(opened), closed
    closed += 1
    for move in n.getMoves():
      if move in opened: continue
      opened.add(move)
      q.append(Node(move, n))
  return None, len(opened), closed
 
def getRootNode(n):
  return getRootNode(n.parent) if n.parent else n
 
def BidirectionalBFS(start_state, end_state):
  def constructPath(p, o):
    while o: 
      t = o.parent
      o.parent = p
      p, o = o, t
    return p
  ns = Node(start_state)
  ne = Node(end_state)
  q = [deque([ns]), deque([ne])]
  opened = [{start_state : ns}, {end_state: ne}]
  closed = [0, 0]
  while q[0]:
    l = len(q[0])
    while l > 0:
      p = q[0].popleft()
      closed[0] += 1
      for move in p.getMoves():
        n = Node(move, p)
        if move in opened[1]:
          o = opened[1][move]
          if getRootNode(n).state == end_state:
            o, n = n, o
          n = constructPath(n, o.parent)
          return n, len(opened[0]) + len(opened[1]), closed[0] + closed[1]
        if move in opened[0]: continue
        opened[0][move] = n
        q[0].append(n)
      l -= 1
    q.reverse()
    opened.reverse()
    closed.reverse()
  return None, len(opened[0]) + len(opened[1]), closed[0] + closed[1]
 
 
def print_path(n):
  if not n: return
  print_path(n.parent)
  n.print()
 
def solvable(state):
  inv = 0
  for i in range(N*N):
    for j in range(i + 1, N*N):
      if all((state[i] > 0, state[j] > 0, state[i] > state[j])):
        inv += 1
  return inv % 2 == 0
 
if __name__ == '__main__':
  s = [1, 2, 3, 4, 5, 6, 7, 0, 8]
  e = [1, 2, 3, 4, 5, 6, 7, 8, 0]
  i = 0
  while True:
    # random.shuffle(s)
    if not solvable(s): 
        continue
    # n1, opened1, closed1 = AStarSearch(tuple(s), tuple(e), heuristic=Manhattan)
    # n2, opened2, closed2 = AStarSearch(tuple(s), tuple(e), heuristic=Hamming)
    n3, opened3, closed3 = BFS(tuple(s), tuple(e))
    # n4, opened4, closed4 = BidirectionalBFS(tuple(s), tuple(e))
    # print("%d\t%d\t%d\t%d" % (closed1, closed2, closed3, closed4))
    # sys.stdout.flush()

    i += 1
    if i == 1000: break
    

# print("A*")
# print_path(n1)
# print('---------------')
print("BFS")
print_path(n3)
# print('---------------')
# print("Bi-BFS")
# print_path(n4)
# print('---------------')
 