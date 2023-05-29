from .sequential.sop import sop_state
from .sequential.sop import sop


def op(f,R,beta) :
    S = sop_state()
    S = sop(S,f,R,beta)
    return S.s
