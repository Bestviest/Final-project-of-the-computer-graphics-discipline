#include <glut.h>
#include <math.h>
#define pi 4*atan(1)
//créditos Roberto Júnior

GLfloat angle, fAspect, x, z, c = 1;
GLint rox = 30, roy = 0, roz = 0, ang;
static int year = 0, day = 0, wire = 1;
float teta = 0;

void Desenha(void)
{
    // Limpa a janela e o depth buffer (ser realista e dar profundidade) 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    //--------------------------------------------------------------------------------------------------
    glPushMatrix(); //SOL
    glRotatef((GLfloat)day / 10, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); //cor verde
    if (wire == 0) glutSolidSphere(1.0, 25, 25);
    else glutWireSphere(1.0, 25, 25);
    glPopMatrix();
    //--------------------------------------------------------------------------------------------------
    glPushMatrix(); //P1
    glTranslatef(x, 0, z);//raio do Planeta
    glColor3f(1.0, 0.0, 1.0); // cor roxa na lua 
    if (wire == 0) glutSolidSphere(0.3, 25, 25);
    else glutWireSphere(0.3, 25, 25);
    glPopMatrix();
    glutSwapBuffers();
}

//mudar a cor
void Inicializa(void)
{
    GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
    GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };       // "cor"
    GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 }; // "brilho"
    GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

    // Capacidade de brilho do material
    GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
    GLint especMaterial = 60;

    // Especifica que a cor de fundo da janela sera' preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glShadeModel(GL_SMOOTH);// Habilita o modelo de colorizacao de Gouraud ( um método de interpolação usado em computação gráfica para produzir continuous shading de superfícies)
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);// Define a refletancia do material
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);// Define a concentracao do brilho
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);// Ativa o uso da luz ambiente

    // Define os parametros da luz de numero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glEnable(GL_COLOR_MATERIAL);// Habilita a definicao da cor do material a partir da cor corrente
    glEnable(GL_LIGHTING);//Habilita o uso de iluminacao
    glEnable(GL_LIGHT0);// Habilita a luz de numero 0
    glEnable(GL_DEPTH_TEST);// Habilita o depth-buffering

    angle = 25;
}

// Funcao usada para especificar o volume de visualizacao
void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);// Especifica sistema de coordenadas de projecao
    glLoadIdentity();// Inicializa sistema de coordenadas de projecao
    gluPerspective(angle, fAspect, 0.4, 500);// Especifica a projecao perspectiva
    glMatrixMode(GL_MODELVIEW);// Especifica sistema de coordenadas do modelo
    glLoadIdentity();// Inicializa sistema de coordenadas do modelo
    if (rox > 0) gluLookAt(0, rox, 1, 0, 0, 0, 0, 1, 0);
    else gluLookAt(0, 0, rox, 0, 0, 0, 0, 1, 0);
    //gluLookAt(rox,roy,roz, 0,0,0, 0,1,0);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w / (GLfloat)h;
    EspecificaParametrosVisualizacao();
}

void spinDisplay(void)
{
    year = (year + 1);
    day = (day + 2);
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-in
            if (angle >= 10) angle -= 5;
            //glutIdleFunc(spinDisplay);
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-out
            if (angle <= 130) angle += 5;
        }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void GerenciaTEspeciais(int key, int x, int y)
{

    if (key == GLUT_KEY_UP)
    {
        rox += 10; roy = 0; roz = 0;
        ang += 10;
    }
    if (key == GLUT_KEY_DOWN)
    {
        rox -= 10; roy = 0; roz = 0;
        ang -= 10;
    }
    if (key == GLUT_KEY_LEFT)
    {
        rox = 0; roy += 1; roz = 0;
        ang += 10; wire = 0;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        rox = 0; roy -= 1; roz = 0;
        ang -= 10; wire = 1;
    }

    Desenha;
    glutPostRedisplay();
}

void Keyboard_Function(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 65:   // A
    {
        ++rox;
        break;
    }
    case 97:   // a
    {
        --rox;
        break;
    }
    case 83:    // S
    {
        ++roy;
        break;
    }
    case 115:    // s
    {
        --roy;
        break;
    }

    case 68:    //D
    {
        ++roz;
        break;
    }

    case 100:    //d
    {
        --roz;
        break;
    }
    }

    glutPostRedisplay();
}


void Timer(int value)
{

    x = 5 * cos(teta);
    z = 3 * sin(teta);
    //teta = teta*180/pi + 1;
    teta = teta + 0.01;
    //if (teta==2*pi) teta=0;

    spinDisplay();

    EspecificaParametrosVisualizacao();
    Desenha;
    glutPostRedisplay();
    glutTimerFunc(10, Timer, 5);
}

int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 350);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    glutSpecialFunc(GerenciaTEspeciais);
    glutKeyboardFunc(Keyboard_Function);
    glutTimerFunc(500, Timer, 1);
    Inicializa();
    glutMainLoop();
}