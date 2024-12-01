c = input("Change: ")

while not c.replace('.', '').isnumeric() or float(c) < 0:
    c = input("Change: ")

c = float(c) * 100
ans = 0

while c > 0:
    if c >= 25:
        c -= 25
    elif c >= 10:
        c -= 10
    elif c >= 5:
        c -= 5
    else:
        c -= 1
    ans += 1

print(ans)