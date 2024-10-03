'''
Returns a list of size rows, where each entry is itself
a list of size columns, where each entry contains the value '.'
'''
def get_initial_board(rows, columns):
    '''
    Title: [['.']*rows for _ in range(columns)]
        Author: Mark Byers
        Date: 9/2/2024
        Code version: Unknown
        Availability: https://stackoverflow.com/questions/2739552/2d-list-has-weird-behavor-when-trying-to-modify-a-single-value/2739564
    '''
    board= [['.']*rows for _ in range(columns)]
    return board

'''
Prints a copy of the board, where board is a list of
list objects, each entry a one-character str object
'''
def print_board(board):
    width = len(board[0])
    printWidth = (2 * width) - 1
    print(('_' * printWidth).center(printWidth + 2))
    for row in range(len(board) - 1, -1, -1):
        print('|', end='')
        for column in range(len(board[0])):
            if column < width - 1:
                print(board[row][column], end=' ')
            else:
                print(f'{board[row][column]}|')
    print(('-' * printWidth).center(printWidth + 2))

'''
Places a chip in the column of the board of the chip type.
This method should find the next available spot in that column,
if any. This method returns the row in which the chip settles
'''
def insert_chip(board, column, chip):
    height = len(board)
    for row in range(0, height):
        if board[row][column] != '.':
            continue
        else:
            board[row][column] = chip
            return row

'''
This method checks if the player represented by specified chip
 type has won the game by looking on the board at the position
 (row, column). If this is a win for the player, returns True;
 otherwise, returns False.
'''
def is_win_state(chip, board, row, column):
    width = len(board[0])

    # search by row (vertical)
    count = 0
    for bottom in range(row, -1, -1):
        if board[bottom][column] == chip and count == 3:
            return True
        elif board[bottom][column] == chip:
            count += 1
        else:
            count = 0

    count = 0
    # search by column (horizontal)
    for side in range(0, width):
        if board[row][side] == chip and count == 3:
            return True
        elif board[row][side] == chip:
            count += 1
        else:
            count = 0


'''
This method checks if the board is full. If it
is full, returns True; otherwise, returns False
'''
def is_board_full(board):
    for row in board:
        for column in range(0, len(row)):
            if row[column] == '.': return False
    return True

def validity(name, var):
    try:
        var = int(var)
    except ValueError:
        print("Error: not a number!")
        return False
    if var < 4:
        print(f'Error: {name} must be at least 4!')
    elif var > 25:
        print(f'Error: {name} can be at most 25!')
    else:
        return True

def column_full(board, column):
    for row in range(0, len(board)):
        if board[row][column] != '.':
            continue
        else:
            return False
    return True

if __name__ == "__main__":
    print('Welcome to Find Four!\n---------------------')
    valid = False
    while not valid:
        height = input("Enter height of board (rows): ")
        valid = validity('height', height)
    height = int(height)
    valid = False
    while not valid:
        width = input("Enter width of board (columns): ")
        valid = validity('width', width)
    width = int(width)

    board = get_initial_board(height, width)
    print_board(board)

    print("\nPlayer 1: x\nPlayer 2: o")
    players = [["Player 1", 'x'], ["Player 2", 'o']]

    player = 0
    while True:
        valid = False
        print()
        currentCol = 0
        currentRow = 0
        while not valid:
            column = input(f'{players[player][0]} - Select a column: ')
            try:
                column = int(column)
                if column > width or column < 0 or column == width:
                    print("Error: no such column!")
                elif column_full(board, column):
                    print("Error: column is full!")
                else:
                    currentRow = insert_chip(board, column, players[player][1])
                    currentCol = column
                    valid = True
            except ValueError:
                print("Error: not a number!")
        print_board(board)
        # check game state
        if is_board_full(board):
            print("\nDraw game! Players tied.")
            exit()
        elif is_win_state(players[player][1], board, currentRow, currentCol):
            print(f'\n{players[player][0]} won the game!')
            exit()
        else:
            if player == 0:
                player = 1
            else:
                player = 0
