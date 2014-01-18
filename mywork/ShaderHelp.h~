#ifndef SHADERHELP_H_INCLUDED
#define SHADERHELP_H_INCLUDED
#include <dirent.h>
#include "initShaders.h" 
#include <vector>
#include <cstring>

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
	ProgInfo programs=new ProgInfo[0];
	

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

	programs[0].progNum=initShaders(shaders);
}

void setupUniforms(Glenum prog){
		
		/*
    int i=0;
    glGetIntegerv(GL_CURRENT_PROGRAM,&i);
    */
    
    glm::mat4 temp;
    //temp=glm::perspective(gameOptions.fov, (gameOptions.RESOLUTION_X)/((float)gameOptions.RESOLUTION_Y), 2.0f, 5000.0f);
    temp=glm::ortho(-gameOptions.RESOLUTION_X/20.0f,gameOptions.RESOLUTION_X/20.0f,gameOptions.RESOLUTION_Y/-20.0f,gameOptions.RESOLUTION_Y/20.0f, 2.0f, 5000.0f);
    int tempLoc=glGetUniformLocation(prog, "projectionMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    temp= glm::mat4();
    tempLoc=glGetUniformLocation(prog, "modelMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    //temp=glm::translate(temp,glm::vec3(0,10,-30));
    //temp=glm::rotate(temp,-50.0f,glm::vec3(1,0,0));
    //temp=glm::rotate(temp,40.0f,glm::vec3(0,0,1));

    //temp=glm::rotate(temp,-50.0f,glm::vec3(1,0,0));
    //temp=glm::rotate(temp,40.0f,glm::vec3(0,0,1));

    tempLoc=glGetUniformLocation(prog, "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    tempLoc=tempLoc=glGetUniformLocation(prog, "Sampler");
    glUniform1i(tempLoc, 0);
    glUseProgram(prog);
}

#endif // SHADERHELP_H_INCLUDED
