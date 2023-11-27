#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

bool filePathAndOpen(std::ofstream& file) {
		try {
				file.open("Statement.txt", std::ios::app);
				if (!file.is_open())
						throw std::runtime_error("Error opening file");
				else
						return true;
		} catch (const std::exception& e) {
				std::cerr << "Exception catch: " << e.what() << std::endl;
				return false;
		}
}

bool isLeapYear(int year) {
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int month, bool leapYear) {
		if (month == 2)
				return leapYear ? 29 : 28;
		else if (month == 4 || month == 6 || month == 9 || month == 11)
				return 30;
		else
				return 31;
}

bool isValidDate(const std::string& date) {
		try {
				int day = std::stoi(date.substr(0, 2));
				int month = std::stoi(date.substr(3, 2));
				int year = std::stoi(date.substr(6, 4));

				if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month, isLeapYear(year)))
						throw std::invalid_argument("Invalid date");

				return true;
		} catch (const std::exception& e) {
				return false;
		}
}

int main() {
		std::string name;
		std::string date;
		std::string salary;

		std::ofstream file;
		if (filePathAndOpen(file)) {
				do {
						std::cout << "Enter the name: ";
						std::getline(std::cin, name);

						do {
								std::cout << "Enter the date (dd.mm.yyyy): ";
								std::getline(std::cin, date);
						} while (!isValidDate(date));

						std::cout << "Enter the salary: ";
						std::cin >> salary;
					  file << name << " " << date << " " << salary << std::endl;
							
						std::cin.ignore();
					  char choice;
            std::cout << "Do you want to add another record? (y/n): ";
					  std::cin >> choice;
					  if(choice != 'y')
							break;

				} while (true);
		}
    file.close();
		return 0;
}