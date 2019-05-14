#include "BiologicalData.h"
#include <fstream>

DNA::DNA()
{
    length = 0;
}

// build the DNA by taking its information from a file using its index as a key
DNA::DNA(string fileName , int index)
{
    int atype = loadSeqFromFile(fileName , index );
    getComp();

    switch (atype)
    {
    case 0 :
        type = promoter;
        break;
    case 1:
        type = motif;
        break;
    case 2:
        type = tail;
        break;
    case 3:
        type = noncoding;
        break;
    }
}

// if i need to take the information
// of the DNA from a file using its index as a key
void DNA::loadfromFile(string fileName ,int index){

    int atype = loadSeqFromFile(fileName , index );

    getComp();

    switch (atype)
    {
    case 0 :
        type = promoter;
        break;
    case 1:
        type = motif;
        break;
    case 2:
        type = tail;
        break;
    case 3:
        type = noncoding;
        break;
    }
}

DNA::DNA(char * seq, DNA_Type atype)
{
    this -> type = atype;
    this -> seq = new char [strlen( seq)];
    this -> seq = seq;
    this -> length = strlen(seq);

    for (int i = 0; i < length ; i++)
	{
		if (seq[i] != 'A' && seq[i] != 'T' && seq[i] != 'G' && seq[i] != 'C' )
		{
			throw (1);
		}
    }

    getComp();
}

//Copy constructor
DNA::DNA(const DNA& rhs)
{
    this-> type = rhs.type;
    this-> length = rhs.length;

    seq = new char[length];
    strcpy(seq,rhs.seq);

    this-> complementary_strand = new DNA;
    this-> complementary_strand->seq = new char[length];
    this-> complementary_strand-> length = length;

    strcpy(complementary_strand-> seq ,rhs.complementary_strand-> seq);

}

//// set a DNA using = operator
DNA DNA::operator= (const DNA& rhs)
{
    this-> type = rhs.type;
    this-> length = rhs.length;

    seq = new char[length];
    strcpy(seq,rhs.seq);

    this-> complementary_strand = new DNA;
    this-> complementary_strand->seq = new char[length];
    this-> complementary_strand-> length = length;

    strcpy(complementary_strand-> seq ,rhs.complementary_strand-> seq);
}

// to compare between 2 DNAs
bool DNA:: operator== (DNA& rhs)
{
    if(std::strcmp(seq , rhs.getSeq()) == 0 && type == rhs.type){
        return 1;
    }
    else return 0;
}
// to compare between 2 DNAs
bool DNA:: operator!= (DNA& rhs)
{
    return !(*this == rhs);
}

DNA::~DNA()
{}

// function printing DNA sequence information to user
void DNA::Print(){

    startIndex = 1;
    endIndex = length;

    cout << "DNA: ";
    for(int i = startIndex - 1 ; i < endIndex ; i++ )
    {
        cout << seq[i];
    }
    cout << endl;

    cout << "The Complementary Sequence : ";
    for(int i = startIndex - 1 ; i < endIndex  ; i++ ){
        cout << complementary_strand -> seq[i];
    }
    cout << endl;
    cout << "The DNA Type is : " << type << endl;

}

// function to convert the DNA sequence to RNA sequence
// It starts by building the complementary_strand of the current
// DNA sequence (starting from the startIndex to the endIndex), then,
// it builds the RNA corresponding to that complementary_strand.
RNA DNA::ConvertToRNA()
{
    char *RNAseq = new char [length + 1];

    for(int i = 0 ; i < length ; i++){
         RNAseq[i] = seq[i];
    }

    for(int i = 0 ; i < length ; i++)
    {
        if (seq[i] == 'T')
            RNAseq[i] = 'U';
        else
            RNAseq[i] = seq[i];
    }

    RNA rna ( RNAseq , mRNA );

    return rna;
}
// function to build the second strand/pair of DNA sequence
// To build a complementary_strand (starting from the startIndex to
// the endIndex), convert each A to T, each T to A, each C to G, and
// each G to C. Then reverse the resulting sequences
void DNA::getComp()
{
    complementary_strand = new DNA;
    complementary_strand -> seq = new char[length];
    complementary_strand -> length = length ;

    for(int  i = 0 ; i < length ; i++ ){
        if( seq[i] == 'T' )
            complementary_strand->seq[i] = 'A';
        else if(seq[i] == 'A' )
            complementary_strand->seq[i] = 'T';
        else if(seq[i] == 'C' )
            complementary_strand->seq[i] = 'G';
        else if(seq[i] == 'G' )
            complementary_strand->seq[i] = 'C';
    }

    char * tempSeq = new char [length + 1];

    for (int i = 0 ; i < length ; i++){
        tempSeq[i] = complementary_strand->seq[length-i-1];
    }

    for (int i = 0 ; i < length ; i++){
        complementary_strand->seq[i] = tempSeq[i];
    }

    delete[] tempSeq;

}

// function to build the second strand/pair of DNA sequence
// To build a complementary_strand (starting from the startIndex to
// the endIndex), convert each A to T, each T to A, each C to G, and
// each G to C. Then reverse the resulting sequence.
void DNA:: BuildComplementaryStrand()
{

    cout << "Write the start index you want to complement = ";
    cin >> startIndex;
    cout << "Write the end index you want to complement = ";
    cin >> endIndex;

    if(startIndex == -1 && endIndex == -1){
        startIndex = 0;
        endIndex = length-1;
    }

    cout << "The complimented part of the DNA is : ";
    for (int i = startIndex - 1 ; i < endIndex ; i++ )
        cout << complementary_strand -> seq[i];


     cout<< endl;
}

///************************************************************************************
/// Extra Helpful Function :
//overloading operator << so that it can output the DNA types not as numbers bit as strings
ostream& operator<< ( ostream& out , DNA_Type atype)
{
    switch (atype)
    {
    case 0 :
        cout << "Promoter" << endl;
        break;
    case 1:
        cout << "motif" << endl;
        break;
    case 2:
        cout << "tail" << endl;
        break;
    case 3:
        cout << "nonCoding" << endl;
        break;
    }
    return out;
}


void DNA::addtoFile(string FileName)
{
    int atype;

    // Convert The type of the seq to an int number to be able to represent it in the file
    switch(type)
    {
    case promoter:
        atype = 0;
        break;
    case motif:
        atype = 1;
        break;
    case tail:
        atype = 2;
        break;
    case noncoding:
        atype = 3;
        break;
    }

    // add the seq to the end of the file
    saveSecToFile(FileName , getSeq() , atype);
}

char* DNA::operator+(DNA &rhs)
{
    int length2 = this->length + rhs.length;
    char * concSeq = new char [length2];
    int counter = 0;
    for (int i = 0 ; i < length ; i++){
        concSeq[i] = this->seq[i];
    }
    for (int j = length ; j < length2 ; j++){
        concSeq[j] = rhs.seq[counter];
        counter++;
    }

	return concSeq;
}




