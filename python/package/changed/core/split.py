from .point_function import point_function

def split(f,g,R) :
    a,d = min(R),max(R)
    internal = [(c,f(a,b) + g(c,d)) for b,c in zip(R[:-1],R[1:])]
    return min([(a,g(a,d))] + internal + [(d,f(a,d))] ,key = lambda x : x[1])
