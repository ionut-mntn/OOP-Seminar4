#include "Auto.h"

Auto::Auto(int newId, std::string newMarke, std::string newModell) {

	this->id = newId;
	this->marke = newMarke;
	this->modell = newModell;


}

Auto::Auto() {
	id = NULL;
	marke = "";
	modell = "";

}

int Auto::getId() {
	
	return this->id;
}

std::string Auto::getMarke() {

	return this->marke;
}


std::string Auto::getModell() {

	return this->modell;
}

void Auto::setId(int newValue) {

	this->id = newValue;
}


void Auto::setMarke(std::string newValue) {

	this->marke = newValue;
}

void Auto::setModell(std::string newValue) {

	this->modell = newValue;
}

bool Auto::isEqualTo(Auto other) {

	if (this->getId() == other.getId() && this->getMarke() == other.getMarke() && this->getModell() == other.getModell()) {

		return true;
	}
	return false;

}