#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos); //no additional array
int countRuns(const string a[], int n);
int flip(string a[], int n); //no additional array
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter); //no additional array
int resetArray(const string a_1[], string a_reset[], int n);

int main()
{
	string people[5] = { "boris", "gordon", "rishi", "liz", "john" };
	cerr << "FUNCTION 1 -- appendToAll" << endl;
	int func_1_return = appendToAll(people, 3, "!!!");
	for (int i = 0; i < 5; i++)
	{
		cerr << people[i] << endl;
	}
	cerr << func_1_return << endl;
	cerr << "FUNCTION 1 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 2 -- lookup" << endl;
	assert(lookup(people, 0, "john") == -1);  // should return -1 (not found)
	assert(lookup(people, 1, "john") == -1);
	assert(lookup(people, 2, "john") == -1);
	assert(lookup(people, 3, "john") == -1);
	assert(lookup(people, 4, "john") == -1);
	assert(lookup(people, 5, "john") == 4);
	cerr << "FUNCTION 2 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 3 -- positionOfMax" << endl;
	string pm[6] = { "david", "liz", "boris", "tony", "tony", "boris" };
	assert(positionOfMax(pm, 0) == -1);
	assert(positionOfMax(pm, 1) == 0);
	assert(positionOfMax(pm, 2) == 1);
	assert(positionOfMax(pm, 3) == 1);
	assert(positionOfMax(pm, 4) == 3);
	assert(positionOfMax(pm, 5) == 3);
	assert(positionOfMax(pm, 6) == 3);
	cerr << "FUNCTION 3 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 4 -- rotateLeft" << endl;
	const string mp_c[5] = { "john", "david", "liz", "theresa", "margaret" };

	string mp[5];
	resetArray(mp_c, mp, 5);
	assert(rotateLeft(mp, 5, 0) == 0 && mp[0] == "david" && mp[1] == "liz" && mp[2] == "theresa" && mp[3] == "margaret" && mp[4] == "john");
	resetArray(mp_c, mp, 5);
	assert(rotateLeft(mp, 5, 1) == 1 && mp[0] == "john" && mp[1] == "liz" && mp[2] == "theresa" && mp[3] == "margaret" && mp[4] == "david");
	resetArray(mp_c, mp, 5);
	assert(rotateLeft(mp, 5, 2) == 2 && mp[0] == "john" && mp[1] == "david" && mp[2] == "theresa" && mp[3] == "margaret" && mp[4] == "liz");
	resetArray(mp_c, mp, 5);
	assert(rotateLeft(mp, 5, 3) == 3 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "margaret" && mp[4] == "theresa");
	resetArray(mp_c, mp, 5);
	assert(rotateLeft(mp, 5, 4) == 4 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "theresa" && mp[4] == "margaret");
	resetArray(mp_c, mp, 5);
	//assert(rotateLeft(mp, 5, 5) == -1 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "theresa" && mp[4] == "margaret");
	//resetArray(mp_c, mp, 5);
	//assert(rotateLeft(mp, 3, 5) == -1 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "theresa" && mp[4] == "margaret");
	//resetArray(mp_c, mp, 5);
	//assert(rotateLeft(mp, 3, 5) == -1 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "theresa" && mp[4] == "margaret");
	//resetArray(mp_c, mp, 5);
	//assert(rotateLeft(mp, 3, 5) == -1 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "theresa" && mp[4] == "margaret");
	//resetArray(mp_c, mp, 5);
	//assert(rotateLeft(mp, 3, 5) == -1 && mp[0] == "john" && mp[1] == "david" && mp[2] == "liz" && mp[3] == "theresa" && mp[4] == "margaret");
	//resetArray(mp_c, mp, 5);
	cerr << "FUNCTION 4 -- TESTS PASSED" << endl;


	cerr << "FUNCTION 5 -- countRuns" << endl;
	string d[9] = {
		"tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"
	};
	assert(countRuns(d, -5) == -1);
	assert(countRuns(d, 0) == 0);
	assert(countRuns(d, 1) == 1);
	assert(countRuns(d, 2) == 2);
	assert(countRuns(d, 3) == 3);
	assert(countRuns(d, 4) == 3);
	assert(countRuns(d, 5) == 4);
	assert(countRuns(d, 6) == 4);
	assert(countRuns(d, 7) == 4);
	assert(countRuns(d, 8) == 5);
	assert(countRuns(d, 9) == 5);
	cerr << "FUNCTION 5 -- TESTS PASSED" << endl;


	cerr << "FUNCTION 6 -- flip" << endl;
	string flip_numbers1[6] = { "1", "2", "3", "4", "5", "6" };
	string flip_numbers2[5] = { "1", "2", "3", "4", "5", };
	string flip_numbers3[2] = { "1", "" };
	string flip_numbers4[1] = { "" };
	assert(flip(flip_numbers1, 6) == 6 && flip_numbers1[0] == "6" && flip_numbers1[1] == "5" && flip_numbers1[2] == "4" && flip_numbers1[3] == "3" && flip_numbers1[4] == "2" && flip_numbers1[5] == "1");
	assert(flip(flip_numbers2, 5) == 5 && flip_numbers2[0] == "5" && flip_numbers2[1] == "4" && flip_numbers2[2] == "3" && flip_numbers2[3] == "2" && flip_numbers2[4] == "1");
	assert(flip(flip_numbers3, 2) == 2 && flip_numbers3[0] == "" && flip_numbers3[1] == "1");
	assert(flip(flip_numbers4, 1) == 1 && flip_numbers4[0] == "");
	assert(flip(flip_numbers4, 0) == 0);
	cerr << "FUNCTION 6 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 7 -- differ" << endl;
	string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
	string politician[5] = { "boris", "rishi", "david", "", "tony" };
	assert(differ(leader, 6, politician, 5) == 2);
	assert(differ(leader, 2, politician, 1) == 1);
	cerr << "FUNCTION 7 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 8 -- subsequence" << endl;
	string names[10] = { "john","margaret", "theresa", "rishi", "boris", "liz" };
	string names1[3] = { "margaret", "theresa", "rishi" };
	string names2[2] = { "john", "rishi" };
	assert(subsequence(names, 6, names1, 3) == 1);
	assert(subsequence(names, 5, names2, 2) == -1);

	string f8_numbers1[7] = { "1","2","3","4","5","6","7" };
	string f8_numbers2[3] = { "5","6","7" };
	string f8_numbers3[3] = { "1","2","3" };
	assert(subsequence(f8_numbers1, 7, f8_numbers2, 3) == 4);
	assert(subsequence(f8_numbers1, 7, f8_numbers2, 0) == 0);
	assert(subsequence(f8_numbers1, 0, f8_numbers2, 0) == 0);
	assert(subsequence(f8_numbers1, 0, f8_numbers2, 1) == -1);
	assert(subsequence(f8_numbers1, 7, f8_numbers3, 3) == 0);
	cerr << "FUNCTION 8 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 9 -- lookupAny" << endl;
	string f9_names[6] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
	string f9_set1[4] = { "david", "boris", "rishi", "margaret" };
	string f9_set2[2] = { "tony", "gordon" };
	assert(lookupAny(f9_names, 6, f9_set1, 4) == 1);
	assert(lookupAny(f9_names, 6, f9_set2, 2) == -1);
	assert(lookupAny(f9_names, 6, f9_set2, 0) == -1);
	assert(lookupAny(f9_names, 0, f9_set2, 1) == -1);
	cerr << "FUNCTION 9 -- TESTS PASSED" << endl;

	cerr << "FUNCTION 10 -- split" << endl;

	string splitter;
	string mySplit1[5] = { "1","2","3","4","4" };
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit1, 5, splitter) << endl; // SHOULD BE 5
	for (int i = 0; i < 5; i++)
	{
		cerr << mySplit1[i] << " ";

	}
	cerr << endl;


	string mysplit2[2] = { "5","1" };
	splitter = "4";
	cerr << "returned value: " << split(mysplit2, 2, splitter) << endl; // should be 2
	for (int i = 0; i < 2; i++)
	{
		cerr << mysplit2[i] << " ";

	}
	cerr << endl;
	string mysplit3[7] = { "1","4","2","3","4","1","4" }; // should be  7
	splitter = "4";
	cerr << "returned value: " << split(mysplit3, 7, splitter) << endl;;
	for (int i = 0; i < 7; i++)
	{
		cerr << mysplit3[i] << " ";

	}
	cerr << endl;

	string mySplit4[2] = { "1","4" }; // should be  7
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit4, 2, splitter) << endl;;
	for (int i = 0; i < 2; i++)
	{
		cerr << mySplit4[i] << " ";

	}
	cerr << endl;

	string mySplit5[7] = { "5","4","5","3","4","1","4" }; // should be  5
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit5, 7, splitter) << endl;;
	for (int i = 0; i < 7; i++)
	{
		cerr << mySplit5[i] << " ";

	}
	cerr << endl;

	string mySplit6[7] = { "5","4","5","5","5","4","4" }; // should be  7
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit6, 7, splitter) << endl;;
	for (int i = 0; i < 7; i++)
	{
		cerr << mySplit6[i] << " ";

	}
	cerr << endl;

	string mySplit7[1] = { "1" };
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit7, 1, splitter) << endl;;
	for (int i = 0; i < 1; i++)
	{
		cerr << mySplit7[i] << " ";

	}
	cerr << endl;

	string mySplit8[1] = { "4" };
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit8, 1, splitter) << endl;;
	for (int i = 0; i < 1; i++)
	{
		cerr << mySplit8[i] << " ";

	}
	cerr << endl;

	string mySplit9[1] = { "5" };
	splitter = "4";
	cerr << "RETURNED VALUE: " << split(mySplit9, 1, splitter) << endl;;
	for (int i = 0; i < 1; i++)
	{
		cerr << mySplit9[i] << " ";

	}
	cerr << endl;
	cerr << "FUNCTION 10 -- TESTS PASSED" << endl;

}
// Append value to the end of each of the n elements of the array and return n.
int appendToAll(string a[], int n, string value)
{
	if (n >= 0)
	{
		for (int i = 0; i < n; i++)
		{
			a[i] += value; // appends string to each element.
		}
		return n;
	}
	else
		return -1;
}

