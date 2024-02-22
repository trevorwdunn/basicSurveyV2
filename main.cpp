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

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

std::vector<std::string> getLocationDetails();
std::vector<std::string> getClassNames();
bool getStudentStatus();
std::vector<std::string> getClassNamesFromFile();
std::vector<std::string> getLocationDetailsFromFile();

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
  getClassNamesFromFile();

  return 0;
}

bool getStudentStatus() {
  // This block gets the user's school status.
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
  // Get the class count from the user and determine if the provided input is
  // sane.
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

std::vector<std::string> getClassNamesFromFile() {
  std::vector<std::string> classNames;

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
    for (bool tryAgain = true; tryAgain != true;) {
      std::cout << "Would you like to try again? (y/n)" << std::endl;
      std::cin >> userTryAgain;
      tolower(userTryAgain);

      if (userTryAgain == 'y') {
        tryAgain = true;
      } // if condition
      else if (userTryAgain == 'n') {
        break;
      } // else if condition
      else {
        throw std::runtime_error("Invalid Response. You answered: " +
                                 std::string(1, userTryAgain));
      } // else condition
    }   // for loop
  }     // if file is opened

  // This is print debug condition. I will remove it before I'm finished.
  if (file) {
    std::cout << "The file was opened successfully!" << std::endl;
  }
  file.close();
  return classNames;
}
