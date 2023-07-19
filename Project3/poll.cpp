#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <cctype>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
bool isValidPollString(string pollData);
int countSeats(string pollData, char party, int& seatCount);


int main()
{
	assert(isValidPollString(""));
	assert(!isValidPollString("C"));
	assert(!isValidPollString("c"));
	assert(!isValidPollString("3")); 
	assert(!isValidPollString("3C")); // same lines run as the above one
	assert(!isValidPollString("C3"));
	assert(!isValidPollString("c3"));
	assert(isValidPollString("CA"));
	assert(isValidPollString("cA"));
	assert(isValidPollString("Ca"));
	assert(isValidPollString("ca"));
	assert(!isValidPollString("CAD"));
	assert(!isValidPollString("CAd"));
	assert(!isValidPollString("CA3"));
	assert(!isValidPollString("CA33"));
	assert(isValidPollString("CA3D"));
	assert(!isValidPollString("CA3D3"));
	assert(!isValidPollString("CA3DD"));
	assert(!isValidPollString("CA3D33"));
	assert(isValidPollString("CA3D3D"));
	assert(isValidPollString("CA3D33D"));
	assert(!isValidPollString("CA3D333"));
	assert(!isValidPollString("CA3D33D3"));
	assert(!isValidPollString("CA3D33DD"));
	assert(!isValidPollString("CA3D,M"));
	assert(!isValidPollString("CA3D,M3"));
	assert(isValidPollString("CA3D,MT"));
	assert(!isValidPollString("CA3D,MT3"));
	assert(!isValidPollString("CA3D,MT33"));
	assert(isValidPollString("CA3D,MT3D"));
	assert(isValidPollString("CA3D,MT33D"));
	assert(!isValidPollString("CA3D,MT33D3"));
	assert(!isValidPollString("CA3D,MT33D33"));
	assert(!isValidPollString(","));
	assert(!isValidPollString("C,"));
	assert(!isValidPollString("CA,"));
	assert(!isValidPollString("CA3,"));
	assert(!isValidPollString("CA33,"));
	assert(!isValidPollString("CA33D,"));
	assert(!isValidPollString("CA,"));
	
	assert(isValidPollString("CT91D81A32B93C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C"));
	assert(!isValidPollString("Ct5b,VTT"));
	assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
	assert(!isValidPollString("OH5D,DM8G,KL325M"));
	assert(!isValidPollString("MN7T,C44D,PT55K"));
	assert(!isValidPollString("AZP23F,AK00Z,WVH,CT00S,UT07Y,MD76Z"));
	assert(isValidPollString("MT90T,MT22D,MT36T,NH7T"));
	assert(!isValidPollString("KS47Z0,CAA6Z"));
	assert(!isValidPollString("ND39P,CA4,CA345D"));
	assert(!isValidPollString("IL25G,LA54B,MN22F,P55O"));
	assert(!isValidPollString("RI876Y,LA54B,MN22F"));
	assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));

	int seats;

	seats = -999;    // so we can detect whether countSeats sets seats
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 21);
	seats = -999;    // so we can detect whether countSeats changes seats
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
	assert(countSeats("", 'd', seats) == 0 && seats == 0);
	seats = -999;
	assert(countSeats("RI876Y,LA54B,MN22F", 'd', seats) == 1 && seats == -999);
	cerr << "All tests succeeded" << endl;

}

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.
bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}


//*************************************
//  isValidPollString
//*************************************

