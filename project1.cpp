
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
using namespace std;

int     digit_to_col(char       inChar);
int     char_to_col(char        inChar);

int	main()
{
//	int	index;

	int	identifier[6][2]; // first dimension , states. Second Dimension Language "alphabetical" or "_"
	int	digitReal[5][2];  // first diemnsion , states. Second Dimension, Language "digit " or "."
	string	tokens[]={"Unknown","Seperator","Operator", "keyword", "identifier", "integer", "real" };
	char	seperators[]= {"[]{}(),;"};
	char	str[256];

	//initialize the matrices
	//		IDENTIFIER       
	/*          L                          _        */
	//1 is accepted
	identifier[0][0]= 1;  		identifier[0][1]= 5;
	//2 is accepted
	identifier[1][0]= 2;		identifier[1][1]= 3;
	//4 are accepted
	identifier[2][0]= 4;		identifier[2][1]= 3;
	identifier[3][0]= 4;		identifier[3][1]= 3;
	identifier[4][0]= 4;		identifier[4][1]= 3;
	identifier[5][0]= 5;		identifier[5][1]= 5;
	

		
	//		Integer | Real			//
	/*       D                             .        */
	//1 is accepted, if 1 == integer
	digitReal[0][0]= 1;		digitReal[0][1]= 2;
	digitReal[1][0]= 1;		digitReal[1][1]= 2;
	// 3 is accepted, if 3 == successful Real
	digitReal[2][0]= 3;		digitReal[2][1]= 4;
	digitReal[3][0]= 3;		digitReal[3][1]= 4;
	digitReal[4][0]= 4;		digitReal[4][1]= 4;
	
	//display to test
	for(int i=0; i<6; i++)    //This loops on the rows.
	{
		for(int j=0; j<2; j++) //This loops on the columns
		{
			cout << identifier[i][j]  << "  ";
		}
		cout << endl;
	}


	cout << "Enter the name of an existing rat15 text file: ";
	cin.get(str,236); 
	fstream	inFile(str);
	
//	inFile.open("rat15.txt", ios::in);
	//{ cout << "Opened \n"; }

	
	int	total = 0;
        string  word;
				cout << "Token               Lexeme\n";
        int     i;
	string 	fileChar;
	int	state = 0;
	int	column;
	int	tracker;
	bool	test;
	do{

		// Begin to read from file
		inFile  >> fileChar;
		tracker = 0;
		// if EOF, break look
		if( inFile.eof() )
		{
			cout << " EOF reached \n";
			break;
		}
		// if the first character of  the string we read is a digit OR a "." , then it must be a real or an int
		if( isdigit(fileChar[tracker]) || fileChar[tracker] == '.' )
		{
//			cout << "we're in isdigit(fileChar[0] \n";
		 	state = 0;
			for(i = 0; i < fileChar.length() ; i++)
        		{
				column = digit_to_col(fileChar[i]);
		
				// quickly test to see if the column failed
				if (column == -1)
				{
					//tracker = i;
					break; // out of loop
				}

				state = digitReal[state][column]; 
			}
			tracker = i;
				

			if( state == 1 ) // int
			{	// right now i'm writing to stdout, at the end of program, I will write to an outFile.txt
				cout << tokens[5] << "           ";
				for(i=0; i< tracker; i++)
                                {
                                        cout << fileChar[i];
                                }
                                cout << endl;
				//if we didn't make it across the entire string
				if(tracker < fileChar.length() )
				{
	                                inFile.putback(fileChar[tracker+1]);
				}
			}
			if( state == 3 ) // real
			{	// write to outFile before turned in
				cout << tokens[6] << "			";
                                for(i=0; i< tracker; i++)
                                {
                                        cout << fileChar[i];
                                }
                                cout << endl;
				//if we didn't make it across the entire string
				if(tracker < fileChar.length() )
				{
					//put back the character
					inFile.putback(fileChar[tracker]);
				}
			}
		}
		// if the first character read is an alpha, it must be an identifier or keyword
		if( isalpha(fileChar[tracker]) )
		{
//			cout << "we're in isalpha(fileChar[0] \n";
			state = 0;
			for( i = 0; i < fileChar.length() ; i++)
			{
				column = char_to_col(fileChar[i]);

				// test for column failure
				if(column == -1)
				{	
					//tracker = i;
					break; // and do something, not sure what yet.
				}
				
				state = identifier[state][column];
				//tracker = i;
			}
			tracker = i;
			if( (state == 1) || (state ==2) || (state ==4) )
			{
				//write to  that we had success
				cout << tokens[4] << "		";
				for(i=0; i< tracker; i++)
				{
					cout << fileChar[i];
				}
				cout << endl;
				inFile.putback(fileChar[tracker]);
			}

		}
		// it must be a seperator, or operator
		else
		{
			test = false;
			//quick loop to test for Seperators
			
			
				for(i = 0; i < 8; i++)
	        	        {
        		                if( seperators[i] == fileChar[tracker])
        		                {
        		                        cout << tokens[1]<< "		" << fileChar[tracker] << endl; 
						test = true;	
						if(fileChar[tracker+1] != ' ' )
						{
							inFile.putback(fileChar[tracker+1]);
							
						}
        		                }
        		        }

 
			if(!test)
			{
			switch(fileChar[tracker])
			{
				case '=':
					if( '>' == fileChar[tracker +1] )
					{
						cout << tokens[2] << "		" << fileChar[tracker] << fileChar[tracker +1] << endl; 
						break;
					}
					else
					{
						cout << tokens[2] << "           " <<  fileChar[tracker] << endl;
						break;
					}
				case '!':
					if(  '=' == fileChar[tracker +1] )
					{
						cout << tokens[2] << "		" << fileChar[tracker] << fileChar[tracker +1] << endl;
						break;
					}
					else 
					{ 
						cout << tokens[0] << "		" << fileChar[tracker] << endl;
						break;
					}
				case '>':
					cout << tokens[2] << "		" << fileChar[tracker] << endl;
					break;
				case '<':
					if ( '=' == fileChar[tracker +1] )
					{
						cout << tokens[2] << "		" << fileChar[tracker] << fileChar[tracker + 1] << endl;
						break;
					}
					else 
					{ 	
						cout << tokens[2] << "		" << fileChar[tracker] << endl; 
						break;
					}
				case '-':
					cout << tokens[2] << "		" << fileChar[tracker] << endl; 
					break;
				case '*':
					cout << tokens[2] << "		" << fileChar[tracker] << endl;
					break;
				case '/':
					cout << tokens[2] << "		" << fileChar[tracker] << endl;
					break;
				case '+' :
					cout << tokens[2] << " 		" << fileChar[tracker] << endl;
					break;
				case ':':
					if( '=' == fileChar[tracker + 1] )
					{
						cout << tokens[2] << "		" << fileChar[tracker] << fileChar[tracker+1] << endl;
						break;
					}
				case '@':
					if( '@' == fileChar[tracker +1] )
					{
						cout << tokens[1] << "		" << fileChar[tracker] << fileChar[tracker +1] << endl;
						break;
					}
					else
					{
						cout << tokens[0] << "		" << fileChar[tracker] << endl;
						break;
					}
				// continue here in similar form (or maybe a loop through the array of operators) for operators..
//				default:
//					cout << tokens[0]  << "		" << fileChar[tracker] << endl;
//					break;
			}// end switch
			}//end if booltest
		}  
			// check for operators/seperators/keywords
// 2    string  operators[]= {"=","!=",">","<","=>","<=","*","/","+","-", ":="};
// 1        string  seperators[]= {"@@","[","]","{","}","(",")",",",";"};
//        string  keywords[]= {"int","if","else","endif","while","return","read",
  //                              "function","real","boolean","true","false","do",
    //                            "write"};
	}while(true);

	return 0;


}

int	digit_to_col(char	inChar)
{
	if ( isdigit(inChar) )	// then it's a digit, it belongs to the first column
	{
		return 0;
	}
	if( inChar == '.' ) // then it's clearly a decimal, it belongs to the second column
	{
		return 1;
	}
	else
	{
		//it's neither ( dont know what to do here ) perhaps return -1?
		return -1;
	}
	

}	

int	char_to_col(char	inChar)
{
	if( isalpha(inChar) )
	{
		return 0;
	}
	if( inChar == '_' )
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
	

