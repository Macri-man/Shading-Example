#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player;
typedef void (*Controller) (SDL_Event &event, Player &p);
int PlayersNumber =0;//unique identifier for players

class Player{

protected:
void setupVAO();

public:

Player(Controller c);
~Player();
Player (const Player& p);
Player operator= (const Player &p);

void render();

bool renderSetup;
GLuint vao, vbo[2];
glm::vec2 pos;
float speed;
int moving[4];//udrl for use in controllers
int number;
Controller control;

int frame;//sent to shader

};

Player::Player(Controller c){
renderSetup=false;
vao=0;
vbo[0]=0;
vbo[0]=0;
for(int x=0;x<4;x++)
moving[x]=0;
speed=.05;
pos.x=0;
pos.y=0;
frame=0;
control=c;
number=PlayersNumber++;
}

Player::~Player(){
if(renderSetup){
glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(2,vbo);
}
}

Player::Player (const Player& p){
renderSetup=false;
vao=0;
vbo[0]=0;
vbo[0]=0;
for(int x=0;x<4;x++)
moving[x]=0;
frame=0;
pos=p.pos;
speed=p.speed;
control=p.control;
number=p.number;
}

Player Player::operator= (const Player &p){
if(renderSetup){
glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(2,vbo);
}
renderSetup=false;
vao=0;
vbo[0]=0;
vbo[0]=0;

speed=p.speed;
pos=p.pos;
control=p.control;
number=p.number;
}

void Player::setupVAO(){
float width =2,height=5;
float depth= -40;
    GLfloat texCoords[8]={0,0,0,1,1,1,1,0};
    GLfloat vertexCoords[12]={width,height,depth,
                                width,-height,depth,
                                -width,-height,depth,
                                -width,height,depth};

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
    renderSetup=true;
}

void Player::render(){

if(!renderSetup)
setupVAO();

glBindTexture(GL_TEXTURE_2D,getTexture("wizard2"));
glUseProgram(shaders["main"]);

glm::mat4 temp;
temp=glm::translate(temp,glm::vec3(pos,0));
int tempLoc=glGetUniformLocation(shaders["main"], "modelMatrix");
glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

tempLoc=glGetUniformLocation(shaders["main"], "time");
glUniform1i(tempLoc, ++frame);
//cout<<frame<<endl;


glBindVertexArray(vao);
glDrawArrays(GL_QUADS,0,4);

glBindVertexArray(0);
glUseProgram(0);
glBindTexture(GL_TEXTURE_2D,0);
}

#endif // PLAYER_H_INCLUDED
