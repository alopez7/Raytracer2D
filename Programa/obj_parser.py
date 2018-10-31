"""Script encargado de parsear de un OBJ a una lista de segmentos."""

import sys
import math


class Vertex:
    """Representa un vértice."""

    def __init__(self, x, y, z=0):
        """Inicializa un vértice."""
        self.x = x
        self.y = y
        self.z = z

    def max_s(self):
        """Entrega la componente más alta."""
        return max(self.x, self.y)

    def min(self, other):
        """Entrega un vértice mínimo entre dos vértices."""
        return Vertex(min(self.x, other.x), min(self.y, other.y))

    def max(self, other):
        """Entrega un vértice máximo entre dos vértices."""
        return Vertex(max(self.x, other.x), max(self.y, other.y))

    def __sub__(self, other):
        """Entrega la resta vectorial de dos vertices."""
        return Vertex(self.x - other.x, self.y - other.y)

    def __add__(self, other):
        """Entrega la suma vectorial de dos vertices."""
        return Vertex(self.x + other.x, self.y + other.y)

    def __truediv__(self, other):
        """Divide un vertice por un numero."""
        return Vertex(self.x / other.x, self.y / other.y)

    def __mul__(self, other):
        """Multiplica dos vertices componente a componente."""
        return Vertex(self.x * other.x, self.y * other.y)


class Segment:
    """Representa un segmento de recta."""

    def __init__(self, par):
        """Inicializa un Segmento."""
        self.v1 = par[0]
        self.v2 = par[1]

    def length(self):
        """Calcula el largo de un segmento."""
        # El cuadrado de la hipotenusa
        hip_squared = (self.v1.x - self.v2.x)**2 + (self.v1.y - self.v2.y)**2
        return math.sqrt(hip_squared)

    def min(self):
        """Entrega un vértice mínimo."""
        return self.v1.min(self.v2)

    def max(self):
        """Entrega un vértice máximo."""
        return self.v1.max(self.v2)

    def __sub__(self, vertex):
        """Desplaza este segmento segun un vértice."""
        v1 = self.v1 - vertex
        v2 = self.v2 - vertex
        return Segment((v1, v2))

    def __add__(self, vertex):
        """Desplaza este segmento segun un vértice."""
        v1 = self.v1 + vertex
        v2 = self.v2 + vertex
        return Segment((v1, v2))

    def __truediv__(self, vertex):
        """Escala este segmento segun un vertice."""
        v1 = self.v1 / vertex
        v2 = self.v2 / vertex
        return Segment((v1, v2))

    def __mul__(self, vertex):
        """Escala este segmento segun un vertice."""
        v1 = self.v1 * vertex
        v2 = self.v2 * vertex
        return Segment((v1, v2))

    def __str__(self):
        """Representación como string."""
        return "{} {} {} {}".format(self.v1.x, self.v1.y, self.v2.x, self.v2.y)

    def __repr__(self):
        """Representación como string."""
        return "{} {} {} {}".format(self.v1.x, self.v1.y, self.v2.x, self.v2.y)


class Triangle:
    """Representa un triángulo."""

    def __init__(self, v1, v2, v3):
        """Inicializa un triangulo."""
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3

    def is_horizontal(self):
        """Revisa si un triangulo es horizontal."""
        if self.v1.z == self.v2.z == self.v3.z:
            return True
        return False

    def is_earthbound(self):
        """Ve si un triangulo está pegado al suelo, y entrega esos vertices."""
        if self.v1.z == self.v2.z == 0:
            return (self.v1, self.v2)
        elif self.v2.z == self.v3.z == 0:
            return (self.v2, self.v3)
        elif self.v3.z == self.v1.z == 0:
            return (self.v3, self.v1)
        return ()


def main():
    """Función principal del programa."""
    if len(sys.argv) != 4:
        print("Modo de uso: {} obj out thick\nDonde\n".format(sys.argv[0]))
        print("obj: Es el archivo .obj a parsear\n")
        print("out: Es el archivo .txt donde se escribe la escena\n")
        print("thick: es el grosor en metros de las paredes\n")
        return

    # Cargamos los input del programa
    [script, filename, outfile, thickness] = sys.argv
    # Grosor de las paredes
    thickness = float(thickness) * 100
    # Saltar las caras que no sean paredes
    skip = False
    # Lista de vertices
    vertices = []
    # Lista de segmentos
    segments = []

    # Leemos el archivo completo
    with open(filename) as obj:
        lines = obj.readlines()
        for line in lines:
            line = line.split(' ')
            # Comentarios
            if line[0] == '#':
                continue
            # Materiales
            elif line[0] == 'usemtl':
                if 'wall' not in line[1]:
                    skip = True
                else:
                    skip = False
            # Vertices
            elif line[0] == 'v':
                x = float(line[1])
                y = float(line[3])
                z = float(line[2])

                vertices.append(Vertex(x, y, z))
            # Triangulos
            elif line[0] == 'f':
                if skip:
                    continue

                # Indice de vertice, ignoramos la normal
                iv1 = int(line[1].split('//')[0]) - 1
                iv2 = int(line[2].split('//')[0]) - 1
                iv3 = int(line[3].split('//')[0]) - 1

                # Crear el triangulo con los vertices especificados
                tri = Triangle(vertices[iv1], vertices[iv2], vertices[iv3])

                # Solo nos interesa si no es horizontal
                if not tri.is_horizontal():
                    # Y para eliminar repetidos, si tiene dos puntos en tierra
                    points = tri.is_earthbound()

                    # De ser así, creamos un segmento con esos dos puntos
                    if points:
                        segment = Segment(points)
                        if segment.length() > thickness:
                            segments.append(segment)
            else:
                pass

    # Mínimos y máximos del plano
    min_v = Vertex(math.inf, math.inf)
    max_v = Vertex(-math.inf, -math.inf)

    for segment in segments:
        min_v = min_v.min(segment.min())
        max_v = max_v.max(segment.max())

    # Ancho y alto
    x_span = max_v.x - min_v.x
    y_span = max_v.y - min_v.y

    # Ajustamos tambien la posicion del máximo
    max_v -= min_v

    # Escala todos los vertices al intervalo 0-1
    segments = list(map(lambda x: (x - min_v) / max_v, segments))

    if x_span > y_span:
        x_scale = 600
        y_scale = x_scale * (y_span / x_span)
        scale = Vertex(x_scale, y_scale)
    else:
        y_scale = 600
        x_scale = y_scale * (x_span / y_span)
        scale = Vertex(x_scale, y_scale)

    # Escala todos los vertices al intervalo 20-620
    padding = Vertex(20, 20)
    segments = list(map(lambda x: (x * scale) + padding, segments))

    true_segments = []

    average = Vertex(2, 2)

    for i in range(len(segments)):
        if i % 2 == 0:
            seg1 = segments[i]
            seg2 = segments[i+1]

            v1 = (seg1.v1 + seg2.v2) / average
            v2 = (seg1.v2 + seg2.v1) / average

            true_segments.append(Segment((v1, v2)))

    segments = true_segments

    # Imprime en el archivo
    with open(outfile, "w") as output:
        # Las dimensiones de la imagen
        output.write("{} {}\n".format(int(y_scale + 40), int(x_scale + 40)))
        # La cantidad de luces
        output.write("0\n")
        # Las luces TODO

        # La cantidad de segmentos
        output.write(str(len(segments)) + "\n")
        # Y cada segmento
        for segment in segments:
            output.write(str(segment) + "\n")


if __name__ == "__main__":
    main()
