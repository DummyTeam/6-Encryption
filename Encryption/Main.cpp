﻿#include<iostream>
#include<string>
#include<cmath>

using namespace std;

#define ull unsigned long long 

string XOR(string, string);
string BCH(string);
string decToBin(ull);
string strToBin(string);

// A1 and B2 should be in binary
string OR(string a1, string a2)
{
	string larger = a1.size() >= a2.size() ? a1 : a2;
	string smaller = a1.size() < a2.size() ? a1 : a2;


	string res = "";

	for (int i = 1; i <= larger.size(); i++)
	{
		char next = '0';
		if (i > smaller.size())
		{
			next = (larger[larger.size() - i] - '0' >= 1) ? '1' : '0';
			res = next + res;
			continue;
		}
		next = (larger[larger.size() - i] - '0' + smaller[smaller.size() - i] - '0' >= 1) ? '1' : '0';
		res = next + res;
	}

	return res;
}

// A1 and B2 should be in binary
string XOR(string a1, string a2)
{
	int size = a1.size() < a2.size() ? a1.size() : a2.size();
	string res = "";

	for (size_t i = 1; i <= size; i++)
	{
		char next = (a1[a1.size() - i] - '0' + a2[a2.size() - i] - '0' == 1) ? '1' : '0';
		res = next + res;
	}

	// TODO: Substring the fron excess part of the 
	//		 larger string to the front of res string

	return res;
}

// Binary Coded Hexadecimal - returns binary of hex number
string BCH(string hexadec) { // TODO: Must convert all chars toUpperCase
	string res = "";

	for (size_t i = 0; i < hexadec.size(); i++)
	{
		string charBin = decToBin((hexadec[i] > '9') ? hexadec[i] - 'A' + 10 : hexadec[i] - '0');

		int initialPadding = 4 - charBin.size();

		while (initialPadding--)
		{
			charBin = "0" + charBin;
		}

		res += charBin;
	}

	return res;
}

string decToBin(ull dec) {
	int bin;

	string charBin = "";

	while (dec > 0)
	{
		bin = dec % 2;
		charBin = to_string(bin) + charBin;
		dec /= 2;
	}

	return charBin;
}

string toUpper(string str) {
	for (string::iterator i = str.begin(); i != str.end(); i++)
	{
		if ((*i) >= 'a' && (*i) <= 'z')
		{
			(*i) -= ('a' - 'A');
		}
	}
	return str;
}

string strToBin(string message) {
	string res = "";

	for (size_t i = 0; i < message.size(); i++)
	{
		ull decMessage = (ull)message[i];

		string charBin = decToBin(decMessage);

		int initialPadding = 8 - charBin.size();

		while (initialPadding--)
		{
			charBin = "0" + charBin;
		}

		res += charBin;
	}

	return res;
}

int binToDec(string input) {
	int dec = 0;
	for (int i = input.size() - 1, j = 0; i >= 0; i--, j++)
	{
		dec += (input[i] - '0') * pow(2, j);
	}

	return dec;
}

string runThroughTable(string input, int arr[], int size) {
	string res = "";

	for (size_t i = 0; i < size; i++)
	{
		res += input[arr[i] - 1];
	}

	return res;
}

string shiftLeft(string input, int shiftValue) {
	string res = input.substr(shiftValue);

	for (size_t i = 0; i < shiftValue; i++)
	{
		char c = input[i];
		res.push_back(c);
	}

	return res;
}

