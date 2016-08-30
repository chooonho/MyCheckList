vector<string> createList(string file_name) {
    vector<string> text_list;
    ifstream infile(file_name.c_str(), ios::in);
    string line;
    while (getline(infile,line)) {
        text_list.push_back(line);
    }
    return text_list;
}

bool verifyUser(string username1) {
    bool test_bool = false;
    ifstream infile("users.txt", ios::in);
    string line;
    while (getline(infile,line)) {
        string username2 = line.substr(0,line.find(","));
        if (username1 == username2) {
            infile.close();
            test_bool = true; // User exists
            break;
        }
    }
    return test_bool;
}

void createUser(string username,string password) {
    string user_info = username + "," + password;
    string user_checklist = username + ".txt";
    ofstream outfile1("users.txt", ios_base::app);
    ofstream outfile2(user_checklist.c_str(), ios_base::app);
    outfile1 << user_info << endl;
    outfile2 << "";
    outfile1.close();
    outfile2.close();
}

void listUsers(vector<string> user_list) {
    int user_id;
    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("User(s): ",78) <<"|\n\
--------------------------------------------------------------------------------\n\
|                                                                              |\n";
    for (int i = 0 ; i < user_list.size(); i++) {
        user_id = i + 1;
        string user_info = user_list.at(i);
        string long_username = user_info.substr(0,user_info.find(","));
        vector<string> split_username (splitStrPos(long_username,73));
        if (user_id < 10) {
            cout << "| " << user_id << " . ";
        } else {
            cout << "| " << user_id << ". ";
        }
        for (int u = 0 ; u < split_username.size() ; u++) {
            if (u == 0) {
                cout << bSpaceStr(split_username.at(u),73) << "|\n";
            } else {
                cout << "|     " << bSpaceStr(split_username.at(u),73) << "|\n";
            }
        }
    }
    cout << "\
|                                                                              |\n\
--------------------------------------------------------------------------------\n";
}

void deleteUser(int user_id,vector<string> user_list) {
    vector<string> new_list;
    for (int i = 0; i < user_list.size() ; i++) {
        if (user_id != i) {
            new_list.push_back(user_list.at(i));
        }
    }

    string user_info = user_list.at(user_id);
    string username = user_info.substr(0,user_info.find(","));
    string user_checklist = username + ".txt";
    remove(user_checklist.c_str());

    ofstream outfile("users.txt", ios::out);
    for (int i = 0;i < new_list.size();i++) {
        outfile << new_list.at(i) << endl;
    }
    outfile.close();
}

bool loginUser(string username,string password) {
    bool test_bool = false;
    string user_info = username + "," + password;
    ifstream infile("users.txt",ios::in);
    string line;
    while (getline(infile,line)) {
        if (user_info == line) {
            infile.close();
            test_bool = true; // Login success
            break;
        }
    }
    return test_bool;
}

bool verifyTask(string username,string task) {
    bool test_bool = false;
    string user_checklist = username + ".txt";
    ifstream infile(user_checklist.c_str(), ios::in);
    string line;
    while (getline(infile,line)) {
        if (task == line) {
            infile.close();
            test_bool = true; // Task exists
            break;
        }
    }
    return test_bool;
}

void createTask(string username,string task) {
    string user_checklist = username + ".txt";
    ofstream outfile(user_checklist.c_str(),ios_base::app);
    outfile << task << endl;
    outfile.close();
}

void listTasks(vector<string> task_list) {
    int task_id;
    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Your task(s): ",78) <<"|\n\
--------------------------------------------------------------------------------\n\
|                                                                              |\n";
    for (int i = 0 ; i < task_list.size(); i++) {
        task_id = i + 1;
        vector<string> split_task (splitStrPos(task_list.at(i),73));
        if (task_id < 10) {
            cout << "| " << task_id << " . ";
        } else {
            cout << "| " << task_id << ". ";
        }
        for (int u = 0 ; u < split_task.size() ; u++) {
            if (u == 0) {
                cout << bSpaceStr(split_task.at(u),73) << "|\n";
            } else {
                cout << "|     " << bSpaceStr(split_task.at(u),73) << "|\n";
            }
        }
    }
    cout << "\
|                                                                              |\n\
--------------------------------------------------------------------------------\n";
}

