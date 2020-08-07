// LWZ.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string inputfile(string filename)
{
    fstream f;
    f.open(filename, ios::in);

    string data;
    getline(f, data);

    return data;
}


bool is_in_Dic(vector<string> dic, string c)
{   
    for (int i = 0; i < dic.size(); ++i) {
        if (dic[i] == c) {
            //cout << dic[i] << " " << c << "\n";
            return true;
        }
    }
    return false;
}

vector<string> Encoder_LZW(string code) {
    vector<string> dic{ "A","B","C" };
    vector<string> output{};
    string s;
    string c;
    int i = 0;
    s = code[i];
    while (i < code.length()) {
        c = code[i + 1];
        if (is_in_Dic(dic, s + c)) {
            s += c;
            //cout << s << endl;
        }
        else
        {
            for (int i = 0; i < dic.size(); ++i)
            {
                if (s == dic[i]) {
                    output.push_back(to_string(i + 1));
                }
            }
            dic.push_back(s + c);
            s = c;
        }
        ++i;
    }
    return output;
}

vector<string> Decoder_LZW(string inputcode)
{   
    vector<string> dic{ "A","B","C" };
    vector<string> output;
    string s = "NIL";
    int i = 0;
    while (i < inputcode.size())
    {
       int k = inputcode[i]-48;
       string entry = dic[k-1];
       output.push_back(entry);
       //cout << entry;
       if (s != "NIL")
       {
           dic.push_back(s + entry[0]);
       }
       s = entry;
       i++;
    }
    return output;
}



int main()
{
    int choice = 0;
    string inputcode;
    vector<string> output;
    cout << "1. Encoder\n";
    cout << "2. Decoder\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        inputcode = inputfile("Encode.txt");
        output = Encoder_LZW(inputcode);
        for (int i = 0; i < output.size(); i++)
        {
            cout << output[i] << " ";
        }
        break;
    case 2:
        inputcode = inputfile("Decode.txt");
        output = Decoder_LZW(inputcode);
        break;
    default:
        break;
    }

}

