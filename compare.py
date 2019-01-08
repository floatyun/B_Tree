import sys

std = open("output.txt", "r")
my = open("out.txt", "r")
inp = open("input.txt", "r")
li = 0
for s in std:
    li = li+1
    try:
        m = my.readline()
        i = inp.readline()
    except IOError:
        print("你的只有" + str(li - 1) + "行")
        print("输入文件中的" + i + "未处理")
        break
    if m != s:
        print(li)
        print("输入命令"+i)
        print("标准输出："+s)
        print("你的输出："+m)
        break