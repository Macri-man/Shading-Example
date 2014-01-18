#ifndef SHADERHELP_H_INCLUDED
#define SHADERHELP_H_INCLUDED
#include <dirent.h>
#include <vector>
#include <cstring>

vector<GLuint> subShaders;
map<string,GLuint> shaders;

void printLog(GLuint obj)
{
	int infologLength = 0;
	int maxLength;

	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);

	char infoLog[maxLength];

	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);

	if (infologLength > 0)
		printf("%s\n",infoLog);
	printf("Log:%s\n",gluErrorString(glGetError()));
}

GLuint loadShader(string s,GLenum type){
string shad;

ifstream in(s.c_str());
      string line;
      while ( in.good() ){
      getline (in,line);
      shad+=line+"\n";
        }
    in.close();

GLchar* vShad = new char [shad.length()+1];
  strcpy (vShad, shad.c_str());

GLuint vs;
vs = glCreateShader(type);
	glShaderSource(vs, 1, (const GLchar**)(&vShad), NULL);
	glCompileShader(vs);
	printLog(vs);

delete[] vShad;

return vs;
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

multimap<string,string> shaderPrograms;
vector<string> files;
scanDirectory(files,"Shaders");

for(int x=0;x<files.size();x++){
//cout<<files.at(x)<<endl;

int temp=files.at(x).find(".");
string id=files.at(x).substr(0,temp);

shaderPrograms.insert(pair<string,string>(id,files.at(x)));
}
printf("7:%s\n",gluErrorString(glGetError()));
GLuint prog=0, shad=0;
string last="";
for (multimap<string,string>::iterator it=shaderPrograms.begin(); it!=shaderPrograms.end(); ++it){
    //std::cout << (*it).first << " => " << (*it).second << '\n';
    if(it->first!=last){
    if(last!=""){

        glBindAttribLocation(prog,0,"in_Position");
        glBindAttribLocation(prog,2,"in_Tex");

    glLinkProgram(prog);
	printLog(prog);
	GLint IsLinked;
        glGetProgramiv(prog, GL_LINK_STATUS, (GLint *)&IsLinked);
        if(IsLinked==false)
	cout<<"something isn't linked!!!"<<endl;
	
    }
    prog=glCreateProgram();
    shaders[it->first]=prog;
    last=it->first;
    }

    if(it->second.find("vert")!=string::npos)
    shad=loadShader("Shaders/"+it->second,GL_VERTEX_SHADER);
    else if(it->second.find("frag")!=string::npos)
    shad=loadShader("Shaders/"+it->second,GL_FRAGMENT_SHADER);
    else if(it->second.find("geom")!=string::npos)
    shad=loadShader("Shaders/"+it->second,GL_GEOMETRY_SHADER);
    //
    //else if(it->second.find("comp")!=string::npos)
    //shad=loadShader("Shaders/"+it->second,GL_COMPUTE_SHADER);
    else if(it->second.find("tess")!=string::npos)
    shad=loadShader("Shaders/"+it->second,GL_TESS_CONTROL_SHADER);
    else if(it->second.find("eval")!=string::npos)
    shad=loadShader("Shaders/"+it->second,GL_TESS_EVALUATION_SHADER);


    glAttachShader(prog,shad);

}
printf("8:%s\n",gluErrorString(glGetError()));
for(map<string,GLuint>::iterator it=shaders.begin();it!=shaders.end();it++)
cout<<"loaded program "<<it->first<<endl;



}


void setupUniforms(){
	printf("6:%s\n",gluErrorString(glGetError()));
    glUseProgram(shaders["main"]);
    int i=0;

    printf("5:%s\n",gluErrorString(glGetError()));
    glGetIntegerv(GL_CURRENT_PROGRAM,&i);
    cout<<shaders["main"]<<" "<<i<<" "<<(int)glIsProgram(shaders["main"])<<endl;
    
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

void cleanupShaders(){

for(int x=0;x<subShaders.size();x++)
glDeleteShader(subShaders.at(x));


}

#endif // SHADERHELP_H_INCLUDED
