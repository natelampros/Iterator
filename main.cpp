#include "LinkedList.h"
#include <iostream>
#include <sstream>
#include <string>

//#ifdef _MSC_VER
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#else
//#define VS_MEM_CHECK;
//
//
//#endif

using namespace std;

int main(int argc, char * argv[]) {
    //VS_MEM_CHECK;
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);

    LinkedList<string> linked_list; ///WHY DOES IT HAVE TO BE A POINTER TO WORK????
    LinkedList<string> copyList;

// process input strings
    for (string line; getline(in, line);)
    {
        try {
            string item1, item2;
            if (line.size() == 0) continue;

            istringstream iss(line);
            iss >> item1;
            if (item1 == "Insert") {
                out << line;
                while (iss >> item2)
                {
                    linked_list.push_front(item2);
                }
                out << endl;
            }

            else if (item1 == "PrintList") {
                out << "PrintList ";
                if (linked_list.size() > 0) {
                    out << linked_list;
                }
                else {
                    out << "Empty!";
                }
                    out << endl;
            }

            else if (item1 == "Clear") {
                out << "Clear ";
                linked_list.clear();
                out << " OK" << endl;
            }

            else if (item1 == "Size") {
                out << "Size ";
                int counter = linked_list.size();
                out << counter << endl;
            }

            else if (item1 == "Empty") {
                out << "Empty ";
                if (linked_list.size() == 0) {
                    out << "true";
                }
                else {
                    out << "false";
                }

                out << endl;
            }

            else if (item1 == "Iterate") {
                LinkedList<string>::Iterator iter = linked_list.begin();

                out << "Iterate ";

                if (linked_list.size() == 0) {
                    out << "Empty!";
                }
                else {
                    while (iter != linked_list.end()) {
                        out << endl << " [" << *iter << "]";
                        ++iter;
                    }
                }
                out << endl;
            }

            else if (item1 == "Erase") { //TODO
                out << "Erase ";

                string value;
                iss >> value;
                out << value;

                LinkedList<string>::Iterator position = linked_list.begin();
                LinkedList<string>::Iterator begin = linked_list.begin();
                LinkedList<string>::Iterator end = linked_list.end();

                position = linked_list.find(begin, end, value);
                linked_list.erase(position);

                out << " OK" << endl;
            }

            else if (item1 == "Find") {
                out << "Find ";

                LinkedList<string>::Iterator begin = linked_list.begin();
                LinkedList<string>::Iterator end = linked_list.end();

                string value;
                iss >> value;
                out << value;

                linked_list.find(begin, end, value);

                out << " OK" << endl;
            }

            else if (item1 == "InsertAfter") {
                out << "InsertAfter ";

                string positionString;
                iss >> item2;
                iss >> positionString;

                LinkedList<string>::Iterator position = linked_list.begin();
                LinkedList<string>::Iterator begin = linked_list.begin();
                LinkedList<string>::Iterator end = linked_list.end();

                out << item2 << " " << positionString << " ";

                position = linked_list.find(begin, end, positionString);
                linked_list.insert_after(position, item2);

                out << "OK" << endl;
            }

            else if (item1 == "Replace") {
                out << "Replace ";

                string oldValue;
                iss >> oldValue;
                string newValue;
                iss >> newValue;
                out << oldValue << " " << newValue;

                LinkedList<string>::Iterator begin = linked_list.begin();
                LinkedList<string>::Iterator end = linked_list.end();

                linked_list.replace(begin, end, oldValue, newValue);

                out << " OK" << endl;
            }

            else if (item1 == "InsertBefore"){
                out << "InsertBefore ";

                string value;
                iss >> value;
                string before_position;
                iss >> before_position;

                out << value << " " << before_position << " ";

                LinkedList<string>::Iterator position = linked_list.begin();
                LinkedList<string>::Iterator begin = linked_list.begin();
                LinkedList<string>::Iterator end = linked_list.end();

                position = linked_list.find(begin, end, before_position);
                linked_list.insert_before(position, value);

                out << "OK" << endl;
            }
            else {
                linked_list.clear();
            }
        }

        catch (string error) {
            out << error << endl;
        }

    }
    linked_list.clear();
    copyList.clear();

    return 0;

}
