

my_name = "Eray Mercan"
my_id = "230102002009"
my_email = "e.mercan2023@gtu.edu.tr"
# github.com/eraymerc

# read_file
# This function will take one parameter as string
# for filename. This function opens the
# file, reads the words and board entries, and
# assign them different lists.
# -------------------------------------------
# string filename : name of the file | Default: "test_puzzle.txt"
# -------------------------------------------
# output1 : list of strings for words
# output2 : list of string for board
# -------------------------------------------


def read_file(filename="test_puzzle.txt"):
    try:
        words = []  # list for words
        board = []  # list for board
        with open(filename, 'r') as file:

            boardFlag = False  # when True, start filling the list, board
            while True:
                line = file.readline()
                if line == "\n":
                    boardFlag = True
                    continue
                elif not line:  # if no value, reached the end of the file.
                    break
                if line[-1] == "\n":
                    line = line[:-1]
                if boardFlag:
                    board.append(line)
                else:
                    words.append(line)
        return words, board

    # Exceptions...
    except FileNotFoundError:
        # print(f"The file {filename} was not found.")
        return None, 1
    except Exception as e:
        return None, e

# check_consistency
# Checks the all rows and columns are in same size.
# ---------
# output: Boolean value


def check_consistency(board):
    width = len(board[0])
    for i in range(1, len(board)):
        if width != len(board[i]):
            return False
    return True

# mutates the board as list of lists of strings
# example : [["0","0","1"],["0","0","1"]]


def create_board(board):
    for i in range(len(board)):
        mini = []
        for j in range(len(board[i])):
            mini = mini + [board[i][j]]
        board[i] = mini
    return None

# does a thing


def identifier(words):
    mylist = [False] * len(words)
    return mylist


def print_board(board):
    for row in board:
        for cell in row:
            if cell == "0":
                print("+", end="")
            else:
                print(" ", end="")
        print("")
    return None

# print_board with rows and columns


def print_board_w_c(board):
    c = 0
    columnCount = len(board[0])
    print("   ", end="")
    for i in range(1, columnCount+1):
        print(f"C{i :<2}", end=" ")
    print()
    for row in board:
        c += 1
        print(f"R{c:<2}", end=" ")
        for cell in row:
            if cell == "0":
                print("+", end="   ")
            elif cell == "1":
                print(" ", end="   ")
            else:
                print(cell, end="   ")
        print("")
    return None


def print_wordlist(words, wstatus):
    maxWordWidth = len(max(words, key=len))
    maxWordWidth = maxWordWidth*(maxWordWidth > 5)+6*(maxWordWidth < 6)
    print(f"Word List{' ' * (maxWordWidth - 9)}     Status")
    for i in range(len(words)):
        print(f"W{i+1 :<3} {words[i] :<{maxWordWidth}}", end="   ")
        if wstatus[i] == False:
            print("NOT USED")
        else:
            print("USED")
    return None


def check_entries(coordinates, wordno, board, words):
    isCoordinatesValid = ((len(board) >= coordinates[0] and coordinates[0] > 0) and (
        (len(board[0]) >= coordinates[1] and coordinates[1] > 0)))

    isWordNoValid = (len(words) >= wordno and wordno > 0)
    return isCoordinatesValid, isWordNoValid


def check_location(board, words, coordinates, wordno, direction='H'):

    r = coordinates[0]-1  # row
    c = coordinates[1]-1  # column
    # check if the starting cell is forbidden cell
    if board[r][c] == "0":
        return False, 1

    # check if the direction is vertical and the upper cell is NOT A forbidden cell if any
    if direction == "V" and not ((r-1) < 0):
        if board[r-1][c] != "0":
            return False, 2

    # check if the direction is horizontal and the left cell is NOT A forbidden cell if any
    if direction == "H" and not ((c-1) < 0):
        if board[r][c-1] != "0":
            return False, 3

    # Check, from starting coordinates, if the word exceeds the board
    wordLength = len(words[wordno-1])
    if direction == "H":
        if ((c + wordLength) > len(board[r])):
            return False, 4
    else:
        if ((r + wordLength) > len(board)):
            return False, 7

    line = ""
    # check the gap
    if direction == "H":
        # just take the necessary part, no need to waste ram space
        line = board[r][c:c+wordLength]
        for cell in line:
            if cell == "0":
                return False, 5
    else:
        # take the vertical line
        line = [row[c] for row in board][r:r+wordLength]
        for cell in line:
            if cell == "0":
                return False, 8

    if direction == "H" and not ((c+wordLength) == (len(board[r]))):
        if board[r][c+wordLength] != "0":
            return False, 6
    if direction == "V" and not ((r+wordLength) == (len(board))):
        if board[r+wordLength][c] != "0":
            return False, 9
    return True, 0


