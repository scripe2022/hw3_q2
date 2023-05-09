#!/usr/bin/python3
import random
import subprocess

n = 100
m = 140
num = 10
p = 1
graph = subprocess.check_output(['./graph_gen', str(n), str(m), str(num)]).decode()

dot_file = "graph.dot"
input_file = "data.in"

def graphviz_dump():
    lines = graph.split('\n')
    output = "graph {\n   "
    data = str(n) + " " + str(m) + "\n"
    for i in range(n):
        output += " " + str(i)
        if (i == 0 or i == n-1): output += "[color=\"blue\"]"
    output += ";\n"
    for line in lines:
        if (line == ""): continue
        u, v, w = line.split(' ')
        toll = random.randint(0, p)
        toll_str = ""
        data += line
        if (toll == 0):
            toll_str = "color=\"red\""
            data += " 1\n"
        else:
            data += " 0\n"
        output += "    " + str(u) + " -- " + str(v) + " [label=\"" + str(w) + "\"" + toll_str + "];\n"
    output += "}"
    with open(dot_file, 'w') as f:
        print(output, file=f)
    with open(input_file, 'w') as f:
        print(data, file=f)

graphviz_dump()