string runThroughSBoxes(string input48) {

	int S[][4][16] = {
		{
			{ 14,  4,  13,  1,   2, 15,  11,  8,   3, 10,  6, 12,   5,  9,  0,  7 },
			{ 0,  15,   7,  4,  14,  2,  13,  1,  10,  6, 12, 11,   9,  5,  3,  8 },
			{ 4,   1,  14,  8,  13,  6,   2, 11,  15, 12,  9,  7,   3, 10,  5,  0 },
			{ 15, 12,   8,  2,   4,  9,   1,  7,   5, 11,  3, 14,  10,  0,  6, 13 }
		},
		{
			{ 15,  1,   8, 14,   6, 11,  3,  4,   9,  7,   2,  13,  12,  0,   5, 10 },
			{ 3 , 13,   4,  7,  15,  2,  8, 14,  12,  0,   1,  10,   6,  9,  11,  5 },
			{ 0 , 14,   7, 11,  10,  4, 13,  1,   5,  8,  12,   6,   9,  3,   2, 15 },
			{ 13,  8,  10,  1,   3, 15,  4,  2,  11,  6,   7,  12,   0,  5,  14,  9 }
		},
		{
			{ 10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8 },
			{ 13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1 },
			{ 13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7 },
			{  1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12 }
		},
		{
			{  7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15 },
			{ 13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9	},
			{ 10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4	},
			{  3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14	}
		},
		{
			{  2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9 },
			{ 14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6 },
			{  4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14 },
			{ 11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3 }
		},
		{
			{ 12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11	},
			{ 10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8	},
			{  9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6	},
			{  4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13	}
		},
		{
			{  4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6, 1  },
			{ 13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8, 6  },
			{  1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9, 2  },
			{  6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12 }
		},
		{
			{ 13, 2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7 },
			{ 1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2 },
			{ 7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8 },
			{ 2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11 }
		},
	};

	string res = "";

	for (size_t i = 0; i < 8; i++)
	{
		string SInput = input48.substr(i * 6, 6);

		int row = binToDec(string({ SInput[0], SInput[SInput.size() - 1] }));
		int column = binToDec(SInput.substr(1, 4));

		res += OR(decToBin(S[i][row][column]), "0000");

	}

	return res;
}

string f(string input, string key) {

	int E[] = { 32,     1,    2,     3,     4,    5,
				  4,     5,    6,     7,     8,    9,
				  8,     9,   10,    11,    12,   13,
				 12,    13,   14,    15,    16,   17,
				 16,    17,   18,    19,    20,   21,
				 20,    21,   22,    23,    24,   25,
				 24,    25,   26,    27,    28,   29,
				 28,    29,   30,    31,    32,    1 };

	int permutation32to32[] = {
						 16,   7,  20,  21,
						 29,  12,  28,  17,
						  1,  15,  23,  26,
						  5,  18,  31,  10,
						  2,   8,  24,  14,
						 32,  27,   3,   9,
						 19,  13,  30,   6,
						 22,  11,   4,  25 };

	string expanded48 = runThroughTable(input, E, 48);

	string res48 = XOR(key, expanded48);

	string res32 = runThroughSBoxes(res48);

	return runThroughTable(res32, permutation32to32, 32);

}

string binToHex(string bin) {
	string res = "";
	for (size_t i = 0; i < bin.size() / 4; i++)
	{
		int decNum = binToDec(bin.substr(i * 4, 4));
		string hexNum = (decNum < 10) ? to_string(decNum) : string(1, decNum - 10 + 'A');
		res += hexNum;
	}

	return res;
}

string stringToHex(string str) {
	string bin = strToBin(str);
	string hex = binToHex(bin);
	return hex;
}

string formatMessage(string input) {
	string carriageReturn = "0D";
	string lineFeed = "0A";

	string totalMessage = stringToHex(input) + carriageReturn + lineFeed;
	totalMessage += string((16 - totalMessage.size() % 16), '0');
	return totalMessage;
}

