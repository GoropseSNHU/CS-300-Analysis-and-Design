//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Aidan Gorospe April 18, 2024
// Version     : 1.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;


void MenuDisplay()
{
	cout << "1: Load Data Structure" << endl;
	cout << "2: Print Course List" << endl;
	cout << "3: Print Course" << endl;
	cout << "4: Remove Course" << endl;
	cout << "9: Exit" << endl;
	cout << "Input: ";
}
struct Course
{
	string CourseID;
	string CourseName;
	vector<string> PreList;
};
class BinarySearchTree
{
 private:
	struct Node
	{
		Course course;
		Node* left;
		Node* right;
		Node()
		{
			left = nullptr;
			right = nullptr;
		}
		Node(Course aCourse) : Node()
		{
			this->course = aCourse;
		}
	};
	Node* root;
	void InOrder(Node* node);
	int size = 0;
 public:
	Node* root;
	BinarySearchTree();
	void InOrder();
	void Insert(Course aCourse);
	void Remove(string CourseID);
	Course Search(string CourseID);
	void PrintCourse(Node* node);
	int Size();
};
BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
}
void BinarySearchTree::InOrder()
{
	InOrder(root);
}
void BinarySearchTree::Insert(Course aCourse)
{
	Node* node = root;
	if (root == nullptr)
	{
		root = new Node(aCourse);
	}
	else
	{
		while(node != nullptr)
		{
			if(aCourse.CourseID < node->course.CourseID)
			{
				if(node->left == nullptr)
				{
					node->left = new Node(aCourse);
				}
				else
				{
					node = node->left;
				}
			}
			else
			{
				if(node->right == nullptr)
				{
					node->right = new Node(aCourse);
				}
				else
				{
					node = node->right;
				}
			}
		}
	}
}
Course BinarySearchTree::Search(string courseid)
{
	Node* node = root;
	while(node != nullptr)
	{
		if(node->course.CourseID == courseid)
		{
			cout << node->course.CourseID << "|" << node->course.CourseName << endl;
			cout << "Prereq: ";
			for(string i : node->course.PreList)
			{
				if(i == node->course.PreList.back())
				{
					cout << i << endl;
				}
				else
				{
					cout << i << "| ";
				}
			}
		}
		else if(courseid < node->course.CourseID)
		{
			if(node->left != nullptr)
			{
				node = node->left;
			}
		}
		else
		{
			node = node->right;
		}
	}
	return node;
}
void BinarySearchTree::InOrder(Node* node)
{
	if(node == nullptr)
	{
		return;
	}
	InOrder(node->left);
	cout << node->course.CourseID << "|" << node->course.CourseName << endl;
	InOrder(node->right);
}
void BinarySearchTree::PrintCourse(Node* node)
{
	if(node == nullptr)
	{
		return;
	}
	PrintCourse(node->left);
	cout << node->course.CourseID << "|" << node->course.CourseName << endl;
	PrintCourse(node->right);
}
void LoadCourse(string path, BinarySearchTree* searchList)
{
	ifstream file(path);
	file.open(path);
	if(file.is_open())
	{
		while(!file.eof())
		{
			vector<string> courselines;
			string line;
			getline(file, line);
			while (line.length() > 0)
			{
				unsigned int num = line.find(',');
				if(num < 100)
				{
					courselines.push_back(line.substr(0, num));
					line.erase(0, num+1);
				}
				else
				{
					courselines.push_back(line.substr(0,line.length()));
					line = "";
				}
			}
			Course aCourse;
			aCourse.CourseID = courselines[0];
			aCourse.CourseName = courselines[1];
			for(unsigned int j = 2; j < courselines.size(); j++)
			{
				aCourse.PreList.push_back(courselines[j]);
			}
			searchList->Insert(aCourse);
		}
	}
	file.close();
	return;
}
void main()
{
	BinarySearchTree* courselist = new BinarySearchTree();
	string file;
	string course;
	int userinput = 0;
	try
	{
		while(userinput != 9)
		{
			MenuDisplay();
			cin >> userinput;
			switch(userinput)
			{
			case 1:
				cout << "load file";
				cin >> file;
				LoadCourse(file, courselist);
				break;
			case 2:
				cout <<"Here is the list of classes";
				courselist->PrintCourse(courselist->root);
				break;
			case 3:
				cout << "Search for Class here: ";
				cin >> course;
				courselist->Search(course);
				break;
			case 4:
				cout << "Type which class to remove here: ";
				cin >> course;
				courselist->Remove(course);
				break;
			case 9:
				cout << "goodbye";
				break;
			}
		}
	}
	catch(int err)
	{
		cout << "Incorrect input";
	}
	cin.clear();
	cin.ignore();
}
