from dataclasses import dataclass


@dataclass
class Path:
    room_name: str
    ant_num: int


@dataclass
class Room:
    name: str
    x: int
    y: int


@dataclass
class Link:
    start: Room
    end: Room


@dataclass
class Move:
    start: Room
    end: Room
    ant_name: str
