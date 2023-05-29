def amoc(f,R,beta) :
    a,b = min(R),max(R)
    index,cost = split(f,f,R)
    return (index,cost + beta) if cost + beta < f(a,b) else (a,cost)
