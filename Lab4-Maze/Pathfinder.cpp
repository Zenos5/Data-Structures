#include "Pathfinder.h"

string Pathfinder::toString() const
{
	stringstream ss;
	for (int lvl = 0; lvl < LVL_SIZE; lvl++) {
		for (int col = 0; col < COL_SIZE; col++) {
			for (int row = 0; row < ROW_SIZE; row++)
			{
				ss << maze_grid[row][col][lvl];
				if (row != 4)
				{
					ss << " ";
				}
			}
			ss << "\n";
		}
		if (lvl != LVL_SIZE - 1)
		{
			ss << "\n";
		}
	}
	cout << ss.str();
	return ss.str();
}

/*
* createRandomMaze
*
* Generates a random maze and stores it as the current maze.
*
* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
*/
void Pathfinder::createRandomMaze()
{
	string line;
	for (int lvl = 0; lvl < LVL_SIZE; lvl++)
	{
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				if ((lvl == 0 && row == 0 && col == 0)
					|| (lvl == 4 && row == 4 && col == 4))
				{
					//cout << "[" << row << "][" << col << "][" << lvl << "]=" << 1 << endl;
					maze_grid[row][col][lvl] = 1;
				}
				else
				{
					int value = rand() % 2;
					//cout << "[" << row << "][" << col << "][" << lvl << "]=" << value << endl;
					maze_grid[row][col][lvl] = value;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------

//Part 2-----------------------------------------------------------------------------------
/*
* importMaze
*
* Reads in a maze from a file with the given file name and stores it as the current maze.
* Does nothing if the file does not exist or if the file's data does not represent a valid
* maze.
*
* The file's contents must be of the format described above to be considered valid.
*
* Parameter:	file_name
*				The name of the file containing a maze
* Returns:		bool
*				True if the maze is imported correctly; false otherwise
*/
bool Pathfinder::importMaze(string file_name)
{
	int lineCount = 0;
	try {
		cout << "importMaze from " << file_name << endl;
		fstream file(file_name.c_str());
		if (!file.is_open())
		{
			return(false);
		}
		if (file.is_open()) {
			string line;
			int row_count = 0;
			for (unsigned int lvl = 0; lvl < LVL_SIZE; lvl++)
			{
				for (unsigned col = 0; col < COL_SIZE; col++)
				{
					getline(file, line);
					lineCount++;
					if (line.empty())
					{
						if (lvl == 0 && col == 0)
						{
							return(false);
						}
						getline(file, line);
						lineCount++;
						if (line.empty())
						{
							return(false);
						}
					}
					if (line.size() != 9)
					{
						return(false);
					}
					stringstream ss(line);
					for (unsigned int row = 0; row < ROW_SIZE; row++)
					{
						int value;
						ss >> value;
						//cout << value << endl;
						maze_grid[row][col][lvl] = value;
						//cout << "[" << row << "][" << col << "][" << lvl << "]=" << maze_grid[row][col][lvl] << endl;
					}
				}
			}
			getline(file, line);
			if (line.empty())
			{
				return(false);
			}
			if (maze_grid[0][0][0] != 1 || maze_grid[4][4][4] != 1)
			{
				return(false);
			}
			if (lineCount != 29)
			{
				return(false);
			}
		}
		return(true);
	}
	catch (exception e) {
		cout << "Not Valid Maze";
		return false;
	}
	
}
//-----------------------------------------------------------------------------------------



bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][LVL_SIZE], int r, int c, int l) {
	//cout << "find_maze_path [" << r << "][" << c << "][" << l << "]" << endl;
	//cout << this->toString();
	if (r < 0 || c < 0 || l < 0 || r >= ROW_SIZE || c >= COL_SIZE || l >= LVL_SIZE)
		return false;      // Cell is out of bounds.
	else if (grid[r][c][l] != BACKGROUND)
		return false;      // Cell is on barrier or dead end.
	else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && l == LVL_SIZE - 1) {
		grid[r][c][l] = PATH;         // Cell is on path
		solution.insert(solution.begin(), "(" + to_string(r) + ", " + to_string(c) + ", " + to_string(l) + ")");
		return true;               // and is maze exit.
	}
	else {
		// Recursive case.
		// Attempt to find a path from each neighbor.
		// Tentatively mark cell as on path.
		grid[r][c][l] = PATH;
		if (find_maze_path(grid, r - 1, c, l)
			|| find_maze_path(grid, r + 1, c, l)
			|| find_maze_path(grid, r, c - 1, l)
			|| find_maze_path(grid, r, c + 1, l)
			|| find_maze_path(grid, r, c, l - 1)
			|| find_maze_path(grid, r, c, l + 1)) {
			solution.insert(solution.begin(), "(" + to_string(r) + ", " + to_string(c) + ", " + to_string(l) + ")");
			return true;
		}
		else {
			grid[r][c][l] = TEMPORARY;  // Dead end.
			return false;
		}
	}
}
//Part 3-----------------------------------------------------------------------------------
/*
* solveMaze
*
* Attempts to solve the current maze and returns a solution if one is found.
*
* A solution to a maze is a list of coordinates for the path from the entrance to the exit
* (or an empty vector if no solution is found). This list cannot contain duplicates, and
* any two consecutive coordinates in the list can only differ by 1 for only one
* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
* where x, y, and z are the integer coordinates of a cell.
*
* Understand that most mazes will contain multiple solutions
*
* Returns:		vector<string>
*				A solution to the current maze, or an empty vector if none exists
*/

vector<string> Pathfinder::solveMaze()
{
	solution.clear();
	find_maze_path(maze_grid, 0, 0, 0);
	for (auto s : solution) {
		//cout << s << endl;
	}
	for (int lvl = 0; lvl < LVL_SIZE; lvl++)
	{
		for (int col = 0; col < COL_SIZE; col++)
		{
			for (int row = 0; row < ROW_SIZE; row++)
			{
				if (maze_grid[row][col][lvl] != 0)
				{
					maze_grid[row][col][lvl] = 1;
				}
			}
		}
	}
	return solution;
}