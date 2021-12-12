import cs50

def main():
    height = get_height()
    print_pyramid(height)

def get_height():
    n = 0
    while(True):
        n = input("Height: ")
        if n.isnumeric():
            if 0 < int(n) < 9:
                break
    return int(n)

def print_pyramid(height):
    for count in range(height):
        space = height - (count + 1)
        brick = height - space
        for i in range(space):
            print(" ", end="")
        for i in range(brick):
            print("#", end="")
        print("  ", end="")
        for i in range(brick):
            print("#", end="")
        print()




main()