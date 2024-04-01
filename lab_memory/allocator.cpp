#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "allocator.h"
#include "fileio.h"

using namespace std;

/**
 * Allocator constructor
 */
Allocator::Allocator(const string & studentFile, const string & roomFile)
{
	std::cout << "/* Allocator: constructing */" << std::endl;
	createLetterGroups();
	loadStudents(studentFile);
	loadRooms(roomFile);
	std::cout << "/* Allocator: Done constructing */" << std::endl;
}

/**
 * Allocates the array of letters
 */
void Allocator::createLetterGroups()
{
	std::cout << "/* Allocator: Creating letter groups */" << std::endl;
	// Make letters (A - Z lettergroups)
	alpha = new Letter[26];
	for (int i = 0; i < 26; i++)
		alpha[i].letter = 'A' + i;

	std::cout << "/* Allocator: Done creating letter groups */" << std::endl;
}

/**
 * Reads the students from the students file and places them in their letter
 * groups.
 */
void Allocator::loadStudents(const string & file)
{
	std::cout << "Allocator: Loading students" << std::endl;
	// Read in students
	fileio::loadStudents(file);
	studentCount = fileio::getNumStudents();

	for (int i = 0; i < studentCount; i++)
	{
		string name = fileio::nextStudent();
		char letter = name[0];
		int index = (int)letter - 'A';
		alpha[index].addStudent();
	}
	std::cout << "Allocator: Done loading students" << std::endl;
}

/**
 * Reads rooms from the rooms file
 */
void Allocator::loadRooms(const string & file)
{
	std::cout << "Allocator: Loading rooms" << std::endl;
	// Read in rooms
	fileio::loadRooms(file);
	rooms = new Room[roomCount];
	std::cout << roomCount << std::endl;

	totalCapacity = 0;
	int i = 0;
	while (fileio::areMoreRooms())
	{
		i++;
		std::cout << i << std::endl;
		rooms[i] = fileio::nextRoom();
		// rooms[i].print();
		totalCapacity += rooms[i].capacity;
	}
	std::cout << "Allocator: Done loading rooms" << std::endl;
}

void Allocator::printStudents()
{
	// Output number of each last letter name
	cout << "Student counts (" << studentCount << " total)" << endl;
	for (int i = 0; i < 26; i++)
		cout << alpha[i].letter << ": " << alpha[i].count << endl;
}

/**
 * Main allocation function
 * Allocates student letter groups to rooms
 */
void Allocator::allocate()
{
	std::cout << "/* Allocator: allocating */" << std::endl;
	// Perform the allocation
	int border = solve();

	// Check for an error
	if (border < 0)
	{
		cerr << endl << "Cannot allocate all students." << endl << endl;
		exit(-1);
	}
}

/**
 * Prints the rooms and their fullness
 */
void Allocator::printRooms()
{
	// Output the allocation
	cout << "Room Allocation (" << studentCount << "/" << totalCapacity << ")" << endl;
	for (int i = 0; i < roomCount; i++)
		rooms[i].print();
}

/**
 * Calculates the allocation
 */
int Allocator::solve()
{
	stable_sort(alpha, alpha + 26);
	
	for (int L = 0; L < 26; L++)
	{
		Room * r = largestOpening();
		r->addLetter(alpha[L]);
	}
	
	return minSpaceRemaining();
}

/**
 * Returns the amount of seats remaining in the room with the fewest
 * spare seats
 */
int Allocator::minSpaceRemaining()
{
	int border = 1000000;
	for (int i = 0; i < roomCount; i++)
		if (rooms[i].spaceRemaining() < border)
			border = rooms[i].spaceRemaining();
	return border;
}

/**
 * Return the room with the largest number of open seasts
 */
Room * Allocator::largestOpening()
{
	std::cout << "Allocator: Largest opening" << std::endl;
	int index = 0;
	int max_remaining = 0;
	for (int i = 0; i < roomCount; i++)
	{
		if (rooms[i].spaceRemaining() > max_remaining)
		{
			index = i;
			max_remaining = rooms[i].spaceRemaining();
		}
	}
	std::cout << "Allocator: returning Largest opening: " << std::endl;
	return &rooms[index];
}
