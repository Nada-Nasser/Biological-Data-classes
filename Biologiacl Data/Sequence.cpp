#include "Sequence.h"
#include <algorithm>

// constructors and destructor
Sequence::Sequence()
{
}

Sequence::Sequence(int length)
{
//    this -> length = length;
}

Sequence::Sequence(Sequence& rhs)
{
    length = rhs.length;

    delete []seq;
    seq = new char[rhs.length];
    seq = rhs.seq;
}

Sequence::~Sequence()
{
    delete []seq;
}


// friend function that will find the LCS (longest common
// subsequence) between 2 sequences of any type, according to
// polymorphism
char* Align(Sequence * s1, Sequence * s2)
{
    char *seq1 = new char [s1-> length];
    char *seq2 = new char [s2-> length];
    char *LCS;

     for(int i = 0 ; i < s1->length ; i++ ){
        seq1[i] = s1->seq[i];
    }
    for(int i = 0 ; i < s2->length ; i++ ){
        seq2[i] = s2->seq[i];
    }

    int seq1Size = s1-> length;
    int seq2Size = s2-> length;

    int intMatrix[seq1Size + 1][seq2Size + 1];

    for( int i = 0 ; i < seq1Size + 1 ; i++)///intializing the intMatrix with zeros
    {
        for( int j = 0 ; j < seq2Size + 1 ; j++)
        {
            intMatrix [i][j] = 0;
        }
    }

    for( int i = 1 ; i < seq1Size + 1 ; i++ )
    {
        for(int j = 1 ; j < seq2Size + 1 ; j++)
        {
            if( seq1[i - 1] == seq2[j - 1] )
                intMatrix[i][j] = intMatrix[i - 1][j - 1] + 1;

            else if( intMatrix[i - 1][j] > intMatrix[i][j - 1] )
                intMatrix[i][j] = intMatrix[i - 1][j];

            else
                intMatrix[i][j] = intMatrix[i][j - 1];

        }
    }

    int LCSsize = intMatrix[seq1Size][seq2Size];

    LCS = new char [LCSsize];
    int k=0;

    for( int i = seq1Size - 1 ; i >= 0 ; i-- )
    {
        for( int j = seq2Size - 1 ; j >= 0 ; j-- )
        {
            if( intMatrix[i][j] != intMatrix[i - 1][j - 1] )
            {
                LCS[k++] = seq1[i];
                i = i - 1;
                j = j - 1;
                break;
            }

        }
    }

    LCS[LCSsize]='\0';
    reverse (LCS,LCS +LCSsize);

    return LCS;
}

// friend function that will find the LCS (longest common
// subsequence) between 2 sequences of any type, according to
// polymorphism
char* globalAlign(Sequence * s1, Sequence * s2){

   char *seq1 , *seq2;

    seq1 = new char [s1->length];
    seq2 = new char [s2->length];

    for(int i = 0 ; i < s1->length ; i++ ){
        seq1[i] = s1->seq[i];
    }
    for(int i = 0 ; i < s2->length ; i++ ){
        seq2[i] = s2->seq[i];
    }


    cout << seq1 << " " << seq2 << endl;
    int intMat[s1->length+1][s2->length+1];
    int seq1Size = s1->length+1;
    int seq2Size = s2->length+1;

    for(int i = 0  ; i < seq1Size ; i++ )
    {
        for(int j = 0 ; j < seq2Size ; j++ )
        {
            intMat[i][j] = 0;
        }
    }

    for(int i = 1  ; i < seq1Size ; i++ )
    {
        intMat[i][0] = intMat[i-1][0] - 1;
        for(int j = 1 ; j < seq2Size ; j++ )
        {
            intMat[0][j] = intMat[0][j-1] - 1;
        }
    }
    int choice[3];

    for (int i = 1 ; i < seq1Size ; i++ ) ///"GCATGCU" ,"GATTACA"
    {
        for (int j = 1 ; j < seq2Size ; j++)
        {
            if ( seq1[i-1] == seq2[j-1] )
            {
                choice[0] = intMat [i-1][j-1] + 1;
                choice[1] = intMat [i][j-1] - 1;
                choice[2] = intMat [i-1][j] - 1;
                intMat[i][j] = *max_element (choice,choice+3);
            }
            else
            {
                choice[0] = intMat [i-1][j-1] - 1;
                choice[1] = intMat [i][j-1] - 1;
                choice[2] = intMat [i-1][j] - 1;
                intMat[i][j] = *max_element (choice,choice+3);
            }
        }
    }


    char *result = new char[100];
    int k = 2,choice1[3];

    result[0] = '/0';
    result[1] = seq2[seq2Size - 2];

    int i = seq1Size - 2;
    int j = seq2Size - 2;

    for( i ; i > 0 ;  ){
        for( j ; j > 0 ; ){
            if(seq1[i-1] == seq2[j-1] )
            {
                choice1[0] = intMat[i-1][j-1] + 1;
                choice1[1] = intMat[i-1][j] - 1;
                choice1[2] = intMat[i][j-1] - 1;
            }
            else
            {
                choice1[0] = intMat[i-1][j-1] - 1;
                choice1[1] = intMat[i-1][j] - 1;
                choice1[2] = intMat[i][j-1] - 1;

            }

            if( &choice1[0] == max_element (choice1,choice1+3))
            {
                result [k++] = seq2[j-1];
                i--;
                j--;
                break;
            }
            else if( &choice1[1] == max_element (choice1,choice1+3))
            {
                result [k++] = '-';
                i--;
                break;

            }
            else if(&choice1[2] == max_element (choice1,choice1+3))
            {
                result [k++] = seq2[i];
                j--;
                break;
            }
        }
    }
    reverse(result,result+k);

    cout << result;

    return result;
}

// take from user the file name and the index of the sequence as a key to load its information in an object
int Sequence::loadSeqFromFile(string fileName, int index)
{
    ifstream SequenceFlie;
    SequenceFlie.open(fileName, ios::in);

    int indx = 0;
    string newSeq;
    int atype;
    int line = 0;

    while(!SequenceFlie.eof() && !SequenceFlie.fail())
    {
        SequenceFlie >> indx >> newSeq >> atype;
            if(index == indx)
                break;
    }

    length = newSeq.size();

    seq = new char [newSeq.size()];
    for(int i = 0 ; i < newSeq.size() ; i++)
        seq[i] = newSeq[i];

    return atype;
}

// add the sequence to the end of the file
void Sequence::saveSecToFile(string filename, char* InSeq, int dataType)
{
    ifstream readDatafile;
    readDatafile.open(filename, ios::in );

    int index = 6, atype;

    string data;

    while(!readDatafile.eof() && !readDatafile.fail())
    {
        readDatafile >> index >> data >> atype;
    }
    readDatafile.close();

    ofstream AddtoFile;
    AddtoFile.open(filename, ios::out | ios::app);

    AddtoFile << endl << index+1 << "  " << InSeq << "  " << dataType;

}