void deleteTask(string username, int task_id, vector<string> task_list) {
    vector<string> new_list;
    for (int i = 0 ; i < task_list.size() ; i++) {
        if (task_id != i) {
            new_list.push_back(task_list.at(i));
        }
    }

    string user_checklist = username + ".txt";
    ofstream outfile(user_checklist.c_str(),ios::out);
    for (int i = 0 ; i < new_list.size() ; i++) {
        outfile << new_list.at(i) << endl;
    }
    outfile.close();
}

bool tickTask(string username, int task_id, vector<string> task_list) {
    bool test_bool;
    vector<string> new_list;
    for (int i = 0 ; i < task_list.size() ; i++) {
        if (task_id == i) {
            if ((task_list.at(i).find("COMPLETED: ")) == string::npos) {
                string task = "COMPLETED: " + task_list.at(i);
                new_list.push_back(task);
                test_bool = true;
            } else {
                string task = eraseStr(task_list.at(i),"COMPLETED: ");
                new_list.push_back(task);
                test_bool = false;
            }
        } else {
            new_list.push_back(task_list.at(i));
        }
    }

    string user_checklist = username + ".txt";
    ofstream outfile(user_checklist.c_str(),ios::out);
    for (int i = 0 ; i < new_list.size() ; i++) {
        outfile << new_list.at(i) << endl;
    }
    outfile.close();
    return test_bool;
}

