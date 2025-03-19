/**
 * @file ZipIndex.h
 * @brief Header file for managing the primary key index for zip code lookups.
 * @details Class that provides functionality to search a primary key index for Zip code record. 
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
 * @details The ZipIndex class maintains a hash map of Zip codes to their byte offsets in the file. 
 */
class ZipIndex {
private:
    unordered_map<string, long> index; ///< Maps Zip Codes to byte offsets in the file.

public:
    /**
     * @brief Builds the index from a length-indicated file.
     * @param filename The file containing length-indicated Zip Code records.
     * @details Scans the file, records the byte offset for each Zip Code. 
     */
    void buildIndex(const string& filename);

    /**
     * @brief Saves the index to a file.
     * @param indexFilename The output index file.
     * @details Write Zip code and its byte offset to a comma-separated file. 
     */
    void saveIndex(const string& indexFilename) const;

    /**
     * @brief Loads the index from a file.
     * @param indexFilename The index file to load.
     * @details Reads the index from comma-separated files. 
     */
    void loadIndex(const string& indexFilename);

    /**
     * @brief Finds the byte offset of a given Zip Code.
     * @param zipCode The Zip Code to search for. 
     * @return The byte offset if found, or -1 if not found.
     * @details Performs a constant-time lookup in the hash map to find the byte offset. 
     */
    long findZipCode(const string& zipCode) const;
     /**
     * @brief Return the size of the index.
     * @return Number of entries in the index.
     * @details Tells the total count of ZIP codes stored in the index.
     */
     size_t size() const;
};

#endif // ZIPINDEX_H
