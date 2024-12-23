import re

def count_letters(text):
    return len([char for char in text if char.isalpha()])

def count_words(text):
    return len(text.split())

def count_sentences(text):
    return len(re.findall(r'[.!?]', text))

def calculate_grade(text):
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    grade = 0.0588 * L - 0.296 * S - 15.8
    return round(grade)

def main():
    # Solicita entrada do usuário
    text = input("Text: ")

    # Calcula o índice de Coleman-Liau
    grade = calculate_grade(text)

    # Exibe o resultado
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")

if __name__ == "__main__":
    main()
