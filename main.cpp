#include <iostream>
#include "fastcrypt.hpp"

int main(int argc, char** argv)
{
    std::string command = argv[1];

    fastcrypt::Machine machine;

    if(command=="encrypt"){

        if(argv[2] != NULL){
            //encryptFile(argv[2]);
            machine.encrypt(argv[2]);
        }else{
            std::cout << "There's no file given.\n";
        }

    }else if(command=="decrypt"){

        if(argv[2] != NULL){
            //decryptFile(argv[2]);
            machine.decrypt(argv[2]);
        }else{
            std::cout << "There's no file given.\n";
        }

    }else if(command=="--version"){

            std::cout << "\n Build from: " << std::string(__DATE__) << "\n\n" ;
        
    }else if(command=="-help"){
        std::cout << "--version                 - returns version.\n";
        std::cout << "encrypt <pathtofile>      - encrypts given file.\n";
        std::cout << "decrypt <pathtofile>      - decrypts given file.\n";

    }else{
        std::cout << "\n\nunknown command use \"-help\" argument to get avaliable commands list.\n\n";
    }
  
    return 0;
}