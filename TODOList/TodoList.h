#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TodoListInterface.h"

using namespace std;

class TodoList : public TodoListInterface 
{
private:
	vector <string> tasks;
public:
	TodoList()
	{
		cout << "In Constructor" << endl;
		ifstream infile("TODOList.txt");
		string line;
		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				cout << line << endl;
				tasks.push_back(line);
			}
			infile.close();
		}
	}

	virtual ~TodoList() 
	{
		cout << "In Destructor" << endl;
		ofstream outfile;
		outfile.open("TODOList.txt", ofstream::out | ofstream::trunc);
		for (int i = 0; i < tasks.size(); i++)
		{
			cout << tasks[i] << '\n';
			outfile << tasks[i] << endl;
		}
		outfile.close();
	}

	/*
	*   Adds an item to the todo list with the data specified by the string "_duedate" and the task specified by "_task"
	*/
	virtual void add(string _duedate, string _task) 
	{
		cout << "In add " << _duedate << " " << _task << endl;
		tasks.push_back(_duedate + " " + _task);
	}

	/*
	*   Removes an item from the todo list with the specified task name
	*
	*   Returns 1 if it removes an item, 0 otherwise
	*/
	virtual int remove(string _task) 
	{
		cout << "In Remove" << " " << _task << endl;
		for (int i = 0; i < tasks.size(); i++)
		{
			cout << "Task " << i + 1 << ": " << tasks.at(i).substr(tasks.at(i).find(" ") + 1, tasks.at(i).size() - (tasks.at(i).find(" ") + 1)) << endl;
			if (tasks.at(i).substr(tasks.at(i).find(" ") + 1, tasks.at(i).size() - (tasks.at(i).find(" ") + 1)) == _task)
			{
				tasks.erase(tasks.begin() + i);
				cout << "Removed " << _task << " from list" << endl;
				return 1;
			}
		}
		cout << "Failed to remove " << _task << "from list" << endl;
		return 0;
	}

	/*
	*   Prints out the full todo list to the console
	*/
	virtual void printTodoList() 
	{
		cout << "In List" << endl;
		
		cout << "To Do List:" << endl;
		for (int i = 0; i < tasks.size(); i++)
		{
			cout << tasks.at(i) << endl;
		}
	}

	/*
	*   Prints out all items of a todo list with a particular due date (specified by _duedate)
	*/
	virtual void printDaysTasks(string _date) 
	{
		cout << "In Days Tasks" << endl;

		cout << "Tasks Due on " << _date << ":" <<endl;
		for (int i = 0; i < tasks.size(); i++)
		{
			if (tasks.at(i).substr(0, tasks.at(i).find(" ")) == _date)
			{
				cout << tasks.at(i) << endl;
			}
		}
	}
};

#endif