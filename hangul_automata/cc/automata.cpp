#include <iostream>
#include <wchar.h>
#include <queue>
#include <string.h>
#include <clocale>
#define START 0
#define J 1
#define JM 2
#define JMM 3
#define JMJ 4
#define JMXJ 5
#define JA 6
#define MO 7
#define O (-1)
using namespace std;
queue <wchar_t> buf;
const wchar_t ja[] = L"ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅍㅌㅋㅎㅃㅉㄸㄲㅆ";
const wchar_t mo[] = L"ㅏㅑㅓㅕㅗㅛㅜㅠㅡㅣㅐㅔㅒㅖ";
int state;


bool check_ja(wchar_t ch){
    for (int i =0; i<wcslen(ja); i++){
        if(ja[i] == ch)
            return true;
    }
    return false;

}
bool check_mo(wchar_t ch){
    for (int i =0; i<wcslen(mo); i++){
        if(mo[i] == ch)
            return true;
    }
    return false;
}
int check_jamo(wchar_t ch){
    if(check_ja(ch))
        return JA;
    else if (check_mo(ch))
        return MO;
    else
        return O;
}
void start(wchar_t ch);
void j(wchar_t ch);
void jm(wchar_t ch);
void jmm(wchar_t ch);
void jmj(wchar_t ch);
void jmxj(wchar_t ch);

void run(wchar_t ch){
    switch (state){
        case START:
            start(ch);
            break;
        case J:
            j(ch);
            break;
        case JM:
            jm(ch);
            break;
        case JMM:
            jmm(ch);
            break;
        case JMJ:
            jmj(ch);
            break;
        case JMXJ:
            jmxj(ch);
            break;
    }
}
int main (int argc, char * argv[]){
    wchar_t wc; 
    setlocale(LC_ALL, "");

    state =START;
    while((wc=getwchar())!=WEOF){
       run(wc); 
    }
    return 0;
}
void start(wchar_t ch){
    int cond = check_jamo(ch);
    if(cond == JA){
        buf.push(ch);
        state = J;
    }
    else{
        buf.push(ch);
        cout<<"/";
        while(!buf.empty()){
            putwchar(buf.front());
            buf.pop();
        }
        state =START;
    }
}
void j(wchar_t ch){
    int cond = check_jamo(ch);
    if (cond == MO){
        buf.push(ch);
        state = JM;
    }

}
void jm(wchar_t ch){
    int cond = check_jamo(ch);
    if(cond == JA){
        buf.push(ch);
        state = JMJ;
    }
    else if (cond == MO){
        buf.push(ch);
        state = JMM;
    }
    else{
        cout<<"/";
        while (!buf.empty()){
            putwchar(buf.front());
            buf.pop();
        }
        cout<<"/";
        putwchar(ch);
        state = START;
    }

}
void jmj(wchar_t ch){
    int cond = check_jamo(ch);
    if (cond == JA){
        buf.push(ch);
        state = JMXJ;
    }
    else if (cond == MO){
        cout<<"/";
        while (buf.size()!=1){
            putwchar(buf.front());
            buf.pop();
        }
        buf.push(ch);
        state = JM;
    }
    else{
        cout<<"/";
        while (!buf.empty()){
            putwchar(buf.front());
            buf.pop();
        }
        cout<<"/";
        putwchar(ch);
        state = START;
    }

}
void jmm(wchar_t ch){
    int cond = check_jamo(ch);
    if(cond == JA){
        buf.push(ch);
        state = JMXJ;
    }
    else{
        buf.push(ch);
        cout<<"/";
        while (!buf.empty()){
            putwchar(buf.front());
            buf.pop();
        }
        state = START;
    }
}
void jmxj(wchar_t ch){
    int cond = check_jamo(ch);
    if(cond == JA){
        cout<<"/";
        while (!buf.empty()){
            putwchar(buf.front());
            buf.pop();
        }
        buf.push(ch);
        state = J;
    }
    else if (cond == MO){
        cout<<"/";
        while (buf.size()!=1){
            putwchar(buf.front());
            buf.pop();
        }
        buf.push(ch);
        state = JM;
    }
    else{
        buf.push(ch);
        cout<<"/";
        while (!buf.empty()){
            putwchar(buf.front());
            buf.pop();
        }
        cout<<"/";
        buf.push(ch);
        state = START;
    }
}

