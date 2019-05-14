#ifndef DNA_H
#define DNA_H

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


#include "Sequence.h"

#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;


class RNA;

ostream& operator<< ( ostream& out , DNA_Type atype); // to print the type as a string not 0 , 1 ,2...

class DNA : public Sequence
{
private:
    DNA_Type type;
    DNA * complementary_strand;
    int startIndex;
    int endIndex;
public:
    // constructors and destructor
    DNA();
    DNA(string fileName , int index); // build the DNA by taking its information from a file using its index as a key

    DNA(char * seq, DNA_Type atype);
    DNA(const DNA& rhs); //copy constructor
    virtual ~DNA();

    DNA operator= (const DNA& rhs); // set a DNA using = operator
    bool operator== (DNA& rhs); // to compare between 2 DNAs
    bool operator!= (DNA& rhs); // to compare between 2 DNAs
    char* operator+(DNA &rhs); // added the seqs of 2 DNAs to be one sequence

    // function printing DNA sequence information to user
    void Print();
    // function to convert the DNA sequence to RNA sequence
    // It starts by building the complementary_strand of the current
    // DNA sequence (starting from the startIndex to the endIndex), then,
    // it builds the RNA corresponding to that complementary_strand.
    RNA ConvertToRNA();
    // function to build the second strand/pair of DNA sequence
    // To build a complementary_strand (starting from the startIndex to
    // the endIndex), convert each A to T, each T to A, each C to G, and
    // each G to C. Then reverse the resulting sequence.
    void getComp();
    void BuildComplementaryStrand();

    void addtoFile(string FileName);// add the DNA information to the end of the file

    void loadfromFile(string fileName ,int index); // if i need to take the information
                                                   //of the DNA from a file using its index as a key
};


#endif // DNA_H
