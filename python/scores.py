# Lecture 06 - "Python"
# Program 10


scores = []

for i in range(3):
    score = int(input("score: "))
    scores.append(score)


avg = sum(scores) / len(scores)
print(avg)
