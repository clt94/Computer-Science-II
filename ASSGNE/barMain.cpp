/*
   COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved.
   CSII Assignment E
   Author.  Connor Taylor
            clt94@zips.uakron.edu
   Version. 1.01 10.17.2019
   Purpose: Encodes and decodes 27 number bar codes of 0's and 1's to 5 digit zip codes
*/

#include <iostream>
#include <string>

// place your classes and methods here
// Defines class ZipCode
class ZipCode
{
public:
    ZipCode(int zip)                    // overloaded and inlined public constructor that is passed an integer, code,
    {   this->zip = zip;  }             // that sets to the int zip
    ZipCode(std::string barCode)        // overloaded and inlined public constructor that is passed a string, code,
    {   zip = parseBarCode(barCode);}   // by reference and converts it to and int, zip
    int getZipCode()                  // inlined getter function that returns the int, zip
    {   return zip; }
    std::string getBarCode();         // getter function that returns a string containing the bar code
private:
    int zip;                        // private int zip (should be a maximum of 5 digits
    int parseBarCode(std::string&); // private method that converts a string bar code to an int and returns an int
    bool isValid(std::string&);     // private method that validates a bar code and returns true if it is valid
};

// Precondition: None
// Cpnstructor that converts 5 digit zip code to a 27 digit string of 0's and 1's
// Postcondition: returns a string
std::string ZipCode::getBarCode()
{
    // initializes string with 1 as the bar code requires a 1 one each end
    std::string barCode = "11";
    // initializes an int, tempZip, so zip does not get changed
    int tempZip = zip;
    // initializes an int, digit, which will be set to each individual value in zip
    int digit = 0;
    // for loop that iterates through each digit in zip
    for(size_t i{0}; i < 5; ++ i)
    {
        // sets digit to the last digit in tempZip
        digit = tempZip % 10;
        // removes last digit from tempZip
        tempZip /= 10;
        // switch statements that takes digit and adds the appropriate string to index 1 of barCode because it is working backwards
        switch (digit)
        {
        case 0:
            barCode.insert(1, "11000");
            break;
        case 1:
            barCode.insert(1, "00011");
            break;
        case 2:
            barCode.insert(1, "00101");
            break;
        case 3:
            barCode.insert(1, "00110");
            break;
        case 4:
            barCode.insert(1, "01001");
            break;
        case 5:
            barCode.insert(1, "01010");
            break;
        case 6:
            barCode.insert(1, "01100");
            break;
        case 7:
            barCode.insert(1, "10001");
            break;
        case 8:
            barCode.insert(1, "10010");
            break;
        case 9:
            barCode.insert(1, "10100");
            break;
        }
    }
    // returns string barCode
    return barCode;
}

// Precondition: passed a string named barCode by reference
// Validates and then converts barCode to an int
// Postcondition: an int that should be 5 digits
int ZipCode::parseBarCode(std::string& barCode)
{
    // calls isValid function to ensure that barCode is within guidelines
    if(isValid(barCode))
    {
        // sets tempCount to 0 which tracks the index for every 5 characters of barCode, set tempTotal which
        // totals every five characters to a digit 0 to 9, and sets zip to 0
        int tempCount = 0;
        int tempTotal = 0;
        zip = 0;
        // iterates from 1 to 25 because the first and last digit are one and exclusive from sequence
        for(size_t i{1}; i < 26; ++i)
        {
            // if the first index is 1 then it adds 7 for that digit
            if(tempCount == 0 && barCode[i] == '1')
            {
                tempTotal += 7;
            }
            // if the second index is 1 then it adds 4 for that digit
            else if(tempCount == 1 && barCode[i] == '1')
            {
                tempTotal += 4;
            }
            // if the third index is 1 then it adds 2 for that digit
            else if(tempCount == 2 && barCode[i] == '1')
            {
                tempTotal += 2;
            }
            // if the fourth index is 1 then it adds 1 for that digit
            else if(tempCount == 3 && barCode[i] == '1')
            {
                tempTotal += 1;
            }
            // if the fifth index enter and doesn't add anything as it would just add 0
            else if(tempCount == 4)
            {
                // checks if total is 11, if it is then it adds 0 instead of 11
                if(tempTotal == 11)
                {
                    zip += 0;
                }
                // else just add total to that place in zipCode
                else
                {
                    zip += tempTotal;
                }
                // resets tempCount and tempTotal
                tempCount = -1;
                tempTotal = 0;
                // checks to ensure it is not at the end of the bar code
                // if it is not then multiply by 10 to enter next digit in the zip code
                if(i != 25)
                {
                    zip *= 10;
                }
            }
            // iterates tempCount by 1
            ++ tempCount;
        }
        // returns the final zip
        return zip;
    }
    // returns -1 to show something went wrong
    return -1;
}

