#pragma once

#include <iostream> 
#include <bits/stdc++.h>
#include <fstream>
#include <string>

namespace fastcrypt{
    class Machine{
        public:
            Machine(){}
            ~Machine(){}
            void encrypt(std::string filePath){
                char c;

                std::string originalExtension = "";

                size_t lastindex = filePath.find_last_of("."); 
                std::string path = filePath;
                filePath = filePath.substr(0, lastindex); 

                //std::cout << lastindex << '\n';
                if(path.find(".") != std::string::npos){
                    originalExtension = path.substr(lastindex+1, path.length()-lastindex);
                }

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
 
                std::fstream fin, fout;
 
                fin.open(path, std::fstream::in);
                fout.open(out, std::fstream::out);

                fout << originalExtension.length();
                fout << originalExtension;
 
                while (fin >> std::noskipws >> c) {
                    int temp = (c + intkey);
                    fout << (char)temp;
                }
 
                fin.close();
                fout.close();
            }

            void decrypt(std::string filePath){
                char c;

                size_t lastindex = filePath.find_last_of("."); 
                std::string path = filePath;
                filePath = filePath.substr(0, lastindex); 

                std::string extension = "";
            
                std::string key = path.substr(lastindex+1,3);
                int intkey = strToIntKey(key);

                char sep = '/';
                std::string fileName = filePath;

                #ifdef _WIN32
                    sep = '\\';
                #endif

    
                std::fstream fin;
                fin.open(path, std::fstream::in);

                bool first = true;
                int count = 0,cnt = 0;

                char firstChar;
 
                while (fin >> std::noskipws >> c) {
                    if(first){
                        count = c - 48;
                        cnt = count;
                        first = false;
                    }else{
                        if(count > 0){
                            count--;
                            extension.push_back(c);
                        }else{
                            firstChar = (c - intkey);
                            break;
                        }
                    }
                }

                std::string out;

                if(cnt > 0){
                    out = filePath + "." + extension;
                }else{
                    out = filePath;
                }

                std::cout << "> Attempting to decrypt: " << path << "\n> Output file: " << out << "\n";

                std::fstream fout;
                fout.open(out, std::fstream::out);

                fout << firstChar;

                while (fin >> std::noskipws >> c) {
                    int temp = (c - intkey);
                    fout << (char)temp;
                }

                fin.close();
                fout.close();

            }
        private:

            std::string gen_random(const int len) {
                srand(time(NULL));

                static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
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
                    temp += std::to_string(tempInt);
                }

                out = std::stoi(temp);
                return out;
            }
    };
}