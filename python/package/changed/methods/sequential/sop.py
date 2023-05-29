from ...core.point_function import point_function
from ...core.split import split

class sop_state :
    def __init__(self) :
        self.a = None
        self.fstar = point_function()
        self.f = lambda i,j : self.fstar(j)
        self.s = point_function()
        self.T = []
        self.cost = None

def sop(S,g,R,beta) :
    if S.cost == None :
        S.a = min(R)
        S.cost = -beta
        for r in R :
            print(r)
            S.fstar.union({(r,S.cost + beta)})
            S.T.append(r)
            index,S.cost = split(S.f,g,S.T)
            S.s.union({(r,(index,S.cost))})
    return S