// Return the position of a string in the array that is equal to target; 
// if there is more than one such string, return the smallest position number of such a matching string. 
// Return -1 if there is no such string.
int lookup(const string a[], int n, string target)
{
	if (n >= 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (a[i] == target)
				return i; //returns the position of the target
		}
	}
	return -1; // returns -1 if target is not found in the array.
}

//Return the position of a string in the array such that that string is >= every string in the array.
//If there is more than one such string, return the smallest position number of such a string.
//Return -1 if the array has no interesting elements.
int positionOfMax(const string a[], int n)
{
	if (n >= 1)
	{
		string max = a[0];
		for (int i = 1; i < n; i++) // Find the maximum value in a with length n
		{
			if (a[i] >= max)
				max = a[i];
		}

		for (int i = 0; i < n; i++)
		{
			if (a[i] == max)
				return i; //returns the position of the target
		}
	}
	return -1;
}

//Eliminate the item at position pos by copying all elements after it one place to the left. 
//Put the item that was thus eliminated into the last position of the array. 
//Return the original position of the item that was moved to the end. 
int rotateLeft(string a[], int n, int pos)
{
	if (n >= 1) // If it is empty returns -1
	{
		if (pos >= 0 && pos < n) // pos should be a valid index.
		{
			string temp = a[pos]; // saves the element to put at the end.
			for (int i = pos; i < n - 1; i++)
			{
				a[i] = a[i + 1];  // shifts elements after the saved element.
			}
			a[n - 1] = temp; // writes element to end.
			return pos;
		}
		else
			return -1;
	}
	else
		return -1;
}

