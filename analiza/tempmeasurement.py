class TempMeasurement():
    def __init__(self, temp1, temp2):
        self.temp1 = temp1
        self.temp2 = temp2
    def temp_combinations(self):
        combinations = []
        for i in range(self.temp1 + 1):
            for j in range(self.temp2 + 1):
                combinations.append((i,j))
        return combinations


krotka = tuple()
measurement = TempMeasurement(2, 3)

print(measurement.temp_combinations())

class Measurement():
    def __init__(self, meas1, meas2):
        self.meas1 = meas1
        self.meas2 = meas2
    def __repr__(self):
        return f'{self.meas1} {self.meas2}'

meas  = Measurement("Pomiar", "PH")

print(meas)
