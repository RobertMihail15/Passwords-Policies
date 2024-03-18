#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

class Policy{
protected:
    bool isChecked;
public:
    virtual void check(const string & parola)=0;
    bool getCheck()const{
        return isChecked;
    }
    

};
class LengthPolicy : public Policy{
private:
    uint16_t maxLength,minLength;
public:
    LengthPolicy(uint16_t x){
        minLength=x;
        maxLength=255;
        
    }
    LengthPolicy(uint16_t x,uint16_t y){
        minLength=x;
        maxLength=y;
        
    }
   
    void check(const string & p){
        
        if(p.size()>=minLength && p.size()<=maxLength) 
        isChecked=true;
        else 
        isChecked=false;
    }
};
class ClassPolicy : public Policy{
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t val){
        minClassCount=val;
        
    }
    
    void check(const string & p){
        int cif=0;
        int lm=0;
        int Lm=0;
        int alte=0;
        char s[256];
        strcpy(s,p.c_str());
        for(int i=0;i< strlen(s);i++){
            if(!isalnum(s[i])) alte++;
            if(isdigit(s[i])) cif++;
            if(isalpha(s[i])){
                if(isupper(s[i])) Lm++;
                else lm++;
            }
        }
        int k=0;
        if(cif!=0) k++;
        if(Lm!=0) k++;
        if(lm!=0) k++;
        if(alte!=0) k++;
        if(k>=minClassCount) 
        isChecked=true;
        else 
        isChecked=false;
    }
};
class IncludePolicy : public Policy{
private:
    char characterType;
public:
    IncludePolicy(char x){
        characterType=x;
        
    }
    
    void check(const string & p){
        char s[256];
        strcpy(s,p.c_str());
        for(int i=0;i< strlen(s);i++){
            if(characterType=='A'){
                if(isupper(s[i])) {
                    isChecked = true;
                    return;
                }
            }
            if(characterType=='a'){
                if(islower(s[i])){
                    isChecked=true;
                    return;
                }
            }
            if(characterType=='0'){
                if(isdigit(s[i])){
                    isChecked=true;
                    return;
                }
            }
            if(characterType=='$'){
                if(!isalnum(s[i])){
                    isChecked=true;
                    return;
                }
            }
        }
        isChecked=false;
    }
};
class NotIncludePolicy : public Policy{
private:
    char characterType;
public:
    NotIncludePolicy(char x){
        characterType=x;
        
    }
    
    void check(const string & p){
        char s[256];
        strcpy(s,p.c_str());
        for(int i=0;i< strlen(s);i++){
            if(characterType=='A'){
                if(isupper(s[i])) {
                    isChecked = false;
                    return;
                }
            }
            if(characterType=='a'){
                if(islower(s[i])){
                    isChecked=false;
                    return;
                }
            }
            if(characterType=='0'){
                if(isdigit(s[i])){
                    isChecked=false;
                    return;
                }
            }
            if(characterType=='$'){
                if(!isalnum(s[i])){
                    isChecked=false;
                    return;
                }
            }
        }
        isChecked=true;
    }
};
class RepetitionPolicy : public Policy{
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t val){
        maxCount=val;
        
    }
    
    void check(const string & p){
        char s[256];
        int  lmax=0;
        strcpy(s,p.c_str());
        int k=1;
        for(int i=0;i< strlen(s);i++){
            if(s[i]==s[i+1]){
                k++;
                if(lmax<k) lmax=k;
            }
            else
            {
                k=1;
            }
        }
        if(lmax<= maxCount) isChecked=true;
        else isChecked=false;
    }
};
class ConsecutivePolicy : public Policy{
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t val){
        maxCount=val;
        
    }
   
    void check(const string & p){
        char s[256];
        int  lmax=0;
        strcpy(s,p.c_str());
        int k=1;
        for(int i=0;i< strlen(s);i++){

            if(s[i]==s[i+1]-1){
                k++;
                if(lmax<k) lmax=k;
            }
            else
            {
                k=1;
            }
        }
        if(lmax<= maxCount) isChecked=true;
        else isChecked=false;
    }
};
string checkPassword(string p, vector<Policy *> ps){
    for(Policy * cerinta : ps){
        cerinta->check(p);
        if(cerinta->getCheck()==false){
           
            return "NOK";
        }
    
    }
    return "OK";
}
int main(){
    int n;
    vector<Policy * > cerinte;
    cin>>n;
    cin.get();
    string cerinta;
    bool ok=false;
    char s[256];
    for(int i=0;i<n;i++){
        int val1,val2;
        int k=0;
        char t[20];
        cin.getline(s,256);
        char * p = strtok(s," ");
        while(p!=NULL){
            
            k++;

            if(k==1){
                string comanda(p);
                cerinta=comanda;
            }
            if(k==2){
                strcpy(t,p);
                if(cerinta=="include"){
                    cerinte.push_back(new IncludePolicy(p[0]));
                }
                if(cerinta=="repetition"){
                    val1= atoi(p);
                    cerinte.push_back(new RepetitionPolicy(val1));
                }
                if(cerinta=="consecutive"){
                    val1= atoi(p);
                    cerinte.push_back(new ConsecutivePolicy(val1));
                }
                if(cerinta=="class"){
                    val1= atoi(p);
                    cerinte.push_back(new ClassPolicy(val1));
                }
                if(cerinta=="ninclude"){
                    cerinte.push_back(new NotIncludePolicy(p[0]));
                }
            }
            if(k==3)
            {val1= atoi(t);
                val2=atoi(p);
                cerinte.push_back(new LengthPolicy(val1,val2));
            }
            p= strtok(NULL," ");
        }
        if(cerinta=="length" && k==2){
            val1= atoi(t);
            cerinte.push_back(new LengthPolicy(val1));
        }

    }
    
    string parola;
    while(cin>>parola){
        cout<<checkPassword(parola,cerinte)<<endl;
    }
    return 0;
}
