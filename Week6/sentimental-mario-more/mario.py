while(True):
    height = input("Height: ")
    try:
        height = int(height)
        if height > 0 and height < 9:
            break
        else:
            print("That number is invalid")
    except:
        print("Thats not an int")

for i in range(1, height + 1):
    print(" " * (height - i), end = "")
    print("#" * i, end = "")
    print("  ", end = "")
    print("#"* i)