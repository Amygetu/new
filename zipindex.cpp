/**
 * @file ZipIndex.cpp
 * @brief Implements the ZipIndex class for managing the primary key index.
 */

#include "zipindex.h"
#include <sstream>

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
        // Finds second field (zip code) after first coma
        size_t firstCommaPos = line.find(',');
        if (firstCommaPos != string::npos) {
            // Getting the Zip code (5 char. after the coma) 
            string zipCode = line.substr(firstCommaPos + 1, 5); // Assuming Zip Code is 5 characters
            // store the zip code and its offset
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
    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string zipCode = line.substr(0, commaPos);
            long offset;
            try {
                offset = stol(line.substr(commaPos + 1));
                index[zipCode] = offset;
            }
            catch (const std::exception& e) {
                cerr << "Error parsing the offset for this zip code" << zipCode << e.what() << endl;
            }
        }
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

/**
 * @brief Returns the size of the index.
 * @return The number of entries in the index.
 */
size_t ZipIndex::size() const {
    return index.size();
}
