#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <direct.h>
#include <vector>
using namespace std;
#include "zString.hpp"
#include "main.hpp"

string username;
string password;
bool authenticate = false;

int main() {
    _mkdir("config");
    _chdir("config");
    do {
    //
    //
    // Start
    //
    //
    while (authenticate == false) { // MAIN MENU
        char user_choice;
        vector<string> user_list (createList("users.txt"));
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Welcome to MyCheckList!",78)<<"|\n\
|"<< centerStr("What would you like to do?",78)<<"|\n\
|"<< centerStr("1 - Create a new user",78)<<"|\n\
|"<< centerStr("2 - Delete a user    ",78)<<"|\n\
|"<< centerStr("3 - Login            ",78)<<"|\n\
|"<< centerStr("4 - Quit             ",78)<<"|\n\
|"<< centerStr("(Enter the number before an operation to start)",78)<<"|\n\
|"<< centerStr("(For example: key in 1 if you want to create a new user)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        if (user_choice != '2') {
            cout << ">> ";
            cin.clear();
            cin.sync();
            cin.get(user_choice);
        }
        switch (user_choice) {
            case '1': // USER CREATION
                userCreator(username,password,user_list);
                break;
            case '2': // USER DELETION
                userRemover(user_choice,user_list);
                break;
            case '3': // USER AUTHENTICATION
                userAuthenticator(username,password,authenticate);
                break;
            case '4': // EXIT PROGRAM
                exitProgram();
                return 0;
            default: // INVALID INPUT
                invalidInput("Please choose between 1, 2, 3 or 4!\n");
        }
    }
    //
    //
    // Successfully logged in
    //
    //
    while (authenticate == true) { // USER MENU
        char user_choice;
        string user_checklist = username + ".txt";
        vector<string> task_list (createList(user_checklist));
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Welcome",78)<<"|\n\
|"<< centerStr(username,78)<<"|\n\
|"<< centerStr("What would you like to do?",78)<<"|\n\
|"<< centerStr("0 - Logout       ",78)<<"|\n\
|"<< centerStr("1 - Create a task",78)<<"|\n\
|"<< centerStr("2 - Delete a task",78)<<"|\n\
|"<< centerStr("3 - Tick a task  ",78)<<"|\n\
|"<< centerStr("4 - Quit         ",78)<<"|\n\
|"<< centerStr("(Enter the number before an operation to start)",78)<<"|\n\
|"<< centerStr("(For example: key in 1 if you want to create a task)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        if (task_list.size() > 0) {
            listTasks(task_list);
        } else {
            cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("You don't have any task(s).",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        }
        if (user_choice != '2' && user_choice != '3') {
            cout << ">> ";
            cin.clear();
            cin.sync();
            cin.get(user_choice);
        }
        switch (user_choice){
            case '0':
                authenticate = false;
                break;
            case '1': // TASK CREATION
                taskCreator(username,task_list);
                break;
            case '2': // TASK DELETION
                taskRemover(username,user_choice,task_list);
                break;
            case '3': // TASK COMPLETION
                taskMarker(username,user_choice,task_list);
                break;
            case '4': // EXIT PROGRAM
                exitProgram();
                return 0;
            default: // INVALID INPUT
                invalidInput("Please choose between 0, 1, 2, 3 or 4!\n");
        }
    }
    } while (1==1);
    return 0;
}
