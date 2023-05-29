from .point_function import point_function

def split(f,R) :
    ra,rb = min(R),max(R)
    return min([(r,f(ra,r) + f(r,rb)) for r in R],key = lambda x : x[1])
