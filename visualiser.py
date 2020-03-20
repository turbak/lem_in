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


class Path:
	def __init__(self):
		self.room_name = None
		self.ant_num = None


class Link:
	def __init__(self):
		self.start = None
		self.end = None


class Room:
	def __init__(self, name, x, y, ispath):
		self.name = name
		self.x = x
		self.y = y
		self.ispath = ispath


def draw(canvas, link):
	canvas.create_line(link.start.x, link.start.y, link.end.x, link.end.y, width=2)
	canvas.create_oval(link.start.x - NODE_SIZE, link.start.y - NODE_SIZE,
					link.start.x + NODE_SIZE, link.start.y + NODE_SIZE, outline="black",
					fill=("gray" if not link.start.ispath else "yellow"))
	canvas.create_oval(link.end.x - NODE_SIZE, link.end.y - NODE_SIZE,
					link.end.x + NODE_SIZE, link.end.y + NODE_SIZE, outline="black",
					fill=("gray" if not link.end.ispath else "yellow"))
	canvas.create_text(link.start.x, link.start.y, text=link.start.name, font="Times 10 bold", fill='black')
	canvas.create_text(link.end.x, link.end.y, text=link.end.name, font="Times 10 bold", fill='black')


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
	paths_by_turn = re.findall('L.*?\n', data)
	# print(rooms)
	# print(links)
	print(paths)
	paths_list = []
	for path in paths:
		buf = path.split('-')
		paths_list.append(buf[1])
	rooms_list = []
	links_list = []
	for room in rooms:
		buf = room.split(' ')
		rooms_list.append(Room(buf[0], int(buf[1]) * ZOOM, int(buf[2]) * ZOOM,
						buf[0] in paths_list or buf[0] == start or buf[0] == end))
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
	for path in paths:
		buf = path.replace('\n', '')
	for link in links_list:
		draw(canvas, link)
	window.mainloop()


if __name__ == '__main__':
	main()
