string centerStr(string input_s,int container_width) {
    string new_s;
    int s_mid_point = (container_width - input_s.length()) / 2;
    for (int i = 0 ; i < container_width+1 ; i++) {
        if (i == s_mid_point) {
            new_s += input_s;
            i = i + input_s.length();
        } else {
            new_s += " ";
        }
    }
    return new_s;
}

string bSpaceStr(string input_s,int container_width) {
    string new_s;
    for (int i = 0 ; i < container_width+1 ; i++) {
        if (i == 0) {
            new_s += input_s;
            i = i + input_s.length();
        } else {
            new_s += " ";
        }
    }
    return new_s;
}

/* canceled **
vector<string> splitStrDel(string input_s,string delimiter) {
    vector<string> new_s;
    string token;
    while (input_s.find(delimiter) != string::npos) {
        int pos = input_s.find(delimiter);
        token = input_s.substr(0, pos);
        new_s.push_back(token);
        input_s.erase(0, pos + delimiter.length());
    }
    new_s.push_back(input_s);
    return new_s;
}
*/

vector<string> splitStrPos(string input_s,int max_width) {
    vector<string> new_s;
    string token;
    while (input_s.length() > max_width) {
        token = input_s.substr(0, max_width);
        new_s.push_back(token);
        input_s.erase(0, max_width);
    }
    new_s.push_back(input_s);
    return new_s;
}

string eraseStr(string str_to_use,string str_to_erase) {
    string new_s;
    new_s = str_to_use.erase(str_to_use.find(str_to_erase),str_to_erase.length());
    return new_s;
}
