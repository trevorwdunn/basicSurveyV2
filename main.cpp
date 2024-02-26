//
//  main.cpp
//  basicSurveyV2
//
//  The intention of this project is to improve upon my basicSurvey program by
//  adding support for premade .txt. files. I also intend to clean up the code a
//  lot.
//
//  Created by Trevor Dunn on 2/20/24.
//

/*
    TO DO:
    1. Get ...FromFile functions to read in data and pass all of the relevant
    vectors to main.
    2. Create a "class" class. Which won't be confusing at all.
*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

std::vector<std::string> getLocationDetails();
std::vector<std::string> getClassNames();
bool getStudentStatus();
std::vector<std::string>
getClassNamesFromFile(std::vector<std::string> *pFileData);
std::vector<std::string>
getLocationDetailsFromFile(std::vector<std::string> *pFileData);
std::vector<std::string> readFile();
char parseFileData(std::vector<std::string> &fileData);

int main() {
  // This block gets the user's name.
  std::string userName;
  std::cout << "What is your name?" << std::endl;
  getline(std::cin, userName);

  // Get the student status from a function.
  bool isAttendingClasses;
  isAttendingClasses = getStudentStatus();

  // Get the class names from a function.
  std::vector<std::string> classNames;
  if (isAttendingClasses) {
    std::vector<std::string> classNames = getClassNames();
  }

  // Get the location data from the user via promots.
  // std::vector<std::string> locationData = getLocationDetails();
  std::vector<std::string> fileData = readFile();
  std::vector<std::string> *pFileData = &fileData;
  getClassNamesFromFile(pFileData);
  getLocationDetailsFromFile(pFileData);

  return 0;
}

bool getStudentStatus() {
  // This function is designed to get the user's school status.
  char schoolResponse = false;
  std::cout << "Are you currently attending classes? (y/n)" << std::endl;
  std::cin >> schoolResponse;
  tolower(schoolResponse);

  // This block converts the user input to a boolean value.
  bool isAttendingClasses;
  if (schoolResponse == 'y') {
    isAttendingClasses = static_cast<bool>(schoolResponse);
  } else if (schoolResponse == 'n') {
    isAttendingClasses = false;
  } else {
    throw std::runtime_error("Invalid Choice. You entered: " +
                             std::string(1, schoolResponse));
  }
  return isAttendingClasses;
}

std::vector<std::string> getClassNames() {
  // This function is designed to get class information manually from the user.

  int classCount;
  std::cout << "How many classes are you taking? Please enter an integer."
            << std::endl;
  std::cin >> classCount;

  // Get the class names
  std::vector<std::string> classes;
  for (int i = 0; i < classCount; i++) {
    std::string classTemp;
    std::cout << "What is your class in slot number " << (i + 1) << "?"
              << std::endl;
    if (i == 0) {
      std::cin.ignore(); // this is here to prevent the loop from skipping the
                         // first question without getting input
    }
    getline(std::cin, classTemp);
    classes.push_back(classTemp);
  }
  return classes;
}

std::vector<std::string> getLocationDetails() {
  // This function is designed to get location details manually from the user.

  // Establish variables.
  std::string userCountry;
  std::string userProvince;
  std::string userCity;

  // Prompt for input from the user.
  std::cout << "In which country do you reside? " << std::endl;
  getline(std::cin, userCountry);

  std::cout << "In which province or state do you reside? " << std::endl;
  getline(std::cin, userProvince);

  std::cout << "In which city do you reside?" << std::endl;
  getline(std::cin, userCity);

  // Create and set up the location vector. This is done this way to streamline
  // input file support. I may change this if that turns out to be a bad idea.
  // NOTE: Try to find a way to combine the next four lines.
  std::vector<std::string> userLocation;
  userLocation.push_back(userCountry);
  userLocation.push_back(userProvince);
  userLocation.push_back(userCity);

  return userLocation;
}

std::vector<std::string> readFile() {
  // This function is designed to read data in from the file specified by the
  // user, then create the vector and pass it to main.
  std::vector<std::string> fileData;
  // Ask the user for the name of the file to be opened.
  std::string fileName;
  std::cout << "What is the name of the file you would like to open?"
            << std::endl;
  std::cin.ignore();
  getline(std::cin, fileName);

  std::ifstream file(fileName);
  bool openSuccess = false;
  if (!file) {
    char userTryAgain;
    bool tryAgain = false;
    std::cin.sync(); // clear the input buffer

    // this line is not running for some reason.
    do {
      std::cout << "Would you like to try again? (y/n)" << std::endl;
      std::cin >> userTryAgain;

      if (tolower(userTryAgain) == 'y') {
        tryAgain = true;
        std::cout << "What is the name of the file you would like to open?"
                  << std::endl;
        std::cin.ignore();
        getline(std::cin, fileName);

        std::ifstream file(fileName);
        if (file) {
          std::cout << "The file was opened successfully!" << std::endl;
          tryAgain = false;
        }
      } // if condition
      else if (tolower(userTryAgain) == 'n') {
        break;
      } // else if condition
      else {
        throw std::runtime_error("Invalid Response. You answered: " +
                                 std::string(1, userTryAgain));
      }                 // else condition
    } while (tryAgain); // for loop
  }                     // if file is opened

  std::string line;
  while (getline(file, line)) {
    fileData.push_back(line);
  }

  file.close();
  return fileData;
}

std::vector<std::string>
getClassNamesFromFile(std::vector<std::string> *pFileData) {
  // This function is designed to interact with a fileData vector which holds
  // class information.
  std::vector<std::string> classNames;

  return classNames;
}

std::vector<std::string>
getLocationDetailsFromFile(std::vector<std::string> *pFileData) {
  // This function is designed to interact with a fileData vector which holds
  // location details.
  std::vector<std::string> locationDetails;

  return locationDetails;
}

char parseFileData(std::vector<std::string> &fileData) {
  // This function is designed to read the first character in the first string
  // of the fileData vector, then determine from there whether the vector
  // contains class names or location details.
  if (fileData.empty()) {
    throw std::invalid_argument("The fileData vector is empty.");
  }

  const std::string &firstElement = fileData.front();

  if (firstElement.empty()) {
    throw std::invalid_argument("The first element of the vector was empty.");
  }

  char firstChar = firstElement[0];

  if (isdigit(firstChar)) {
    return 'N'; // This indicates that the first character of the vector is a
                // number.
  } else if (isalpha(firstChar)) {
    return 'A'; // This indicates that the first character of the vector is a
                // letter.
  } else {
    return 'O'; // This indicates that teh first character of the vector was
                // neither a number nor a letter, but also was not empty.
  }
}
