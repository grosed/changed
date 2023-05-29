
class point_function :
    def __init__(self) :
        self.D = {}
    def union(self,S) :
        for x,y in S :
            self.D[x] = y
    def diff(self,S) :
        for s in S :
            self.D.pop(s[0])
    def __call__(self,*args) :
        x = args
        if len(x) == 1 :
            x = x[0]
        return self.D[x]
    def domain(self) :
        return list(self.D.keys())
    def image(self) :
        return list(self.D.values())
