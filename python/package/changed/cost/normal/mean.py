from itertools import accumulate
from math import inf

class mean :
    def __init__(self,X,minseglen=0) :
        self.X = X
        self.SX = [0] + list(accumulate(X))
        self.SXX = [0] + list(accumulate([x*x for x in X]))
        self.minseglen = minseglen
    def __call__(self,a,b) :
        if b - a + 1 < self.minseglen :
            return inf
        val = self.SX[b+1] - self.SX[a]
        val *= val
        val /= (b - a + 1)
        val = -val
        val += self.SXX[b+1] - self.SXX[a]
        return val
