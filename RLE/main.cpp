#include <iostream>
#include <string>

/// Finds the next int in a delimiter-separated kind-of list
/// (used for finding run lengths for the decoding function)
std::string::size_type nextInt(std::string str, char delimiter,
               int& result, std::string::size_type start = 0) {

  std::string intString = "";
  std::string::size_type lastPos = start;
  // Loop through string starting at "start" position
  for(auto i : str.substr(start, std::string::npos)) {
    if(i != delimiter) {
      // If current char is not delimiter, append it to the int string
      lastPos++;
      intString.append(1, i);
    } else {
      // Else the int string is complete, so convert and return
      result = std::stoi(intString);
      return lastPos;
    }
  }
  // No new delimiter found, and the loop has ended, so no new int to return
  return std::string::npos;
}

/// Encodes a string using RLE algorithm
std::string encode(std::string str) {
  std::string RLEString = "";
  int charRunLength = 0;
  char lastChar = -1;

  // Loop through string
  for(auto i : str) {
    if(i == lastChar) {     //  If it's the same char as the prev one,
      charRunLength++;      //    just add to the run length

    } else {                //  Else add it up to the encoded string in
      if(lastChar != -1) {  //    format <run length>*<char>
        RLEString = RLEString + std::to_string(charRunLength) +
                    std::string("*") + std::string(1, lastChar);
      }
      lastChar = i;
      charRunLength = 1;
    }
  }

  // Also add the last one
  RLEString = RLEString + std::to_string(charRunLength) +
              std::string("*") + std::string(1, lastChar);

  // Return the encoded string, we're done :)
  return RLEString;
}

/// Decodes a string that was encoded using RLE algorithm
std::string decode(std::string RLEString) {
  std::string str = "";
  char character;
  int runLength;
  std::string::size_type currentPos = 0;

  // Loop through all the runs and rips
  while((currentPos =
           nextInt(RLEString, '*',
                   runLength, currentPos)) != std::string::npos) {
    // Skip to the rip pos
    ++currentPos;

    // Gen the run length
    character = RLEString.at(currentPos);

    // And add the chars to the decoded string
    str.append(runLength, character);

    // Skip to the next run pos
    ++currentPos;
  }

  //Return the decoded string, we're done :)
  return str;
}

/// Main function
int main() {
  std::string toEncode, encoded;
  std::string toDecode, decoded;

  // Encode sequence
  std::cout << "Data to encode: ";
  std::cin >> toEncode;
  std::cin.ignore();
  encoded = encode(toEncode);
  std::cout << "Result: " << encoded << std::endl;

  // Print an extra line for fanciness
  std::cout << std::endl;

  // Decode sequence
  std::cout << "Data to decode: ";
  std::cin >> toDecode;
  std::cin.ignore();
  decoded = decode(toDecode);
  std::cout << "Result: " << decoded << std::endl;
  system("pause");
  return 0;
}
