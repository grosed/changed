from .point_function import point_function

def split(f,R) :
    a,d = min(R),max(R)
    return min([(a,f(a,d))] + [(c,f(a,b) + f(c,d)) for b,c in zip(R[:-1],R[1:])],key = lambda x : x[1])
