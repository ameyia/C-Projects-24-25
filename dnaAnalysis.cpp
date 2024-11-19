#include <iostream> 
#include <iomanip>
#include <cstring>

using namespace std; 

bool isValidBase(char base)
{
    //if the char is A C G or T
    if (base == 'A'|| base == 'C'|| base == 'G'|| base == 'T')
    {
        return true; //it is valid 
    }
    return false; //if not then false 
}

bool isValidStrand(string strand)
{
    if (strand.length() == 0) //if strand length is zero  
    {
        return false; //returns false 
    }
    for (double i = 0; i < strand.length(); i++)
    {
        //goes through a loop to check if each placement is one of the letters - AGTC
        bool valid = isValidBase(strand[i]); 
        if (!valid)
        {
            return false; //if it is not then return false 
        }
        //if there are spaces in the strand
        else if (strand[i] == ' ')
        {
            return false; //return false 
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
    cout<<"Best similarity score: "<<bestScore<<endl; //prints the best score of the strands 
    return bestIndex; //returns the best alignment index
}

//trying to turn the input into the target
void identifyMutations(string input_strand, string target_strand)
{
    int bestIndex; //stores best alignment index
    string input; //stores the aligned version of the input strand 
    string target; //stores the aligned version of the target strand
    int maxLength = max(input_strand.length(), target_strand.length()); //finds the max length between the two for alignment
   
    //make sure that the length does not become an issue 
    //call beststrand match to find the best matching alignment between input and target
    //if input is longer 
    if (input_strand.length() > target_strand.length())
    {
        //passes this; store best indesx for target against index 
        bestIndex = bestStrandMatch(input_strand, target_strand); 
    }
    //if input is shorter, then passes this 
    else
    {
        bestIndex = bestStrandMatch(target_strand, input_strand);
    }
    //prints the aignment index 
    cout<<"Best alignment index: "<<bestIndex<<endl;
    
    //checks if the mutation is found 
    bool mutationFound = false; 

    //fillers, puts . in, represents gaps during alignments 
    for (int i = 0; i < maxLength; i++)
    {
        input+=(".");  
        target+=("."); 
    }
    
    
    //aligns the strand based on thier lengths
    //when inpyt is shorter than target, align input to the best index in target 
    if (input_strand.length() < target_strand.length())
    {
        for (unsigned i = 0; i < input_strand.length(); i++)
        {
            //Fill the input string starting at the bestIndex with the characters from input
            input[bestIndex + i] = input_strand[i]; //Align input in the proper position
        }
        // Fill the entire target string with the characters from target
        for (unsigned i = 0; i < target_strand.length(); i++)
        {
            target[i] = target_strand[i]; // Align target
        }
    }
     // If input_strand is longer or equal, align target_strand to the best index in input
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

    // Check for mutations by comparing the aligned input and target 
    for (int i = 0; i < maxLength; i++)
    {
        // Check for insertion mutations when input has a gap ('.') and target has a character
        if (input[i] == '.' && target[i] != '.')
        {
            cout<<"Insertion at position "<< i + 1 << ": "<<target[i] << " is inserted in target strand"<<endl; 
            mutationFound = true; 
        }
            // Check for deletion mutations when target has a gap ('.') and input has a character
        else if (input[i] != '.' && target[i] == '.')
        {
            
            cout<<"Deletion at position "<< i + 1 << ": "<<input[i] << " is deleted in target strand"<<endl; 
            mutationFound = true; 
        }
        // Check for substitution mutations when both input and target have characters, but they don't match
        else if ((input[i] != '.' && target[i] != '.') && input[i] != target[i] )
        {
            cout<<"Substitution at position "<< i + 1 << ": "<<input[i] << " -> "<< target[i] <<endl; 
            mutationFound = true; 
        }

    }
//if no mutations found
 if (!mutationFound)
    {
     cout<<"No mutations found."<<endl; //print this
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

    cout<<newStrand<<endl; //prints the transcribed DNA
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
   }  

}
//checks function;

int main()
{
    //put after the switches 
    //
    cout<<"--- DNA Analysis Menu ---"<<endl; 
    cout<<"1. Calculate the similarity between two sequences of the same length"<<endl;
    cout<<"2. Calculate the best similarity between two sequences of either equal or unequal length"<<endl;
    cout<<"3. Identify mutations"<<endl;
    cout<<"4. Transcribe DNA to RNA"<<endl; 
    cout<<"5. Find the reverse complement of a DNA sequence"<<endl; 
    cout<<"6. Extract coding frames"<<endl; 
    cout<<"7. Exit"<<endl; 
    //asks user to input the choice they want from the menu 
    int choice; 
    cout<<"Please enter your choice (1 - 7):"<<endl;
    cin>>choice; 

    //holds the values 
    string firstStrand; 
    string secondStrand; 
    strandSimilarity(firstStrand, secondStrand); 
   //bool validStrand = isValidStrand(firstStrand) && isValidStrand(secondStrand); 
    //bool validStrand2 = isValidStrand(secondStrand); 
    
    //keeps looping if the user inputs a number that is not 7 
    while (choice!=7)
    {
        //goes through the switch when the user chooses a number 
        switch(choice)
        {
        
         //similarity between two sequences of the same length
         //goes through case 1 if the user selects 1
         case 1: 
            //asks for the DNA sequence and goes through the function isvalidstrand to see if it uses valid letters
            //if not valid it asks to input another until it is valid 
            cout<<"Enter the first DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the first DNA sequence:"<<endl; 
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; //stops when valid; shoudl work without the break but gives me peace of mind
                    }
                }
                //same as above but with the second strand input 
            cout<<"Enter the second DNA sequence:"<<endl; 
             cin>>secondStrand;
                while (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==false )
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the second DNA sequence:"<<endl; 
                    cin>>secondStrand; 
                    if(isValidStrand(secondStrand)==true)
                    {
                        break; 
                    }
                }
            //checks if the strands are equal in length, if not outputs "error"
            if (firstStrand.length() != secondStrand.length())
            {
                cout<<"Error: Input strands must be of the same length."<<endl; 
            }
            //if they are equal and valid then prints out the similarity score 
            if((firstStrand.length() == secondStrand.length())&& (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
            {
            cout<<"Similarity score: "<<strandSimilarity(firstStrand, secondStrand)<<endl; 
            }
            break; 

            //best similarity between two sequences of either equal or unequal length
            //when user choice = 2
         case 2: 
            //same as case 1 
            cout<<"Enter the first DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the first DNA sequence:"<<endl; 
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }
            //same as case 1 
            cout<<"Enter the second DNA sequence:"<<endl; 
             cin>>secondStrand;
                while (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==false )
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the second DNA sequence:"<<endl; 
                    cin>>secondStrand; 
                    if(isValidStrand(secondStrand)==true)
                    {
                        break; 
                    }
                }
            
            //if it is all valid then it prints out the score; the "best sim score: " comes from the function
            bestStrandMatch(firstStrand, secondStrand); 
            break; 
            
            
            //identifying mutations, subsitution, insertion, deletion
            //when user puts 3 as choise 
         case 3:
         //same as case 1
            cout<<"Enter the first DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the first DNA sequence:"<<endl; 
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }
            //same as case 1
            cout<<"Enter the second DNA sequence:"<<endl; 
             cin>>secondStrand;
                while (isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==false )
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the second DNA sequence:"<<endl; 
                    cin>>secondStrand; 
                    if(isValidStrand(secondStrand)==true)
                    {
                        break; 
                    }
                }
                //if they are all valid strands
                //then identify mutations
                if((isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
                {
                    identifyMutations(firstStrand, secondStrand); 
                }
                break; 
            
             //Transcribe DNA to RNA
             //choice = 4
             case 4:
            //same as case 1 but only asks for one strand 
             cout<<"Enter the DNA sequence to be transcribed:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the DNA sequence to be transcribed:"<<endl; 
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

                //if strand 1 valid
                //then it transcribes using the function  
                if((isValidStrand(firstStrand)==true))
                {
                    cout<<"The transcribed DNA is: "; 
                    transcribeDNAtoRNA(firstStrand); 
                }
                break; 

              //reverse compliment //keep working on 
              //choice = 5 
             case 5:
             //checks for valid 
                cout<<"Enter the DNA sequence:"<<endl; 
             cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the DNA sequence:"<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }

                //if strand 1 valid 
                //then reverse tht string 
                if((isValidStrand(firstStrand)==true))
                {
                    cout<<"The reverse complement is: "; 
                    reverseComplement(firstStrand); 
                }
                break; 

             //extracting reading frames 
             //choice = 6
             case 6:
                cout<<"Enter the DNA sequence:"<<endl; 
                cin>>firstStrand; 
                while(isValidStrand(firstStrand)==false)
                {
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                    cout<<"Enter the DNA sequence:"<<endl;
                    cin>>firstStrand; 
                    if(isValidStrand(firstStrand)==true)
                    {
                        break; 
                    }
                }
                //if it is valid then it prints the reading frames 
                if((isValidStrand(firstStrand)==true))
                {
                    cout<<"The extracted reading frames are: "<<endl;
                    getCodingFrames(firstStrand);  
                }
                break; 
 
            //when the user does not choose choice betwerrn 1-6; any number less than 1 and greater than 6 but not 7
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
        cout<<"6. Extract coding frames"<<endl; 
        cout<<"7. Exit"<<endl; 

        //asks user to input another choice 
        cout<<"Please enter your choice (1 - 7):"<<endl;
        cin>>choice; 

    }
    //when the user picks 7, the program is done
    if (choice == 7)
        {
            cout<<"Exiting program."<<endl; 
        }

}