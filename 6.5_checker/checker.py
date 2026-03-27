'''
ID: dermotl1
LANG: PYTHON3
PROG: checker
'''

n = 0
row_used = [False] * 14
first_diagonal = [False] * 30
second_diagonal = [False] * 30
positions = [0] * 14
solutions = []


def placeHere(col):
    global n, row_used, first_diagonal, second_diagonal, positions, solutions
    if col == n:
        temp = [0] * n
        for i in range(n):
            temp[i] = positions[i]
        
        solutions.append(temp)
        return
    
    for i in range(n):
        first_d = i + col
        second_d = i - col + n - 1

        if not row_used[i] and not first_diagonal[first_d] and not second_diagonal[second_d]:
            row_used[i] = True
            first_diagonal[first_d] = True
            second_diagonal[second_d] = True

            positions[col] = i + 1
            placeHere(col + 1)

            row_used[i] = False
            first_diagonal[first_d] = False
            second_diagonal[second_d] = False

def main():
    global n
    with open("checker.in", "r") as fin:
        n = int(fin.read().strip())
    
    placeHere(0)
    solutions.sort()

    with open("checker.out", "w") as fout:
        printed = min(len(solutions), 3)
        for i in range(printed):
            for j in range(n):
                if j != 0:
                    fout.write(" ")
                fout.write(str(solutions[i][j]))
            fout.write("\n")

        fout.write(str(len(solutions)) + "\n")


if __name__ == "__main__":
    main()