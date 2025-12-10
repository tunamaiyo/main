#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <random>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<int> homework;
    int exam{};
    double finalAvg{};
    double finalMed{};

public:
    // Constructor
    Person() = default;

    // Copy constructor (Rule of Three)
    Person(const Person& other)
        : name(other.name),
          surname(other.surname),
          homework(other.homework),
          exam(other.exam),
          finalAvg(other.finalAvg),
          finalMed(other.finalMed) {}

    // Assignment operator (Rule of Three)
    Person& operator=(const Person& other) {
        if (this == &other) return *this;
        name = other.name;
        surname = other.surname;
        homework = other.homework;
        exam = other.exam;
        finalAvg = other.finalAvg;
        finalMed = other.finalMed;
        return *this;
    }

    // Destructor (Rule of Three)
    ~Person() {}

    // Input (overloaded >>)
    friend std::istream& operator>>(std::istream& in, Person& p) {
        std::cout << "Enter name: ";
        in >> p.name;

        std::cout << "Enter surname: ";
        in >> p.surname;

        std::cout << "Enter homework grades (type -1 to stop):\n";
        p.homework.clear();
        int n;
        while (true) {
            in >> n;
            if (n == -1) break;
            p.homework.push_back(n);
        }

        std::cout << "Enter exam grade: ";
        in >> p.exam;

        return in;
    }

    // Output (overloaded <<)
    friend std::ostream& operator<<(std::ostream& out, const Person& p) {
        out << std::left << std::setw(10) << p.name
            << std::left << std::setw(12) << p.surname
            << std::right << std::setw(10) << std::fixed << std::setprecision(2)
            << p.finalAvg << " | "
            << std::setw(10) << p.finalMed;
        return out;
    }

    // Calculate average
    double calcAverage() {
        double sum = 0;
        for (int g : homework) sum += g;
        double avg = sum / homework.size();
        finalAvg = 0.4 * avg + 0.6 * exam;
        return finalAvg;
    }

    // Calculate median
    double calcMedian() {
        std::vector<int> temp = homework;
        std::sort(temp.begin(), temp.end());
        double med;

        int size = temp.size();
        if (size % 2 == 0)
            med = (temp[size/2 - 1] + temp[size/2]) / 2.0;
        else
            med = temp[size/2];

        finalMed = 0.4 * med + 0.6 * exam;
        return finalMed;
    }

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }

    // Random generator
    void generateRandom() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);

        homework.resize(5);
        for (int& g : homework) g = dist(gen);
        exam = dist(gen);
    }

    // Load from file one line
    void loadFromFile(std::string n, std::string s, std::vector<int> hw, int ex) {
        name = n;
        surname = s;
        homework = hw;
        exam = ex;
    }
};

// ------------------------------------------------------------

int main() {
    std::vector<Person> students;

    // Read from file
    std::ifstream file("Students.txt");
    if (file.is_open()) {
        std::string name, surname;
        int h1, h2, h3, h4, h5, exam;

        // Skip header
        std::string skipLine;
        std::getline(file, skipLine);

        while (file >> name >> surname >> h1 >> h2 >> h3 >> h4 >> h5 >> exam) {
            Person p;
            p.loadFromFile(name, surname, {h1, h2, h3, h4, h5}, exam);
            p.calcAverage();
            p.calcMedian();
            students.push_back(p);
        }
        file.close();
    }

    // Sort by name
    std::sort(students.begin(), students.end(),
              [](const Person& a, const Person& b) {
                  return a.getName() < b.getName();
              });

    // Print results
    std::cout << std::left << std::setw(10) << "Name"
              << std::left << std::setw(12) << "Surname"
              << std::right << std::setw(12) << "Final(A) |"
              << std::setw(10) << "Final(M)" << "\n";

    std::cout << "--------------------------------------------------------\n";

    for (const auto& s : students)
        std::cout << s << "\n";

    return 0;
}
