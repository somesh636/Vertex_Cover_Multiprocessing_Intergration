# Vertex_Cover_Multiprocessing_Intergration
In this project the Vertex Cover Problem is solved by using Python and C++
First the random coordinated are generated using rgen.cpp and then the output of
rgen is fed to the input of Pyhton, the Python code generates the Vertex and the
Edges needed for calculating the shorted path. The Shortest path is calculated
in the shortest.cpp file and then the user can enter the query for the shortest
path.

A small desciption for the files
* rgen.cpp- generates random streets and coordinates.
* ece650-a1.py- takes input from the rgen to generate Vertices and Edges
* ece650-a2.cpp- calculates the shortest path for the given queries.
* ece650-a3.cpp- Integrates the above files for Multiprocessing.

* To run follow the steps
&& cmake ../ && make install && cd /run/bin && ./ece650-a3 -s 5 -n 4 -l 5
• -s k — where k is an integer ≥ 2. The number of streets is a random integer in [2, k].
If this option is not specified, it use a default of k = 10; that is, the number of streets
is a random integer in [2, 10].
• -n k — where k is an integer ≥ 1. The number of line-segments in each street is a
random integer in [1, k]. Default: k = 5.
• -l k — where k is an integer ≥ 5. the process waits a random number w seconds,
where w is in [5, k] before generating the next (random) input. Default: k = 5.
• -c k — where k is an integer ≥ 1. the process generates (x, y) coordinates such that
every x and y value is in the range [−k, k]. For example, if k = 15, all of the coordinate values
are integers between −15 and 15. Default: k = 20.
