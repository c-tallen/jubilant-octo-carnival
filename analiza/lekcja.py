class Button():
    def __init__(self, name):
        self.name = name

class Pies():
    liczba_psow = 0
    def __init__(self, imie, rasa):
        Pies.liczba_psow += 1
        self.imie = imie
        self.rasa = rasa
    def introduce(self):
        print('My name is', self.imie, 'and I am a', self.rasa)
    def get_imie(self):
        return self.imie
    def set_imie(self, nowe_imie):
        self.imie = nowe_imie

hektor = Pies('Hektor', 'West Highland Terrier')
print(Pies.liczba_psow)
print(hektor.get_imie())
hektor.introduce()
new_button = Button('Submit')

