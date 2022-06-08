#include <fstream>
#include <string>
#include <vector>
#include "splines.h"
#include "writer.h"

void WritePointsIntoFile(ArrayPoints points, std::string path) {
    using namespace std;
    ofstream oFile(path);
    if (!oFile.is_open()) {
        printf("Sth went wrong\n");
        return;
    }
    for (auto p: points)
        //oFile << "(" << p.x << "; " << p.y << "), ";
        oFile << p.x << " " << p.y << ", ";
    //oFile << "\n";
    oFile.close();
}