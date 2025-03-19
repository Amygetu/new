/**
 * @file ZipIndex.h
 * @brief Header file for managing the primary key index for zip code lookups.
 */

#ifndef ZIPINDEX_H
#define ZIPINDEX_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * @class ZipIndex
 * @brief Handles the creation, storage, and lookup of the primary key index for zip codes.
 */
class ZipIndex {
private:
    unordered_map<string, long> index; ///< Maps Zip Codes to byte offsets in the file.

public:
    /**
     * @brief Builds the index from a length-indicated file.
     * @param filename The file containing length-indicated Zip Code records.
     */
    void buildIndex(const string& filename);

    /**
     * @brief Saves the index to a file.
     * @param indexFilename The output index file.
     */
    void saveIndex(const string& indexFilename) const;

    /**
     * @brief Loads the index from a file.
     * @param indexFilename The index file to load.
     */
    void loadIndex(const string& indexFilename);

    /**
     * @brief Finds the byte offset of a given Zip Code.
     * @param zipCode The Zip Code to search for.
     * @return The byte offset if found, or -1 if not found.
     */
    long findZipCode(const string& zipCode) const;
};

#endif // ZIPINDEX_H
