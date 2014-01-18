#ifndef SHADERHELP_H_INCLUDED
#define SHADERHELP_H_INCLUDED
#include <dirent.h>
#include "initShaders.h" 
#include <vector>
#include <cstring>

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

#ifndef __scanDirectory
#define __scanDirectory
    void scanDirectory(vector<string> &files, string dirr){

        DIR *dir;
    struct dirent *ent;
    /* open directory stream */
    dir=opendir(dirr.c_str());
    if(dir!=NULL){
      /* print all the files and directories within directory */
      while ((ent=readdir (dir))!=NULL){
       // switch (ent->d_type) {
      //  case DT_REG:
          //printf ("%*.*s\n", ent->d_namlen, ent->d_namlen, ent->d_name);
          files.push_back(ent->d_name);
      //    break;

      //  case DT_DIR:
          //printf ("%s (dir)\n", ent->d_name);
      //    break;

//        default:
 //       break;
          //printf ("%s:\n", ent->d_name);
 //       }
      }

      closedir (dir);
    } else {
      /* could not open directory */
      cerr<<"Could not open "<<dirr<<" Folder!";
    }


        }
#endif

void setupShaders(){

	vector<string> files;
	scanDirectory(files,"Shaders");
	ShaderInfo shaders[files.size()];

	for(int i=0;i<files.size();i++){
		int temp=files[i].find(".");
		string id=files[i].substr(0,temp);
			switch(id){
 	  	 case"vert":shaders[i].type=GL_VERTEX_SHADER;break;
 	  	 case"geom":shaders[i].type=GL_GEOMETRY_SHADER_EXT;break;
 	  	 case"frag":shaders[i].type=GL_FRAGMENT_SHADER;break;
 	  	 case"tess":shaders[i].type=GL_TESS_EVALUATION_SHADER;break;
 	  	 case"eval":shaders[i].type=GL_TESS_CONTROL_SHADER;break;
 	 	}
		shaders[i].filename=file.at(i);
	}

	initShaders(shaders);
}

void setupUniforms(){

    int i=0;

    glGetIntegerv(GL_CURRENT_PROGRAM,&i);
    
    glm::mat4 temp;
    //temp=glm::perspective(gameOptions.fov, (gameOptions.RESOLUTION_X)/((float)gameOptions.RESOLUTION_Y), 2.0f, 5000.0f);
    temp=glm::ortho(-gameOptions.RESOLUTION_X/20.0f,gameOptions.RESOLUTION_X/20.0f,gameOptions.RESOLUTION_Y/-20.0f,gameOptions.RESOLUTION_Y/20.0f, 2.0f, 5000.0f);
    int tempLoc=glGetUniformLocation(shaders["main"], "projectionMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    temp= glm::mat4();
    tempLoc=glGetUniformLocation(shaders["main"], "modelMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);



    //temp=glm::translate(temp,glm::vec3(0,10,-30));
    //temp=glm::rotate(temp,-50.0f,glm::vec3(1,0,0));
    //temp=glm::rotate(temp,40.0f,glm::vec3(0,0,1));

    //temp=glm::rotate(temp,-50.0f,glm::vec3(1,0,0));
    //temp=glm::rotate(temp,40.0f,glm::vec3(0,0,1));

    tempLoc=glGetUniformLocation(shaders["main"], "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    tempLoc=tempLoc=glGetUniformLocation(shaders["main"], "Sampler");
    glUniform1i(tempLoc, 0);



    glUseProgram(0);

}

#endif // SHADERHELP_H_INCLUDED
