class IncrementIterator:

    def __init__(self, n):
        self.n = n
        self.i = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.n == self.i:
            raise StopIteration


        self.i += 2
        return self.i
print([a for a in IncrementIterator(10)])