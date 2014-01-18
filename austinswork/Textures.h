#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED

#include <dirent.h>
#include <map>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


GLuint defaultTex;
map<string,GLuint> loadedTextures;
void scanDirectory(vector<string> &files, string dir);

bool is2Pwr(int x){
while (x%2==0){
x/=2;
}
return x==1;
}

void loadPicture(std::string file, GLuint tex){

    if(file.find(".bmp")==string::npos)
    return;

    cout<<"Loaded: "<<file<<endl;


    SDL_Surface *image;
    SDL_Surface *fixed;
    image = SDL_LoadBMP(file.c_str());

    if(!image){
    cerr<<"error loading:"<<file;
    return;
    //system("pause");
    }

    fixed=SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);

    if(!fixed){
    cerr<<"error loading:"<<file;
    return;
    //system("pause");
    }



    if(!(is2Pwr(image->w)&&is2Pwr(image->h)))
    cerr<<"image is not power of 2 it may load incorrectly"<<endl;
// handle error

    glBindTexture(GL_TEXTURE_2D,tex);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    //if(alpha)
    //glTexImage2D( GL_TEXTURE_2D, 0, 4, image->w, image->h, 0,GL_BGRA, GL_UNSIGNED_BYTE, image->pixels );
    //else
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,GL_RGBA, GL_UNSIGNED_BYTE, fixed->pixels );

    if ( image ) {
	SDL_FreeSurface( image );
    }

    }

void loadTextures(){
glGenTextures(1, &defaultTex);

vector<string> files;
scanDirectory(files,"Textures");


GLuint temps[files.size()];
glGenTextures(files.size(),temps);

for(int x=0;x<files.size();x++){
loadPicture("Textures/"+files.at(x),temps[x]);
loadedTextures[files.at(x).substr(0,files.at(x).size()-4)]=temps[x];
}

    }

void unloadTextures(){

for(map<string,GLuint>::iterator it=loadedTextures.begin();it!=loadedTextures.end();it++)
glDeleteTextures(1,&it->second);

}

#ifndef __scanDirectory
#define __scanDirectory
    void scanDirectory(vector<string> &files, string dirr){

        DIR *dir;
    struct dirent *ent;
    /* open directory stream */
    dir = opendir (dirr.c_str());
    if (dir != NULL) {

      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          files.push_back(ent->d_name);
      }

      closedir (dir);
    } else {
      /* could not open directory */
      cerr<<"Could not open "<<dirr<<" Folder!";
    }


        }
#endif

GLuint getTexture(std::string s){
std::map<string,GLuint>::iterator it= loadedTextures.find(s);
if(it==loadedTextures.end())
return loadedTextures["dne"];
return it->second;
}


class TextRenderer{

public:

TextRenderer(GLuint shad){
shader=shad;
charSheet=getTexture("TextW");
charsPerLine=30;
linesPerSheet=19;
charWidth=.995/charsPerLine;
charHeight=.995/linesPerSheet;

renderHeight=charHeight*10;
renderWidth=charWidth*10;
color[0]=1;color[1]=1;color[2]=1;color[3]=1;
}

TextRenderer(string text, GLuint shad, int cpl, int lps, float offx, float offy){
shader=shad;
charSheet=getTexture(text);
charsPerLine=cpl;
linesPerSheet=lps;
charWidth=(1-offx)/charsPerLine;
charHeight=(1-offy)/linesPerSheet;

renderHeight=charHeight;
renderWidth=charWidth;
color[0]=1;color[1]=1;color[2]=1;color[3]=1;
}

void renderString(string s);
void renderShadedString(string s);
void renderToBox(string s, float width, float height);
void getTexCoords(char c, float *ret);
void setColor(float r, float g, float b, float a){
color[0]=r;color[1]=g;color[2]=b;color[3]=a;
}

protected:
GLuint shader;
GLuint charSheet;
float charWidth;
float charHeight;
int charsPerLine;
int linesPerSheet;
float renderWidth;
float renderHeight;
float color[4];

};

