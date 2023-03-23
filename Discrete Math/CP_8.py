# n - число вершин в первой доле
# k - число вершин во второй доле
# edges[i] - список вершин из второй доли, соединенных с вершиной i первой доли

# mt содержит информацию о текущем паросочетании
# mt[i] номер вершины первой доли, связанной ребром с вершиной i второй доли (или -1, если никакого ребра нет)
# used — массив посещений вершин в обходе в глубину (чтобы обход в глубину не заходил в одну вершину дважды)

# Функция try_kuhn — обход в глубину.
# Она возвращает true, если удалось найти увеличивающую цепь из вершины v
# При этом считается, что эта функция уже произвела чередование паросочетания вдоль найденной цепи.

##############################################################################
# Выражаю огромную благодарность Жилину Михаилу за помощь с написанием проги #
##############################################################################

from tkinter import *
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import networkx as nx
matplotlib.use('TkAgg')


def copy(m: list):
    m1 = []
    for i in range(len(m)):
        m1.append([])
        for j in range(len(m[i])):
            if m[i][j] == 0:
                m1[i].append([0])
            else:
                m1[i].append([i, j])
    return m1


def algo(matr_f: list):
    matr = copy(matr_f)
    matr2 = ([[[0] for j in range(n)] for i in range(n)])
    matr1 = matr
    global a
    a = []
    qwe = 3
    for ans in range(n - 2):
        for i in range(n):
            for j in range(n):
                z = 0
                for q in range(n):
                    if matr[i][q] == [0] or matr1[q][j] == [0]:
                        continue
                    else:
                        if len(matr1[q][j]) > 1 and type(matr1[q][j][0]) != int:
                            for z in range(len(matr1[q][j])):
                                if z > 0:
                                    matr2[i][j].append([0])
                                matr2[i][j][z] = matr[i][q]
                                t = matr2[i][j][z][len(matr2[i][j][z]) - 1]
                                matr2[i][j][z].pop(len(matr2[i][j][z]) - 1)
                                matr2[i][j][z] = matr2[i][j][z] + matr1[q][j][z]
                                matr[i][q].append(t)
                                z = z + 1
                        else:
                            if z > 0:
                                matr2[i][j].append([0])
                            matr2[i][j][z] = matr[i][q]
                            t = matr2[i][j][z][len(matr2[i][j][z]) - 1]
                            matr2[i][j][z].pop(len(matr2[i][j][z]) - 1)
                            if type(matr1[q][j][0]) != int:
                                matr2[i][j][z] = matr2[i][j][z] + matr1[q][j][0]
                            else:
                                matr2[i][j][z] = matr2[i][j][z] + matr1[q][j]
                            matr[i][q].append(t)
                            z = z + 1
        matr1 = matr2
        matr2 = ([[[0] for j in range(n)] for i in range(n)])
        for i in range(n):
            for j in range(n):
                if matr1[i][j] != [0]:
                    if type(matr1[i][j][0]) != int:
                        z = 0
                        while z < len(matr1[i][j]):
                            if matr1[i][j][z][0] == matr1[i][j][z][len(matr1[i][j][z]) - 1]:
                                matr1[i][j].pop(z)
                            else:
                                z = z + 1
                    else:
                        if matr1[i][j][0] == matr1[i][j][len(matr1[i][j]) - 1]:
                            matr1[i][j][0] == [0]
                if matr1[i][j] == []:
                    matr1[i][j] = [0]
                else:
                    if type(matr1[i][j][0]) != int:
                        z = 0
                        while z < len(matr1[i][j]):
                            for x in range(1, n + 1):
                                if matr1[i][j][z].count(x) > 1:
                                    matr1[i][j].pop(z)
                                    z = z - 1
                                    break
                            z = z + 1
                    else:
                        for x in range(1, n + 1):
                            if matr1[i][j].count(x) > 1:
                                matr1[i][j] == [0]
                if matr1[i][j] == []:
                    matr1[i][j] = [0]

        put = 0
        for i in range(n):
            for j in range(n):
                if type(matr1[i][j][0]) != int:
                    put = put + len(matr1[i][j])
                else:
                    if matr1[i][j] != [0]:
                        put = put + 1

        a.append((qwe, []))
        for i in range(n):
            for j in range(n):
                if type(matr1[i][j][0]) != int:
                    for z in range(len(matr1[i][j])):
                        s = ''
                        for num in range(len(matr1[i][j][z])):
                            s = s+str(matr1[i][j][z][num])
                            if num != len(matr1[i][j][z]) - 1:
                                s = s + "-"
                        a[ans][1].append(s)
        qwe = qwe + 1


