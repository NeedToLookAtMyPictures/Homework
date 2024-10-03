import heifer_generator as moo
import sys

if __name__ == "__main__":
    if sys.argv[1] == '-l':
        # cowsay.py -l list all available cows
        print('Cows available: heifer kitteh')
    elif sys.argv[1] == '-n':
        # cowsay.py -n COW MESSAGE print message and then moo.HeiferGenerator.cows[0 or 1] equals COW
        moo.get_cows()
        if sys.argv[2] == "heifer":
            output = " ".join(sys.argv[3:])
            print(output) # MESSAGE printed
            print(moo.HeiferGenerator.cows[0].get_image())
        elif sys.argv[2] == "kitteh":
            output = " ".join(sys.argv[3:])
            print(output) # MESSAGE printed
            print(moo.HeiferGenerator.cows[1].get_image())
        else:
            print(f'Could not find {sys.argv[2]} cow!')
    else:
        # cowsay.py MESSAGE print message and then moo.HeiferGenerator.cows[0]
        moo.get_cows()
        output = " ".join(sys.argv[1:])
        print(output) # MESSAGE printed
        print(moo.HeiferGenerator.cows[0].get_image())
