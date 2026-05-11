#include "BitcoinExchange.hpp"
#include "iostream"
#include "sstream"
#include "fstream"
#include <cstdlib>

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): database(other.database){}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
     if (this != &other){
        database = other.database;
    }
    return *this; 
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::loadDatabase(const std::string& filename){
    std::ifstream file(filename.c_str());
    if (!file.is_open()){
        std::cout << "Error : could not open file" << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string date;
        std::string rateStr;

        std::getline(ss, date, ',');
        std::getline(ss, rateStr);

        float rate = std::atof(rateStr.c_str());
        database.insert(std::pair<std::string,float>(date,rate));
    }
}

void BitcoinExchange::processInput(const std::string& filename){
    std::ifstream file(filename.c_str());
    if(!file.is_open()){
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;
        std::getline(ss, date, '|');
        std::getline(ss, valueStr);
        if (!date.empty() && date[date.size() - 1] == ' ')
            date.erase(date.size() - 1);
        if (!valueStr.empty() && valueStr[0] == ' ')
            valueStr.erase(0, 1);
        if (date.empty() || valueStr.empty()){
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        float value = std::atof(valueStr.c_str());
        if (!isValidDate(date)){
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!isValidValue(value)){
            if (value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else
                std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        float rate = getExchangeRate(date);
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) const{
    if (date.length() != 10)
        return false;

    if (!std::isdigit(date[0]) || !std::isdigit(date[1]) ||
        !std::isdigit(date[2]) || !std::isdigit(date[3]) ||
        !std::isdigit(date[5]) || !std::isdigit(date[6]) ||
        !std::isdigit(date[8]) || !std::isdigit(date[9]))
        return false;

    if(date[4] != '-' || date[7] != '-')
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0)
        return false;
    
    if (month < 1 || month > 12)
        return false;

    int maxDay = 31;

    if (month == 3 || month == 6 || month == 9 || month == 11)
        maxDay = 30;
    else if (month == 2)
        maxDay = 28;
    
    if (day < 1 || day > maxDay)
        return false;
    
    return true;
}

bool BitcoinExchange::isValidValue(float value) const{
    if (value < 0 || value > 1000)
        return false;
    return true;
}

float BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, float>::const_iterator it;
    it = database.lower_bound(date);
    if (it == database.end()){
        --it;
        return it->second;
    }
    if (it != database.end() && it->first == date)
        return it->second;
    if (it == database.begin())
        return it->second;
    it--;
    return it->second;
}