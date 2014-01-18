#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif


#include <map>
#include <list>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameOptions.h"
#include "Textures.h"
#include "ShaderHelp.h"
#include "Player.h"
#include "Controllers.h"
#include "Terrain.h"

#include "GLHelp.h"
#include "Input.h"
#include "Game.h"
#include <time.h>



int main ( int argc, char** argv )
{

    loadGameOptions();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    //freopen("CON", "w", stderr);



    //sound_buffer== new Uint8[1024];
    //SDL_PauseAudio(0);
    //SDL_Surface* screen = SDL_SetVideoMode(gameOptions.RESOLUTION_X, gameOptions.RESOLUTION_Y, 0, (gameOptions.fullScreen?SDL_FULLSCREEN:0)|SDL_HWSURFACE|SDL_GL_DOUBLEBUFFER|SDL_OPENGL);
    //SDL_WM_SetCaption("WACOM", "WACOM");
    SDL_Window* screen = SDL_CreateWindow("WWRAC",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,gameOptions.RESOLUTION_X, gameOptions.RESOLUTION_Y, (gameOptions.fullScreen?SDL_WINDOW_FULLSCREEN:0)|SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext=SDL_GL_CreateContext(screen);
    SDL_ShowCursor(false);
    GLenum err = glewInit();
    if (GLEW_OK != err){
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    //inialize things
    loadTextures();
    setupGL();
    printf("4:%s\n",gluErrorString(glGetError()));
    setupUniforms();
    setupGame();


    srand(time(NULL));


    if ( !screen )
    {
        printf("Unable to start video: %s\n", SDL_GetError());
        cout<<gameOptions.RESOLUTION_X<<"x"<<gameOptions.RESOLUTION_Y<<endl;
        return 1;
    }


//vars here
time_t ticks;
time_t count=0;

printf("3:%s\n",gluErrorString(glGetError()));
    while (!quit)
    {

        ticks=time(NULL);
        count++;

        gameInput();
        mainLoop(count);
        render(screen);

    } // end main loop

    //cleanup
    shutdownGL();
    unloadTextures();
    shutdownGame();
    SDL_GL_DeleteContext(glcontext);
    // all is well ;)
    printf("Exited cleanly\n");
    //exit(0);
        return 0;
}
