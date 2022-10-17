# TODO
import re
import math


while True:
    try:
        text = input("Text: ")
        break
    except:
        print("INVALID")
letters = re.findall("[a-zA-Z]", text)
# print(letters)
# print(len(letters))
words = re.split("\s", text)
# print(words)
# print(len(words))
sentences = re.findall("[.?!]", text)
# print(sentences)
# print(len(sentences))

letter_count = int(len(letters))
word_count = int(len(words))
sentence_count = int(len(sentences))
L = letter_count/word_count*100
#print(L)
S = sentence_count/word_count*100
#print(S)
index = round(.0588 * L - 0.296 * S - 15.8)
# print(index)

if index >= 16:
    print("Grade 16+")
elif index < 16 and index > 1:
    print(f"Grade {int(index)}")
elif index :
    print("Before Grade 1")