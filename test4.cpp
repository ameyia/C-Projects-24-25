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
    
    string input; //used for fillers for the input strand
    string target; //used for fillers for the target strand

    //compares two DNA sequences to identify all types of mutations between them 
    int bestIndex = bestStrandMatch(input_strand, target_strand); 
    
    //stores length of longer string; built in fucntion max 
    int maxLength = max(input_strand.length(), target_strand.length()); 
    
    
    //does not return -1 from the bestStrandMatch function and goes out of scope 
    //makes sure that bestStrandMatch //to find the longest strand and 
    if(input_strand.length() > target_strand.length())
    {
        bestIndex = bestStrandMatch(input_strand, target_strand);  
    }

    else if(input_strand.length() < target_strand.length())
    {
        bestIndex = bestStrandMatch(target_strand, input_strand);  
    
    }
    //add the best alignment positon where the best index is 
    cout<<"Best alignment index: "<<bestIndex<<endl; 
    
    //aligning the strings
    //aligns them by finding the best index and setting the input there 
    //and it only goes up until however long the target strand is 
    //position is at the best index 
    //length is how long the target strand is 
    //aligned index is only the length of target, and disregards the 
    //letters before/after the input
    //string alignedInput = input_strand.substr(bestIndex, target_strand.length());  
    
    for (int i = 0; i < maxLength; i++)
    {
        input.append("."); 
        
    }
    for (int i = 0; i < maxLength; i++)
    {
        target.append("."); 
    }
    //will use in the for loop to see if there is a mutation 
    bool mutationFound = false; 
    
    //checks to see if the bestStrandMatch function is longer, then fills the strings so the characters line up
    //with the bestindex alignment
    if(input_strand.length() < target_strand.length())
    {
        for(unsigned int i = 0; i< input_strand.length(); i++)
        {
        
            input[bestIndex + i] = input_strand[i]; 
        }
        for (unsigned int i = 0; i<target_strand.length(); i++)
        {
           
            target[i] = target_strand[i]; 
        }
    }
    else if (target_strand.length() < input_strand.length())//if the target is longer than the input 
    {
        for (unsigned int i = 0; i < target_strand.length(); i++)
        {
            target[bestIndex + i] = target_strand[i]; 
        }
        for (unsigned int i = 0; i < input_strand.length(); i++)
        {
            input[i] = input_strand[i]; 
        }
    }

    //loops to go through position, as the code is ordered by position
    for (int i = 0; i < maxLength; i++)
    {
    
        if (input[i] == '.' && target[i] != '.')
        {
            cout<<"Insertion at position " << i + 1 << ": "<<target[i]<< " is inserted in target strand"<<endl; 
            mutationFound = true;  
        }
        else if (input[i] != '.' && target[i] == '.')
        {
            cout<<"Deletion at position "<<i + 1<<": "<<input[i]<<" is deleted in target strand"<<endl;
            mutationFound = true;
        }
        
        else if (input[i] != '.' && target[i] != '.')
        {
         if (input[i] != target[i])
        {
            cout << "Substitution at position " << i + 1 << ": " <<input[i] << " -> " << target[i] << endl; 
            mutationFound = true; 
        }
        }
    }

 if (!mutationFound)
    {
     cout<<"No mutations found."<<endl; 
    }
}

/*

void reverseComplement(string strand)
{
    for (int i = 0; i<strand.length(); i++)
    {
        if (strand[i] == 'A')
        {
            strand[i] = 'T'; 
        }
        else if (strand[i] == 'T')
        {
            strand[i] = 'A'; 
        }
        else if (strand[i] == 'C')
        {
            strand[i] = 'G'; 
        }
        else if (strand[i] == 'G')
        {
            strand[i] = 'C'; 
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
    */

    string targetStrand = "GCGTAC";
    string inputStrand = "TCAATC";
    //double bestStrand = bestStrandMatch(inputStrand, targetStrand);
    identifyMutations(inputStrand, targetStrand); 

    //reverseComplement(strand); 
    return 0; 

}