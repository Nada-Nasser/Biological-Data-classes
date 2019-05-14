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

#include "BiologicalData.h"

using namespace std;

void startingOne();
void SecondOptions();
void RNAOptions();
void ProteinChoices();

int main()
{
    CodonsTable table;

    int choice , SecondChoice;
try{
    while(true){
        startingOne();
        cin >> choice;
        if(choice == 1){
            int index;
            cout << "Write the key of the required DNA : ";
            cin >> index;
            DNA dna("DNAFile.txt" , index);
            while(true){
                SecondOptions();
                cin >> SecondChoice;
                if(SecondChoice == 1){
                    (dna.ConvertToRNA()).Print();
                }
                if(SecondChoice == 2){
                    cout << "Write the key of the second DNA : ";
                    cin >> index;
                    DNA SecondDNA("DNAFile.txt" , index);
                    cout << "DNA 1 == DNA 2 ?" << (dna==SecondDNA) << endl;
                    cout << "DNA 1 != DNA 2 ?" << (dna!=SecondDNA) << endl;
                }
                if(SecondChoice == 3){
                    cout << "Write the key of the second DNA : ";
                    cin >> index;
                    DNA SecondDNA("DNAFile.txt" , index);
                    cout << (dna + SecondDNA) << endl;
                }
                if(SecondChoice == 4){
                    dna.addtoFile("DNAFile.txt");
                }
                if(SecondChoice == 5){
                    cout << "Write the key of the new DNA : ";
                    cin >> index;
                    dna.loadfromFile("DNAFile.txt" , index);
                }
                if(SecondChoice == 6){
                    break;
                }
                if(SecondChoice == 7){
                    dna.Print();
                }
            }
        }
        if(choice == 2){
            int index;
            cout << "Write the key of the required RNA : ";
            cin >> index;
            RNA rna("RNAFile.txt" , index);
            while(true){
                RNAOptions();
                cin >> SecondChoice;
                if(SecondChoice == 1){
                    (rna.ConvertToDNA()).Print();
                }
                if(SecondChoice == 2){
                    cout << "Write the key of the second RNA : ";
                    cin >> index;
                    RNA SecondRNA("RNAFile.txt" , index);
                    cout << "RNA 1 == RNA 2 ? " << (rna==SecondRNA) << endl;
                    cout << "RNA 1 != RNA 2 ? " << (rna!=SecondRNA) << endl;
                }
                if(SecondChoice == 3){
                    cout << "Write the key of the second RNA : ";
                    cin >> index;
                    RNA SecondRNA("RNAFile.txt" , index);
                    cout << (rna + SecondRNA) << endl;
                }
                if(SecondChoice == 4){
                    rna.addtoFile("RNAFile.txt");
                }
                if(SecondChoice == 5){
                    cout << "Write the key of the new DNA : ";
                    cin >> index;
                    rna.loadfromFile("RNAFile.txt" , index);
                }
                if(SecondChoice == 6){
                    break;
                }
                if(SecondChoice == 7){
                    rna.Print();
                }
                if(SecondChoice == 8){
                    cout << "protein : " << endl;
                    (rna.ConvertToProtein(table)).Print();
                }
            }
        }
        if(choice == 3){
            int index;
            cout << "Write the key of the required Protein : ";
            cin >> index;
            Protein prt("ProteinFile.txt" , index);
            while(true){
                RNAOptions();
                cin >> SecondChoice;
                if(SecondChoice == 1){
                    cout << "Write the key of the DNA you need : ";
                    cin >> index;
                    DNA dna("DNAFile.txt" , index);
                    prt.GetDNAStrandsEncodingMe(dna , table);
                }
                if(SecondChoice == 2){
                    cout << "Write the key of the second RNA : ";
                    cin >> index;
                    Protein SecondProtein("ProteinFile.txt" , index);
                    cout << "Protein 1 == Protein 2 ? " << (prt==SecondProtein) << endl;
                    cout << "Protein 1 != Protein 2 ? " << (prt!=SecondProtein) << endl;
                }
                if(SecondChoice == 3){
                    cout << "Write the key of the second RNA : ";
                    cin >> index;
                    Protein SecondProtein("ProteinFile.txt" , index);
                    cout << (prt + SecondProtein) << endl;
                }
                if(SecondChoice == 4){
                    prt.addtoFile("ProteinFile.txt");
                }
                if(SecondChoice == 5){
                    cout << "Write the key of the new Protein : ";
                    cin >> index;
                    prt.loadfromFile("ProteinFile.txt" , index);
                }
                if(SecondChoice == 6){
                    break;
                }
                if(SecondChoice == 7){
                    prt.Print();
                }
            }
        }
        if(choice == 4){
            return 0;
        }
    }
}
catch(int i)
{
    cout << "Something went wrong here" << endl;
}

}


void startingOne(){
    cout << "Which Type of sequences you want to work on now :" << endl;
    cout << "1- DNA"     << endl
         << "2- RNA"     << endl
         << "3- Protein" << endl
         << "4- Exit"    << endl;
}

void SecondOptions(){
    cout << "What do you want to do ? "         << endl;
    cout << "1- Convert to (DNA -> RNA)"        << endl
         << "2- Compare between two sequences?" << endl
         << "3- Concatenate two DNAs"           << endl
         << "4- Add to file"                    << endl
         << "5- Load a new one from the file"   << endl
         << "6- Return to the previous menu "   << endl
         << "7- Print"                          << endl;
}

void RNAOptions(){
    cout << "What do you want to do ? "                  << endl;
    cout << "1- Convert to (RNA -> DNA) or (DNA -> RNA)" << endl
         << "2- Compare between two sequences?"          << endl
         << "3- Concatenate two RNAs"                    << endl
         << "4- Add to file"                             << endl
         << "5- Load a new one from the file"            << endl
         << "6- Return to the previous menu "            << endl
         << "7- Print"                                   << endl
         << "8- Convert to (RNA -> protein)"             << endl;
}

void ProteinChoices(){
    cout << "What do you want to do ? "                << endl ;
    cout << "1- GAT the DNA strand from this Protein " << endl
         << "2- Compare between two sequences?"        << endl
         << "3- Concatenate two Proteins"              << endl
         << "4- Add to file"                           << endl
         << "5- Load a new one from the file"          << endl
         << "6- Return to the previous menu "          << endl
         << "7- Print"                                 << endl;
}

