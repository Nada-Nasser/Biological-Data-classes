#include "BiologicalData.h"
#include <fstream>

Protein::Protein(){}

// constructors and destructor
//pareterised constructor to take the type of Protein and the sequence
Protein::Protein(char * p , Protein_Type atype)
{
/**
    for (int i = 0; i < length ; i++)
	{
		if (p[i] != 'A' && p[i] != 'U' && p[i] != 'G' && p[i] != 'C' )
		{
			throw (2);
		}
    }
*/
    type = atype;
    seq = new char [strlen(p) + 1];

    strcpy( seq , p );

    length = strlen( seq );
}

//copy constructor to make deep copy of the Protein sequence when it is sent by value
Protein::Protein(const Protein& p)
{
    type = p.type;
    seq = new char [strlen(seq)];
    strcpy( seq , p.seq );

    length = p.length ;
}
// build the DNA by taking its information from
// a file using its index as a key
Protein::Protein(string fileName , int index)
{
    int atype = loadSeqFromFile(fileName , index);

    switch (atype)
    {
    case 0 :
        type = Hormon;
        break;
    case 1:
        type = Enzyme;
        break;
    case 2:
        type = TF;
        break;
    case 3:
        type = Cellular_Function;
        break;
    }
}
// if i need to take the information
// of the DNA from a file using its index as a key
void Protein::loadfromFile(string fileName , int index)
{
    int atype = loadSeqFromFile(fileName , index);

    switch (atype)
    {
    case 0 :
        type = Hormon;
        break;
    case 1:
        type = Enzyme;
        break;
    case 2:
        type = TF;
        break;
    case 3:
        type = Cellular_Function;
        break;
    }
}

Protein::~Protein()
{}

//overloading == to compare between 2 protein sequences
bool Protein::operator== (Protein rhs){

    if(std::strcmp(seq , rhs.getSeq()) == 0 && type == rhs.type){
        return 1;
    }
    return 0;
}

//overloading != to compare between 2 protein sequences
bool Protein::operator!= (Protein rhs){
    return !(*this == rhs);
}



// return an array of DNA sequences that can possibly
// generate that protein sequence
void Protein::GetDNAStrandsEncodingMe(DNA  & bigDNA , CodonsTable & table)
{
    RNA rna = bigDNA.ConvertToRNA();

    int index = 0 , nStrands = 0;

    for(int i = 0 ; i <= (rna.getlength() - length*3) ; i++)
    {
        char *TempSeq = new char [length*3 + 1];
        TempSeq = subchar(rna.getSeq() , index , length*3);

        Protein FlagProtein = ConvertCharToProtein(TempSeq , table);

        if(FlagProtein == *this)
        {
            cout << TempSeq << endl;

        }
        index ++;
    }
}

/**
char *DNAsubSeq = new char [length*3 + 1];
DNAsubSeq = subchar(bigDNA.getSeq() , index , length*3);

DNA requiredStrand (DNAsubSeq, promoter);
return requiredStrand;

*/
/*
char *DNAsubSeq = new char [length*3];

DNAsubSeq = subchar(bigDNA.getSeq() , index , length*3);

DNA strand(DNAsubSeq , promoter);

ArrayOfStrands[nStrands++] = strand;

delete[] DNAsubSeq;
*/


/*
DNA *requiredStrand = new DNA(TempSeq , promoter);
return requiredStrand;
*/


///*************************************************************************
//overloading operator << so that it can oytput the enum types not as integers but as the types in strings
ostream& operator<< ( ostream& out , Protein_Type atype)
{
    switch (atype)
    {
    case 0 :
        cout << "Hormon" << endl;
        break;
    case 1:
        cout << "Enzyme" << endl;
        break;
    case 2:
        cout << "TF" << endl;
    case 3:
        cout << "Cellular_Function" << endl;
        break;
    default:
        cout<<"no type\n";
        break;
    }
    return out;
}
///________________________________________________________________
//this function takes a char array and return  a new char array from start index and take n chars
char* subchar(char* arr, int start , int n)
{
    char* output = new char [n];

    int index = 0;

    for (int i = 0 ; i < n ; i++)
    {
        output[i] = arr[ index + start ];
        index ++;
    }

    return output;
}

///________________________________________________________________
// convert any char to a protein seq if its valid chars
Protein ConvertCharToProtein(char* Seq , CodonsTable & table)
{
    char *ConvertedSeq = new char[(strlen(Seq)/3)];

    for(int i = 0 , j = 0 ; i < strlen(Seq) ; i+=3 , j++)
    {
        char tempSeq[4] = {Seq[i] ,Seq[i+1] , Seq[i+2]};

        ConvertedSeq[j] = (table.getAminoAcid(tempSeq)).AminoAcid;
    }

    Protein ConvertedProtein(ConvertedSeq, Hormon);

    return ConvertedProtein;
}

void Protein::addtoFile(string FileName){

    int atype;

    switch(type)
    {
    case Hormon:
        atype = 0;
        break;
    case Enzyme:
        atype = 1;
        break;
    case TF:
        atype = 2;
        break;
    case Cellular_Function:
        atype = 3;
        break;
    }

    saveSecToFile(FileName , getSeq() , atype);
}

char* Protein::operator+(Protein &pr)
{
    int length2 = this->length + pr.length;
    char * concSeq = new char [length2];
    int counter = 0;
    for (int i = 0 ; i < length ; i++){
        concSeq[i] = this->seq[i];
    }
    for (int j = length ; j < length2 ; j++){
        concSeq[j] = pr.seq[counter];
        counter++;
    }

	return concSeq;
}

istream& operator>> (istream& in , Protein& pr)
{
    cout << " Enter protein length " << endl;
    in >> pr.length;

    cout << " Enter protein strand " << endl;
    for (int i = 0; i < pr.length; i++){
        in >> pr.seq[i];
    }

    cout << " Enter protein type 0 for Harmon, 1 for Enzyme , 2 for TF , 3 for Cellular_function " << endl;
    int atype;
    in >> atype;

    switch (atype)
    {
    case 0 :
        pr.type = Hormon;
        break;
    case 1:
        pr.type = Enzyme;
        break;
    case 2:
        pr.type = TF;
        break;
    case 3:
        pr.type = Cellular_Function;
        break;
    }

    return in;
}// return istream to be able to get the DNA using the same (cin) Ex : cin >> dna >> dna2 << ...


ostream& operator<< (ostream& out , Protein pr)
{
    out << "The protein is : " << endl;

    for(int i = 0 ; i < pr.length ; i++)
        out << pr.seq[i] ;

    out << "The protein type is : " << endl;
    out << pr.type << endl;

    return out;// return ostream to be able to print the DNA using the same (cout) Ex : cout << dna << dna22 << ...;
}
