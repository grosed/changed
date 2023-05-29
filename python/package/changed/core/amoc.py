from .split import split
from .add import add

def amoc(g,R,beta) :
    def f(i,j) : return 0 if i == j else g(i,j-1) + beta
    return split(add(f,g),R)
