#ifndef CODONSTABLE_H
#define CODONSTABLE_H

/*
Course:  CS213 - Programming II  - 2018
Title:   Assignment III
Program: CS213-2018-A4
Purpose: dealing Biological Data  sequences
Authors: 1- Name :- Nada Nasser Al-Said El-Azab .................. ID :- 20170369
         2- Name :- Hanan Mohamed Abd-El-Rahim  .................. ID :- 20170375
         3- Name :- Farah Mohamed Osama Mostafa .................. ID :- 20170351
         4- Name :- Aya Tarek .................................... ID :- 20170069
Date:    13 December 2018
Version: 2.0
*/


#include <iostream>
using namespace std;

// struct representing a codon of 3 DNA/RNA characters and ‘\0’
struct Codon
{
  	char value[4] = "...";    	// 4th location for null character
    char AminoAcid = '.';  	    // corresponding AminoAcid according to Table

    bool operator== (Codon);
    bool operator!= (Codon);
    void showCodon();
};

bool isValid(char value[3], char AminoAcid); // to be sure that the char array contain just a valid char of protein sequences

///----------------------------------------------------------------------------------------

// need to create one object of that class to load the AminoAcids table
// into memory
class CodonsTable
{
  	private:
        Codon codons[64];//Codons array that contain all AminoAcid and its value from the table
   	public:
 	 	// constructors and destructor
        CodonsTable();
        ~CodonsTable();
 	 	// function to load all codons from the given text file
        void LoadCodonsFromFile(string codonsFileName); // take the table filename and load it to the array
        Codon getAminoAcid(char * value); //looking for a codon using its AminoAcid

        void setCodon(char * value, char AminoAcid, int index);// if i need to add a codon to the table
};


#endif // CODONSTABLE_H
