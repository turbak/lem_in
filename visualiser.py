#!/usr/bin/python

import re
import sys
import pygame

from model import Room, Link, Move, Ant

ZOOM = 50
NODE_SIZE = 20
SPEED = 5
WINDOWWIDTH = 1500
WINDOWHEIGHT = 1000
FPS = 30
BGCOLOR = [245, 235, 179]
BLACK = [0, 0, 0]
WHITE = [255, 255, 255]
RED = [255, 0, 0]
ANIM_SPEED = 5


class Game:
    def __init__(self, links, moves_list):
        pygame.init()
        pygame.key.set_repeat(150, 5)
        self.clock = pygame.time.Clock()
        self.screen = pygame.display.set_mode([WINDOWWIDTH, WINDOWHEIGHT], 0, 32)
        self.fps = FPS
        self.links = links
        self.moves_list = moves_list
        self.ants = []
        self.current_move = 0
        self.made_move = None
        pygame.display.set_caption("lem-in visualizer\n")

    def draw(self):
        self.screen.fill(BGCOLOR)
        for link in self.links:
            pygame.draw.line(self.screen, BLACK, link.start.center, link.end.center, 3)
            pygame.draw.circle(self.screen, WHITE, [link.start.x, link.start.y], NODE_SIZE)
            pygame.draw.circle(self.screen, WHITE, [link.end.x, link.end.y], NODE_SIZE)
            self.create_ants()
            self.draw_ants()
        pygame.display.flip()

    def create_ants(self):
        current_move = self.moves_list[self.current_move]
        if current_move != self.made_move:
            for key in current_move:
                move = current_move[key]
                self.ants.append(Ant(move.start.x, move.start.y, move.end.x, move.end.y))
            self.made_move = current_move

    def events(self):
        for self.event in pygame.event.get():
            if self.event.type == 2:
                print(self.event.key)
                if self.event.key == 27:
                    quit(1)
                elif self.event.key == 276 and self.current_move - 1 in range(0, len(self.moves_list) - 1):
                    print('move left')
                    self.current_move -= 1
                    self.made_move = None
                elif self.event.key == 275 and self.current_move + 1 in range(0, len(self.moves_list) - 1):
                    print('move right')
                    self.current_move += 1
                    self.made_move = None

    def run(self):
        while 1:
            self.clock.tick(self.fps)
            self.events()
            self.draw()
            self.move_ants()

    def move_ants(self):
        for ant in self.ants:
            if ant.anim_turn + ANIM_SPEED not in range(0, len(ant.line)):
                self.ants.remove(ant)
            else:
                ant.anim_turn += ANIM_SPEED

    def draw_ants(self):
        for ant in self.ants:
            current_pos = ant.line[ant.anim_turn]
            pygame.draw.circle(self.screen, RED, current_pos, 4)


def main():
    if len(sys.argv) == 2:
        map_name = sys.argv[1]
    else:
        exit(1)
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
        rooms_dict[buf[0]] = (Room(buf[0], int(buf[1]) * ZOOM, int(buf[2]) * ZOOM, NODE_SIZE))
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

    game = Game(links_list, moves_list)
    game.run()


if __name__ == '__main__':
    main()
