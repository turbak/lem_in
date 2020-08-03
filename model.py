from dataclasses import dataclass
import pytweening


@dataclass
class Path:
    room_name: str
    ant_num: int


class Room:
    def __init__(self, name, x, y, nodesize):
        self.name = name
        self.x = x
        self.y = y
        self.center = (self.x + nodesize / 5, self.y + nodesize / 5)


@dataclass
class Link:
    start: Room
    end: Room


@dataclass
class Move:
    start: Room
    end: Room
    ant_name: str


class Ant:
    def __init__(self, x1, y1, x2, y2):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.line = pytweening.getLine(x1, y1, x2, y2)
        self.anim_turn = 0
