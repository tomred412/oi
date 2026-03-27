'''
ID: dermotl1
LANG: PYTHON3
PROG: clocks
'''

original_clocks = [0] * 9
current_clocks = [0] * 9
press_count = [0] * 10

moves = [[0], [0, 1, 3, 4, -1], [0, 1, 2, -1], [1, 2, 4, 5, -1],
    [0, 3, 6, -1], [1, 3, 4, 5, 7, -1], [2, 5, 8, -1], [3, 4, 6, 7, -1],
    [6, 7, 8, -1], [4, 5, 7, 8, -1]]

min_total_moves = 10**9
best = [0] * 10

def checkCombination():
    global original_clocks, current_clocks, moves, total_moves, min_total_moves, best
    for i in range(9):
        current_clocks[i] = original_clocks[i]
    for i in range(1, 10):
        times = press_count[i]

        if times > 0:
            for j in range(6):
                pos = moves[i][j]
                if pos == -1:
                    break
                current_clocks[pos] += times

    for i in range(9):
        if current_clocks[i] % 4 != 0:
            return
    
    total_moves = 0

    for i in range(1, 10):
        total_moves += press_count[i]

    if total_moves < min_total_moves:
        min_total_moves = total_moves
        for i in range(1, 10):
            best[i] = press_count[i]
    
def main():
    with open("clocks.in", "r") as fin:
        data = []
        for i in fin:
            temp = i.split()
            for j in temp:
                data.append(int(j))

    for i in range(9):
        temp = data[i]
        if temp == 12:
            original_clocks[i] = 0
        else:
            original_clocks[i] = temp // 3
    
    for press_count[1] in range(4):
        for press_count[2] in range(4):
            for press_count[3] in range(4):
                for press_count[4] in range(4):
                    for press_count[5] in range(4):
                        for press_count[6] in range(4):
                            for press_count[7] in range(4):
                                for press_count[8] in range(4):
                                    for press_count[9] in range(4):
                                        checkCombination()
    
    with open("clocks.out", "w") as fout:
        temp = True
        for i in range(1, 10):
            for j in range(best[i]):
                if not temp:
                    fout.write(" ")

                fout.write(str(i))
                temp = False

        fout.write("\n")

if __name__ == "__main__":
    main()