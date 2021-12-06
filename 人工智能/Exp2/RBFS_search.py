from puzzle import Puzzle
from sys import maxsize


def recursive_best_first_search(initial_state):
    node=RBFS_search(Puzzle(state=initial_state, parent=None, action=None, path_cost=0, needs_hueristic=True), f_limit=maxsize)
    node=node[0]
    return node.find_solution()

def RBFS_search(node,f_limit):
    successors=[]

    if node.goal_test():
        return node,None
    children=node.generate_child()
    if not len(children):
        return None, maxsize
    count=-1
    for child in children:
        count+=1
        successors.append((child.evaluation_function,count,child))
    while len(successors):
        successors.sort()
        best_node=successors[0][2]
        if best_node.evaluation_function > f_limit:
            return None, best_node.evaluation_function
        alternative=successors[1][0]
        result,best_node.evaluation_function=RBFS_search(best_node,min(f_limit,alternative))
        successors[0]=(best_node.evaluation_function,successors[0][1],best_node)
        if result!=None:
            break
    return result,None

