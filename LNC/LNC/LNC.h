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


	LargeNumber::LargeNumber(string const& rostrNumber)
	{
		//Eliminating leading and trailing blanks
		int iEnd;
		iEnd = rostrNumber.size() - 1;

		/*do{
			iEnd--;
		} while ((rostrNumber[iEnd] == ' ') && iEnd >= 0);*/

		
		for (; (rostrNumber[iEnd] == ' ')&&(iEnd >= 0); iEnd--);

		if (iEnd < 0)
		{
			Num_Sign = 1;
			Build(0, m_oNumber);
			return;
		}
		int iBeg;
		for (iBeg = 0; ' ' == rostrNumber[iBeg]; iBeg++);
		string ostrNumber = rostrNumber.substr(iBeg, iEnd - iBeg + 1);
		iBeg = 0;
		if ('-' == ostrNumber[0])
		{
			Num_Sign = -1;
			iBeg = 1;
		}
		else
			Num_Sign = 1;
		Build(ostrNumber.c_str() + iBeg, m_oNumber);
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
	void LargeNumber::Build(string const& rostrNumber, vector<char>& rvN)
	{
		rvN.clear();
		for (int i = rostrNumber.size() - 1; i >= 0; i--)
		{
			if (rostrNumber[i]<'0' || rostrNumber[i]>'9')
				break;
			else
				rvN.push_back(rostrNumber[i] -'0');   //Since this is from a string. rostrNumber[i] holds the ASCII equivalent of integer value.
		}
		Clean(rvN);
	}

	void LargeNumber::Clean(vector<char>& rvN)
	{
		int count = 0;
		//Eliminate all leading 0s
		vector<char>::iterator it = rvN.end();

		cout << rvN[0] << endl;

		while (it != rvN.begin())
		{count++;
			it--;

			if (*it != 0)
				break;
			
		}
	//	cout << count << endl;
		rvN.erase(it + 1, rvN.end());
	}




	LargeNumber LargeNumber::operator+(LargeNumber const& roLN) const
	{
		LargeNumber oLNRes;
		if (1 == Num_Sign && 1 == roLN.Num_Sign)
		{
			oLNRes.Num_Sign = 1;
			Add(m_oNumber, roLN.m_oNumber, oLNRes.m_oNumber);
		}
		return oLNRes;
	}

	string LargeNumber::ToString() const
	{
		if (0 == m_oNumber.size())
			return "0";
		string ostr;
		if (-1 == Num_Sign)
			ostr += '-';
		vector<char>::const_reverse_iterator rIter = m_oNumber.rbegin();
		for (; rIter != m_oNumber.rend(); rIter++)
			ostr += *rIter +'0';
		return ostr;
	}
private:
	char Num_Sign;
	vector<char> m_oNumber;

};


void LargeNumber::Add(vector<char> const& rcvN1, vector<char> const& rcvN2, vector<char>& rvNRes)
{
	rvNRes.clear();
	//Local copies
	vector<char> vN1 = rcvN1;
	vector<char> vN2 = rcvN2;
	int iSize1 = vN1.size();
	int iSize2 = vN2.size();
	int i, iSize;
	//Fill with '0'
	if (iSize1 > iSize2)
	{
		for (i = iSize2; i < iSize1; i++)
			vN2.push_back(0);
		iSize = iSize1;
	}
	else
	{
		for (i = iSize1; i < iSize2; i++)
			vN1.push_back(0);
		iSize = iSize2;
	}
	int iC = 0, iR;
	for (i = 0; i<iSize; i++)
	{
		iR = vN1[i] + vN2[i] + iC;
		
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
		rvNRes.push_back(iC);
}