//Return the number of sequences of one or more consecutive identical items in a.
int countRuns(const string a[], int n)
{
	if (n >= 0) //return 0 if n = 0
	{
		int countSeq = 0; // number of sequence starts at 0, if no sequence found returns 0.
		if (n > 0)
		{
			string temp = a[0]; // saves the first element in an non-empty array.
			countSeq++;

			for (int i = 1; i < n; i++)
			{
				if (a[i] != temp) // checks whether the next element is same as the previous one. If it is not same, a new sequence has started.
				{
					temp = a[i]; // saves the element to use at the next iteration.
					countSeq++;
				}
			}
		}
		return countSeq;
	}
	else
		return -1;
}

//Reverse the order of the elements of the array and return n. { "1", "2", "3", "4", "5", };
int flip(string a[], int n)
{
	if (n >= 0)
	{
		string temp;
		for (int i = 0, j = n - 1; i < n / 2; i++, j--) // reverses the array by swapping first index with end, first + 1 with end - 1. It goes on until i reaches the middle of the array.
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		return n;
	}
	else
		return -1;
}

//Return the position of the first corresponding elements of a1 and a2 that are not equal. n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2.
//If the arrays are equal up to the point where one or both runs out, return whichever value of n1 and n2 is less than or equal to the other.
int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 >= 0 && n2 >= 0)
	{
		int min_n = n2;
		if (min_n >= n1) // I found the minimum(n1,n2) to use it to iterate over the two arrays.
			min_n = n1;

		for (int i = 1; i < min_n; i++)
		{
			if (a1[i] != a2[i]) // returns the index where both arrays do not have the same element.
				return i;
		}
		return min_n;
	}
	else
		return -1;
}


