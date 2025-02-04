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
    //if the input strand is shorter than the target strand, the function
    //returns -1 as the alignment index and prints out ”Best similarity
    //score: 0.0”.
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

//trying to turn the target into the input
void identifyMutations(string input_strand, string target_strand)
{
    
    //compares two DNA sequences to identify all types of mutations between them 
    int bestIndex; 
    if(input_strand.length() > target_strand.length())
    {
        bestIndex = bestStrandMatch(input_strand, target_strand);  
    }

    else if(input_strand.length() < target_strand.length())
    {
        bestIndex = bestStrandMatch(target_strand, input_strand);  
    }
   //if the beststrandmatch is -1/the lengths do not work out, then there are no mutations found
   //and the best alignment index is -1 as target is bigger than input 
   /* if (bestIndex == -1)
    {
        cout<<"Best alignment index: -1"<<endl;
        cout<<"No mutations found."<<endl; 
        return; 
    }
    */
    //add the best alignment positon where the best index is 
    cout<<"Best alignment index: "<<bestIndex<<endl; 
    
    //aligning the strings
    //aligns them by finding the best index and setting the input there 
    //and it only goes up until however long the target strand is 
    //position is at the best index 
    //length is how long the target strand is 
    //aligned index is only the length of target, and disregards the 
    //letters before/after the input
    string alignedInput = input_strand.substr(bestIndex, target_strand.length());  

    //will use in the for loop to see if there is a mutation 
    bool mutationFound = false; 
    
 if (input_strand.length() < target_strand.length())
 {
    
    //when the target is larger than the input
    //goes through position first of the input
    for (int i = 0; i < input_strand.length(); i++)
    {
        //deletion
        //when best index is greater than the positon it at the input
        //when input is bigger than target then you delete the input 
        if(bestIndex > i)
        {
            //used input so it would work 
            cout<<"Deletion at position "<<i + 1<<": "<<input_strand[i]<<" is deleted in target strand"<<endl;
            mutationFound = true; 
        }
    }
 }
    
    
    //when the target is smaller than the input 
    
    //if (target_strand < input_strand)
    //{
        //goes through the position starting at bestIndex
        //might need to change target to aligned but they should be the same length
        //insertion
        for(int i = 0; i < input_strand.length(); i++)
        {
            if(bestIndex + target_strand.length() - 1 < i )
            {
                cout<<"Insertion at position "<<i + 1<<": "<<target_strand[i]<<" is inserted in target strand"<<endl;
                mutationFound = true; 
            }
        }
        
   // }
    

   
}
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

    string inputStrand = "CGTAG";
    string targetStrand = "CGGCTATCGTAG";
    //double bestStrand = bestStrandMatch(inputStrand, targetStrand);
    identifyMutations(inputStrand, targetStrand); 

    //reverseComplement(strand); 
    return 0; 

}

