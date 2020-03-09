/**
* @file main.cpp
* @author Ghanem Jamal Eddine <gjamaled@umd.edu>
* @version 2.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
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
   current position (starting with Start position) is valid, i.e. not out 
   of bounds and not on an obstacle. Then, the function is called again 
   after going north, east, south, then west by order. If no path is 
   possible, the function returns false and prints "Path not found". 
   The function solves the maze using backtracking by recursion. If a 
   possible path is found, it is marked by "+". If the path does not 
   lead to the goal position, the "+" is cleared and replaced with "." to 
   look for a different path. The function will always find a solution if 
   one is possible. The path is not necessarily the shortest path because 
   of the nature of the search method (DFS), but it will always find a possible solution.
*/

#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
* @brief A function that validates the start position coordinates
* @author Ghanem Jamal Eddine
* @param maze The predefined maze design
* @param xx_s x coordinate of start position
* @param yy_s y coordinate of start position
* @return Used to call a pointer if position is valid.
**/  
void ValidateStart(string maze[6][6], int* xx_s, int* yy_s); // Function prototype for the start point validation function
void ValidateStart(string maze[6][6], int* xx_s, int* yy_s){ // Validates start position coordiantes
	string coord_s;
	int x_s, y_s;
	
	getline(cin, coord_s); // Read input line as string
	while (coord_s.length()!=3){ // Length of input should not exceed 3 (2 numbers and 1 space)
		cout << "Input not valid. Try again: ";
		getline(cin, coord_s);
	}
	while (!(isdigit(coord_s[0])) || !(isdigit(coord_s[2]))){ // Validating that first and second elements are integers
		cout << "Input not an integer. Try again: ";
		getline(cin, coord_s);
		while (coord_s.length()>3 ){
			cout << "Input not valid. Try again: ";
			getline(cin, coord_s);
		}
	}
	x_s = stoi(coord_s.substr(0,1)); // Converting string to integer
	y_s = stoi(coord_s.substr(2));
	while (x_s >= 6 || x_s < 0 || y_s >= 6 || y_s < 0 || maze[5-y_s][x_s] == "#"){ // Validating that input is within maze boundaries and not on obstacles
		cout << "Input out of bounds/blocked. Try again: ";
		getline(cin, coord_s);
		while (!(isdigit(coord_s[0])) || !(isdigit(coord_s[2]))){
			cout << "Input not an integer. Try again: ";
			getline(cin, coord_s);
			while (coord_s.length()!=3 ){
				cout << "Input not valid. Try again: ";
				getline(cin, coord_s);
			}
		}
		x_s = stoi(coord_s.substr(0,1));
		y_s = stoi(coord_s.substr(2));
	}
	*xx_s = x_s;
	*yy_s = y_s;
}

/**
* @brief A function that validates the goal position coordinates
* @author Ghanem Jamal Eddine
* @param maze The predefined maze design
* @param xx_g x coordinate of goal position
* @param yy_g y coordinate of goal position
* @return Returns Used to call a pointer if position is valid.
**/  
void ValidateGoal(string maze[6][6], int* xx_g, int* yy_g); // Function prototype for the start point validation function
void ValidateGoal(string maze[6][6], int* xx_g, int* yy_g){ // Validates goal position coordinates
	string coord_g;
	int x_g, y_g;
	
	getline(cin, coord_g); // Read input line as string
	while (coord_g.length()!=3){ // Length of input should not exceed 3 (2 numbers and 1 space)
		cout << "Input not valid. Try again: ";
		getline(cin, coord_g);
	}
	while (!(isdigit(coord_g[0])) || !(isdigit(coord_g[2]))){ // Validating that first and second elements are integers
		cout << "Input not an integer. Try again: ";
		getline(cin, coord_g);
		while (coord_g.length()>3 ){
			cout << "Input not valid. Try again: ";
			getline(cin, coord_g);
		}
	}
	x_g = stoi(coord_g.substr(0,1)); // Converting string to integer
	y_g = stoi(coord_g.substr(2));
	while (x_g >= 6 || x_g < 0 || y_g >= 6 || y_g < 0 || maze[5-y_g][x_g] == "#" || maze[5-y_g][x_g] == "S"){ // Validating that input is within maze boundaries and not on obstacles or start point
		cout << "Input out of bounds/blocked. Try again: ";
		getline(cin, coord_g);
		while (!(isdigit(coord_g[0])) || !(isdigit(coord_g[2]))){
			cout << "Input not an integer. Try again: ";
			getline(cin, coord_g);
			while (coord_g.length()!=3 ){
				cout << "Input not valid. Try again: ";
				getline(cin, coord_g);
			}
		}
		x_g = stoi(coord_g.substr(0,1));
		y_g = stoi(coord_g.substr(2));
	}
	*xx_g = x_g;
	*yy_g = y_g;
}

