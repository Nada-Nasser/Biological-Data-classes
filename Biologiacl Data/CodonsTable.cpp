#include "CodonsTable.h"

#include <fstream>
#include <cstring>
#include <cctype>
#include <string>

void Codon ::showCodon()
{
    cout << value << "  " << AminoAcid << endl;
}

bool Codon :: operator== (Codon codn)
{
    if(codn.AminoAcid != this -> AminoAcid){
        return 0;
    }

    for(int j = 0 ; j < 3 ; j++)
        if(this->value[j] != codn.value[j])
            return 0;

    return 1;
}
///___________________________________________________________

bool Codon :: operator != (Codon codn)
{
    return !(*this == codn);
}

///___________________________________________________________

bool isValid(char value[3], char AminoAcid){

    Codon tempCodon;
    tempCodon.AminoAcid = AminoAcid;
    for(int i = 0 ; i < 3 ; i++ ){
        tempCodon.value[i] = value[i];
    }
    CodonsTable table;

    for(int i = 0 ; i < 64 ; i++){
        if(tempCodon == table.getAminoAcid(value))
        {
            return 1;
        }
    }

    return 0;
}
//___________________________________________________________

///***************************************************************
CodonsTable::CodonsTable()
{
    LoadCodonsFromFile("CodonsTable.txt");
}
///___________________________________________________________
// constructors and destructor
CodonsTable::~CodonsTable()
{}
//___________________________________________________________
// function to load all codons from the given text file
void CodonsTable::LoadCodonsFromFile(string codonsFileName)
{
    ifstream AminoAcidsTable;
    AminoAcidsTable.open(codonsFileName , ios::in);

    int nOfCodons = 0 ;

    while(!AminoAcidsTable.eof() && !AminoAcidsTable.fail() && nOfCodons < 64)
    {
        string data = "";
        AminoAcidsTable >> data;

        for(int i = 0 ; i < 3 ; i++){
            codons[nOfCodons].value[i] = data[i];
        }

        if(data.size() == 3)
            codons[nOfCodons].AminoAcid = '\t';
        else
            codons[nOfCodons].AminoAcid = data[3];

        nOfCodons++;
    }

    AminoAcidsTable.close();
}
//________________________________________________________________________________

Codon CodonsTable::getAminoAcid(char * value)
{
    for(int i = 0 ; i < 64 ; i++)
    {
        if(std::strcmp(value , codons[i].value) == 0){
            return codons[i];
        }

    }

    cout << "there is NO CODON has this value .." << endl; /// if this line printed then there is something wrong with the input
                                                           /// because there is no way find a value does not have an Aminoacide
}
//_________________________________________________________________________________
void CodonsTable::setCodon(char * value, char AminoAcid, int index)
{
    if(index < 1 || index > 64){
        return;
    }
    for(int i = 0 ; i < 3 ; i++){
        this -> codons[index-1].value[i] = value[i];
    }
    this -> codons[index-1].AminoAcid = AminoAcid;
}
//_____________________________________________________________________________

