# Inverted Search

## Overview

Inverted Search is a command-line application developed in C that creates an index of words from multiple text files and enables efficient searching of those words.

The project implements the concept of an **inverted index**, a fundamental data structure used by search engines to quickly locate documents containing a specific word.

Instead of scanning every file during each search operation, the application preprocesses the input files and stores word occurrences in an optimized data structure for faster retrieval.

---

## Features

* Create an index from multiple text files
* Search for a word across all indexed files
* Display the list of files containing the searched word
* Show the number of occurrences of a word in each file
* Save the indexed database to a backup file
* Update the database from a saved backup file
* Avoid duplicate file indexing
* Case-insensitive word search
* Menu-driven command-line interface

---

## Problem Statement

Searching for a word by scanning each file sequentially becomes inefficient as the number of files increases.

An inverted index solves this problem by maintaining:

* A list of unique words
* The files in which each word occurs
* The frequency of occurrence in each file

This significantly reduces search time.

---

## Data Structures Used

The project uses a combination of:

* Hash Table
* Linked Lists

### Hash Table

* Stores indexed words based on hash values
* Enables faster lookup operations

### Linked Lists

Each hash table node contains:

* Word information
* File count
* Linked list of file details

---

## Workflow

1. Read input text files.
2. Validate file availability and avoid duplicates.
3. Tokenize words from each file.
4. Generate hash keys for words.
5. Store words in the hash table.
6. Maintain file names and occurrence counts.
7. Search words using hash-based indexing.
8. Save or update the database when required.

---

## Project Structure

```text
.
├── main.c
├── create_database.c
├── display_database.c
├── search_database.c
├── save_database.c
├── update_database.c
├── file_validation.c
├── hash.c
├── inverted_search.h
├── Makefile
└── sample_files/
```

---

## Hash Function

The hash key is generated using the first character of each word.

Example:

| Word   | Hash Key |
| ------ | -------- |
| apple  | 0        |
| banana | 1        |
| cat    | 2        |

This distributes words into different index positions for efficient searching.

---

## Build Instructions

Compile using GCC:

```bash
gcc *.c -o inverted_search
```

Or use the Makefile:

```bash
make
```

---

## Usage

Run the executable:

```bash
./inverted_search file1.txt file2.txt file3.txt
```

The application provides options to:

1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database
6. Exit

---

## Example Search

Input:

```text
Enter the word to search: data
```

Output:

```text
Word found

File Name        Word Count
--------------------------------
file1.txt        5
file3.txt        2
```

---

## Concepts Covered

* Hash Tables
* Linked Lists
* File Handling
* Dynamic Memory Allocation
* String Manipulation
* Command-Line Arguments
* Data Structures and Algorithms
* Modular Programming

---

## Applications

* Search Engines
* Document Retrieval Systems
* Digital Libraries
* Log Analysis Tools
* Content Management Systems

---

## Future Enhancements

* Support phrase-based searching
* Implement ranking algorithms
* Add wildcard search support
* Develop a graphical user interface
* Export search results to files
* Support larger datasets

---

## Learning Outcomes

This project helped in understanding:

* Inverted indexing techniques
* Efficient data retrieval methods
* Hash table implementation
* Dynamic memory management
* File parsing and tokenization
* Designing scalable search systems

---

## Author

**Pardha Sai**

GitHub: https://github.com/Pardhasai28
