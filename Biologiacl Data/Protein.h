#ifndef PROTEIN_H
#define PROTEIN_H

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

ostream& operator<< ( ostream& out , Protein_Type atype); // to print the type as a string not 0 , 1 ,2...

class Protein : public Sequence
{
    // overloading the operators >> and << to be able to take the data from the user
    friend istream& operator>> (istream& in , Protein& pr);
    friend ostream& operator<< (ostream& out , Protein pr);

  	private:
        Protein_Type type;
    public:
 	 	// constructors and destructor
 	 	Protein();
 	 	Protein(string fileName , int index); // build the DNA by taking its information from
                                              // a file using its index as a key
 	 	Protein(char * p , Protein_Type atype);
 	 	Protein(const Protein& protein); // copy constructor

 	 	char* operator+ (Protein &pr); // added the seqs of 2 DNAs to be one sequence
 	 	bool operator== (Protein rhs);// to compare between 2 DNAs
        bool operator!= (Protein rhs);// to compare between 2 DNAs

 	 	virtual ~Protein();
 	 	void Print(){cout << "Protein : "<< seq << "\nType : " << type << endl;}
 	 	// return an array of DNA sequences that can possibly
        // generate that protein sequence
        void GetDNAStrandsEncodingMe(DNA & bigDNA , CodonsTable & table);

        void loadfromFile(string fileName ,int index); // if i need to take the information
                                                       // of the DNA from a file using its index as a key
        void addtoFile(string filename); // add the DNA information to the end of the file

};

char* subchar(char* arr, int start , int n);

Protein ConvertCharToProtein(char* Seq , CodonsTable & table);


#endif // PROTEIN_H
