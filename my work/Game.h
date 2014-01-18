#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

void setupGame(){
theWorld= new World();
theWorld->players.push_back(Player(keyboardController));
theWorld->players.push_back(Player(keyboardController));

}

void shutdownGame(){
    if(theWorld)
        delete theWorld;


}



void mainLoop(time_t time){




}

#endif // GAME_H_INCLUDED
