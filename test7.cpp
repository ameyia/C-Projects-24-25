else if((firstStrand.length() != secondStrand.length())(isValidStrand(firstStrand)==true && isValidStrand(secondStrand)==true))
            {    //if the first strand is shorter, need to make it the target and not the input
                //so it does not return 0.0 and -1 by default
                if (firstStrand.length() < secondStrand.length())
                {
                    bestStrandMatch(secondStrand, firstStrand); 
                }
                else //if (firstStrand.length() > secondStrand.length())
                {
                    bestStrandMatch(firstStrand, secondStrand); 
                }
                
            }