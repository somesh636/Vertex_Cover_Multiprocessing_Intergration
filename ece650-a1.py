#!/usr/bin/env python
from __future__ import print_function

if __name__ == '__main__':
    import re    # Import regular expression module
    import sys   # Import Sys Module


    # Class for Vertex
    class Vertex:
        def __init__(self, x, y, index = None):
            self.x = x
            self.y = y
            self.index = index

        try:
            def __eq__(self, vertex):
                return (self.x == vertex.x and self.y == vertex.y)
        except Exception:
            print("Error:")

        def __hash__(self):
            return hash((self.x, self.y))

    # Class for Edge
    class Edge:

        def __init__(self, start, end):
            self.start = start
            self.end = end

        def __eq__(self, edge):
            if not isinstance(edge, Edge):
                return False

            return ((self.start == edge.start or self.start == edge.end) and
                    (self.end == edge.start or self.end == edge.end))

        def __hash__(self):
            return hash((self.start, self.end))

        def does_intersect(self, edge):
            m1 = None
            m2 = None
            c1 = None
            c2 = None

            try:
                m1 = float(self.end.y - self.start.y) / (self.end.x - self.start.x)
                c1 = (self.end.y - m1 * self.end.x)
            except ZeroDivisionError:
                c1 = 0
                m1 = None

            try:
                m2 = float(edge.end.y - edge.start.y) / (edge.end.x - edge.start.x)
                c2 = (edge.end.y - m2 * edge.end.x)
            except ZeroDivisionError:
                c2 = 0
                m2 = None

            intersected = False
            y_int = None
            try:
                if m1 is not None and m2 is not None:
                    x_int = float(c2 - c1) / (m1 - m2)
                    y_int = m1 * x_int + c1
                    intersected = x_int <= max(self.start.x, self.end.x) and \
                                  x_int >= min(self.start.x, self.end.x) and \
                                  x_int <= max(edge.start.x, edge.end.x) and \
                                  x_int >= min(edge.start.x, edge.end.x)
                elif m1 is None and m2 is None:
                    return (False, None, None)
                else:
                    if m1 is None:
                        x_int = self.start.x
                        y_int = m2 * x_int + c2
                        intersected = y_int <= max(edge.end.y, edge.start.y) and \
                                      y_int >= min(edge.end.y, edge.start.y) and \
                                      y_int <= max(self.end.y, self.start.y) and \
                                      y_int >= min(self.end.y, self.start.y)
                    elif m2 is None:
                        x_int = edge.start.x
                        y_int = m1 * x_int + c1

                        intersected = y_int <= max(self.end.y, self.start.y) and \
                                      y_int >= min(self.end.y, self.start.y) and \
                                      y_int <= max(edge.end.y, edge.start.y) and \
                                      y_int >= min(edge.end.y, edge.start.y)
                    else:
                        sys.stderr.write("Error: Reached an Unexpected condition.\n")

            except ZeroDivisionError:
                return (False, None, None)

            return (intersected, x_int, y_int)

    #Class for Street
    class Street:

        def __init__(self, coordinates):
            self.vertices = []
            self.edges = []
            for  i in range(len(coordinates)):
                vertex = Vertex(int(coordinates[i][1:-1].split(',')[0]),
                                int(coordinates[i][1:-1].split(',')[1]))
                self.vertices.append(vertex)

                if i > 0:
                    edge = Edge(self.vertices[i-1], self.vertices[i])
                    self.edges.append(edge)

    street_dict = {}  # Dictionary for Streets
    vertices = {}     # Dictionary for Vertices
    edges = []        # List of all the Edges

    def add_edge(idx1, idx2):
        edge_to_create = (idx1, idx2)
        edge_exists = False
        for edge in edges:
            if set(edge_to_create) == set(edge):
                edge_exists = True
                break

        if not edge_exists:
            edges.append(edge_to_create)


    def add_vertex(vertex):
        for key, value in vertices.items():
            if vertex == value:
                return key
        index = len(vertices)
        vertices[index] = vertex
        return index

    while True:
        try:
            # Take the user input
            data = raw_input().lower().strip()
        except Exception:
            sys.exit(0)
        except KeyboardInterrupt:
            sys.exit(0)

        # Pattern for the User Input
        pattern = '^(?P<command>\w{1})((\s+(?P<street>".*"))(?P<coordinates>((\s+)?\(-?\d+,-?\d+\))*))?$'

        p = re.compile(pattern)

        has_error = False
        try:
            command = p.match(data).group('command')
            street_name = p.match(data).group('street')
            coordinates = p.match(data).group("coordinates")

            #print street_name
        except AttributeError:
            sys.stderr.write("Error: Incorrect input format.\n")
            has_error = True

        if not has_error:
            # Checking the command for adding and changing the street
            if command == 'a':

                if street_name and coordinates:
                    coords = []
                    coord_start_idx = 0
                    if street_name not in street_dict.keys():
                        for idx in range(len(coordinates)):
                            if coordinates[idx] is ')':
                                coords.append(coordinates[coord_start_idx:idx+1].strip())
                                coord_start_idx = idx + 1
                        street_dict[street_name] = Street(coords)
                    else:
                        sys.stderr.write("Error: street currently exists.\n")
                else:
                    sys.stderr.write("Error: Incorrect input format.\n")

            elif command =='c':
                if street_name in street_dict.keys():
                    coords = []
                    coord_start_idx = 0
                    for idx in range(len(coordinates)):
                        if coordinates[idx] is ')':
                            coords.append(coordinates[coord_start_idx:idx+1].strip())
                            coord_start_idx = idx + 1
                    street_dict[street_name] = Street(coords)
                else:
                    sys.stderr.write("Error: 'c' or 'r' specified for a street that does not exist.\n")

            # Command for remmoving the street
            elif command == 'r':
                if street_name and not coordinates:
                    try:
                        street_dict.pop(street_name)
                    except KeyError:
                        sys.stderr.write("Error: 'r' specified for a street that does not exist.\n")
                else:
                    sys.stderr.write("Error: Incorrect input format.\n")

            # Command for generating the graph
            elif command == 'g':
                if not street_name and not coordinates:
                    streets = street_dict.values()

                    edges_dict = {}
                    for street_index in range(len(streets)):
                        for edge in streets[street_index].edges:
                            for other_street_index in range(street_index + 1, len(streets)):
                                for comparison_edge in streets[other_street_index].edges:
                                    r = edge.does_intersect(comparison_edge)
                                    if edge not in edges_dict.keys():
                                        edges_dict[edge] = []

                                    if comparison_edge not in edges_dict.keys():
                                        edges_dict[comparison_edge] = []

                                    if r[0]:
                                        vertex_to_add = Vertex(r[1], r[2])
                                        try:
                                            if vertex_to_add not in edges_dict[edge]:
                                                edges_dict[edge].append(vertex_to_add)
                                        except Exception:
                                            vertex_to_add = 0
                                            edges_dict = {}
                                        try:
                                            if vertex_to_add not in edges_dict[comparison_edge]:
                                                edges_dict[comparison_edge].append(vertex_to_add)
                                        except Exception:
                                            comparison_edge = 0
                                            edges_dict = {}


                    for edge, intersection_pts in edges_dict.items():
                        line_pts = []
                        if len(intersection_pts) > 0:
                            if edge.start not in intersection_pts:
                                line_pts = [edge.start]
                            line_pts.extend(intersection_pts)
                            if edge.end not in intersection_pts:
                                line_pts.append(edge.end)
                            line_pts = sorted(line_pts, key=lambda vertex: (vertex.x-edge.start.x)**2 + (vertex.y-edge.start.y)**2)

                        last_idx = None
                        for i in range(len(line_pts)):
                            current_idx = add_vertex(line_pts[i])
                            if i > 0:
                                add_edge(current_idx, last_idx)
                            last_idx = current_idx

                    check_index = 0
                    for index, vertex in vertices.items():
                        check_index = index

                    if check_index !=0:
                        # Print the Vertices
                        total_index = 0
                        print("V", end=' ')
                        sys.stdout.flush()
                        for index, vertex in vertices.items():
                            total_index = index
                        print((total_index + 1))
                        sys.stdout.flush()

                        # Print the Edges
                        print("E {", end='')
                        sys.stdout.flush()
                        for coordinates in edges:
                            if coordinates != edges[-1]:
                                print("<{0},{1}>,".format(coordinates[0],coordinates[1]),end='')
                                sys.stdout.flush()
                            else:
                                print("<{0},{1}>".format(coordinates[0],coordinates[1]), end='')
                                sys.stdout.flush()


                        print("}")
                        sys.stdout.flush()

                    vertices = {}
                    edges = []
                    edges_dict = {}
                else:
                    sys.stderr.write("Error: Did not specify any street name(s) or coordinate(s).\n")
            else:
                sys.stderr.write("Error: Incorrect input format.\n")
