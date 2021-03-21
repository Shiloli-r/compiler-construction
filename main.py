number = int(input("Number of students: "))
i = 0
total_marks = 0
names = [None for x in range(number)]
marks = [None for x in range(number)]
while i < number:
    print("i -> ", i)
    name = input("Name of Student: ")
    names[i] = name
    mark = float(input("Student Mark: "))
    marks[i] = mark
    total_marks += mark
    i += 1
i = 0
while i < len(names):
    print(names[i], " : ", marks[i])
    i += 1
print("Average = ", total_marks / number)