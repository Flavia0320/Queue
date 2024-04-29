#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Students {
	std::string name;
	int duration;
};

struct Nod {
	Students student;
	Nod* next = nullptr;
	int id;
};

struct Queue {
	Nod* first = nullptr;
	Nod* last = nullptr;
	int nr_elem=1;

	void push(Students infoStudent) {
		Nod* new_node = new Nod;
		new_node->student = infoStudent;
		new_node->id = nr_elem;
		if (last != nullptr) {
			last->next = new_node;
			last = new_node;
		}
		else {
			first = last = new_node;
			nr_elem = 1;

		}
		nr_elem++;
	}

	void pop() {
		Nod* new_node = new Nod;
		if (first != nullptr) {
			new_node = first;
			first = first->next;
			if (first == nullptr) {
				last = nullptr;
			}
			delete new_node;
		}
	}

	Nod* front() {
		return first;
	}

	Nod* back() {
		return last;
	}

	bool empty() {
		return front() == nullptr && back() == nullptr;
	}

	void clear() {
		while (back() != nullptr) {
			pop();
		}
	}

	int size() {
		int size = 0;
		Nod* current = first;
		while (current != nullptr) {
			size++;
			current = current->next;
		}
		return size;
	}

	void print(Nod* left, Nod* right) {
		for (Nod* element = left; element != right; element = element->next)
			std::cout << "ID: " << element->id << " Name: " << element->student.name <<" Time:"<<element->student.duration<< "\n";
		std::cout << "\n";
	}
};

void formareCoada(Queue& coada, int& nrStudents,int& timeDay) {
	std::ifstream f("Date_intrare.txt");
	srand(time(NULL));
	f >> timeDay >> nrStudents;
	for (int i = 0; i < nrStudents; i++) {
		Students new_student;
		f >> new_student.name;
		new_student.duration= std::rand() % 11 + 5;
		coada.push(new_student);
	}
	f.close();
}

void examenFirst(Queue& coada, int time) {
	int nr = coada.size();
	for (int i = 0; i < nr; i++) {
		if (!coada.empty()) {
			if (time - coada.first->student.duration >= 0) {
				time -= coada.first->student.duration;
				coada.pop();
			}
		}
	}
}

void printFile(Queue coada) {
	std::ofstream f("Date_iesire.txt");
	Nod* left=coada.first;
	Nod* right=coada.last->next;
	for (Nod* element = left; element != right; element = element->next)
		f << "ID: " << element->id << " Name: " << element->student.name << " Time:" << element->student.duration << "\n";
		f << "\n";
		f.close();
}

void main() {
	int nrStudents, timeDay;
	Queue coada;
	formareCoada(coada, nrStudents,timeDay);
	coada.print(coada.first, coada.last->next);
	timeDay = timeDay * 60;
	examenFirst(coada, timeDay);
	printFile(coada);

}