def check_word_fits(board, words, coordinates, wordno, direction='H'):
    r = coordinates[0]-1  # row
    c = coordinates[1]-1  # column
    word = words[wordno-1]
    if direction == "H":
        for i in range(len(word)):
            if board[r][c+i] != "1" and board[r][c+i] != word[i]:
                return False, 1
    else:
        for i in range(len(word)):
            if board[r+i][c] != "1" and board[r+i][c] != word[i]:
                return False, 2
    return True, 0


def clear_board(board, wstatus):
    for i in range(len(wstatus)):
        wstatus[i] = False
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] != "1" and board[i][j] != "0":
                board[i][j] = "1"
    return None


def decompose_command(str1):
    direction = "H"
    str1 = str1.lower()

    isAllInfoAvailable = -4

    wordno = 0
    coordinates = [0, 0]
    # operation flag
    # 0 for word
    # 1 for row
    # 2 for column
    # 3 for direction
    opFlag = -1
    for char in str1:

        if char == "w":
            opFlag = 0
            isAllInfoAvailable += 1
            continue
        elif char == "r":
            opFlag = 1
            isAllInfoAvailable += 1
            continue
        elif char == "c":
            opFlag = 2
            isAllInfoAvailable += 1
            continue
        elif char == "d":
            opFlag = 3
            isAllInfoAvailable += 1
            continue

        if opFlag == 0:
            if char.isdigit():
                wordno = wordno*10 + int(char)
            continue
        elif opFlag == 1:
            if char.isdigit():
                coordinates[0] = coordinates[0]*10 + int(char)
            continue
        elif opFlag == 2:
            if char.isdigit():
                coordinates[1] = coordinates[1]*10 + int(char)
            continue
        elif opFlag == 3:
            if char == "v":
                direction = "V"
            continue

    if isAllInfoAvailable != 0:
        isAllInfoAvailable = -1
        wordno = None
        coordinates = None
        direction = None

    return isAllInfoAvailable, wordno, coordinates, direction


def word_it(board, words, wstatus, coordinates, wordno, direction):
    isCoordinatesValid, isWordNoValid = check_entries(
        coordinates, wordno, board, words)
    if not (isCoordinatesValid and isWordNoValid):
        return False
    isLocationValid, _ = check_location(
        board, words, coordinates, wordno, direction)
    if not isLocationValid:
        return False
    isWordFits, _ = check_word_fits(
        board, words, coordinates, wordno, direction)
    if not isWordFits:
        return False
    # check the word is used--
    if wstatus[wordno-1]:
        return False
    # --
    # place the word--
    r = coordinates[0]-1  # row
    c = coordinates[1]-1  # column
    word = words[wordno-1]
    if direction == "H":
        for i in range(len(word)):
            board[r][c+i] = word[i]
    else:
        for i in range(len(word)):
            board[r+i][c] = word[i]
    # --
    wstatus[wordno-1] = True
    # print(board)
    return True


def copy_board(board):
    res = []
    for i in range(len(board)):
        res.append([])
        for cell in board[i]:
            res[i].append(cell)
    return res


def track_move(mvn, trackboard, coordinates, wordno, direction, board, wstatus):
    trackboard.append((coordinates, wordno, direction,
                      copy_board(board), wstatus))
    return mvn+1


def check_solved(board):
    for row in board:
        for cell in row:
            if cell == "1":
                return False
    return True


def mutateToPrev(board, prev):
    for row in range(len(board)):
        for cell in range(len(board[0])):
            board[row][cell] = prev[row][cell]
    return None


def solve_board(board, words):  # now works faster!
    if check_solved(board):
        return True
    # start with longer words to
    # solve it much more faster.
    # this line mutates the original words list but,
    # we close the program after solving it automatically,
    # due to that reason it's not an issue
    words.sort(key=len)

    for wordno in range(len(words), 0, -1):  # reverse loop
        for r in range(len(board)):
            for c in range(len(board[r])):
                direction = "H"

                prevBoard = copy_board(board)
                isWordedIt = word_it(
                    board, words, [False]*len(words), [r+1, c+1], wordno, direction)
                # remove the word from the list

                if isWordedIt:
                    newWords = [i for i in words]
                    newWords.pop(wordno-1)
                    if solve_board(board, newWords) == True:
                        return True
                    mutateToPrev(board, prevBoard)

                direction = "V"

                prevBoard = copy_board(board)
                isWordedIt = word_it(
                    board, words, [False]*len(words), [r+1, c+1], wordno, direction)
                if isWordedIt:
                    newWords = [i for i in words]
                    newWords.pop(wordno-1)
                    # remove the word from the list
                    if solve_board(board, newWords) == True:
                        return True
                    mutateToPrev(board, prevBoard)

    return False


def undoMove(board, wstatus, trackMoves):
    if trackMoves:
        wordno = trackMoves.pop()[1]
        if trackMoves:
            mutateToPrev(board, trackMoves[-1][3])
            wstatus[wordno-1] = False
        else:
            clear_board(board, wstatus)
        return True
    else:
        return False


