import math as mt
import random as rd

class Light:

    instances = []

    def __init__(self, posx, posy, r, g, b, intensity):
        self.posx = posx
        self.posy = posy
        self.r = r
        self.g = g
        self.b = b
        self.intensity = intensity
        Light.instances.append(self)

    def __repr__(self):
        return str(self.posx) + " " + str(self.posy) + " " + str(self.r) + " " + str(self.g) + " " + str(self.b) + " " + str(self.intensity)


class Line:

    instances = []

    def __init__(self, posx1, posy1, posx2, posy2):
        self.posx1 = posx1
        self.posy1 = posy1
        self.posx2 = posx2
        self.posy2 = posy2
        Line.instances.append(self)


    def __repr__(self):
        return str(self.posx1) + " " + str(self.posy1) + " " + str(self.posx2) + " " + str(self.posy2)



def colition(x, y, r, poligonos):
    for i in poligonos:
        if mt.sqrt((y-i[1])**2+(x-i[0])**2) < r + i[2]:
            return True
    return False


height = int(input("height: "))
width = int(input("width: "))


poligonos = []
while True:
    max_radius = rd.uniform(10, 60)
    centrox = rd.uniform(max_radius, width-max_radius)
    centroy = rd.uniform(max_radius, height-max_radius)
    tries = 0
    while colition(centrox, centroy, max_radius, poligonos):
        max_radius = rd.uniform(10, 60)
        centrox = rd.uniform(max_radius, width-max_radius)
        centroy = rd.uniform(max_radius, height-max_radius)
        if tries > 500:
            break
        tries += 1
    if tries > 500:
        break
    poligonos.append((centrox, centroy, max_radius))
    lados = rd.randint(3, 10)
    init_angle = rd.uniform(0, 360)*mt.pi/180
    init_radius = rd.uniform(max_radius*1/3, max_radius)
    angle = init_angle
    radius = init_radius
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
        radius = rd.uniform(max_radius*1/3, max_radius)
    posx = mt.cos(init_angle) * init_radius + centrox
    posy = mt.sin(init_angle) * init_radius + centroy
    Line(lastx, lasty, posx, posy)


for i in range(int(len(poligonos)*0.4)):
    pol = rd.choice(poligonos)
    angle = rd.uniform(0, 2*mt.pi)
    x = mt.cos(angle) * pol[2] + pol[0]
    y = mt.sin(angle) * pol[2] + pol[1]
    Light(x, y, rd.uniform(0, 1), rd.uniform(0, 1), rd.uniform(0, 1), rd.uniform(30, 50))


filename = input("filename (sin .txt): ")
with open(filename+".txt", "w") as file:
    file.write(str(height) + " " + str(width) + "\n")
    file.write(str(len(Light.instances)) + "\n")

    for i in Light.instances:
        file.write(str(i) + "\n")

    file.write(str(len(Line.instances)) + "\n")
    for i in Line.instances:
        file.write(str(i) + "\n")