string DES(string mesBlock64, string keyBlock64) {
	string binMessage = mesBlock64;
	string binKey = keyBlock64;

	/// Key generation
	// Initialized PC-1 and PC-2 table
	int pc1[] = { 57, 49, 41, 33, 25, 17,  9,
				   1, 58, 50, 42, 34, 26, 18,
				  10,  2, 59, 51, 43, 35, 27,
				  19, 11,  3, 60, 52, 44, 36,
				  63, 55, 47, 39, 31, 23, 15,
				   7, 62, 54, 46, 38, 30, 22,
				  14,  6, 61, 53, 45, 37, 29,
				  21, 13,  5, 28, 20, 12,  4 };

	int pc2[] = { 14, 17, 11, 24, 1,   5,
				  3, 28, 15,  6,  21, 10,
				 23, 19, 12,  4,  26,  8,
				 16,  7, 27, 20,  13,  2,
				 41, 52, 31, 37,  47, 55,
				 30, 40, 51, 45,  33, 48,
				 44, 49, 39, 56,  34, 53,
				 46, 42, 50, 36,  29, 32 };


	// Run the binary key through PC-1 table to get permuted 56bit key
	string permutedKey56 = runThroughTable(binKey, pc1, 56);

	// Initialized arrays for C and D parts of the round keys
	string C[17];
	string D[17];

	// Initialized array of final subkeys
	string K[16];

	// Splited the key into left and right halves, where each half has 28 bits.
	C[0] = permutedKey56.substr(0, 28);
	D[0] = permutedKey56.substr(28, 28);

	// Initialized left-shift table
	int leftShifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

	// Shifting the C and D parts to left to get other subkeys
	for (size_t i = 1; i < 17; i++)
	{
		C[i] = shiftLeft(C[i - 1], leftShifts[i - 1]);
		D[i] = shiftLeft(D[i - 1], leftShifts[i - 1]);

		// Run the concatenated C and D parts through PC-2 table to get final subkeys
		K[i - 1] = runThroughTable(C[i] + D[i], pc2, 48);
	}


	/// Encode each 64-bit block of data.
	// Initialized initial permutation table
	int ip[] = { 58, 50, 42, 34, 26, 18, 10, 2,
				 60, 52, 44, 36, 28, 20, 12, 4,
				 62, 54, 46, 38, 30, 22, 14, 6,
				 64, 56, 48, 40, 32, 24, 16, 8,
				 57, 49, 41, 33, 25, 17,  9, 1,
				 59, 51, 43, 35, 27, 19, 11, 3,
				 61, 53, 45, 37, 29, 21, 13, 5,
				 63, 55, 47, 39, 31, 23, 15, 7 };

	// Run the binary message through initial permutation table
	string permutatedMes = runThroughTable(binMessage, ip, 64);

	// Initialized arrays L(left) and R(right) part of the coded message
	string L[18];
	string R[18];

	// Splited the message into left and right halves, where each half has 32 bits.
	L[0] = permutatedMes.substr(0, 32);
	R[0] = permutatedMes.substr(32, 32);

	// Calculated all other 16 L and R parts
	for (int i = 1; i < 17; i++)
	{
		//Ln = Rn-1 
		L[i] = R[i - 1];

		// Rn = Ln-1 + f(Rn-1,Kn)
		R[i] = XOR(L[i - 1], f(R[i - 1], K[i - 1]));
	}

	// Initialized final permutation IP-1
	int IP_Minus1[] = { 40,   8,   48,   16,   56,   24,   64,   32,
					   39,   7,   47,   15,   55,   23,   63,   31,
					   38,   6,   46,   14,   54,   22,   62,   30,
					   37,   5,   45,   13,   53,   21,   61,   29,
					   36,   4,   44,   12,   52,   20,   60,   28,
					   35,   3,   43,   11,   51,   19,   59,   27,
					   34,   2,   42,   10,   50,   18,   58,   26,
					   33,   1,   41,    9,   49,   17,   57,   25 };

	string concatenatedResult = R[16] + L[16];

	return runThroughTable(concatenatedResult, IP_Minus1, 64);
}