def printColored(text, colorText, colorBack, isColored=True, end="\n"):
    colorBack = colorBack.lower()
    colorText = colorText.lower()
    textColors = {"red": "\u001b[31m",
                  "white": "\u001b[97m", "cyan": "\u001b[36m"}
    backColors = {"red": "\u001b[41m", "green": "\u001b[42m"}
    defaultCommand = "\u001b[0m"
    if not isColored:
        print(text)
        return
    if colorBack == "":
        print(f"{textColors[colorText]}{text}{defaultCommand}", end=end)
    else:
        print(
            f"{backColors[colorBack]}{textColors[colorText]}{text}{defaultCommand}", end=end)
    return None


def word_puzzle():
    isColored = input(
        "Does your terminal support ANSI Escape Codes? y:yes, n:no : ")
    isColored = isColored.lower()
    isColored = (isColored == "yes" or isColored == "y")

    isFileRead = False
    wstatus = None
    trackMoves = []
    while True:
        if not isFileRead:
            fileName = input("Type a file name (Default : test_puzzle.txt) : ")
            if fileName == "":
                words, board = read_file()
            else:
                words, board = read_file(fileName)

            if isinstance(words, type(None)):
                if board == 1:
                    printColored("File not found!\a", "red", "", isColored)
                    isRetry = input("Do you want to retry? y:yes, n:no : ")
                    if isRetry == "n" or isRetry == "no":
                        print("Bye!")
                        exit(0)
                    continue

            if not check_consistency(board):
                printColored("The Board is not consistent!\a",
                             "red", "", isColored)
                isRetry = input("Do you want to retry? y:yes, n:no : ")
                if isRetry == "n" or isRetry == "no":
                    print("Bye!")
                    exit(0)
                continue
            wstatus = identifier(words)
            create_board(board)
            isFileRead = True

        print()
        print_wordlist(words, wstatus)
        print()
        print_board_w_c(board)
        print(
            """Please choose,
        \ta word from list,
        \ta row and a column, and
        \tdirection of the word, V:Vertical H:Horizontal
        \tExample Command: W1R1C2DV
        \tother commands:
        \t\tb  : undo a move   | q  : quit
        \t\tcb : clear board   | s  : autosolve
        \n>:""", end="")
        command = input()
        if command == "b":
            if not undoMove(board, wstatus, trackMoves):
                printColored("Can't move back further!\a",
                             "red", "", isColored)
        elif command == "cb":
            clear_board(board, wstatus)
        elif command == "q":
            printColored("QUITING", "cyan", "", isColored)
            exit(0)
        elif command == "s":
            printColored("\tBRUTE FORCING THE SOLUTION...",
                         "white", "red", isColored)
            clear_board(board, wstatus)
            isSolved = solve_board(board, words)
            if isSolved:
                printColored("\t\tSOLVED!\a", "white", "green", isColored)
                print_board_w_c(board)
                input("-press enter to quit program-")
                printColored("QUITING", "cyan", "", isColored)
                exit(0)
            else:
                clear_board(board, wstatus)
                printColored(
                    "\tThis puzzle doesn't have a solution >:(\a", "white", "red", isColored)
                input("-press enter to quit program-")
                printColored("\tKILLING THE PROGRAM"+" " *
                             20, "white", "red", isColored)
                exit(0)
        else:
            iflag, wordno, coordinates, direction = decompose_command(command)
            if iflag == -1:
                printColored("UNAVAILABLE COMMAND!\a",
                             "white", "red", isColored)
            else:
                isWordedIt = word_it(board, words, wstatus,
                                     coordinates, wordno, direction)
                if not isWordedIt:
                    printColored("ILLEGAL MOVE!\a", "white", "red", isColored)
                else:
                    isSolved = check_solved(board)
                    if isSolved:
                        print_board_w_c(board)
                        printColored(
                            "YOU DID IT! NOW YOU ARE THE MASTER OF CROSSWORD PUZZLES!!!\a", "white", "green", isColored)
                        input("-press enter to quit program-")
                        printColored(
                            "           GAME OVER, KILLING THE PROGRAM"+" "*17, "white", "RED", isColored)
                        exit(0)
                    track_move(0, trackMoves, coordinates,
                               wordno, direction, board, wstatus)


if __name__ == "__main__":
    word_puzzle()
    #a = check_location([[1, 1, 1, 1, 0], [0, 0, 0, 0, 0], [1, 0, 0, 0, 0], [
    #               1, 0, 0, 0, 0], [1, 0, 0, 0, 0]], ['TECH', 'GTU'], [1, 1], 1, 'H')
    #b = check_location([["1", "1", "1", "1", "0"], ["0", "0", "0", "0", "0"], ["1", "0", "0", "0", "0"], [
    #               "1", "0", "0", "0", "0"], ["1", "0", "0", "0", "0"]], ['TECH', 'GTU'], [1, 1], 1, 'H')

    #print(a)
    #print(b)


    #check_solved([['T', 'E', 'C', 'H', 0], [0, 0, 1, 0, 0], [
    #             1, 0, 1, 0, 0], [1, 0, 0, 0, 0], [1, 1, 1, 1, 1]])


# :)
