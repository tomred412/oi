def main():
    t, k = map(int, input().split())

    while t > 0:
        n = int(input())
        s = input()
        if k == 0:
            print("YES")
            t -= 1
            continue
        else:
            answer = [''] * n
            flip = False

            for i in range(n - 1, -1, -1):
                c = s[i]

                if flip:
                    if c == 'O':
                        c = 'M'
                    else:
                        c = 'O'
                    
                if c == 'M':
                    answer[i] = 'M'
                else:
                    answer[i] = 'O'
                    flip = not flip

        print("YES")
        for i in answer:
            print(i, end = "")

        print()

        t -= 1

if __name__ == "__main__":
    main()
