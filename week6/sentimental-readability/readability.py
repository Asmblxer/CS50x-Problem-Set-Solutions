def main():
    letter = 0
    word = 1
    sentence = 0
    
    text = input("Text: ")
    
    for char in text:
        if char.isalpha():
            letter += 1
        elif char == ' ':
            word += 1
        elif char in ['!', '.', '?']:
            sentence += 1
    
    L = (letter / word) * 100
    S = (sentence / word) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    
    if index <= 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

if __name__ == "__main__":
    main()
