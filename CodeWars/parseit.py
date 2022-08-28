import re
from tkinter import W
class problem:
    def __init__(this, level):
        this.level = level
        this.description = "hey"
        this.language = "lang"
        this.source = ""


def loadfile():
    with open("codewarsProfile.txt", 'r') as f:
        return f.readlines()

def parseIt(data):
    state = "kyu"
    langCount = 0
    table = []
    current = problem("sentinel")
    for line in data:
        if re.match(r"\s{3}\d\skyu\s*$", line):
            table.append(current)
            state = "desc"
            level = re.sub(r"^\s*", "", line)
            level = re.sub(r"(\n|\r)*", "", level)
            current = problem(level)
        elif state == "desc":
            current.description = re.sub(r"^\s*", "", line)
            current.description = re.sub(r"(\n|\r)*", "", current.description)
            state = "lang"
            langCount = 0
        elif state == "lang":
            if langCount == 1:
                current.language = re.sub(r"^\s*", "", line)
                current.language = re.sub(r"(\n|\r)*", "", current.language)
            elif langCount == 2:
                state = "source"
            langCount += 1                
        elif state == "source":
            current.source += line

    table.append(current)
    return table

def makeFileName(program):
    cleaned = re.sub(r"[^A-Za-z0-9 ]", "", program.description)
    cleaned = re.sub(r" ", "_", cleaned)
    if program.language == "C++:":
        cleaned += ".cpp"
    elif program.language == "C:":
        cleaned += ".c"
    elif program.language == "Java:":
        cleaned += ".java"
    elif program.language == "JavaScript:":
        cleaned += ".js"
    elif program.language == "Python:":
        cleaned += ".py"
    else:
        assert(True)
    return cleaned        

def dropSourceFooter(program):
    lineCount = 0
    for i in range(len(program.source)):
        if (program.source[-1 * i]) == '\n':
            lineCount += 1
        if lineCount == 4:
            return program.source[:-1 * i]
    print("What")
    return ""            

def dumpFiles(table):
    for problem in table:
        filename = makeFileName(problem)
        with open(filename, 'w') as output:
            output.writelines(dropSourceFooter(problem))

def dumpTable(table):
    lines = []
    for problem in table:
        s = "|%s|[Description]()|[Source](CodeWars/%s)||[link]()|%s|`%s`|\n" %\
            (problem.description, makeFileName(problem), problem.level, problem.language[:-1])
        lines.append(s)
    with open("codewarstable.md", 'w') as output:
        output.writelines(lines)

def main():
    table = parseIt(loadfile())
    dumpFiles(table)
    dumpTable(table)
    # print(dropSourceFooter(table[20]))
    # for problem in table:
    #     print(problem.level, problem.description, problem.language, makeFileName(problem))
    # print("foo")


if __name__ == "__main__":
    main()