def clear():
    for i in range(len(checkBox_list)):
        for j in range(len(checkBox_list[i])):
            checkBox_list[i][j].destroy()
    for i in lbl:
        for j in i:
            j.destroy()
    for i in range(len(r_list)):
        for j in range(len(r_list[i])):
            r_list[i][j].destroy()


def clicked():
    try:
        clear()
    except BaseException:
        pass
    global n
    n = int(txt1.get())
    global checkBox_list, lbl
    checkBox_list = []
    lbl = []
    global r_list
    r_list = []
    for i in range(n):
        r_list.append([])
        for j in range(n):
            r_list[i].append(IntVar())
    for i in range(n):
        lbl.append([Label(window, text="v" + str(1 + i))])
        lbl[i][0].grid(column=3 + i, row=0)
        checkBox_list.append([])
        for j in range(n):
            lbl[i].append(Label(window, text="v" + str(1 + j)))
            lbl[i][j + 1].grid(column=2, row=1 + j)
            checkBox_list[i].append(Checkbutton(window, variable=r_list[i][j]))
            checkBox_list[i][j].grid(column=3 + i, row=j + 1)


def draw():
    matrix = []
    try:
        for i in range(len(r_list)):
            matrix.append([])
            for j in range(len(r_list[i])):
                matrix[i].append(int(r_list[i][j].get()))
        matrix = np.transpose(matrix).tolist()
    except BaseException:
        print("Невозможно считать матрицу")

    algo(matrix)
    colors_list = []
    size_list = []
    graph1 = nx.DiGraph()
    try:
        for i in range(n):
            graph1.add_node(f'v{i+1}')
            size_list.append(500)
        for i in range(n):
            for j in range(n):
                if matrix[i][j]:
                    graph1.add_edge(f'v{i+1}', f'v{j+1}')
    except BaseException:
        pass
    fig, axs = plt.subplots(1, 1, figsize=(10, 4))
    nx.draw_circular(graph1, ax=axs, with_labels=True, node_size=size_list)
    plt.show()

    for i in a:
        k = i[0]
        for j in i[1]:
            y = j.split('-')
            colors_list = []
            try:
                for i1 in range(n):
                    for j1 in range(n):
                        flag = False
                        for k1 in range(len(y)-1):
                            if y[k1] == str(i1) and y[k1+1] == str(j1):
                                flag = True
                        if flag:
                            colors_list.append('red')
                        elif not(flag) and matrix[i1][j1]:
                            colors_list.append('black')

            except BaseException:
                pass
            fig, axs = plt.subplots(1, 1, figsize=(10, 4))
            nx.draw_circular(graph1, ax=axs, with_labels=True, node_size=size_list, edge_color=colors_list)
            plt.show()


def main():
    global window, lbl1, txt1, matrix
    window = Tk()
    window.title("")
    window.geometry('1000x700')
    lbl1 = Label(window, text="Введите количество вершин первой доли")
    lbl1.grid(column=0, row=0)
    txt1 = Entry(window, width=10)
    txt1.grid(column=1, row=0)
    btn = Button(window, text="Ввести", command=clicked)
    btn.grid(column=0, row=5)
    btn_restart = Button(window, text="Ответ", command=draw)
    btn_restart.grid(column=0, row=6)
    window.mainloop()


if __name__ == '__main__':
    main()
