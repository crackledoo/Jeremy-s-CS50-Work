# import cs50

def main():
    text = receive_text()
    grade = processing(text)
    if grade > 15:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")

def receive_text():
    text = cs50.get_string("Text: ")
    return text

def processing(text):
    temp_word = 0
    word_count = 0
    sentence_count = 0
    letter_count = 0
    for i in range(len(text)):
        if text[i].isalpha():
            temp_word += 1
            letter_count += 1
        elif text[i] == ' ':
            if temp_word > 0:
                word_count += 1
                temp_word = 0
        elif text[i] == '.' or text[i] == '!' or text[i] == '?':
            if temp_word > 0:
                word_count += 1
                sentence_count += 1
                temp_word = 0
    #print(f"Letter count is {letter_count}")
    #print(f"Word count is {word_count}")
    #print(f"Sentence count is {sentence_count}")
    big_L = letter_count * (100 / word_count)
    big_S = sentence_count * (100 / word_count)
    grade = (0.0588 * big_L) - (0.296 * big_S) - 15.8
    #print(f"Grade is {grade}")
    return round(grade)



main()