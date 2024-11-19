#include <iostream> 
#include <iomanip>
#include <cstring>

using namespace std; 

bool isValidBase(char base)
{
    if (base == 'A'|| base == 'C'|| base == 'G'|| base == 'T')
    {
        return true; 
    }
    return false; 
}

bool isValidStrand(string strand)
{
    if (strand.length() == 0)
    {
        return false; 
    }
    for (double i = 0; i < strand.length(); i++)
    {
        bool valid = isValidBase(strand[i]); 
        if (!valid)
        {
            return false; 
        }
        else if (strand[i] == ' ')
        {
            return false; 
        }
    }
    return true; 
}

double strandSimilarity(string strand1, string strand2)
{
    double score; //use later to calculate the score
    double count = 0; //finds how many of the same letters they have at the same position
    //checks if the two strings are the same length 
    //if they are not then return 0, if they are then continue
    if (strand1.length() != strand2.length())
    {
        return 0; 
    }
    else 
    {
        //because they are the same length, you can limit i to any one 
        //of the  strands
        for(double i = 0; i < strand1.length(); i++)
        {
            //if the elements of the the strand at i are the same 
            //then add 1 to count
            if (strand1[i]==strand2[i])
            {
                count++; 
            }
        }
       //takes how many of equal elements are in the same space 
       // and divides it by the length of the strands to find the total score
       //so blank out of the length is equal in the same position
        score = (count/strand1.length()); 
    }
    return score; 
}

int bestStrandMatch(string input_strand, string target_strand)
{
    
    //checks if the input length is smaller than the target length, 
    //if so then return -1 and 0 for simularity score
    if (input_strand.length() < target_strand.length())
    {
        cout<<"Best similarity score: 0.0"<<endl;
        return -1; 
    }
 
    double score = 0; 
    double bestScore = 0; 
    int bestIndex = 0; 
    //loop needs to run until there is no more room to slide the target across the input
    //loops is limitied to input_strand.length() - target_strand.length() cuz the
    //target need to fit the input at each position
    for (unsigned i = 0; i <= input_strand.length() - target_strand.length(); i++)
    {
        //takes a substring from input starting at pos i, 
        //the target length makes sure that the substring is taken from the input
        //is the exact same length as target 
        //as i increases the positon increases only checking the til the end 
        //of the target
       string current = input_strand.substr(i, target_strand.length()); 
    
        //calcuates the score using the standSimilarity function, comparing the 
        //two strings to calc the score
       score = strandSimilarity(current, target_strand); 

       //if the current score is higher then it becomes the bestscore 
       //and the index is stored on where the better score is 
     if (score > bestScore)
        {     
         bestScore = score; //updates best score to score 
         bestIndex = i; //stores the index of the best score
        }
            
        
    }
    cout<<"Best similarity score: "<<bestScore<<endl; 
    return bestIndex; 
}

//trying to turn the input into the target
void identifyMutations(string input_strand, string target_strand)
{
    int bestIndex; 
    string input; 
    string target; 
    int maxLength = max(input_strand.length(), target_strand.length()); 

    if (input_strand.length() > target_strand.length())
    {
        bestIndex = bestStrandMatch(input_strand, target_strand); 
    }
    else
    {
        bestIndex = bestStrandMatch(target_strand, input_strand);
    }

    cout<<"Best alignment index: "<<bestIndex<<endl;
    bool mutationFound = false; 

    for (int i = 0; i < maxLength; i++)
    {
        input+=(".");  
        target+=("."); 
    }
    
    

    if (input_strand.length() < target_strand.length())
    {
        for (unsigned i = 0; i < input_strand.length(); i++)
        {
            input[bestIndex + i] = input_strand[i]; 
        }
        for (unsigned i = 0; i < target_strand.length(); i++)
        {
            target[i] = target_strand[i]; 
        }
    }
    
    else 
    {
        for (unsigned int i = 0; i < target_strand.length (); i++)
        {
            target [bestIndex + i] = target_strand[i]; //fill the target string with the characters in target_strand, startin
        }
        for (unsigned int i = 0; i < input_strand.length(); i++)
        {
            input [i] = input_strand[i];
        }
    }

    for (int i = 0; i < maxLength; i++)
    {
        if (input[i] == '.' && target[i] != '.')
        {
            cout<<"Insertion at position "<< i + 1 << ": "<<target[i] << " is inserted in target strand"<<endl; 
            mutationFound = true; 
        }
        else if (input[i] != '.' && target[i] == '.')
        {
            cout<<"Deletion at position "<< i + 1 << ": "<<input[i] << " is deleted in target strand"<<endl; 
            mutationFound = true; 
        }
        else if ((input[i] != '.' && target[i] != '.') && input[i] != target[i] )
        {
            
            
                cout<<"Substitution at position "<< i + 1 << ": "<<input[i] << " -> "<< target[i] <<endl; 
                mutationFound = true; 
            
        }

    }
 if (!mutationFound)
    {
     cout<<"No mutations found."<<endl; 
    }
}

