#pragma warning(disable : 6262)
#define _CRT_SECURE_NO_WARNINGS


#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const char WORDFILENAME[] = "words.txt";
// Windows users:  Use / instead of \ for pathname separators.
//const int MINWORDLEN = 4;
//const int MAXWORDLEN = 6; DONT FORGET TO DELETE CERR BEFORE UPLOADING

const int MAXWORDS = 9000;
const int FILE_NOT_FOUND = 1;
const int MAXPROBWORDLEN = 100;

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);


int main()
{
	char words[MAXWORDS][MAXWORDLEN+1];
	int nWords;
	nWords = getWords(words, MAXWORDS, WORDFILENAME);

	cout.setf(ios::fixed);
	cout.precision(2);

	if (nWords < FILE_NOT_FOUND) {
		cout << "No words were loaded, so I can't play the game." << endl;
		return 1;
	}

	int round;
	int count = 0;
	cout << "How many rounds do you want to play? ";
	cin >> round;
	if (round <= 0)
	{
		cout << "The number of rounds must be positive." << endl;
		return 1;
	}
	else
	{
		int min = 0;
		int max = 0;
		double average = 0;
		int tries = 0;
		cout << endl;
		while (count != round) // Starts the game
		{
			count++;

			int wordnum = randInt(0, nWords - 1);

			
			cout << "Round " << count << endl;
			char* myWord = words[wordnum];
			//cerr << "CHEAT: " << myWord << endl; // CHEATING 
			cout << "The hidden word is " << strlen(myWord) << " letters long." << endl;

			tries = playOneRound(words, nWords, wordnum);
			
			if (tries == -1)
			{
				return 1;
			}

			if (tries == 1)
				cout << "You got it in " << tries << " try." << endl;
			else
				cout << "You got it in " << tries << " tries." << endl;


			if (count == 1)
			{
				min = tries;
				max = tries;
			}
			else
			{
				if (tries < min)
					min = tries;
				if (tries > max)
					max = tries;
			}
			average = ((average * (count - 1)) + tries) / count;

			cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl;
			cout << endl;
		}
	}
	return 0;
}

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum){
	

	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
		return -1;

	char hiddenWord[MAXWORDLEN + 1];
	strcpy(hiddenWord, words[wordnum]); // selectRandom

	int lenHiddenWord = strlen(hiddenWord); // get the length of hiddenWord
	
	bool match[MAXWORDLEN]; // if gold or silver match is found, set index to true. The indices are same as the hiddenWord

	char probeWord[MAXPROBWORDLEN + 1];
	int goldSilverHolder[MAXPROBWORDLEN]; // 0 not found, 1 silver , 2 gold. The indices are same as the probeWord
	int golds; // total number of golds
	int silvers; // total number of silvers

	int numberOfTries = 0; // # of tries for finding the hidden word
	int minLength; // min length of hidden and probe word
	int lenProbeWord; // length of probe word

	bool validProbe; //check whether probe word is valid
	bool knownWord;
	do {
		cout << "Probe word: ";
		cin >> probeWord; // take probe word as input
		

		lenProbeWord = strlen(probeWord); 
		validProbe = true;
		knownWord = false;

		if (lenProbeWord >= 4 && lenProbeWord <= 6) // check whether probe word is valid
		{
			for (int i = 0; i < lenProbeWord; i++)
			{
				if (!islower(probeWord[i]))
				{
					validProbe = false;
					break;
				}
			}
		}
		else
			validProbe = false;


		if (validProbe) {

			// if valid, search in the dictionary
			for (int i = 0; i < nWords; i++)
			{
				if (strcmp(probeWord, words[i]) == 0)
					knownWord = true;
			}

			if (knownWord)
			{
				numberOfTries++;
				golds = 0;
				silvers = 0;

				// Reset goldSilverHolder
				for (int i = 0; i < MAXPROBWORDLEN; i++)
					goldSilverHolder[i] = 0; // 0 for empty, 1 for silver, 2 for gold

				// Reset matching array
				for (int i = 0; i < lenHiddenWord; i++)
					match[i] = false;

				minLength = lenProbeWord;
				if (lenProbeWord > lenHiddenWord)
					minLength = lenHiddenWord;

				// Count golds and mark them
				for (int i = 0; i < minLength; i++)
				{
					if (hiddenWord[i] == probeWord[i])
					{
						golds++;
						goldSilverHolder[i] = 2;
						match[i] = true;
					}
				}


				// Count silvers and mark them
				for (int i = 0; i < lenProbeWord; i++)
				{
					for (int j = 0; j < lenHiddenWord; j++)
					{
						if (goldSilverHolder[i] == 0 && match[j] == false && probeWord[i] == hiddenWord[j])
						{
							silvers++;
							goldSilverHolder[i] = 1;
							match[j] = true;
						}
					}
				}

				// If probeWord is same as hiddenWord terminate round 
				if (strcmp(probeWord, hiddenWord) == 0)
				{

					return numberOfTries;

				}
				else // continue round since hiddenWord is not found
					cout << "Golds: " << golds << ", Silvers: " << silvers << endl;
			}
			else
				cout << "I don't know that word." << endl;
		}
		else
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;


	} while (true);
	
	

}