// Return true if its parameter is a poll data string(i.e., it meets the definition above), or 
// false otherwise.
bool isValidPollString(string pollData)
{
	string stateCode = "";
	string voteCharacter = "";
	string partyCode = "";

	if (pollData.empty())
		return true;

	for (int i = 0; i < pollData.size(); i++) // whole string traversed
	{
		char currentChar = pollData.at(i);
		if (!(currentChar == ','))
		{
			if (isalpha(currentChar))
			{
				if (stateCode.empty())
					stateCode += toupper(currentChar);
				else if (stateCode.size() == 1)
				{
					stateCode += toupper(currentChar);
					if (!isValidUppercaseStateCode(stateCode))
						return false; // although there are two letters for stateCode, stateCode is not a real state.
				}
				else // statecode of stateforecast is found and valid.
				{
					if (voteCharacter.size() == 1 || voteCharacter.size() == 2)
					{
						if (partyCode.empty()) // character is a party code that has voteCharacter votes.
						{
							partyCode += currentChar;
							voteCharacter = "";
						}
						else
							return false; // After party code, another letter can not come.
					}
					else
						return false; // After state code a digit should come
				}
			}
			else if (isdigit(currentChar))
			{
				if (stateCode.size() == 2)
				{
					if (voteCharacter.empty())
					{
						partyCode = ""; // new party data is obtained
						voteCharacter += currentChar;
					}
					else if (voteCharacter.size() == 1)
						voteCharacter += currentChar;
					else
						return false; // vote number should be two digits and immediately followed by party letter.
				}
				else
					return false; // stateCode is not validated.
			}
			else
				return false; // current character is not a digit or letter or coma
		}
		else // coma detected, check last forecast before coma whether it has valid state code and valid last party results.
		{
			if (stateCode.size() != 2)
				return false;
			if (partyCode.empty() && (voteCharacter.size() == 1 || voteCharacter.size() == 2))
				return false; // last party result should be in a valid format ddl or dl.

			stateCode = "";
			voteCharacter = "";
			partyCode = "";
		}
	}
	// after for loop last party result must be valid. ...,VT or ...,VT5D3D it can't be "VT3d," or ...,V ...,V3 ...,VTD ...,
	if (stateCode.size() != 2)
		return false; // last party forecast should have a valid stateCode.
	if (partyCode.empty() && ((voteCharacter.size() == 1 || voteCharacter.size() == 2)))
		return false; // last party result should be in a valid format ddl or dl. this is not valid format d or dd.
	return true;
}

//*************************************
// countSeats
//*************************************

// Return 1 if the parameter pollData is not a poll data string (i.e., it does not meet the definition above). Seatcount does not change.
// Return 2 if the parameter party is not a letter.  Seatcount does not change.
// Return 1 if either of the preceding situations occur. Seatcount does not change.
// Return 0 if neither of the above situations occurs, sets seatCount to the total number of seats that pollData predicts the party indicated by party will win.
int countSeats(string pollData, char party, int& seatCount)
{

	// Do not Modify seatCount
	if (!isValidPollString(pollData))
		return 1;

	// Do not Modify seatCount
	if (!isalpha(party))
		return 2;

	// Modify seatCount
	// FIRST three character can not be party character, so I start loop at the 4th index.
	int voteSum = 0; // Total seats for the party. Initiliazed to zero since we have not counted any votes yet.
	for (int i = 3; i < pollData.size(); i++)
	{
		if (toupper(pollData.at(i)) == toupper(party)) // Checking whether the current character is a party character.
		{
			int voteNum = 0;
			if (isdigit(pollData.at(i - 2))) // If it is a party character, with two digit votes, then this segment should work
			{
				char firstChar = pollData.at(i - 2);
				char secondChar = pollData.at(i - 1);

				int firstDigit = firstChar - '0';
				int secondDigit = secondChar - '0';

				voteNum = 10 * firstDigit + secondDigit; // Base 10 sum
				voteSum += voteNum;
			}
			else if (isdigit(pollData.at(i - 1))) // If it is a party character, with one digit votes, then this segment should work.
			{
				char firstChar = pollData.at(i - 1);

				int firstDigit = firstChar - '0';

				voteNum = firstDigit;
				voteSum += voteNum;
			}
		}
	}
	seatCount = voteSum; // if it is a empty string returns 0 
	return 0;
}
