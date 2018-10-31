"""Holi."""
import math as mt
import random as rd


class Light:
    """Holi."""

    instances = []

    def __init__(self, posx, posy, r, g, b, intensity):
        """Holi."""
        self.posx = posx
        self.posy = posy
        self.r = r
        self.g = g
        self.b = b
        self.intensity = intensity
        Light.instances.append(self)

    def __repr__(self):
        """Holi."""
        return str(self.posx) + " " + str(self.posy) + " " + str(self.r) + " " + str(self.g) + " " + str(self.b) + " " + str(self.intensity)


class Line:
    """Holi."""

    instances = []

    def __init__(self, posx1, posy1, posx2, posy2):
        """Holi."""
        self.posx1 = posx1
        self.posy1 = posy1
        self.posx2 = posx2
        self.posy2 = posy2
        Line.instances.append(self)

    def __repr__(self):
        """Holi."""
        return str(self.posx1) + " " + str(self.posy1) + " " + str(self.posx2) + " " + str(self.posy2)


def colition(x, y, r, poligonos):
    """Holi."""
    for i in poligonos:
        if mt.sqrt((y-i[1])**2+(x-i[0])**2) < r + i[2]:
            return True
    return False


size = int(input("size: "))
cantidad = int(input("cantidad: "))
padding = size/(2*cantidad)
width = size
height = size
radius = int(input("radio: "))
lados = int(input("lados: "))
for row in range(cantidad):
    centrox = padding + width/cantidad * row
    for col in range(cantidad):
        centroy = padding + height/cantidad * col
        angle = 0
        angle_dif = (360/lados)*mt.pi/180
        lastx = None
        lasty = None
        for i in range(lados):
            posx = mt.cos(angle) * radius + centrox
            posy = mt.sin(angle) * radius + centroy
            angle += angle_dif
            if lastx is not None:
                Line(lastx, lasty, posx, posy)
            lastx = posx
            lasty = posy
        posx = mt.cos(0) * radius + centrox
        posy = mt.sin(0) * radius + centroy
        Line(lastx, lasty, posx, posy)


Light(size/2, size/2, 1, 1, 1, 100)


filename = "pilars.txt"
with open(filename, "w") as file:
    file.write(str(height) + " " + str(width) + "\n")
    file.write(str(len(Light.instances)) + "\n")

    for i in Light.instances:
        file.write(str(i) + "\n")

    file.write(str(len(Line.instances)) + "\n")
    for i in Line.instances:
        file.write(str(i) + "\n")