void transcribeDNAtoRNA(string strand)
{
    string newStrand; //will hold the new strand where T is U
    for (unsigned int i = 0; i < strand.length(); i++)
    {
        if(strand[i] == 'T') //finds if there is a T in the position
        {
            strand[i] = 'U'; //if there is then it will change it to U 
        }
        newStrand += strand[i]; //holds the new strand with updated T -> U 
        //it is outside of loop because if it was inside it would only call the U
        //and no other letters in the stting
    }

    cout<<newStrand<<endl; 
}



void reverseComplement(string strand)
{
   
    //reverse the string and make it into a new one
    string reversed ="";   
    //start it at the strand length - 1 to not account for the 0 base 
    //the loop will run until it meets zero to go through all of the string
    //subtracts by one position each time it loops
    //basically starts at the end of the loop and calls it to the 
    //new reversed string                                         
    for (int i = strand.length() - 1; i >= 0; i-- )
    {
        reversed += strand[i]; //reversed now holds the new reversed string 
    }
   
    //holds the new reversed and changed letters string 
    string newStrandComp = ""; 
    //change the letters of the reversed string to thier complemented counterparts 
    for (unsigned int i = 0; i<reversed.length(); i++)
    {
        if (reversed[i] == 'A') //changes A in the position to T
        {
            reversed[i] = 'T'; 
        }
        else if (reversed[i] == 'T')//changes T in the position to A
        {
            reversed[i] = 'A'; 
        }
        else if (reversed[i] == 'C') //changes C in the position to G
        {
            reversed[i] = 'G'; 
        }
        else if (reversed[i] == 'G')//changes G in the position to C
        {
            reversed[i] = 'C'; 
        }
        newStrandComp += reversed[i]; 
        //newStrandComp now holds the new reversed and 
        //changed letters
    }
    cout<<newStrandComp<<endl; 
    //prints the output because voids do not return anything    
}

