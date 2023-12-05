
#include <fstream>
#include <iostream>

using namespace std;
int main(){
    
    int count = 0, i = 0, j = 0;
    char buff[128];
    char sym;
    
    std::fstream clues ("clues.txt");
    
    if (!clues.is_open()){
        exit(0);
    }
    
//    while(!clues.eof()){
//        clues >> buff;
//        count++;
//    }
    for (clues>>buff;!clues.eof();clues>>buff){
        count++;}
    
    int *keys = new int[count+1];
    clues.clear();
    clues.seekg(0);
    
   
    
    while(clues >> std::noskipws >> sym){
        
        if (sym != ' ' && sym != '\n'){
            keys[i] += static_cast<int>(sym);
            
            
        }else{
            i ++;
        }
       
    }
   
    clues.close();

    std::fstream encrypted ("encrypted.txt");
    std::fstream tobeencrypted ("tobeencrypted.txt");
    
    if (!encrypted.is_open() || !tobeencrypted.is_open()){
        exit(0);
    }
    
    while(tobeencrypted >> std::noskipws >> sym){
        if (sym == '\n'){
            encrypted << '\n';
        }else{
            encrypted << static_cast<char>(std::abs(static_cast<int>(sym) + std::abs(keys[j%count]) % 256)%256);
            j++;
        }
    }
    
    tobeencrypted.close();
    encrypted.close();
    
    j = 0;
    
    std::fstream decoded ("decoded.txt");
    std::fstream tobedecoded ("tobedecoded.txt");
    
    if (!decoded.is_open() || !tobedecoded.is_open()){
        exit(0);
    }
    
    while(tobedecoded >> std::noskipws >> sym){
        if (sym == '\n'){
            decoded << '\n';
        }else{
            decoded << static_cast<char>(std::abs(static_cast<int>(sym) - std::abs(keys[j%count]) % 256)%256);
            j++;
        }
    }
    
    tobedecoded.close();
    decoded.close();
    
    delete[] keys;
    return 1;
}