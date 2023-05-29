from .split import split
from .add import add

def amoc(f,g,R,beta) :
    a,b = min(R),max(R)
    index,cost = split(f,g,R)
    return (index,cost + beta) if cost + beta < g(a,b) else (a,cost)
