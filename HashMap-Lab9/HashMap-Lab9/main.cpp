#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Hashmap.h"
#include "WordCounter.h"

const int NUM_FILES = 6; // the total number of files to be read from

const std::string fileArray[NUM_FILES] = { "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt", "file6.txt" }; // the string aray containing the file names

 // This will take a string temp and a Hashmap object and will execute an instruction from the string
 // no return, but writes the results of the instruction into the ofs filestream
void parse_instruction(std::string temp, std::ofstream &ofs, Hashmap* map);

// This function is a platform independent way of reading files of various line ending types.
// It's definiton is at the bottom of the file, don't worry if you don't understand it.
namespace ta {
	std::istream& getline(std::istream& is, std::string& line);
}

int main(int argc, char* argv[])
{
	std::ifstream ifs; // create the stream to read in from the files
	std::ofstream ofs; // create the output stream to write to an output file
	std::string temp; // used to store the current instruction
	Hashmap* map = NULL; // the hashmap

	for (int i = 0; i < NUM_FILES; i++) {
		map = new Hashmap(); // the hashmap
		ifs.open(fileArray[i]); // open the file to read from
		ofs.open("out_" + fileArray[i]); // open the file to write to

		if (!ifs.is_open()) { // if the file did not open, there was no such file
			std::cout << "File " << i + 1 << " could not open, please check your lab setup" << std::endl;
		}
		else {
			std::cout << "Reading file" << i + 1 << ".txt..." << std::endl;
		}

		std::cout << "Beginning out_file" << i + 1 << ".txt write" << std::endl;
		while (ta::getline(ifs, temp)) { // while there are more instructions to get,
			try {
				parse_instruction(temp, ofs, map); // parse the instrutions using hashmap
			}
			catch (...) {
				std::cout << "An exception was thrown that shouldn't have been.\n";
			}
		}
		std::cout << map->toString() << std::endl; // Print map contents at the end
		std::cout << "File write complete" << std::endl << std::endl;
		if(map != NULL) {
			delete map;
			map = NULL;
		}
		ifs.close();
		ofs.close();
	}
	std::cout << "end" << std::endl; // indicate that the program has successfuly executed all instructions
	return 0;
}

void parse_instruction(std::string temp, std::ofstream &ofs, Hashmap* map)
{
	std::string command, key, file;
	int value, size;
	bool didWork;
	std::stringstream ss(temp);
	if (!(ss >> command)) { return; } // get command, but if string was empty, return
	if (command == "insert") { // command to insert key/value pair
		ss >> key >> value;
		map->insert(key, value); // add key/value pair to map
		ofs << temp << std::endl;
	}
	else if (command == "get") { // command to get value for key
		ss >> key;
		try {
			value = map->get(key);
			ofs << temp << " " << value << std::endl;
		}
		catch (std::invalid_argument) { // if an invalid_argument exception was thrown, catch it!
			ofs << temp << " invalid_argument" << std::endl;
		}
	}
	else if (command == "size") { // command to get number of key/value pairs in map
		size = map->size();
		ofs << temp << " " << size << std::endl;
	}
	else if (command == "contains") { // command to test if key exist in map
		ss >> key;
		didWork = map->contains(key);
		ofs << temp << " " << (didWork ? "true" : "false") << std::endl;
	}
	else if (command == "[]") { // command to override [] operator
		ss >> key;
		if(ss >> value) // if value is provided, set value
		{
			(*map)[key] = value;
		}
		else // if value is not provided, get value
		{
			value = (*map)[key];
		}
		ofs << temp << std::endl;
	}
	else if(command == "remove") { // command to remove key/value pair by key
		ss >> key;
		didWork = map->remove(key);
		ofs << temp << " " << (didWork ? "true" : "false") << std::endl;
	}
	else if(command == "clear") { // command to clear all key/value pairs from map
		map->clear();
		ofs << temp << std::endl;
	}
	else if(command  == "WordCounter") { // command to run WordCounter on file
		ss >> file;
		WordCounter wc;
		wc.loadFile(file);
		ofs << temp << std::endl;
		ofs << wc.toString() << std::endl;
		wc.reset();
	}
	else { // invalid command, wrong input file format
		std::cout << "Command: \"" << command << "\"" << std::endl;
		std::cout << "Invalid command.  Do you have the correct input file?" << std::endl;
	}
}

// Version of getline which does not preserve end of line characters
namespace ta {
	std::istream& getline(std::istream& in, std::string& line) {
		line.clear();

		std::istream::sentry guard(in, true); // Use a sentry to maintain the state of the stream
		std::streambuf *buffer = in.rdbuf();  // Use the stream's internal buffer directly to read characters
		int c = 0;

		while (true) { // Continue to loop until a line break if found (or end of file)
			c = buffer->sbumpc(); // Read one character
			switch (c) {
			case '\n': // Unix style, return stream for further parsing
				return in;
			case '\r': // Dos style, check for the following '\n' and advance buffer if needed
				if (buffer->sgetc() == '\n') { buffer->sbumpc(); }
				return in;
			case EOF:  // End of File, make sure that the stream gets flagged as empty
				in.setstate(std::ios::eofbit);
				return in;
			default:   // Non-linebreak character, go ahead and append the character to the line
				line.append(1, (char)c);
			}
		}
	}
}