string decrypt(string chipperBlock64, string keyBlock64) {
	string binMessage = chipperBlock64;
	string binKey = keyBlock64;

	/// Key generation
	// Initialized PC-1 and PC-2 table
	int pc1[] = { 57, 49, 41, 33, 25, 17,  9,
				   1, 58, 50, 42, 34, 26, 18,
				  10,  2, 59, 51, 43, 35, 27,
				  19, 11,  3, 60, 52, 44, 36,
				  63, 55, 47, 39, 31, 23, 15,
				   7, 62, 54, 46, 38, 30, 22,
				  14,  6, 61, 53, 45, 37, 29,
				  21, 13,  5, 28, 20, 12,  4 };

	int pc2[] = { 14, 17, 11, 24, 1,   5,
				  3, 28, 15,  6,  21, 10,
				 23, 19, 12,  4,  26,  8,
				 16,  7, 27, 20,  13,  2,
				 41, 52, 31, 37,  47, 55,
				 30, 40, 51, 45,  33, 48,
				 44, 49, 39, 56,  34, 53,
				 46, 42, 50, 36,  29, 32 };


	// Run the binary key through PC-1 table to get permuted 56bit key
	string permutedKey56 = runThroughTable(binKey, pc1, 56);

	// Initialized arrays for C and D parts of the round keys
	string C[17];
	string D[17];

	// Initialized array of final subkeys
	string K[16];

	// Splited the key into left and right halves, where each half has 28 bits.
	C[0] = permutedKey56.substr(0, 28);
	D[0] = permutedKey56.substr(28, 28);

	// Initialized left-shift table
	int leftShifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

	// Shifting the C and D parts to left to get other subkeys
	for (size_t i = 1; i < 17; i++)
	{
		C[i] = shiftLeft(C[i - 1], leftShifts[i - 1]);
		D[i] = shiftLeft(D[i - 1], leftShifts[i - 1]);

		// Run the concatenated C and D parts through PC-2 table to get final subkeys
		K[i - 1] = runThroughTable(C[i] + D[i], pc2, 48);
	}


	/// Encode each 64-bit block of data.
	// Initialized initial permutation table
	int ip[] = { 58, 50, 42, 34, 26, 18, 10, 2,
				 60, 52, 44, 36, 28, 20, 12, 4,
				 62, 54, 46, 38, 30, 22, 14, 6,
				 64, 56, 48, 40, 32, 24, 16, 8,
				 57, 49, 41, 33, 25, 17,  9, 1,
				 59, 51, 43, 35, 27, 19, 11, 3,
				 61, 53, 45, 37, 29, 21, 13, 5,
				 63, 55, 47, 39, 31, 23, 15, 7 };

	// Run the binary message through initial permutation table
	string permutatedMes = runThroughTable(binMessage, ip, 64);

	// Initialized arrays L(left) and R(right) part of the coded message
	string L[18];
	string R[18];

	// Splited the message into left and right halves, where each half has 32 bits.
	L[0] = permutatedMes.substr(0, 32);
	R[0] = permutatedMes.substr(32, 32);

	// Calculated all other 16 L and R parts
	for (int i = 1; i < 17; i++)
	{
		//Ln = Rn-1 
		L[i] = R[i - 1];

		// Rn = Ln-1 + f(Rn-1,Kn)
		R[i] = XOR(L[i - 1], f(R[i - 1], K[15 - (i - 1)]));
	}

	// Initialized final permutation IP-1
	int IP_Minus1[] = { 40,   8,   48,   16,   56,   24,   64,   32,
					   39,   7,   47,   15,   55,   23,   63,   31,
					   38,   6,   46,   14,   54,   22,   62,   30,
					   37,   5,   45,   13,   53,   21,   61,   29,
					   36,   4,   44,   12,   52,   20,   60,   28,
					   35,   3,   43,   11,   51,   19,   59,   27,
					   34,   2,   42,   10,   50,   18,   58,   26,
					   33,   1,   41,    9,   49,   17,   57,   25 };

	string concatenatedResult = R[16] + L[16];

	return runThroughTable(concatenatedResult, IP_Minus1, 64);
}

string hexToString(string hex) {
	int len = hex.length();
	std::string newString;
	for (int i = 0; i < len; i += 2)
	{
		string byte = hex.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		newString.push_back(chr);
	}
	return newString;
}

int main() {
	string message = "Incredible sentence from DummyTeam";
	string key = "FourChar";

	// TODO: Make it available for both upper and lover case

	// Initialized message and key values
	string messageHex = toUpper(formatMessage(message));	 // In HEX. Pass through toUpper to make sure all in caps
	string keyHex = toUpper(stringToHex(message));			 // In HEX. Pass through toUpper to make sure all in caps

	cout << "Message hex: \t\t" << messageHex << endl;
	cout << "Message text: \t\t" << hexToString(messageHex) << endl;

	// Converted HEX values to binary values
	string binMessage = BCH(messageHex);
	string binKey = BCH(keyHex);

	/////////////////////////////////////////////////////////////////

	string encryptedMessageBin = "";

	for (int i = 0; i < binMessage.size() / 64; i++)
	{
		encryptedMessageBin += DES(binMessage.substr(i * 64, 64), binKey);
	}

	string encryptedMessageHex = binToHex(encryptedMessageBin);

	cout << "Encrypted HEX message: \t" << encryptedMessageHex << endl;

	cout << "Encrypted message: \t" << hexToString(encryptedMessageHex) << endl << endl;

	/////////////////////////////////////////////////////////////////

	string decryptedMessageBin = "";

	for (int i = 0; i < encryptedMessageBin.size() / 64; i++)
	{
		decryptedMessageBin += decrypt(encryptedMessageBin.substr(i * 64, 64), binKey);
	}

	string dencryptedMessageHex = binToHex(decryptedMessageBin);

	cout << "Decrypted HEX message: \t" << dencryptedMessageHex << endl;

	cout << "Decrypted message: \t" << hexToString(dencryptedMessageHex) << endl;

	/////////////////////////////////////////////////////////////////

	cout << endl;

	system("pause");
	return 0;
}