//If all n2 elements of a2 appear in a1, consecutivelyand in the same order, 
//then return the position in a1 where that subsequence begins.If the subsequence appears more than once in a1, return the smallest such beginning position in the array.
//Return -1 if a1 does not contain a2 as a contiguous subsequence.
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 >= 0 && n2 >= 0)
	{
		if (n2 == 0)
		{
			return 0; // a subsequence of 0 element starts at index 0, regardless of a1[];
		}
		else
		{
			int count = 0;
			for (int i = 0; i < n1; i++)
			{
				if (a1[i] == a2[count]) // counting consecutive item matches between a1[] and a2[]
					count++;
				else
					count = 0; // if we get a different element, I reset the matching.

				if (count == n2)
					return i - count + 1; // if all items are found in a1[], returns the start index of the subsequence.
			}
			return -1; // returns -1, if no subsequence is found.
		}
	}
	else
		return -1;
}


//Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2.
//Return -1 if no element of a1 is equal to any element of a2.
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 >= 0 && n2 >= 0)
	{
		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < n2; j++)
			{
				if (a1[i] == a2[j]) // For each element in a1, I check whether that element is also occurs at the a2. If it does I return the position of that element.
					return i;
			}
		}
		return -1; // returns -1 if no element of a1 occurs at a2.
	}
	else
		return -1; // invalid array length.
}

//Rearrange the elements of the array so that all the elements whose value is < splitter come before all the other elements,
//and all the elements whose value is > splitter come after all the other elements.Return the position of the first element that, after the rearrangement, 
//is not < splitter, or n if there are no such elements.
int split(string a[], int n, string splitter) //{ "5", "4", "5", "5", "5", "4", "4" }
{
	if (n >= 1)
	{
		int i = 0;
		int j = n - 1;
		int count = 0;
		string temp;
		while (i != j) // There are two ways to exit this loop, first one is for arrays that do not include splitter. In that case, when i = j, we have splitted the array.
		{

			if (a[i] < splitter)
			{
				i++; //do not do anything just pass index since it is at the valid position.
			}
			else if (a[i] > splitter)
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
				j--; // this element is not in the valid position and should be at the back of the array, 
				//therefore I swap with the end element, and to not touch that value again I decrease the index refers to the end. 
				//Note that i is not changed, therefore a check will be made to the other element that is swapped to front.
			}
			else if (a[i] == splitter)
			{
				while ((i + count) < n && a[i + count] == a[i])
				{
					count++; // try to find an element which is not equal to splitter, swap it with the ith element. 
					// While trying to find the element, we can reach to the end, so we exit the while if we reached.
				}

				if (i + count > j)
				{
					return i + count; //We should not do more swaps since the array is splitted. 
					//This statement also works if i + count reaches to the end. i + count takes the value of n, and j takes the value of n - 1.
				}

				temp = a[i + count]; // swap with the first element that has is not splitter.
				a[i + count] = a[i];
				a[i] = temp;
				count = 0;
			}

		}
		// Array is perfectly splitted, so I can the position of the first element that is > splitter, if not found return n
		for (int k = 0; k < n; k++)
		{
			if (a[k] > splitter)
				return k;
		}
		return n;
	}
	else if (n == 0) // No elements mean that there are no elements such that > splitter. Return n;
		return 0;
	else
		return -1;
}


int resetArray(const string a_1[], string a_reset[], int n)
{
	for (int i = 0; i < n; i++) {
		a_reset[i] = a_1[i];
	}
	return 0;
}