/**
* @brief A recursive function that calls itself to solve the maze problem by backtracking.
* @author Ghanem Jamal Eddine
* @param maze The predefined maze design
* @param x x coordinate of current position
* @param y y coordinate of current position
* @param sol The solution path
* @return Returns True and solution map if path is found, and False if no path is possible.
**/  
bool FindPath(string maze[6][6], int x, int y, string sol[6][6]); // The function prototype for the maze recursive function
bool FindPath(string maze[6][6], int x, int y, string sol[6][6]) 
{ 

	if (x < 0 || y < 0){ // if position is out of bounds
		return false;
	}
	if (x >= 6 || y >= 6){ // if position is out of bounds
		return false;
	}
	if (maze[x][y] == "G"){ // if goal is reached, done
        return true; 
    } 
    // Check if maze[x][y] is valid 
	if ((maze[x][y] == ".") || (maze[x][y] == "S") == true){
        // mark x, y as part of solution path 
        sol[x][y] = "+";
		maze[x][y] = "+";
  
        /* Move North */
        if (FindPath(maze, x - 1, y, sol) == true) 
            return true; 
		/* If moving North doesn't give solution then 
           Move East*/
		if (FindPath(maze, x , y + 1, sol) == true) 
            return true;
		/* If moving East doesn't give solution then 
           Move South*/
		if (FindPath(maze, x + 1, y, sol) == true) 
            return true;
		/* Finally, If moving South doesn't give solution then 
           Move West*/
		if (FindPath(maze, x, y - 1, sol) == true) 
            return true; 

        /* If none of the above movements work, 
            unmark x y as part of solution path */
        sol[x][y] = "."; 
        return false; 
    } 
    return false; 
} 

/* The main function initializes the maze design and prompts the user to enter VALID coordinates.
 * If the user enters anything but an integer, out of bounds coordinates, obstacle coordinates, 
 * or goal coordinates equal to the start coordinates, the user will be reprompted to input coordinates.
 */
int main() 
{ 
	int x_s, y_s, x_g, y_g;
	string maze[6][6] = {  // Initialize maze
		{".","#","#","#","#","#"},
		{".",".",".","#",".","#"},
		{"#",".","#","#",".","#"},
		{"#",".","#","#",".","#"},
		{".",".","#",".",".","."},
		{"#",".",".",".","#","#"}};
	string sol[6][6] = {  // Initialize solution path
		{".","#","#","#","#","#"},
		{".",".",".","#",".","#"},
		{"#",".","#","#",".","#"},
		{"#",".","#","#",".","#"},
		{".",".","#",".",".","."},
		{"#",".",".",".","#","#"}};
 
	cout << "      The Maze\n" << " 5   . # # # # #\n 4   . . . # . #\n 3   # . # # . #\n";
	cout << " 2   # . # # . #\n 1   . . # . . .\n 0   # . . . # #\n(y)\n     0 1 2 3 4 5 (x)\n\n"; // Display initial maze
	
	// Get Start coordinates
	cout << endl << "Enter coordinates (x y) for the Start point, separated by a space: " << endl;
  	ValidateStart(maze, &x_s, &y_s);
  	maze[5-y_s][x_s] = "S"; // Mark Start point on the maze
  	cout << "You entered: (" << x_s << ",";
  	cout << " " << y_s << ")" << endl;
  
  	cout << endl << "Enter coordinates (x y) for the Goal point, separated by a space: " << endl;
  	ValidateGoal(maze, &x_g, &y_g);
  	maze[5-y_g][x_g] = "G"; // Mark Goal point on the maze
  	cout << "You entered: (" << x_g << ",";
  	cout << " " << y_g << ")" << endl;
	
	cout << endl << "The solution path:" << endl;
    if (FindPath(maze, 5 - y_s, x_s, sol) == false) { // Start the recursive function FindPath()
        cout << "Path not found" << endl;  // Returns "Path not found" if no solution is possible
        return false; 
    } 
    sol[5-y_s][x_s] = "S"; // Mark Start position in solution path
	sol[5-y_g][x_g] = "G";  // Mark Goal position in solution path
	cout << endl;
	
    for (int i = 0; i <= 5; i++) { // Print Solved maze
	cout << "     ";
        for (int j = 0; j <= 5; j++){ 
			cout << sol[i][j] << " ";
		}
		cout << endl;
    } 
	cout << endl;
	return 0; 
}