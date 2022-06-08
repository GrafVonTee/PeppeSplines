#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "splines.h"
#include "parser.h"

std::string GetStringFromFile(std::string path) {
    using namespace std;
    ifstream inFile(path);
    stringstream buff;
    if (!inFile.is_open()) {
        printf("Sth went wrong\n");
        return "";
    }
    buff << inFile.rdbuf();
    string str = buff.str();
    inFile.close();
    return str;
}

std::vector<Point> ParsePoints(std::string orig_string) {
    if (orig_string.empty())
        return ArrayPoints {};
    char *new_str = (char*) calloc(orig_string.length(), sizeof(char));
    strcpy(new_str, orig_string.c_str());
    char *token = strtok(new_str, ",");
    ArrayPoints arr;
    while (token) {
        Point new_p = {0, 0};
        sscanf(token, "(%Lf; %Lf)", &new_p.x, &new_p.y);
        arr.push_back(new_p);
        token = strtok(nullptr, ",");
    }
    return arr;
}