/**
 * @file ZipIndex.cpp
 * @brief Implements the ZipIndex class for managing the primary key index.
 */

#include "zipIndex.h"

/**
 * @brief Builds the index from a length-indicated file.
 * @param filename The file containing length-indicated Zip Code records.
 */
void ZipIndex::buildIndex(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    index.clear();
    long offset = file.tellg(); // Start of the file
    string line;

    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string zipCode = line.substr(commaPos + 1, 5); // Assuming Zip Code is 5 characters
            index[zipCode] = offset;
        }
        offset = file.tellg();
    }
    file.close();
}

/**
 * @brief Saves the index to a file.
 * @param indexFilename The output index file.
 */
void ZipIndex::saveIndex(const string& indexFilename) const {
    ofstream file(indexFilename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening index file: " << indexFilename << endl;
        return;
    }

    for (const auto& entry : index) {
        file << entry.first << "," << entry.second << "\n";
    }
    file.close();
}

/**
 * @brief Loads the index from a file.
 * @param indexFilename The index file to load.
 */
void ZipIndex::loadIndex(const string& indexFilename) {
    ifstream file(indexFilename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening index file: " << indexFilename << endl;
        return;
    }

    index.clear();
    string zipCode;
    long offset;
    while (file >> zipCode >> offset) {
        index[zipCode] = offset;
    }
    file.close();
}

/**
 * @brief Finds the byte offset of a given Zip Code.
 * @param zipCode The Zip Code to search for.
 * @return The byte offset if found, or -1 if not found.
 */
long ZipIndex::findZipCode(const string& zipCode) const {
    auto it = index.find(zipCode);
    if (it != index.end()) {
        return it->second;
    }
    return -1;
}
