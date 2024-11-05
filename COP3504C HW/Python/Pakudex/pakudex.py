from pakuri import Pakuri

class Pakudex:
    def __init__(self):
        deck = []
        self.deck = deck

    def get_species_list(self): # prints list of all the Pakuri in Pakudex
        if len(self.deck) == 0:
            return None
        else:
            return [p.get_species() for p in self.deck]

    def get_stats(self, species:str): # gets level, CP, and HP of a specific Pakuri
        for i in self.deck:
            if i.get_species() == species:
                stats = [i.level, i.cp, i.hp]
                return stats
        return None

    def sort_pakuri(self):
        # Bubble Sort
        end = len(self.deck) - 1
        for j in range(end):
            swapped = False
            for i in range(end - j): # iterates through deck
                if self.deck[i].get_species() > self.deck[i+1].get_species():
                    temp = self.deck[i]
                    self.deck[i] = self.deck[i+1]
                    self.deck[i+1] = temp
                    swapped = True
            if not swapped:
                break


    def add_pakuri(self, species: str, level: int):
        if self.get_stats(species) is not None: # new ---------------------------
            return False # Pakuri duplicate so return False
        try:
            level = int(level)
            if level < 0: # new --------------------
                print("Level cannot be negative.") # prints for negative and returns False
                return False
            self.deck.append(Pakuri(species, level))
            return True
        except ValueError:
            return False # returns False if level is still a string (backup)

    def remove_pakuri(self, species:str):
        for i in range(len(self.deck)):
            if self.deck[i].get_species() == species:
                self.deck.pop(i)
                return True
        return False

    def evolve_species(self, species:str):
        for i in self.deck:
            if i.get_species() == species:
                i.level = i.level * 2
                new_attack = i.get_attack() + 1
                i.set_attack(new_attack)
                return True
        return False


def menu():
    print("\nPakudex Main Menu\n"
          "-----------------\n"
          "1. List Pakuri\n"
          "2. Show Pakuri\n"
          "3. Add Pakuri\n"
          "4. Remove Pakuri\n"
          "5. Evolve Pakuri\n"
          "6. Sort Pakuri\n"
          "7. Exit\n")
    try:
        option = int(input("What would you like to do? "))
        if option < 1 or option > 7:
            raise ValueError
    except ValueError:
        print("\nUnrecognized menu selection!")
        option = menu()
    return option

def choice(deck):
    option = menu()
    match option:
        case 1:  # List all Pakuri in Pakudex
            species_list = deck.get_species_list()
            if species_list is None:
                print("\nNo Pakuri currently in the Pakudex!")
            else:
                print("\nPakuri in Pakudex:") # new -------------------------
                # prints in line with formatting for list()
                for i in range(len(species_list)):
                    print(f'{i + 1}. {species_list[i]}')
            choice(deck)
        case 2:  # Show a particular Pakuri
            species = str(input("\nEnter the name of the species to display: "))
            specific_pakuri = deck.get_stats(species)
            if specific_pakuri is None:
                print("Error: No such Pakuri!")
            else:
                print(f'\nSpecies: {species}\n'
                      f'Level: {specific_pakuri[0]}\n'
                      f'CP: {specific_pakuri[1]}\n'
                      f'HP: {specific_pakuri[2]}')
            choice(deck)
        case 3:  # Add Pakuri
            new_species = str(input("\nSpecies: "))
            new_level = None
            if deck.get_stats(new_species) is not None:
                print("Error: Pakudex already contains this species!")
                deck.add_pakuri(new_species, new_level) # new -------------------
                # dummy call so that add_pakuri is still prompted and returns False
                choice(deck)
            else:
                valid = False
                while not valid:
                    new_level = input("Level: ")
                    try:
                        new_level = int(new_level) # new ----------
                        # checks if new_level is castable to int, excepts if it's not
                        if deck.add_pakuri(new_species, new_level):
                            print(f'Pakuri species {new_species} (level {new_level}) added!')
                            valid = True # breaks out of the while loop if pakuri was successfully added
                            # I.E. stops asking user to input new levels
                    except ValueError:
                        print("Invalid level!")
            choice(deck)
        case 4:  # Remove Pakuri
            remove_species = str(input("\nEnter the name of the Pakuri to remove: "))
            if deck.remove_pakuri(remove_species):
                print(f'Pakuri {remove_species} removed.')
            else:
                print("Error: No such Pakuri!")
            choice(deck)
        case 5:  # Evolve Pakuri
            evolve = input("\nEnter the name of the species to evolve: ")
            if deck.evolve_species(evolve):
                print(f'{evolve} has evolved!')
            else:
                print("Error: No such Pakuri!")
            choice(deck)
        case 6:  # Sort Pakuri
            deck.sort_pakuri()
            print("\nPakuri have been sorted!")
            choice(deck)
        case 7:  # Exit
            print("\nThanks for using Pakudex! Bye!")
            exit()

if __name__ == '__main__':
    print("Welcome to Pakudex: Tracker Extraordinaire!")
    deck = Pakudex()
    while 0 < 1:
        choice(deck)
