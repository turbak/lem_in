#!/usr/bin/python

import tkinter
from tkinter.constants import *

import sys
import re
from random import randint


def examaple():
    tk = tkinter.Tk()
    frame = tkinter.Frame(tk, relief=RIDGE, borderwidth=2)
    frame.pack(fill=BOTH, expand=1)
    label = tkinter.Label(frame, text="Hello, World")
    label.pack(fill=X, expand=1)
    button = tkinter.Button(frame, text="Exit", command=tk.destroy)
    button.pack(side=BOTTOM)
    tk.mainloop()


def main():
    if len(sys.argv) == 2:
        fname = sys.argv[1]
    else:
        exit(1)
    window = tkinter.Tk()
    window.title('lem-in')
    canvas = tkinter.Canvas(window, background='white')
    canvas.pack(fill=BOTH, expand=YES)
    canvas.create_line(100, 180, 100, 60, fill='green',
                       width=5, arrow=LAST, dash=(10, 2),
                       activefill='lightgreen',
                       arrowshape="10 20 10")
    file = open(fname, 'r')
    data = file.read()
    start = re.findall('##start\n\w+', data)[0].split('\n')[1]
    links = re.findall('\w+-\w+\n', data)
    rooms = re.findall('\w+ \d+ \d+\n', data)
    end = re.findall('##end\n\w', data)[0].split('\n')[1]
    paths = re.findall('L\d+-\w+', data)
    #window.mainloop()

if __name__ == '__main__':
    main()
