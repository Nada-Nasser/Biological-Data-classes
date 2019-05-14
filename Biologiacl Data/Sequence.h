#ifndef SEQUENCE_H
#define SEQUENCE_H

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

#include <cstring>
#include <cctype>
#include <string>
#include <fstream>

#include <iostream>
using namespace std;

enum DNA_Type{promoter, motif, tail, noncoding};
enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};
enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};

class Sequence
{
  	protected:
        char * seq;
        int length;
    public:
 	 	// constructors and destructor
        Sequence();
        Sequence(int length);
        Sequence(Sequence& rhs);

        virtual ~Sequence();

 	 	// pure virtual function that should be overridden because every
        // type of sequence has its own details to be printed
        virtual void Print()= 0;

 	 	// friend function that will find the LCS (longest common
        // subsequence) between 2 sequences of any type, according to
        // polymorphism
        friend char* Align(Sequence * s1, Sequence * s2);
        friend char* globalAlign(Sequence * s1, Sequence * s2);

        // take from user the file name and the index of the sequence as a key to load its information in an object
        int loadSeqFromFile(string filename , int index);
        // add the sequence to the end of the file
        void saveSecToFile(string filename , char* InSeq , int dataType);

        int getlength(){return length;}
        char* getSeq() {return seq;}
};

//int saveSecToFile(string filename , char* InSeq , int dataType);
#endif // SEQUENCE_H
