#ifndef RNA_H
#define RNA_H

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


#include "DNA.h"
#include "CodonsTable.h"

ostream& operator<< ( ostream& out , RNA_Type atype);// to print the type as a string not 0 , 1 ,2...

class Protein; // add it to be able to use the protein as data type

class RNA : public Sequence
{
    // overloading the operators >> and << to be able to take the data from the user
    friend istream& operator>> (istream& in ,RNA& rna);
    friend ostream& operator<< (ostream& out , RNA rna);


  	private:
        RNA_Type type;
  	public:
 	 	// constructors and destructor
        RNA();
        RNA(string filename , int index);// build the DNA by taking its information from a file using its index as a key
        RNA(char * seq, RNA_Type atype);
        RNA(const RNA& rhs); // copy constructor
        virtual ~RNA();
 	 	// function to be overridden to print all the RNA information
        void Print();
 	 	// function to convert the RNA sequence into protein sequence
        // using the codonsTable object
        Protein ConvertToProtein(CodonsTable & table);
 	 	// function to convert the RNA sequence back to DNA
        DNA ConvertToDNA();
        //// add the DNA information to the end of the file
        void addtoFile(string FileName);
        RNA operator= (const RNA& rhs);// set a DNA using = operator
        char* operator+(RNA &rnaa); // added the seqs of 2 DNAs to be one sequence
        bool operator== (RNA &typee);// to compare between 2 DNAs
        bool operator!= (RNA &typee);// to compare between 2 DNAs

        void loadfromFile(string fileName ,int index); // if i need to take the information
                                                       //of the DNA from a file using its index as a key
};




#endif // RNA_H
