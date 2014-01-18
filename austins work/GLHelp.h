#ifndef GLHELP_H_INCLUDED
#define GLHELP_H_INCLUDED
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



void setupGL(){

    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);

    glViewport(0, 0, gameOptions.RESOLUTION_X, gameOptions.RESOLUTION_Y);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(gameOptions.fov, (gameOptions.RESOLUTION_X)/((float)gameOptions.RESOLUTION_Y), 2, 2550);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);    //http://arcsynthesis.org/gltut/Positioning/Tut05%20Overlap%20and%20Depth%20Buffering.html
    //glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);


    glEnable ( GL_TEXTURE_2D ) ;
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
    setupShaders();
    //setupFrameBuffer();

    //glGenTextures(1,&tex);
    //glBindTexture(GL_TEXTURE_2D,tex);
    /*glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_LSB_FIRST,  GL_TRUE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
    //glTexImage2D( GL_TEXTURE_2D, 0, 4, image->w, image->h, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels );


    glLoadIdentity();


    }

void shutdownGL(){
    cleanupShaders();


}


void render(SDL_Window * win){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glUseProgram(0);

    /*glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex3f(10,10,-50);
    glVertex3f(10,-10,-50);
    glVertex3f(-10,-10,-50);
    glVertex3f(-10,10,-50);
    glEnd();*/

	printf("2:%s\n",gluErrorString(glGetError()));
    theWorld->render();




    SDL_GL_SwapWindow(win);
}


#endif // GLHELP_H_INCLUDED
