/**
 * @file ZipSearch.cpp
 * @brief Standalone program to search for Zip Codes using the primary key index.
 */

#include <iostream>
#include <fstream>
#include "zipIndex.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <datafile> <indexfile> -Z<zip>\n";
        return 1;
    }

    string dataFilename = argv[1];
    string indexFilename = argv[2];
    string zipCode;

    for (int i = 3; i < argc; ++i) {
        string arg = argv[i];
        if (arg[0] == '-' && arg[1] == 'Z') {
            zipCode = arg.substr(2);
        }
    }

    if (zipCode.empty()) {
        cout << "Error: No zip code provided for search.\n";
        return 1;
    }

    // Load index
    ZipIndex index;
    index.loadIndex(indexFilename);

    // Find zip code
    long offset = index.findZipCode(zipCode);
    if (offset == -1) {
        cout << "Zip Code " << zipCode << " not found.\n";
        return 0;
    }

    // Read record from file at offset
    ifstream file(dataFilename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening data file: " << dataFilename << endl;
        return 1;
    }

    file.seekg(offset);
    string record;
    getline(file, record);
    file.close();

    cout << "Zip Code Record: " << record << endl;
    return 0;
}
