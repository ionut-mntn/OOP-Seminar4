#pragma once
#include <string>

class Auto {

protected:

	int id;
	std::string marke;
	std::string modell;

public:

	Auto(int newId, std::string newMarke, std::string newModell);

	int getId();
	std::string getMarke();
	std::string getModell();

	void setId(int newValue);
	void setMarke(std::string newValue);
	void setModell(std::string newValue);

	bool isEqualTo(Auto other);

};