/*
void getCodingFrames(string strand) {
    bool readingFrames = false;
 
    unsigned int offset = 0; 
    string codon; 
    for (unsigned int i = 0; i < strand.length()-3; i++) {
        if (i<offset && offset != 0)
        {
            continue;  //does nothing 
        }
        else if (strand.substr(i,3) == "AGT")
        {
            string stringStart = strand.substr(i);
            for (unsigned int j = 0; j < strand.length()-i; j ++) 
            {
                string stringEnd = strand.substr(i+j, 3);
                if (stringEnd == ("TAA")|| stringEnd == ("TGA")|| stringEnd == ("TAG"))
                {
                    if (j % 3 == 0)
                    {
                        readingFrames = true;
                        cout << strand.substr(i+j, 3) << endl;
                        offset = i + j; 
                        break; 
                    }
                    
                }
            }
        }
        
    }

    if (!readingFrames) {
        cout << "No reading frames found." << endl;
    }
 
}
*/
/*
void getCodingFrames(string strand) {
    bool readingFrames = false;

    unsigned int offset = 0; 
    string start_condon = "ATG";
    string end_condon_1 = "TAA";
    string end_condon_2 = "TAG";
    string end_condon_3 = "TGA";

    for (unsigned int i = 0; i < strand.length()-3; i++) {
        if (i < offset && offset != 0) {
            continue;  // skip over the already processed region
        }
        else if (strand.substr(i, 3) == "ATG") {
            string stringStart = strand.substr(i);
            for (unsigned int j = 0; j < strand.length()-i; j += 3) {
                string stringEnd = strand.substr(i+j, 3);
                if (stringEnd == "TAA" || stringEnd == "TAG" || stringEnd == "TGA") {
                    if (j % 3 == 0) {
                        readingFrames = true;
                        cout << strand.substr(i, j + 3) << endl;
                        offset = i + j; 
                    }
                }
            }
        }
    }

    if (!readingFrames) {
        cout << "No reading frames found." << endl;
    }
}
*/
void getCodingFrames(string strand) {

   unsigned int offset = 0;  //tracks positon in strand after valid coding
   bool readingFrames = false;  //finds if the coding frames are found
   
   //loop starts at one trying to find ATG
   for (unsigned int i = 0; i < strand.length() - 3; i++) {
       //skips over the parts that are processed already
       if (i < offset && offset != 0)
        {
         continue;
        }  
       
       //if the first three positions are ATG 
       else if (strand.substr(i, 3) == "ATG") 
       { 
            //then it loops and stops at codon starting positon if i + j and checks for the three endings
           for (unsigned int j = 0; j < strand.length() - i; j++) 
           {
               string stringEnd = strand.substr(i+j, 3); //holds the current three values 

               //checks if the current three values is a valid ending 
               if (stringEnd == "TAA" || stringEnd == "TAG" || stringEnd == "TGA") {
                   if ((j) % 3 == 0) //sees if the string is divisible by 3
                    {
                       
                    
                       cout << strand.substr(i, (j+3)) << endl;  //prints the codon, from the ATG start to the stop ending
                       readingFrames = true;  //becuase it has what we are looking for, it is true that we found reading frames
                       offset = j + i; //skips the ending frame that we just checked for the outer loop 
                       break;  //stops the inner loop and continues to loop for the next start after the current codon frame 
                   }   
               }
           }

       }
       
   }

   if (!readingFrames) 
   { 
    cout << "No reading frames found." << endl; //if no reading frames are found then it prints that 
   }  // 

}

/*
void getCodingFrames(string strand) {
    bool readingFrames = false;

    if(strand.length() % 3 == 0) {
        for(unsigned int i = 0; i < strand.length(); i++) {
            if(i+2 < strand.length() && strand[i] == 'A' && strand[i+1] == 'T' && strand[i+2] == 'G') {
                string stringStart = strand.substr(i);
                for (int j = 0; j < stringStart.length(); j+=3) {
                    if(j + 2 < stringStart.length() && (stringStart[j] == 'T') && (stringStart[j+1] == 'A' || stringStart[j+1] == 'G')) {
                        if(stringStart[j+1] == 'A' || stringStart[j+1] == 'G') {
                            if(stringStart[j+2] == 'A' || (stringStart[j+2] == 'G' && stringStart[j+1]!='G')) {
                                readingFrames = true;
                                cout << stringStart.substr(0, j+3) << endl;
                                break;
                            }
                        }
                    }
                }
                if (readingFrames) {
                    break;
                }
            }
        }
        if (readingFrames == false) {
            cout << "No reading frames found." << endl;
        }
    }
}
*/
//checks function;

int main()
{
    /*
    char base = 'A'; 
    bool validBase = isValidBase(base); 
    cout<<validBase<<endl; 

    string strand = ""; 
    bool validStrand =  isValidStrand(strand); 
    cout<<validStrand<<endl;

    string strand1 = "CTGTAGAGCT"; 
    string strand2 = "TAGCTACCAT"; 
    double strandSim = strandSimilarity(strand1, strand2); 
    cout<<strandSim<<endl; 
    

    string targetStrand = "A";
    string inputStrand = "T";
    //double bestStrand = bestStrandMatch(inputStrand, targetStrand);
    identifyMutations(inputStrand, targetStrand); 
    */

   string strand = "ATGCGTAAATGCGATAGGGTACGATGTAAATGGCTTAAATGTGACGATGGCTTAG"; 
   //transcribeDNAtoRNA(strand); 
   //reverseComplement(strand); 
    getCodingFrames(strand); 

    //reverseComplement(strand); 
    return 0; 

}