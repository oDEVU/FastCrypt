#include <iostream> 
#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define VERSION "1.0.1"

void encryptFile(std::string filePath);

void decryptFile(std::string filePath);

std::string gen_random(const int len);

int strToIntKey(std::string str);
  
int main(int argc, char** argv)
{
    std::string command = argv[1];

    if(command=="encrypt"){

        if(argv[2] != NULL){
            encryptFile(argv[2]);
        }else{
            std::cout << "There's no file given.\n";
        }

    }else if(command=="decrypt"){

        if(argv[2] != NULL){
            decryptFile(argv[2]);
        }else{
            std::cout << "There's no file given.\n";
        }

    }else if(command=="--version"){

            std::cout << "\n Current instaled version: " << VERSION << " | Build from: " << std::string(__DATE__) << "\n\n" ;
        
    }else if(command=="-help"){
        std::cout << "--version                 - returns version.\n";
        std::cout << "encrypt <pathtofile>      - encrypts given file.\n";
        std::cout << "decrypt <pathtofile>      - decrypts given file.\n";

    }else{
        std::cout << "\n\nunknown command use \"-help\" argument to get avaliable commands list.\n\n";
    }
  
    return 0;
}

void encryptFile(std::string filePath){
    char c;

    size_t lastindex = filePath.find_last_of("."); 
    std::string path = filePath;
    filePath = filePath.substr(0, lastindex); 

    //bool succes = true;
    std::string key = gen_random(3);
    int intkey = strToIntKey(key);

    char sep = '/';
    std::string fileName = filePath;

    #ifdef _WIN32
        sep = '\\';
    #endif

    std::string outPath = "";

    size_t i = filePath.rfind(sep, filePath.length());
    if (i != std::string::npos) {
        fileName = filePath.substr(i+1, filePath.length() - i);
        outPath = filePath.substr(0,i+1);
    }

    std::string out = fileName + "." + key;

    out = outPath+out;

    std::cout << "> Attempting to encrypt: " << path << "\n> Output file: " << out << "\n";
 
    // Input stream
    std::fstream fin, fout;
 
    // Open input file
    // ios::binary- reading file
    // character by character
    fin.open(path, std::fstream::in);
    fout.open(out, std::fstream::out);
 
    // Reading original file till
    // end of file
    while (fin >> std::noskipws >> c) {
        int temp = (c + intkey);
 
        // Write temp as char in
        // output file
        fout << (char)temp;
    }
 
    // Closing both files
    fin.close();
    fout.close();
    

    //return succes;
}

void decryptFile(std::string filePath){
    char c;

    size_t lastindex = filePath.find_last_of("."); 
    std::string path = filePath;
    filePath = filePath.substr(0, lastindex); 

    std::string extension = "txt";

    std::string key = path.substr(lastindex+1,3);

    //std::cout << key;
    int intkey = strToIntKey(key);

    std::cout << "> Give original file extension (its only so system can open it properly, if you not sure you can try changing it manualy later.) : "; std::cin >> extension;

    char sep = '/';
    std::string fileName = filePath;

    #ifdef _WIN32
        sep = '\\';
    #endif

    std::string out = filePath + "." + extension;

    std::cout << "> Attempting to decrypt: " << path << "\n> Output file: " << out << "\n";

    
    std::fstream fin;
    std::fstream fout;
    fin.open(path, std::fstream::in);
    fout.open(out, std::fstream::out);
 
    while (fin >> std::noskipws >> c) {
 
        // Remove the key from the
        // character
        int temp = (c - intkey);
        fout << (char)temp;
    }
 
    fin.close();
    fout.close();
    
}

std::string gen_random(const int len) {
    srand(time(NULL));

    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

int strToIntKey(std::string str){
    int out = 0;
    std::string temp;

    for(int i = 0; i<str.length(); i++){
        char tempChar = str[i];
        int tempInt = int(tempChar);
        //std::cout << "> int: " << tempInt << "\n";
        temp += std::to_string(tempInt);
    }

    out = std::stoi(temp);

    std::cout << "> int key: " << out << "\n";


    return out;
}