void TextRenderer::renderString(string s){

glBindTexture(GL_TEXTURE_2D,charSheet);
for(int x=0;x<s.length();x++){
glColor4f(0,0,0,1);
GLfloat texCoords[8];
getTexCoords(s[x],texCoords);
glBegin(GL_QUADS);
glTexCoord2f(texCoords[0],texCoords[1]);
glVertex3f(x*renderWidth,0,0);
glTexCoord2f(texCoords[2],texCoords[3]);
glVertex3f(x*renderWidth,-renderHeight,0);
glTexCoord2f(texCoords[4],texCoords[5]);
glVertex3f((x+1)*renderWidth,-renderHeight,0);
glTexCoord2f(texCoords[6],texCoords[7]);
glVertex3f((x+1)*renderWidth,0,0);
glEnd();
}
glBindTexture(GL_TEXTURE_2D,0);

}

void TextRenderer::getTexCoords(char c, GLfloat *ret){

int row,column;
row=(unsigned int)(c-1)/charsPerLine;
column=(unsigned int)(c-1)%charsPerLine;

(ret)[0]=column*charWidth;
(ret)[1]=row*charHeight;

(ret)[2]=column*charWidth;
(ret)[3]=(row+1)*charHeight;

(ret)[4]=(column+1)*charWidth;
(ret)[5]=(row+1)*charHeight;

(ret)[6]=(column+1)*charWidth;
(ret)[7]=row*charHeight;
}


void TextRenderer::renderShadedString(string s){
GLint currentShad;
glGetIntegerv(GL_CURRENT_PROGRAM,&currentShad);
glUseProgram(shader);
glBindTexture(GL_TEXTURE_2D,charSheet);

    glm::mat4 modMatrix;
    glGetFloatv(GL_MODELVIEW_MATRIX,&modMatrix[0][0]);
    int modMatrixLoc=glGetUniformLocation(shader, "modelMatrix");
    glUniformMatrix4fv(modMatrixLoc, 1, GL_FALSE, &modMatrix[0][0]);
    int samLoc=glGetUniformLocation(shader, "color");
    glUniform4fv(samLoc,1, color);

glColor4f(0,0,0,1);

GLfloat texCoords[8*s.length()];
GLfloat vertexCoords[8*s.length()];
//getTexCoords(s[x],texCoords);
for(int x=0;x<s.length();x++){
for(int y=0;y<8;y++)
vertexCoords[x*8+y]=0;

vertexCoords[x*8]=x*renderWidth;
vertexCoords[x*8+2]=x*renderWidth;
vertexCoords[x*8+3]=-renderHeight;
vertexCoords[x*8+4]=(x+1)*renderWidth;
vertexCoords[x*8+5]=-renderHeight;
vertexCoords[x*8+6]=(x+1)*renderWidth;
//setup texture coords
getTexCoords(s[x],&texCoords[x*8]);
}
GLuint vao;
GLuint buff[2];

glGenVertexArrays(1,&vao);
glBindVertexArray(vao);

glGenBuffers(2,buff);
glBindBuffer(GL_ARRAY_BUFFER, buff[0]);
glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8*s.length(),vertexCoords,GL_STATIC_DRAW);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

glBindBuffer(GL_ARRAY_BUFFER, buff[1]);
glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8*s.length(),texCoords,GL_STATIC_DRAW);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

///glBindVertexArray(buff[0]);//pretty sure i don't need this
glEnableVertexAttribArray(0);
glEnableVertexAttribArray(2);

glDrawArrays(GL_QUADS,0,4*s.length());

//glDisableVertexAttribArray(0);
//glDisableVertexAttribArray(2);
glBindVertexArray(0);

glDeleteBuffers(2,buff);
glDeleteVertexArrays(1,&vao);
glBindTexture(GL_TEXTURE_2D,0);
glUseProgram(currentShad);
}

void TextRenderer::renderToBox(string s, float width, float height){
GLint currentShad;
glGetIntegerv(GL_CURRENT_PROGRAM,&currentShad);

int maxChars=width/renderWidth;
int maxLines=height/renderHeight;
int cnt=0;
glPushMatrix();
for(int x=0;x<s.length();x+=maxChars){
renderShadedString(s.substr(x,maxChars));
glTranslatef(0,-renderHeight,0);
cnt++;
if(cnt>maxLines)
break;
}
glPopMatrix();
glUseProgram(currentShad);
}


#endif // TEXTURES_H_INCLUDED
