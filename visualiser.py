#!/usr/bin/python

import re
import sys
import tkinter
from tkinter.constants import *

from model import Room, Link, Move

ZOOM = 50
NODE_SIZE = 25

class App(tkinter.Tk):
	def __init__(self, links, paths):
		super().__init__()
		self.geometry('1200x800')
		self.title('lem-in')
		self.links = links
		self.paths = paths
		self.current_move = 0
		self.canvas = tkinter.Canvas(self, background='white')
		canvas = self.canvas
		canvas.bind_all('<Left>', self.moveLeft)
		canvas.bind_all('<Right>', self.moveRight)
		for link in links:
			self.draw(canvas, link)
		canvas.pack(fill=BOTH, expand=YES)

	def draw(self, canvas, link):
		canvas.create_line(link.start.x, link.start.y, link.end.x, link.end.y, width=2)
		canvas.create_oval(link.start.x - NODE_SIZE, link.start.y - NODE_SIZE,
						   link.start.x + NODE_SIZE, link.start.y + NODE_SIZE, outline="black", fill="gray")
		canvas.create_oval(link.end.x - NODE_SIZE, link.end.y - NODE_SIZE,
						   link.end.x + NODE_SIZE, link.end.y + NODE_SIZE, outline="black", fill="gray")
		canvas.create_text(link.start.x, link.start.y, text=link.start.name, font="Times 10 bold", fill='black')
		canvas.create_text(link.end.x, link.end.y, text=link.end.name, font="Times 10 bold", fill='black')

	def moveLeft(self, event):
		print('LeftKey was pressed')
		current_move = self.paths[self.current_move]
		list_rect = []
		for key in current_move:
			ant = current_move[key]
			rect = self.canvas.create_rectangle(ant.start.x, ant.start.y, ant.start.x + 20, ant.start.y + 20)
			list_rect.append(rect)
		self.animate(list_rect)
		self.current_move += 1

	def animate(self, list_rect):
		for ant in list_rect:
			self.canvas.move(ant)
		# unpack array to variables
		#пустить эту функицию в цикле для всех муравьев в ходу


	def moveRight(self, event):
		print('RightKey was pressed')


def main():
	if len(sys.argv) == 2:
		fname = sys.argv[1]
	else:
		exit(1)
	file = open(fname, 'r')
	map_name = sys.argv[1]
	map_file = open(map_name, 'r')

	# ввод данных
	map_data = map_file.read()
	ants_count = re.findall('^\w+', map_data)
	links = re.findall('\w+-\w+', map_data)
	rooms = re.findall('\w+ \d+ \d+', map_data)
	paths = re.findall('(L.*?)\n', map_data)
	print(paths)

	# парсинг данных на узлы, ребра и перемещения за каждый шаг
	rooms_dict = {}
	links_list = []
	for room in rooms:
		buf = room.split(' ')
		rooms_dict[buf[0]] = (Room(buf[0], int(buf[1]) * ZOOM, int(buf[2]) * ZOOM))
		print(buf[0], buf[1], buf[2])
	for link in links:
		buf = link.split('-')
		if not buf[0].startswith('L'):
			line = Link(None, None)
			for room in rooms_dict:
				room = rooms_dict[room]
				if room.name == buf[0]:
					line.start = room
				elif room.name == buf[1]:
					line.end = room
			links_list.append(line)

	ants_cords_dict = {}
	start_room = re.findall('##start\n(\w+)', map_data)[0].split('\n')[0]
	for i in range(1, int(ants_count[0]) + 1):
		ants_cords_dict[i] = [start_room]

	moves_list = []
	moved_ants = set()
	for path in paths:
		move_per_ant = ' ' + path
		move_per_ant = move_per_ant.split(' L')
		moves = {}
		for ant_move in move_per_ant:
			if ant_move != '':
				ant_move = ant_move.split('-')
				if not ant_move[0] in moved_ants:
					moved_ants.add(ant_move[0])
					moves[ant_move[0]] = Move(rooms_dict[start_room], rooms_dict[ant_move[1]], ant_move[0])
				else:
					previous_ant_move = moves_list[-1][ant_move[0]]
					moves[ant_move[0]] = Move(previous_ant_move.end, rooms_dict[ant_move[1]], ant_move[0])
		moves_list.append(moves)

	app = App(links_list, moves_list)
	app.mainloop()


if __name__ == '__main__':
	main()
