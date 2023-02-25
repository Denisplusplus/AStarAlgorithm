# One way to use the Astar algorithm

### Assignment condition:

Write a program that finds the shortest exit from the maze (the shortest in the sense of the fastest, because the speed of movement through different fields is different)  

As input, the program receives table rows in stdin - a representation of the labyrinth.
The response is printed to stdout, the path is displayed with *  

Field designations:
```
* s - start
* - empty field, corridor, speed is 1
*. - sand, speed on it 0.5
* # - wall
```
An example of a successful launch (by the way, two answers are possible here, any in the output)
```
echo \
"###
#s#
# #
## #" | your_walk_out_of_maze_bin
#*##
#*s#
# #
###
```
If there is no exit, the program should exit with code 1

### Solution:

1. Language selection

To solve such problems (related to algorithms and the importance of the speed of programs), C ++ is often used.
We will use it as a tool for solving this problem.

2. Processing of input data

A map of the labyrinth will be submitted to the input of our program. We will store it as a two-dimensional array, after converting the map symbols into numbers, because it will be easier to perform actions with a map converted in this way.

3. Algorithm

There are many algorithms for finding the shortest path. Among them, the most interesting is the AStar algorithm. This algorithm is informed, i.e. it looks first at those routes that "seem" to lead to the goal. The efficiency of this algorithm is achieved through the use of heuristics, specifically for our case we used the Manhattan distance (https://en.wiktionary.org/wiki/Manhattan_distance). Astar is easiest to consider in comparison with Dijkstra's algorithm (a special case of Astar). Dijkstra's algorithm looks at all possible paths, while Astar only looks at its neighbors, choosing the best path.

4. Examples

```
cat test && echo "\n" && ./exec < test
# ########
#    #   #
#### # # #
#    #   #
# ## ### #
#    #s# #
# #### # #
#    # # #
####     #
##########

22
#*########
#****#   #
####*# # #
#****#   #
#*## ### #
#*   #s# #
#*####*# #
#****#*# #
####***  #
##########
```

5. Instructions for launching

```
make
./exec < test
```
The program contains 4 files: Makefile, main.cpp, search.h, search.cpp  

Assembly is done with the make utility.