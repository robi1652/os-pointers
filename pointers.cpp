// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <iomanip>

//To Do:
//Figure out why white space and /0 cause input problems

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;
    std::string idMsg = "Please enter the student's id number: ";
    std::string asnMsg = "Please enter how many assignments were graded: ";
    student.f_name = new char[128];
    student.l_name = new char[128];

    student.id = promptInt(idMsg, 0, 999999);

    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;

    student.n_assignments = promptInt(asnMsg, 0, 134217728);
    std::cout << std::endl;

    student.grades = new double[student.n_assignments];


    int i;
    for (i = 0; i < student.n_assignments; i++) {
        std::string gradesMsg = "Please enter grade for assignment " + std::to_string(i) + ": ";
        student.grades[i] = promptDouble(gradesMsg, 0.0, 1000.0);    
    }

    std::cout << std::endl;

    calculateStudentAverage(&student, &average);

    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;

    std::cout << std::setprecision(3);
    std::cout << "  Average grade: " << average << std::endl;

    // Sequence of user input -> store in fields of `student`

    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    while(true) {
        char *inputVal;
        inputVal = new char[128];
        std::cout << message;
        std::cin >> inputVal;
        int i;
        i = 0;
        bool flag = false;
        while(inputVal[i] != '\0') {
            if (inputVal[i] < 48 || inputVal[i] > 57) {
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
                std::cin.clear();
                std::cin.ignore();
                flag = true;
                break;
            }
            i++;
        }
        if (flag == true) {
            continue;
        }
        int finalVal;
        finalVal = std::stoi(inputVal);
        if (std::cin.fail()) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
        if (finalVal > max || finalVal < min) {
            std::cout << "Input does not fit size bounds. Enter new answer" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
        return finalVal;
    }
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    while(true) {
        char *inputVal;
        inputVal = new char[128];
        std::cout << message;
        std::cin >> inputVal;
        int i;
        i = 0;
        bool flag = false;
        bool decimal = false;
        while(inputVal[i] != '\0') {
            if (inputVal[i] == 46) {
                if(decimal == true) {
                    std::cout << "sorry, I cannot understand your answer" << std::endl;
                    std::cin.clear();
                    std::cin.ignore();
                    decimal = true;
                    flag = true;
                    break;
                }
                decimal = true;
            }
            if ((inputVal[i] < 48 && inputVal[i] != 46) || inputVal[i] > 57) {
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
                std::cin.clear();
                std::cin.ignore();
                flag = true;
                break;
            }
            i++;
        }
        if (flag == true) {
            continue;
        }
        double finalVal;
        try {
            std::stod(inputVal);
        }
        catch(const std::invalid_argument) {
            std::cout << "Something is wrong with your answer" << std::endl;
            continue;
        }
        finalVal = std::stod(inputVal);
        if (std::cin.fail()) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            continue;
        }
        if (finalVal > max || finalVal < min) {
            std::cout << "Input does not fit size bounds" << std::endl;
            continue;
        }
        return finalVal;
    }
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    Student student;
    student = *(Student*)object;
    double total = 0;
    int i;
    for (i = 0; i < student.n_assignments; i++) {
        total += student.grades[i];
    }
    *avg = total / student.n_assignments;
}