// Precondition: passes a string named barCode by reference
// Validates barCode within guidelines
// Postcondition: a bool that is true if the barCode is valid and false if not
bool ZipCode::isValid(std::string& barCode)
{
    // makes sure the barCode is exactly 26 characters (starting at 0), returns false otherwise
    if (barCode.size() == 26)
    {
        std::cout << "ERROR: \'" << barCode << "\' has invalid length\n"
            << "\t(Length must be 5*n+2, where n is the number of\n"
            << "\tdigits in the zip code)" << std::endl;
            return false;
    }
    // makes sure barCode starts and ends in 1, returns false otherwise
    if (barCode[0] != '1' || barCode[26] != '1')
    {
        std::cout << "ERROR: \'" << barCode << "\' must begin and end with \'1\'" << std::endl;
        return false;
    }
    // runs through code and ensures the barCode contains only 1's and 0's, and ensures it has
    // only two 1's every five characters, excluding the beginning, 0, and end, 26
    int oneCount = 0;
    int tempCount = 0;
    // starts at 1 and ends at 25 because the 0 and 26 are both ones and excluded from zip code sequence
    for(size_t i{1}; i < 26; ++i)
    {
        // checks if barCode at index i is either a 1 or 0, and if it is not outputs error and returns false
        if(barCode[i] != '0' && barCode[i] != '1')
        {
            std::cout << "ERROR: \'" << barCode << "\' must contain only \'1\' and \'0\'" << std::endl;
            return false;
        }

        // this half validates for having every 5 values contain only two 1's
        // tempCount serves the purpose of checking only every 5 values of barCode
        // increments count of ones, oneCount, in sequence of 5
        if(barCode[i] == '1')
        {
            ++oneCount;
        }
        // enters if statement after every sequence of 5
        if(tempCount == 4)
        {
            // if a sequence of 5 does not have exactly two 1's, then it returns false
            if(oneCount != 2)
            {
                std::cout << "ERROR: \'" << barCode << " has invalid sequence \'" << barCode.substr(i - 4, 5) << "\'" << std::endl;
                return false;
            }
            // resets tempCount and oneCount to 0 to check next sequence of 5
            tempCount = 0;
            oneCount = 0;
        }
        // increments tempCount if sequence of not a full sequence of 5 yet
        else
        {
            ++ tempCount;
        }
    }
    // returns true if it is completely valid
    return true;
}

// MAIN FUNCTION
int main()
{

    ZipCode zip(99504),
	    zip2("100101010011100001100110001"),
	    zip3(12345),
	    zip4(67890);

    int BAD_ZIP_COUNT = 5;
    std::string bad_zips[][2] = {
      { "10010101001110000110011001", "bad length" },
      { "000101010011100001100110001", "bad start/end character" },
      { "100101010011100001100110000", "bad start/end character" },
      { "100101010011100001100110021", "bad digit" },
      { "100101010011100001100111001", "bad sequence" }
      };
    std::cout << zip.getZipCode() << "'s bar code is '"
         << zip.getBarCode() << "'" << std::endl;
    std::cout << zip2.getZipCode() << "'s bar code is '"
	       << zip2.getBarCode() << "'" << std::endl;
    std::cout << zip3.getZipCode() << "'s bar code is '"
         << zip3.getBarCode() << "'" << std::endl;
    std::cout << zip4.getZipCode() << "'s bar code is '"
	       << zip4.getBarCode() << "'" << std::endl;
    std::cout << std::endl;

    // Test a range of values by first constructing a zip code with
    // an integer, then retrieving the bar code and using that to
    // construct another ZipCode.
    int zip_int = 0;
    for (int i = 0; i < 25; i++)
    {
      // Make an aribrary 5-digit zip code integer, and use it
      // to construct a ZipCode
      int five_digit_zip = (zip_int * zip_int) % 100000;
      ZipCode z1(five_digit_zip);

      // Construct a second ZipCode from the first's bar code
      std::string z1_code = z1.getBarCode();
      ZipCode z2(z1_code);

      std::cout.width(3);
      std::cout << (i + 1) << ": ";
      std::cout.width(5);
      std::cout << z2.getZipCode() << " has code '"
           << z1_code << "'";

      if ((z1_code == z2.getBarCode()) &&
          (z1.getZipCode() == z2.getZipCode()) &&
          (z2.getZipCode() == five_digit_zip))
      {
          std::cout << " [OK]" << std::endl;
      }
      else
      {
          std::cout << " [ERR]" << std::endl;
      }

      // Increment the test value arbitrarily
      zip_int += (233 + zip_int % 7);
    }

    std::cout << std::endl;

    // Test some error conditions. This test assumes that
    // ZipCode will simply set its value to a flag that indicates
    // an error, and will not exit the program.
    for (int i = 0; i < BAD_ZIP_COUNT; i++)
    {
      std::cout << "Testing: " << bad_zips[i][1] << std::endl;
      ZipCode test(bad_zips[i][0]);
      std::cout << std::endl;
    }

    std::cout << "Press any key to continue." << std::endl;
    std::cin.get();

    return 0;
}
