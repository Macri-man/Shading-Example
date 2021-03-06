#ifndef GAMEOPTIONS_H_INCLUDED
#define GAMEOPTIONS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Gamecontants{

    SDL_Keycode move[4];
    SDL_Keycode jump;
    SDL_Keycode alt[8];
    SDL_Keycode aGrav;

    SDL_Keycode down;
    SDL_Keycode toggleView;
    int RESOLUTION_X;
    int RESOLUTION_Y;
    bool fullScreen;
    bool view;
    bool closeUp;
    int closeDist;
    int invert;
    int vol;
    int port;
    string host;
    string name;


    float fov;
    float projectionOffset;

    float dispdist;
    float sensitivity;

    } gameOptions;


/*
SDL_Keycode stringToKey(string s){

if(s=="a") return SDLK_a;
if(s=="b") return SDLK_b;
if(s=="c") return SDLK_c;
if(s=="d") return SDLK_d;
if(s=="e") return SDLK_e;
if(s=="f") return SDLK_f;
if(s=="g") return SDLK_g;
if(s=="h") return SDLK_h;
if(s=="i") return SDLK_i;
if(s=="j") return SDLK_j;
if(s=="k") return SDLK_k;
if(s=="l") return SDLK_l;
if(s=="m") return SDLK_m;
if(s=="n") return SDLK_n;
if(s=="o") return SDLK_o;
if(s=="p") return SDLK_p;
if(s=="q") return SDLK_q;
if(s=="r") return SDLK_r;
if(s=="s") return SDLK_s;
if(s=="t") return SDLK_t;
if(s=="u") return SDLK_u;
if(s=="v") return SDLK_v;
if(s=="w") return SDLK_w;
if(s=="x") return SDLK_x;
if(s=="y") return SDLK_y;
if(s=="z") return SDLK_z;
if(s=="1") return SDLK_1;
if(s=="2") return SDLK_2;
if(s=="3") return SDLK_3;
if(s=="4") return SDLK_4;
if(s=="5") return SDLK_5;
if(s=="6") return SDLK_6;
if(s=="7") return SDLK_7;
if(s=="8") return SDLK_8;
if(s=="9") return SDLK_9;
if(s=="0") return SDLK_0;

if(s=="k1") return SDLK_KP_1;
if(s=="k2") return SDLK_KP_2;
if(s=="k3") return SDLK_KP_3;
if(s=="k4") return SDLK_KP_4;
if(s=="k5") return SDLK_KP_5;
if(s=="k6") return SDLK_KP_6;
if(s=="k7") return SDLK_KP_7;
if(s=="k8") return SDLK_KP_8;
if(s=="k9") return SDLK_KP_9;
if(s=="k0") return SDLK_KP_0;
if(s=="k+") return SDLK_KP_PLUS;
if(s=="k-") return SDLK_KP_MINUS;
if(s=="k*") return SDLK_KP_MULTIPLY;
if(s=="k/") return SDLK_KP_DIVIDE;
if(s=="kenter") return SDLK_KP_ENTER;
if(s=="k.") return SDLK_KP_PERIOD;

if(s=="insert") return SDLK_INSERT;
if(s=="home") return SDLK_HOME;
if(s=="pgup") return SDLK_PAGEUP;
if(s=="pgdown") return SDLK_PAGEDOWN;
if(s=="end") return SDLK_END;
if(s=="delete") return SDLK_DELETE;

if(s=="ralt") return SDLK_RALT;
if(s=="rshift") return SDLK_RSHIFT;
if(s=="rctrl") return SDLK_RCTRL;
if(s=="lalt") return SDLK_LALT;
if(s=="lshift") return SDLK_LSHIFT;
if(s=="lctrl") return SDLK_LCTRL;
if(s=="up") return SDLK_UP;
if(s=="down") return SDLK_DOWN;
if(s=="right") return SDLK_RIGHT;
if(s=="left") return SDLK_LEFT;

if(s=="`") return SDLK_BACKQUOTE;
if(s=="[") return SDLK_LEFTBRACKET;
if(s=="]") return SDLK_RIGHTBRACKET;
if(s=="-") return SDLK_MINUS;
if(s=="=") return SDLK_EQUALS;
if(s=="backspace") return SDLK_BACKSPACE;
if(s=="/") return SDLK_SLASH;
if(s=="\\") return SDLK_BACKSLASH;
if(s==",") return SDLK_COMMA;
if(s==".") return SDLK_PERIOD;
if(s==";") return SDLK_SEMICOLON;
if(s=="'") return SDLK_QUOTE;

if(s=="f1") return SDLK_F1;
if(s=="f2") return SDLK_F2;
if(s=="f3") return SDLK_F3;
if(s=="f4") return SDLK_F4;
if(s=="f5") return SDLK_F5;
if(s=="f6") return SDLK_F6;
if(s=="f7") return SDLK_F7;
if(s=="f8") return SDLK_F8;
if(s=="f9") return SDLK_F9;
if(s=="f10") return SDLK_F10;
if(s=="f11") return SDLK_F11;
if(s=="f12") return SDLK_F12;
if(s=="f13") return SDLK_F13;
if(s=="f14") return SDLK_F14;
if(s=="f15") return SDLK_F15;

if(s=="esc") return SDLK_ESCAPE;
//if(s=="pb") return SDLK_BREAK;

return SDLK_F15;
    }
*/

