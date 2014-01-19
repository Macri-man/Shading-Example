#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED


class World{
    private:
    World (const World& w);//don't copy me.
    World operator= (const World &w);

    public:

    World();
    ~World();

    void render();




    vector <Player> players;
    GLuint vao;
    GLuint vbo[2];

}*theWorld;


World::World () {
    float size =20;
    GLfloat texCoords[8]={0,0,0,1,1,1,1,0};
    GLfloat vertexCoords[12]={size,size,-50,
                                size,-size,-50,
                                -size,-size,-50,
                                -size,size,-50};

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(2,vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8,texCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    }

World::~World(){
    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(2,vbo);
    }

void World::render(){

glBindTexture(GL_TEXTURE_2D,getTexture("cb"));
glUseProgram(shaders["main"]);

glm::mat4 temp;
int tempLoc=glGetUniformLocation(shaders["main"], "modelMatrix");
glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

glBindVertexArray(vao);
glDrawArrays(GL_QUADS,0,4);

glBindVertexArray(0);
glUseProgram(0);
glBindTexture(GL_TEXTURE_2D,0);

printf("1:%s\n",gluErrorString(glGetError()));

for(int x=0;x<players.size();x++)
players.at(x).render();
}




#endif // TERRAIN_H_INCLUDED
