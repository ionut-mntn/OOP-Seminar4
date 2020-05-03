#include <vector>
#include "Auto.h"
#include <iostream>
#include "Person.h"

using namespace std;

/**
* CRUD operations repository interface
*/
template <class E>
class CrudRepository {
public:
	/**
	* @param id -the id of the entity to be returned id must not be null
	* @return the entity with the specified id or null - if there is no entity with the given id
	*
	*/
	virtual E findOne(int id) = 0;
	/**
	* @return all entities
	*/
	virtual vector<E> findAll() = 0;
	/**
	* @param entity entity must be not null
	* @return null- if the given entity is saved otherwise returns the entity (id already exists)
	*
	*/
	virtual E save(E entity) = 0;
	/**
	* removes the entity with the specified id
	*
	* @param id id must be not null
	* @return the removed entity or null if there is no entity with the given id
	*
	*/
	virtual E del(int id) = 0;
	/**
	* @param entity entity must not be null
	* @return null - if the entity is updated, otherwise returns the entity - (e.g id does not exist).
	*
	*/
	virtual E update(E entity) = 0;
	virtual ~CrudRepository() {};
};

class AutoInMemoryRepository : public CrudRepository<Auto> {

	friend class AutoController;

private:
	vector<Auto> vehicles;

public:

	Auto findOne(int id) {

		int len = vehicles.size();

		for (int i = 0; i < len; i++) {

			if (vehicles[i].getId() == id) {

				return vehicles[i];

			}

		}	
		exception exc;
		throw exc;

	}

	vector<Auto> findAll() {

		return vehicles;

	}

	Auto save(Auto entity) {

		int len = vehicles.size();
		for (int i = 0; i < len; i++) {

			if (entity.getId() == vehicles[i].getId()) {

				exception exc;
				throw exc;

			}
		}

		vehicles.push_back(entity);
		return entity;
	}

	Auto del(int id) {

		int len = vehicles.size();
		for (int i = 0; i < len; i++) {


			if (vehicles[i].getId() == id) {


				Auto aux = vehicles[i];
				vehicles.erase(vehicles.begin() + i);
				return aux;
			}

			
		}

		exception c;
		throw c;

	}

	Auto update(Auto entity) {

		int len = vehicles.size();
		for (int i = 0; i < len; i++) {
			if (vehicles[i].getId() == entity.getId()) {

				vehicles[i] = entity;
				return vehicles[i];

			}

		}


	}

	int size() {

		return vehicles.size();
	}

	


};

class AutoController {

private:

	static AutoController* instance;

	AutoInMemoryRepository* repo;



	AutoController(AutoInMemoryRepository *repo) {

		this->repo = repo;

	}

public:

	static AutoController* getInstance(AutoInMemoryRepository *repo) {
		
		if (instance == NULL) {
			instance = new AutoController(repo);
		}
		return instance;

	}

	Auto findAutoById(int id) {

		return repo->findOne(id);
	}

	vector<Auto> findAll() {

		return repo->findAll();
	}

	void saveAuto(Auto a) {
		repo->save(a);
	}

	Auto updateAuto(Auto a) {
		return repo->update(a);
	}

	void sortAutos() {

		std::vector<Auto> autos = repo->findAll();

		for (int i = 0; i < autos.size()-1; i++)
		{
			for (int j = 0; j < autos.size() - i - 1; j++) {

				if (autos[j].getMarke() > autos[j+1].getMarke()) {
					Auto aux = autos[j];
					autos[j] = autos[j+1];
					autos[j + 1] = aux;
				}
				
			}
		}

		repo->vehicles = autos;


	}

	void deleteAuto(int id) {
		repo->del(id);
	}


};
AutoController* AutoController::instance = 0;


class Reservierung {

private:
	Person person;
	Auto car;
	int numberOfDays;

public:

	Reservierung(Person pers, Auto newCar, int nrOfDays) {
		numberOfDays = nrOfDays;
		person = pers;
		car = newCar;

	}

	Person getPerson() {
		return person;
	}
	Auto getAuto() {
		return car;
	}
	int getDays() {
		return numberOfDays;
	}

	void setPerson(Person pers) {
		person = pers;
	}
	void setAuto(Auto newAuto) {
		car = newAuto;
	}
	void setDays(int newDays) {
		numberOfDays = newDays;
	}


};

class Rent {

public:
	std::vector<Reservierung> reservierungen;

	Rent() {
		reservierungen.clear();
	}

	void reserve_auto(Auto car, Person pers, int nrDays) {
		reservierungen.push_back(Reservierung(pers, car, nrDays));
	}
};

class UI {
public:

	void startProgram() {
		AutoInMemoryRepository mainRepo = AutoInMemoryRepository();

		mainRepo.save(Auto(1, "Tesla", "Model 3"));
		mainRepo.save(Auto(2, "Bicycle", "Three Wheeler"));
		mainRepo.save(Auto(3, "Carriage", "Wooden"));
		mainRepo.save(Auto(4, "Audi", "A1"));

		AutoController* controller = AutoController::getInstance(&mainRepo);

		bool quitProgram = false;


		std::string menuText = "\n1. Find car by id\n2. Show all cars\n3. Delete car by id\n4. Save car\n5. Sort cars\n0. Exit program";

		//Main loop of the program
		while (!quitProgram) {

			std::cout << menuText;

			int userInput = -1;

			std::cout << "\nYour choice: ";

			//Take the user choice
			std::cin >> userInput;

			//Check if the input is incorrect 
			if (std::cin.fail()) {

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << std::endl << "Invalid input!" << std::endl;

			}

			switch (userInput) {

			case 0:
				quitProgram = true;
				break;

			case 1:
			{
				int id = -1;
				std::cout << "\nID: ";

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> id;

				if (std::cin.fail()) {

					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << std::endl << "Invalid input!" << std::endl;

					//Take a default case
					id = 0;

				}

				Auto car = controller->findAutoById(id);
				cout << endl << car.getMarke() << " "<< car.getModell();

				break;
			}
			case 2:
			{
				vector<Auto> list = controller->findAll();

				for (int i = 0; i < list.size(); i++)
				{
					cout << endl << list[i].getMarke() << " " << list[i].getModell();
				
				}


				break;
			}

			case 3:
			{
				int id = -1;
				std::cout << "\nID: ";

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> id;

				if (std::cin.fail()) {

					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << std::endl << "Invalid input!" << std::endl;

					//Take a default case
					id = 0;

				}

				controller->deleteAuto(id);
				
				break;

			}
			case 4:
			{
				string marke;
				string model;
				int id = -1;

				cout << "\nMarke: ";
				cin >> marke;

				cout << "\nModell: ";
				cin >> model;

				id = controller->findAll().back().getId() + 1;

				controller->saveAuto(Auto(id, marke, model));


				break;
			}
			case 5:
			{
				controller->sortAutos();

				break;
			}

			}

		}
	}
};


int main() {

	UI uiObj;

	uiObj.startProgram();
	
}