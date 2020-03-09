Directory Structure:

CPP-Maze_Path_Planner
|-- main.cpp
|-- README.txt

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Instructions on running the program:

1. Open and Run main.cpp
2. Enter Start and Goal coordinates as prompted
3. Solution path will be simulated

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Description of program:

This project calls a recursive function that solves the maze design 
described by ENPM809Y RWA 2. First, main() initializes the maze design 
and a copy of the maze design called sol to mark the solution path. main() 
prompts the user to input the coordinates of both the start and goal positions. 
The coordinates are separated by a space. If the input is not a integer, 
out of bounds, or on an obstacle spot, the user is reprompted to enter 
the coordinates. After the user inputs a start position, the program 
inputs the position on the maze and would reprompt the user to enter 
the goal coordinates if they are the same as the start position. 
The recursive function, FindPath(), is then called and checks if the 
current position (starting with Start position) is vali. i.e. not out 
of bounds and not on an obstacle. Then, the function is called again 
after going north, east, south, then west by order. If not path is 
possible, the function returns false and prints "Path not found". 
The function solves the maze using backtracking by recursion. If a 
possible path is found, it is marked by "+". If the path does not 
lead to the goal position, the "+" is cleared and replaced with "." to 
look for a different path. The function will always find a solution if 
one is possible. The path is not necessariliy the shortest path because 
of the nature of the search method (DFS), but will always find a feasible solution.

By Ghanem Jamal Eddine