void userCreator(string& username,string& password,vector<string>& user_list){
    if (user_list.size() < 99) {
        cin.clear();
        cin.sync();
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please key in your preferred username: (no limitation)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        cout << ">> ";
        getline(cin, username);
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please key in your preferred password: (no limitation)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        cout << ">> ";
        getline(cin, password);
        if (username != "" && password != "") {
            if (!verifyUser(username)) {
                createUser(username,password);
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("User successfully created!",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            } else {
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("User already exists.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            }
        } else {
            system("cls");
            cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Invalid input.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
            system("pause");
        }
    } else {
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("You can only have a maximum of 99 users at the moment.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        system("pause");
    }
}

void userRemover(char& user_choice,vector<string>& user_list){
    string input_id;
    string password1;
    if (user_list.size() > 0) {
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Delete a user by entering the number before the user",78)<<"|\n\
|"<< centerStr("0 - Back",78)<<"|\n\
|"<< centerStr("(Key in 0 if you want to go back to the main menu)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        listUsers(user_list);
        cout << ">> ";
        cin.clear();
        cin.sync();
        cin >> input_id;
        if (input_id == "0") {
            user_choice = 'w';
        } else {
            int conv_id = atoi(input_id.c_str());
            if (conv_id != 0) {
                int user_id = conv_id - 1;
                if (user_id < user_list.size()) {
                    cin.clear();
                    cin.sync();
                    system("cls");
                    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please enter your password: ",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                    cout << ">> ";
                    getline(cin,password1);

                    string user_info = user_list.at(user_id);
                    string password2 = user_info.substr(user_info.find(",")+1);
                    if (password1 == password2) {
                        deleteUser(user_id,user_list);
                        system("cls");
                        cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("User successfully deleted.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                        system("pause");
                    } else {
                        system("cls");
                        cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("The password that you have entered does not match.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                        system("pause");
                    }
                } else {
                    system("cls");
                    cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("There is no user with that ID.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                    system("pause");
                }
            } else {
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please key in the number before the user.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            }
        }
    } else {
        user_choice = 'w';
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("There are no user(s).",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        system("pause");
    }
}

void userAuthenticator(string& username,string& password,bool& authenticate){
    cin.clear();
    cin.sync();
    system("cls");
    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Username: ",78)<<"|\n\
--------------------------------------------------------------------------------\n";
    cout << ">> ";
    getline(cin, username);
    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Password: ",78)<<"|\n\
--------------------------------------------------------------------------------\n";
    cout << ">> ";
    getline(cin, password);
    if (username != "" && password != "") {
        if (loginUser(username,password)) {
            authenticate = true;
        } else {
            system("cls");
            cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("User authentication failed.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
            system("pause");
        }
    } else {
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Invalid input.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        system("pause");
    }
}

void exitProgram(){
    system("cls");
    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Thank you for using MyCheckList!",78)<<"|\n\
--------------------------------------------------------------------------------\n";
    system("pause");
}

void invalidInput(string error_msg){
    system("cls");
    cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr(error_msg,78)<<"|\n\
--------------------------------------------------------------------------------\n";
    system("pause");
}

void taskCreator(string& username,vector<string>& task_list){
    if (task_list.size() < 99) {
        string task;
        cin.clear();
        cin.sync();
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please key in your task: ",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        cout << ">> ";
        getline(cin, task);
        if (task != "") {
            if (!verifyTask(username,task)) {
                createTask(username,task);
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Task successfully created!",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            } else {
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Task already exists.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            }
        } else {
            system("cls");
            cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Invalid input.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
            system("pause");
        }
    } else {
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("You can only have a maximum of 99 tasks at the moment.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        system("pause");
    }
}

void taskRemover(string& username,char& user_choice,vector<string>& task_list){
    string input_id;
    if (task_list.size() > 0) {
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Delete a task by entering the number before the task",78)<<"|\n\
|"<< centerStr("0 - Back",78)<<"|\n\
|"<< centerStr("(Key in 0 if you want to go back to the user menu)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        listTasks(task_list);
        cout << ">> ";
        cin.clear();
        cin.sync();
        cin >> input_id;
        if (input_id == "0") {
            user_choice = 'w';
        } else {
            int conv_id = atoi(input_id.c_str());
            if (conv_id != 0) {
                int task_id = conv_id - 1;
                if (task_id < task_list.size()) {
                    deleteTask(username,task_id,task_list);
                    system("cls");
                    cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("Task successfully deleted.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                    system("pause");
                } else {
                    system("cls");
                    cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("There is no task with that ID.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                    system("pause");
                }
            } else {
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please key in the number before the task.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            }
        }
    } else {
        user_choice = 'w';
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("You don't have any task(s).",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        system("pause");
    }
}

void taskMarker(string& username,char& user_choice,vector<string>& task_list){
    string input_id;
    if (task_list.size() > 0) {
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Tick a task by inputting the number before the task",78)<<"|\n\
|"<< centerStr("0 - Back",78)<<"|\n\
|"<< centerStr("(Key in 0 if you want to go back to the user menu)",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        listTasks(task_list);
        cout << ">> ";
        cin.clear();
        cin.sync();
        cin >> input_id;
        if (input_id == "0") {
            user_choice = 'w';
        } else {
            int conv_id = atoi(input_id.c_str());
            if (conv_id != 0) {
                int task_id = conv_id - 1;
                if (task_id < task_list.size()) {
                    if (tickTask(username,task_id,task_list)){
                        system("cls");
                        cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("Task successfully ticked.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                        system("pause");
                    } else {
                        system("cls");
                        cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("Task successfully unticked.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                        system("pause");
                    }
                } else {
                    system("cls");
                    cout << "\
--------------------------------------------------------------------------------\n\
|"+centerStr("There is no task with that ID.",78)+"|\n\
--------------------------------------------------------------------------------\n";
                    system("pause");
                }
            } else {
                system("cls");
                cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("Please key in the number before the task.",78)<<"|\n\
--------------------------------------------------------------------------------\n";
                system("pause");
            }
        }
    } else {
        user_choice = 'w';
        system("cls");
        cout << "\
--------------------------------------------------------------------------------\n\
|"<< centerStr("You don't have any task(s).",78)<<"|\n\
--------------------------------------------------------------------------------\n";
        system("pause");
    }
}
