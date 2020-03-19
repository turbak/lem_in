#!/usr/bin/python

import tkinter
from tkinter.constants import *

import sys
import re
from random import randint

ZOOM = 50
NODE_SIZE = 25


def examaple():
	tk = tkinter.Tk()
	frame = tkinter.Frame(tk, relief=RIDGE, borderwidth=2)
	frame.pack(fill=BOTH, expand=1)
	label = tkinter.Label(frame, text="Hello, World")
	label.pack(fill=X, expand=1)
	button = tkinter.Button(frame, text="Exit", command=tk.destroy)
	button.pack(side=BOTTOM)
	tk.mainloop()


class Link:
	def __init__(self):
		self.start = None
		self.end = None


class Room:
	def __init__(self, name, x, y):
		self.name = name
		self.x = x
		self.y = y


def draw(canvas, x1, y1, x2, y2, name1, name2):
	canvas.create_line(x1, y1, x2, y2, width=2)
	canvas.create_oval(x1 - NODE_SIZE, y1 - NODE_SIZE,
					x1 + NODE_SIZE, y1 + NODE_SIZE, outline="black", fill="gray")
	canvas.create_oval(x2 - NODE_SIZE, y2 - NODE_SIZE,
					x2 + NODE_SIZE, y2 + NODE_SIZE, outline="black", fill="gray")
	canvas.create_text(x1, y1, text=name1, font="Times 10 bold", fill='black')
	canvas.create_text(x2, y2, text=name2, font="Times 10 bold", fill='black')


def main():
	if len(sys.argv) == 2:
		fname = sys.argv[1]
	else:
		exit(1)
	window = tkinter.Tk()
	window.title('lem-in')
	canvas = tkinter.Canvas(window, background='white')
	canvas.pack(fill=BOTH, expand=YES)
	file = open(fname, 'r')
	data = file.read()
	start = re.findall('##start\n\w+', data)[0].split('\n')[1]
	links = re.findall('\w+-\w+', data)
	rooms = re.findall('\w+ \d+ \d+', data)
	end = re.findall('##end\n\w', data)[0].split('\n')[1]
	paths = re.findall('L\d+-\w+', data)
	# print(rooms)
	print(links)
	# print(paths)
	rooms_list = []
	links_list = []
	for room in rooms:
		buf = room.split(' ')
		rooms_list.append(Room(buf[0], int(buf[1]) * ZOOM, int(buf[2]) * ZOOM))
	for room in rooms_list:
		print(room.name + " " + str(room.x) + " " + str(room.y))
	for link in links:
		buf = link.split('-')
		if not buf[0].startswith('L'):
			line = Link()
			for room in rooms_list:
				if room.name == buf[0]:
					line.start = room
				elif room.name == buf[1]:
					line.end = room
			links_list.append(line)
	for link in links_list:
		draw(canvas, link.start.x, link.start.y, link.end.x, link.end.y, link.start.name, link.end.name)
	print(links_list)
	window.mainloop()


if __name__ == '__main__':
	main()