void processINILine(string s){


    int input=s.find('=');
    string mod=s.substr(0,input);
    string key=s.substr(input);


    if(mod=="XRES")
    gameOptions.RESOLUTION_X=atoi(key.c_str());
    if(mod=="YRES")
    gameOptions.RESOLUTION_Y=atoi(key.c_str());

    if(mod=="PORT")
    gameOptions.port=atoi(key.c_str());

    if(mod=="CLOSEDIST")
    gameOptions.closeDist=atoi(key.c_str());

    if(mod=="FOV")
    gameOptions.fov=atoi(key.c_str());
    //if(mod=="GUISIZE")
    //gameOptions.dispdist=atof(mew.c_str());

    if(mod=="SENSE")
    gameOptions.sensitivity=atof(key.c_str());

    if(mod=="FULLSCREEN")
    gameOptions.fullScreen=key=="true";
    if(mod=="CLOSEUP")
    gameOptions.closeUp=key=="true";
    if(mod=="VIEW")
    gameOptions.view=key=="true";

    if(mod=="INVERT")
    gameOptions.invert=(key=="true"?-1:1);

    if(mod == "FORWARD")
    gameOptions.move[0]=SDL_GetKeyFromName(key.cstr());
    if(mod == "LEFT")
    gameOptions.move[1]=SDL_GetKeyFromName(key.cstr());
    if(mod == "BACK")
    gameOptions.move[2]=SDL_GetKeyFromName(key.cstr());
    if(mod == "RIGHT")
    gameOptions.move[3]=SDL_GetKeyFromName(key.cstr());
    if(mod == "JUMP")
    gameOptions.jump=SDL_GetKeyFromName(key.cstr());
    if(mod == "DOWN")
    gameOptions.down=SDL_GetKeyFromName(key.cstr());

    if(mod == "TOGGLEVIEW")
    gameOptions.toggleView=SDL_GetKeyFromName(key.cstr());

    if(mod == "A0")
    gameOptions.alt[0]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A1")
    gameOptions.alt[1]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A2")
    gameOptions.alt[2]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A3")
    gameOptions.alt[3]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A4")
    gameOptions.alt[4]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A5")
    gameOptions.alt[5]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A6")
    gameOptions.alt[6]=SDL_GetKeyFromName(key.cstr());
    if(mod == "A7")
    gameOptions.alt[7]=SDL_GetKeyFromName(key.cstr());
    if(mod == "AGRAV")
    gameOptions.aGrav=SDL_GetKeyFromName(key.cstr());
    if(mod == "IP")
    gameOptions.host=key;
    if(mod == "NAME")
    gameOptions.name=key;
}

void loadGameOptions(){

    gameOptions.dispdist=20;
    gameOptions.vol=100;
    gameOptions.projectionOffset=.7;
    gameOptions.closeDist=250;

    ifstream inFile("settings.ini");
    string temp;
    while(inFile){
    getline(inFile,temp);
    processINILine(temp);
    }
}




#endif // GAMEOPTIONS_H_INCLUDED
