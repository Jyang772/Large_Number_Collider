#include <iostream>
#include <string>
#include <vector>
using namespace std;


class LargeNumber
{
public:
	LargeNumber() : Num_Sign(1) { m_oNumber.push_back(0); }    //This is the default constructor
	
	
	//Constructor that takes an Integer value
	LargeNumber::LargeNumber(int iNumber)
	{
		if (iNumber < 0)
		{
			Num_Sign = -1;
			iNumber = -iNumber;
		}
		else
			Num_Sign = 1;
		Build(iNumber, m_oNumber);
	}			
	void static Add(vector<char> const& NumOne, vector<char> const& NumTwo, vector<char>& Result);    //Add Function Prototype	


	LargeNumber::LargeNumber(string const& rostrNumber)        //Start here. String is passed to constructor. 
	{
		//Eliminating leading and trailing blanks
		int iEnd;
		iEnd = rostrNumber.size() - 1;

		/*do{
			iEnd--;
		} while ((rostrNumber[iEnd] == ' ') && iEnd >= 0);*/

		
		for (; (rostrNumber[iEnd] == ' ')&&(iEnd >= 0); iEnd--);         //This checks for the end of the string. 

		if (iEnd < 0)                                                   //If nothing has been entered. 
		{
			Num_Sign = 1;
			Build(0, m_oNumber);
			return;
		}
		int iBeg;                                                      //integer to hold beginning position of string
		for (iBeg = 0; ' ' == rostrNumber[iBeg]; iBeg++);             //loop until end of string
		string ostrNumber = rostrNumber.substr(iBeg, iEnd - iBeg + 1);            //creates a copy of the original string into ostrNumber
		iBeg = 0;                                                                 //sets beginning position to 0
		if ('-' == ostrNumber[0])                                                 //Check to see if number is negative
		{
			Num_Sign = -1;
			iBeg = 1;
		}
		else                                                                     //else set Num_Sign to one
			Num_Sign = 1;                
		Build(ostrNumber.c_str() + iBeg, m_oNumber);                             //Send to Build function. This is where we construct the vector
	}               
	void LargeNumber::Build(unsigned uN, vector<char>& rvN)                      
	{
		rvN.clear();
		if (0 == uN)
			rvN.push_back(0);
		else
		for (; uN > 0;)
		{
			rvN.push_back(uN % 10);
			uN /= 10;
		}
	}
	void LargeNumber::Build(string const& rostrNumber, vector<char>& rvN)           //Takes in ostrNumber and m_oNumber
	{
		rvN.clear();                                                                //First we clear m_oNumber vector
		for (int i = rostrNumber.size() - 1; i >= 0; i--)                           //NOTICE: Number is pushed onto vector reversed.
		{
			if (rostrNumber[i]<'0' || rostrNumber[i]>'9')                          //If rostrNumber contains anything other than a number, break!!
				break;
			else
				rvN.push_back(rostrNumber[i] -'0');   //Since this is from a string. rostrNumber[i] holds the ASCII equivalent of integer value.
		}                                             //Subtract '0' to obtain the integer value. '0' = 48
		Clean(rvN);                                    //Let's clean this vector up a bit
	}

	void LargeNumber::Clean(vector<char>& rvN)           //Takes in a reference to rvN from Build()
	{
		int count = 0;
		//Eliminate all leading 0s
		vector<char>::iterator it = rvN.end();                     //Set the iterator to PAST THE END of rvN

		cout << rvN[0] << endl;

		while (it != rvN.begin())                          //While it is not at the beginning, we continue iterating through. 
		{   
			//count++;
			it--;

			if (*it != 0)                                     //If we have reached a zero, we break! 
				break;                                        // Ex. 009 -> 900
			                                                  //   When iterator encounters a value != 0, break!
			
		}
	//	cout << count << endl;
		rvN.erase(it + 1, rvN.end());                          //We would erase from after 9 to the end
	}




	LargeNumber LargeNumber::operator+(LargeNumber const& roLN) const               //This is an overloaded addition operator
	{
		LargeNumber oLNRes;                                                         //Create a new LargeNumber object that we can return
		if (1 == Num_Sign && 1 == roLN.Num_Sign)                                    //Check to see if both numbers are positive
		{
			oLNRes.Num_Sign = 1;                                                    //Change oLNRes to positive
			Add(m_oNumber, roLN.m_oNumber, oLNRes.m_oNumber);                       //Send to the Add function of the LargeNumber object to the left of the operator
		}
		return oLNRes;
	}

	string LargeNumber::ToString() const
	{
		if (0 == m_oNumber.size())                               //Check to see if our result vector is 0
			return "0";
		string ostr;
		if (-1 == Num_Sign)                                     //Check to see if our result vector is negative
			ostr += '-';
		vector<char>::const_reverse_iterator rIter = m_oNumber.rbegin();                //Now let us reverse our reversed vector. Therefore obtaining the right result. Ex. 0031 -> 1300
		for (; rIter != m_oNumber.rend(); rIter++)                                      //This is a reverse iterator. Therefore we start from the end and head toward the beginning.
			ostr += *rIter +'0';                                                        //Add '0' to convert from integer back to ASCII symbol
		return ostr;                                                                    //Now we can display the string! :) 
	}
private:
	char Num_Sign;
	vector<char> m_oNumber;

};


void LargeNumber::Add(vector<char> const& rcvN1, vector<char> const& rcvN2, vector<char>& rvNRes)     //Add function takes in three parameters. (left,right,result)
{
	rvNRes.clear();                                                                                   //Make sure the vector to hold the result is clear
	//Local copies
	vector<char> vN1 = rcvN1;
	vector<char> vN2 = rcvN2;
	int iSize1 = vN1.size();
	int iSize2 = vN2.size();
	int i, iSize;
	//Fill with '0'
	if (iSize1 > iSize2)                             //Ex. 1200 + 12 -> 0012 + 21 -> 0012 + 2100; (Remember, both vectors have been reversed)
	{
		for (i = iSize2; i < iSize1; i++)
			vN2.push_back(0);
		iSize = iSize1;                                         //Set iSize to the size of the first vector (the larger)
	}
	else
	{
		for (i = iSize1; i < iSize2; i++)
			vN1.push_back(0);
		iSize = iSize2;                                       //Set iSize to the size of the first vector (the larger)
	}
	int iC = 0, iR;
	for (i = 0; i<iSize; i++)                                                      
	{
		iR = vN1[i] + vN2[i] + iC;                            //iR holds the remainder
		
		if (iR > 9)
		{
			iR -= 10;
			iC = 1;
		}
		else
			iC = 0;
		rvNRes.push_back(iR);         //Passed in integer value. Need to convert back to ASCII equivalent
	}
	if (iC > 0)
		rvNRes.push_back(iC);             //After adding, we still have a reversed vector. We must now use our ToString member function
}