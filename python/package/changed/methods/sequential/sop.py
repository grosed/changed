from ...core.point_function import point_function
from ...core.split import split

class sop_state :
    def __init__(self) :
        self.a = None
        self.fstar = point_function()
        self.f = lambda i,j : self.fstar(j)
        self.s = point_function()
        self.T = []

def sop(S,g,R,beta) :
    if S.a == None :
        S.a = min(R)
    for r in R :
        S.fstar.union({(r,g(S.a,r))})
        S.T.append(r)
        index,cost = split(S.f,g,S.T)
        S.fstar.union({(r,cost + beta})           
        S.s.union({(r,(index,cost))})
    return S
