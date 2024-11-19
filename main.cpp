#include <iostream> 

using namespace std; 

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

int main()
{
    //put after the switches 
    cout<<"--- DNA Analysis Menu ---"<<endl; 
    cout<<"1. Calculate the similarity between two sequences of the same length"<<endl;
    cout<<"2. Calculate the best similarity between two sequences of either equal or unequal length"<<endl;
    cout<<"3. Identify mutations"<<endl;
    cout<<"4. Transcribe DNA to RNA"<<endl; 
    cout<<"5. Find the reverse complement of a DNA sequence"<<endl; 
    cout<<"6. Extract reading frames"<<endl; 
    cout<<"7. Exit"<<endl; 

    int choice; 
    cout<<"Please enter your choice (1 - 7):"<<endl;
    cin>>choice; 


    string firstStrand; 
    string secondStrand; 
    strandSimilarity(firstStrand, secondStrand); 
    bool validStrand = isValidStrand(firstStrand) && isValidStrand(secondStrand); 
    //bool validStrand2 = isValidStrand(secondStrand); 
    
    
    while (choice!=7)
    {
        
        switch(choice)
        {
        
         //similarity between two sequences of the same length
         case 1: 

            cout<<"Enter the first DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

            cout<<"Enter the second DNA sequence:"<<endl; 
             cin>>secondStrand;
                while (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==false )
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>secondStrand; 
                    if(isValidStrand(secondStrand)==true)
                    {
                        break; 
                    }
                }

            if (firstStrand.length() != secondStrand.length())
            {
                cout<<"Error: Input strands must be of the same length."<<endl; 
            }
            if((firstStrand.length() == secondStrand.length())&& (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
            {
            cout<<"Similarity score: "<<strandSimilarity(firstStrand, secondStrand)<<endl; 
            }
            break; 

            //best similarity between two sequences of either equal or unequal length
         case 2: //might need to fix so it does not return the best value

            cout<<"Enter the first DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

            cout<<"Enter the second DNA sequence:"<<endl; 
             cin>>secondStrand;
                while (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==false )
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>secondStrand; 
                    if(isValidStrand(secondStrand)==true)
                    {
                        break; 
                    }
                }
            if((firstStrand.length() == secondStrand.length())&& (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
            {
                cout<<"Similarity score: "<<strandSimilarity(firstStrand, secondStrand)<<endl; 
            }

            else if((isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
            {    //if the first strand is shorter, need to make it the target and not the input
                //so it does not return 0.0 and -1 by default
                if (firstStrand.length() < secondStrand.length())
                {
                    cout<<"Similarity score: "<<bestStrandMatch(secondStrand, firstStrand)<<endl; 
                }
                else 
                {
                    cout<<"Similarity score: "<<bestStrandMatch(firstStrand, secondStrand)<<endl; 
                }
                
            }
            break; 
            
            
            //identifying mutations, subsitution, insertion, deletion
         case 3:
            cout<<"Enter the first DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

            cout<<"Enter the second DNA sequence:"<<endl; 
             cin>>secondStrand;
                while (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==false )
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>secondStrand; 
                    if(isValidStrand(secondStrand)==true)
                    {
                        break; 
                    }
                }
                //if they are all valid strands
                if((isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
                {
                    identifyMutations(firstStrand, secondStrand); 
                }
                break; 
            
             //Transcribe DNA to RNA
             case 4:

             cout<<"Enter the DNA sequence to be transcribed:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

                //if they are strand 1 valid 
                if((isValidStrand(firstStrand)==true))
                {
                    cout<<"The transcribed DNA is: "; 
                    transcribeDNAtoRNA(firstStrand); 
                }
                break; 

              //reverse compliment //keep working on  
             case 5:
                cout<<"Enter the DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

                //if they are strand 1 valid 
                if((isValidStrand(firstStrand)==true))
                {
                    cout<<"The reverse complement is: "; 
                    reverseComplement(firstStrand); 
                }
                break; 

             //extracting reading frames 
             case 6:
                cout<<"Enter the DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

                if((isValidStrand(firstStrand)==true))
                {
                    cout<<"The extracted reading frames are"<<endl; 
                    
                }
                break; 


                







            
            




            
            
            //when the user does not choose choice betwerrn 1
            default:
                cout<<"Invalid input. Please select a valid option."<<endl; 
            break;   


        }

        

        //runs through again, asks for the choice again and if it is not 7 and in range of 
        //1-6 it will keep going through the while loops and cases. 
        cout<<"--- DNA Analysis Menu ---"<<endl; 
        cout<<"1. Calculate the similarity between two sequences of the same length"<<endl;
        cout<<"2. Calculate the best similarity between two sequences of either equal or unequal length"<<endl;
        cout<<"3. Identify mutations"<<endl;
        cout<<"4. Transcribe DNA to RNA"<<endl; 
        cout<<"5. Find the reverse complement of a DNA sequence"<<endl; 
        cout<<"6. Extract reading frames"<<endl; 
        cout<<"7. Exit"<<endl; 

    
        cout<<"Please enter your choice (1 - 7):"<<endl;
        cin>>choice; 

    }
    //when the user picks 7, the program is done
    if (choice == 7)
        {
            cout<<"Exiting program."<<endl; 
        }

}