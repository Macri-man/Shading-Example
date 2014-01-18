#ifndef CONTROLLERS_H_INCLUDED
#define CONTROLLERS_H_INCLUDED

void keyboardController(SDL_Event &event, Player &p){

switch (event.type){

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    // exit if ESCAPE is pressed

                    if(p.number==0){
                    if (event.key.keysym.sym == SDLK_w){
                        p.moving[0]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    if (event.key.keysym.sym == SDLK_s){
                        p.moving[1]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    if (event.key.keysym.sym == SDLK_a){
                        p.moving[2]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    if (event.key.keysym.sym == SDLK_d){
                        p.moving[3]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    }
                    if(p.number==1){
                    if (event.key.keysym.sym == SDLK_i){
                        p.moving[0]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    if (event.key.keysym.sym == SDLK_k){
                        p.moving[1]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    if (event.key.keysym.sym == SDLK_j){
                        p.moving[2]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    if (event.key.keysym.sym == SDLK_l){
                        p.moving[3]=(event.type==SDL_KEYDOWN?1:0);
                        }
                    }

                break;
                }
}


if(p.moving[0])
p.pos.y+=p.speed;
if(p.moving[1])
p.pos.y-=p.speed;
if(p.moving[2])
p.pos.x-=p.speed;
if(p.moving[3])
p.pos.x+=p.speed;

}

#endif // CONTROLLERS_H_INCLUDED
