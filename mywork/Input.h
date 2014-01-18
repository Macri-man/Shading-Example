#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <math.h>
#define SDL_WHEEL_UP 4
#define SDL_WHEEL_DOWN 5


bool quit=false;

/*
glm::vec2 GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    return testWindow(posX,posY,posZ,&wins.at(current));
    //cout<<posX<<" "<<posY<<" "<<posZ<<endl;
    //return CVector3(posX, posY, posZ);
}*/

int gameInput(){
    SDL_Event event;

        do
        {
            if(theWorld){
            for(int x=0;x<theWorld->players.size();x++)
            if(theWorld->players.at(x).control)
            theWorld->players.at(x).control(event,theWorld->players.at(x));
            }


            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                quit=true;
                break;

            case SDL_MOUSEBUTTONDOWN:{





            break;}

            case SDL_MOUSEBUTTONUP:{

            //localPlayer->inputAction(-event.button.button);
            ///wins.at(current).prog->sendClick(GetOGLPos(event.button.x,event.button.y),true,event.button.button);

            }//}
            break;


            case SDL_MOUSEMOTION:



            break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed

                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        quit=true;
                        }









                break;
                }

                case SDL_KEYUP:
                {



                    break;
                }


            } // end switch
        }while (SDL_PollEvent(&event)); // end of message processing
    return 0;
    }



#endif // INPUT_H_INCLUDED
