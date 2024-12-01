h = input("Hight: ")
while not h.isdigit() or int(h) < 1 or int(h) > 8:
    h = input("Hight: ")
h = int(h)
for i in range(h):
    print(" " * (h - i - 1) + "#" * (i + 1))
