g++ -o zipindexbuilder zipIndex.cpp zipIndex.h


g++ -o zipSearch zipsearch.cpp zipIndex.cpp zipIndex.h

./zipIndexbuilder us_postal_codes_length.csv zip_index.txt

./zipsearch us_postal_codes_length.csv zip_index.txt -Z56301

