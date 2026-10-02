#include "FileLogger.h"
#include <fstream>
using namespace std;


void FileLogger::Log(char* message)
{
	ofstream MyFile("filename.txt", std::ofstream::app);

	// Write to the file
	MyFile << message << endl;

	// Close the file
	MyFile.close();
}
