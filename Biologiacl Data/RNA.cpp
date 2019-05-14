#include "BiologicalData.h"
#include <fstream>
// constructors and destructor
RNA::RNA(){}
///____________________________________________________________________________
// constructors
RNA::RNA(char * seq, RNA_Type atype)
{
    type = atype;
    this->seq = new char[length];
    strcpy( this-> seq , seq );
    length = strlen( seq );

/**
    for (int i = 0; i < length ; i++)
	{
		if (seq[i] != 'A' && seq[i] != 'U' && seq[i] != 'G' && seq[i] != 'C' )
		{
			throw (2);
		}
    }
    */

}
///____________________________________________________________________________

// build the DNA by taking its information from a file using its index as a key
RNA::RNA(string fileName , int index)
{
    int atype = loadSeqFromFile(fileName , index);

    switch (atype)
    {
    case 0 :
        type = mRNA;
        break;
    case 1:
        type = pre_mRNA;
        break;
    case 2:
        type = mRNA_exon;
        break;
    case 3:
        type = mRNA_intron;
        break;
    }
}

//Copy constructor ;-
RNA::RNA(const RNA& rhs)
{
    type = rhs.type;
    seq = new char[rhs.length];
    strcpy(seq , rhs.seq);

    length = rhs.length;

}
///____________________________________________________________________________
// if i need to take the information
//of the DNA from a file using its index as a key
void RNA::loadfromFile(string fileName ,int index){

    int atype = loadSeqFromFile(fileName , index);

    switch (atype)
    {
    case 0 :
        type = mRNA;
        break;
    case 1:
        type = pre_mRNA;
        break;
    case 2:
        type = mRNA_exon;
        break;
    case 3:
        type = mRNA_intron;
        break;
    }
}
///____________________________________________________________________________

//overloading the assignment operator so that it does deep copy
RNA RNA:: operator= (const RNA& rhs)
{
    type = rhs.type;
    seq = new char[rhs.length];
    seq = rhs.seq;

    length = rhs.length;

    return *this;
}
///____________________________________________________________________________

RNA::~RNA()
{}

///____________________________________________________________________________
// function to be overridden to print all the RNA information
void RNA:: Print()
{
    cout << "RNA : " << endl;

    for(int i = 0 ; i < length ; i++ )
    {
        cout << seq[i];
    }
    cout << endl;
    cout << "the Type of RNA is : " << type <<endl;
}
///____________________________________________________________________________

// function to convert the RNA sequence into protein sequence
// using the codonsTable object
Protein RNA::ConvertToProtein(CodonsTable & table)
{
    char *ConvertedSeq = new char[(length/3) + 1];

    for(int i = 0 , j = 0 ; i < length ; i+=3 , j++)
    {
        char tempSeq[4] = {seq[i] ,seq[i+1] , seq[i+2]};
        ConvertedSeq[j] = (table.getAminoAcid(tempSeq)).AminoAcid;
    }

    Protein ConvertedProtein(ConvertedSeq, Hormon);

    return ConvertedProtein;

}
///____________________________________________________________________________

// function to convert the RNA sequence back to DNA
DNA RNA::ConvertToDNA()
{
    char *dnaSeq = new char [length];
    strcpy(dnaSeq,seq);

    for (int i = 0 ; i < length ; i++ )
    {
        if (seq[i] == 'U')
            dnaSeq[i] = 'T';
        else
            dnaSeq[i] = seq[i];
    }

    DNA dna (dnaSeq , promoter );

    return dna;
}

///***********************************************************************

ostream& operator<< ( ostream& out , RNA_Type atype)
{
    switch (atype)
    {
    case 0 :
        cout << "mRNA" << endl;
        break;
    case 1:
        cout << "pre_mRNA" << endl;
        break;
    case 2:
        cout << "mRNA_exon" << endl;
        break;
    case 3:
        cout << "mRNA_intron" << endl;
        break;
    }

    return out;
}
///____________________________________________________________________________
 //// add the RNA information to the end of the file
void RNA::addtoFile(string FileName){

    int atype;

    switch(type)
    {
    case mRNA:
        atype = 0;
        break;
    case pre_mRNA:
        atype = 1;
        break;
    case mRNA_exon:
        atype = 2;
        break;
    case mRNA_intron:
        atype = 3;
        break;
    }

    saveSecToFile(FileName , getSeq() , atype);
}

// overloading the operators >> and << to be able to take the data from the user
istream& operator>> (istream& in ,RNA& rna)
{
   cout << " Enter RNA length " << endl;
   in >> rna.length;
   cout << " Enter RNA strand " << endl;
   for (int i = 0; i < rna.length; i++){
        in >> rna.seq[i];
   }
   cout << " Enter RNA type " << endl;
   int atype;
   in >> atype;

    switch (atype)
    {
    case 0 :
        rna.type = mRNA;
        break;
    case 1:
        rna.type = pre_mRNA;
        break;
    case 2:
        rna.type = mRNA_exon;
        break;
    case 3:
        rna.type = mRNA_intron;
        break;
    }

    return in;
}// return istream to be able to get the DNA using the same (cin) Ex : cin >> dna >> dna2 << ...

ostream& operator<< (ostream& out , RNA rna)
{
    out << "The RNA is : " << endl;

    for(int i = 0 ; i < rna.length ; i++)
    {
        out << rna.seq[i] ;
    }

    out << "The RNA type is : " << endl;

    out << rna.type << endl;

    return out;// return ostream to be able to print the RNA using the same (cout) Ex : cout << dna << dna22 << ...;
}


// added the seqs of 2 DNAs to be one sequence
char* RNA :: operator+(RNA &rnaa)
{
    int length2 = this->length + rnaa.length;

    char * concSeq = new char [length2];

    int counter = 0;

    for (int i = 0 ; i < length ; i++){
        concSeq[i] = this->seq[i];
    }

    for (int j = length ; j < length2 ; j++){
        concSeq[j] = rnaa.seq[counter];
        counter++;
    }

    return concSeq;
}

// to compare between 2 DNAs
bool RNA :: operator== (RNA &typee)
{
    for(int  i = 0 ; i < length ; i++ )
    {
        if(( this->seq[i] != typee.seq[i] ) || ( this->type != typee.type ))
            return 0;
    }
    return 1;
}

// to compare between 2 DNAs
bool RNA :: operator!= (RNA &type2){

    return !(*this == type2);
}
