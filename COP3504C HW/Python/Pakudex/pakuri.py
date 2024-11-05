from math import sqrt, floor

class Pakuri:
    def __init__(self, species:str, level:int):
        self.__species = species
        self.__level = level
        self.__attack = (len(species) * 7 + 11) % 16
        self.__defense = (len(species) * 5 + 17) % 16
        self.__stamina = (len(species) * 6 + 13) % 16


    def get_species(self):
        return self.__species

    def get_attack(self):
        return self.__attack

    def get_defense(self):
        return self.__defense

    def get_stamina(self):
        return self.__stamina

    def set_attack(self, new_attack:int):
        self.__attack = new_attack

    # get and set value
    @property
    def cp(self):
        return floor(self.__attack * sqrt(self.__defense) * sqrt(self.__stamina) * self.__level * 0.08)

    # get and set value
    @property
    def hp(self):
        return floor((self.__stamina * self.__level) / 6)

    # get value
    @property
    def level(self):
        return self.__level

    # set value
    @level.setter
    def level(self, new_level:int):
        self.__level = new_level