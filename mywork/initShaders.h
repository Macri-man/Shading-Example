#ifndef INITSHADERS_H_
#define INITSHADERS_H_
//functions for loading in shaders
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "GL/glu.h"

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

//function prototypes
GLuint createShader(GLenum type, const GLchar* shadeSource);
const GLchar* inputShader(const char* filename);
GLuint createProgram(const vector<GLuint> shadeList);
void printLog(Glenum type, GLuint obj);

typedef struct{
  GLenum type;// GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
  const char* filename;//name of file to input
} ShaderInfo;

typedef struct{
	GLenum progNum;
} ProgInfo;

//create the shaders for your program
Gluint initShaders(ShaderInfo* shaders){
  
  ShaderInfo* shade=shaders;
  vector<GLuint> Shadelist;//initialize list of shaders
  
  while(shade->type != GL_NONE){//loop through all the shaders in the list
    Shadelist.push_back(createShader(shade->type,inputShader(shade->filename)));//adding shaders into the list
    ++shade;//incrementation
  }
  
  GLuint program=createProgram(Shadelist);//creates the program linking to all the shaders
  
  glUseProgram(program);//installs a program object as part of current rendering state
  
	return program;
}

//this funtion loads the shader from the vertex, fragments shaders 
const GLchar* inputShader(const char* filename){

  FILE* fshade = fopen(filename, "rb");//opens file
  
  if(!fshade){//check to see if file is opened
    fprintf(stderr,"unable to open file '%s'\n",filename);
    return NULL;
  }
  
  //neat way to get the length of the file
  fseek(fshade, 0, SEEK_END);
  long filesize=ftell(fshade);
  fseek(fshade, 0, SEEK_SET);
  
  
  //allocates memory for the file and read in the file 
  GLchar* shadingSource= new GLchar[filesize+1];//
  fread(shadingSource, 1, filesize, fshade);
  
  
  if(ftell(fshade) == 0){//checks to see if the file is empty
    fprintf(stderr, "File '%s' is empty.\n",filename);
    return NULL;
  }

  fclose(fshade);//closes file
  
  shadingSource[filesize] = 0;//neat way to set a '\0' at end of file
  
  return const_cast<const GLchar*>(shadingSource);//overloads the const so the value with change per file  
  
  //NOTE: if the file is unable to open or is empty this function will segmentation fault your program
}

//this function create your shader
GLuint createShader(GLenum type, const GLchar* shadeSource){
  
  GLuint shader = glCreateShader(type);//create shader based on type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
  glShaderSource(shader, 1, &shadeSource, NULL);//loads the source code of the file into the shader
  
  glCompileShader(shader);//compiles a shader object
  
  GLint compileStatus;//status of the compilation variable
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);//returns the comiple status into the variable
  
  if(!compileStatus){//checks to see if the shader compiled
  	printLog(type,shader);
  }
  return shader;//self explanatory
}

//this function creates the shading program we are going to link the shader too
GLuint createProgram(const vector<GLuint> shadeList){

  GLuint program = glCreateProgram();//creates your program
  
  for(GLuint i=0;i<shadeList.size();i++){glAttachShader(program,shadeList[i]);}//attaches shaders to program
  
  glBindAttribLocation(program, 0, "in_Position");
  glBindAttribLocation(program, 2, "in-Tex");//binds the location an attribute to a program
  glLinkProgram(program);//links program to your program //weird
  
  GLint linkStatus;//status for linking variable
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);//returns the status of linking the program into the variable
  
  if(!linkStatus){//checks to see if your program linked to the program
    printLog(NULL,program);
    for(GLuint i=0;i<shadeList.size();i++){glDeleteShader(shadeList[i]);}//memory management
  }
  return program;//self explanatory
}

void printLog(Glenum type, GLuint obj){
	GLuint logSize;

	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&logSize);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&logSize);
	
	char *infoLog = new char[logSize+1];

	if(glIsShader(obj)){
		glGetShaderInfoLog(obj,maxLength,&infologLength,infoLog);
		const char *shadeType=NULL;
		switch(type){
		  case GL_VERTEX_SHADER: shadeInfo= "vertex";break;
		  case GL_GEOMETRY_SHADER_EXT: shadeInfo = "geometric";break;
      	  case GL_FRAGMENT_SHADER: shadeInfo = "fragment";break;
      	}
      	fprintf(stderr,"\nCompile failure in %u shader: %s\n Error message:\n%s\n",type,shadeInfo,infoLog)
	}else{
		glGetProgramInfoLog(obj,maxLength,&infologLength,infoLog);
		fprintf(stderr,"\nShader linking failed: %s\n",infoLog);
	}
	delete[] infoLog;
	delete[] shadeType;
}

#endif
