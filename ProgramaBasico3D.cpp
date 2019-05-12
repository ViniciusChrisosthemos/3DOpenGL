// **********************************************************************
// PUCRS/Escola Politécnica
// COMPUTAÇÃO GRÁFICA
//
// Programa básico para criar aplicacoes 3D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include "gl\glut.h"
    static DWORD last_idle_time;
#else
    #include <sys/time.h>
    static struct timeval last_idle_time;
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

// **********************************************************************
//
// W - A - S - F movimentam o centro de projeÁ„o
//
// I - J - K - L movimentam o target
//
// Seta Cima e Baixo Rotaciona o observador
//
// **********************************************************************
void DrawAxis();
void DrawGround();
void DrawWalls();
void DrawObjects();

GLfloat AspectRatio, AngY=0;
float obsX = 0, obsY = 2, obsZ = -5;
float targetX = 0, targetY = 2, targetZ = 0;
float alfa = 0.1;
float angleObjects = 0;

// **********************************************************************
//  void Move()
//  Movimenta o observador e o target
// **********************************************************************
void Move()
{
    if(GetKeyState('W') & 0x8000)
    {
        obsZ += alfa;
        targetZ += alfa;
    }

    if(GetKeyState('S') & 0x8000)
    {
        obsZ -= alfa;
        targetZ -= alfa;
    }

    if(GetKeyState('A') & 0x8000)
    {
        obsX += alfa;
        targetX += alfa;
    }

    if(GetKeyState('D') & 0x8000)
    {
        obsX -= alfa;
        targetX -= alfa;
    }

    if(GetKeyState('Q') & 0x8000)
    {
        obsY += alfa;
        targetY += alfa;
        if(obsY < 2 || targetY < 2)
        {
            obsY = 2;
            targetY = 2;
        }
    }

    if(GetKeyState('E') & 0x8000)
    {
        obsY -= alfa;
        targetY -= alfa;
        if(obsY < 2 || targetY < 2)
        {
            obsY = 2;
            targetY = 2;
        }
    }

    if(GetKeyState('I') & 0x8000)
    {
        targetY += abs(alfa);
    }

    if(GetKeyState('K') & 0x8000)
    {
        targetY -= abs(alfa);
    }

    if(GetKeyState('J') & 0x8000)
    {
        targetX += alfa;
    }

    if(GetKeyState('L') & 0x8000)
    {
        targetX -= alfa;
    }
}
// **********************************************************************
//  void DrawWalls(void)
//  Desenha 4 paredes ao redor do ponto de origim
// **********************************************************************
void DrawWalls()
{
    float size = 100.0f;
    float distance = 50.0f;
    //Parede frontal
    glPushMatrix();
    {
        glTranslatef(0,0,distance);
        glBegin ( GL_QUADS );
            glNormal3f(0,0,-1);
            glColor3f(0.0f,0.0f,1.0f); //Azul
            glVertex3f(size, size,  0);
            glVertex3f(size, 0,  0);
            glVertex3f(-size, 0,  0);
            glVertex3f(-size, size,  0);
        glEnd();
    }
    glPopMatrix();
    //Parede atraz
    glPushMatrix();
    {
        glRotatef(180,0,1,0);
        glTranslatef(0,0,distance);
        glBegin ( GL_QUADS );
            glNormal3f(0,0,1);
            glColor3f(0.0f,0.0f,1.0f); //Azul
            glVertex3f(size, size, 0);
            glVertex3f(size, 0,  0);
            glVertex3f(-size, 0,  0);
            glVertex3f(-size, size,  0);
        glEnd();
    }
    glPopMatrix();
    //Parede esquerda
    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        glTranslatef(0,0,distance);
        glBegin ( GL_QUADS );
            glNormal3f(1,0,0);
            glColor3f(0.0f,0.0f,0.5f); //Azul
            glVertex3f(size, size, 0);
            glVertex3f(size, 0,  0);
            glVertex3f(-size, 0,  0);
            glVertex3f(-size, size,  0);
        glEnd();
    }
    glPopMatrix();

    //Parede direita
    glPushMatrix();
    {
        glRotatef(-90,0,1,0);
        glTranslatef(0,0,distance);
        glBegin ( GL_QUADS );
            glNormal3f(-1,0,0);
            glColor3f(0.0f,0.0f,0.5f); //Azul
            glVertex3f(size, size, 0);
            glVertex3f(size, 0,  0);
            glVertex3f(-size, 0,  0);
            glVertex3f(-size, size,  0);
        glEnd();
    }
    glPopMatrix();
}
// **********************************************************************
//  void DrawAxis(void)
//  Desenha eixos em vermelho, para facilitar a localizacao
// **********************************************************************
void DrawAxis()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    {
        glVertex3d(-100,0,0);
        glVertex3d(100,0,0);


        glVertex3d(0,-100,0);
        glVertex3d(0,100,0);


        glVertex3d(0,0,-100);
        glVertex3d(0,0,100);
    }
    glEnd();
}
// **********************************************************************
//  void DrawObjects(void)
//  Desenha diversos objetos no espaÁo
// **********************************************************************
void DrawObjects()
{
    //Chaleira
    glPushMatrix();
    {
        glTranslated(10,3,15);
        glColor3f(1.0f,0.0f,0.0f);
        glutWireTeapot(5.0f);
    }
    glPopMatrix();

    //Cubo
    glPushMatrix();
    {
        glTranslated(0,1,15);
        glColor3f(0.0f,0.0f,0.0f);
        glutWireCube(2.0f);
    }
    glPopMatrix();

    //Esfera
    glPushMatrix();
    {
        glTranslated(-20,20,15);
        glRotated(angleObjects,1,1,1);
        angleObjects++;
        glColor3f(1.0f,1.0f,0.0f);
        glutWireSphere(15, 10, 20);
    }
    glPopMatrix();

    //Cone
    glPushMatrix();
    {
        glTranslated(-20,10,-20);
        glColor3f(1.0f,1.0f,0.0f);
        glutWireCone(10, 8, 10, 10);
    }
    glPopMatrix();

    //Torus
    glPushMatrix();
    {
        glTranslated(20,28,-20);
        glRotated(angleObjects,0,0,1);
        glColor3f(1.0f,1.0f,0.0f);
        glutWireTorus(15, 10, 50, 25);
    }
    glPopMatrix();

    //Icosaedro
    glPushMatrix();
    {
        glTranslated(-2,5,-1);
        glColor3f(1.0f,1.0f,0.0f);
        glutWireIcosahedron();
    }
    glPopMatrix();

    //Octaedro
    glPushMatrix();
    {
        glRotated(-90,0,1,0);
        glTranslated(0,10,30);
        glColor3f(1.0f,1.0f,0.0f);
        glutWireTetrahedron();
    }
    glPopMatrix();
}

// **********************************************************************
//  void DefineLuz(void)
// **********************************************************************
void DefineLuz(void)
{
  // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.4, 0.4, 0.4f } ;
  GLfloat LuzDifusa[]   = {0.7, 0.7, 0.7};
  GLfloat LuzEspecular[] = {0.9f, 0.9f, 0.9 };
  GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f };
  GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f};

   // ****************  Fonte de Luz 0

 glEnable ( GL_COLOR_MATERIAL );

   // Habilita o uso de iluminaÁ„o
  glEnable(GL_LIGHTING);

  // Ativa o uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
  // Define os parametros da luz número Zero
  glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
  glEnable(GL_LIGHT0);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentraçãoo do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  glMateriali(GL_FRONT,GL_SHININESS,51);

}


// **********************************************************************
//  void init(void)
//		Inicializa os par‚metros globais de OpenGL
// **********************************************************************
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

	glShadeModel(GL_SMOOTH);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_DEPTH_TEST);
	glEnable ( GL_CULL_FACE );

    // Obtem o tempo inicial
#ifdef WIN32
    last_idle_time = GetTickCount();
#else
    gettimeofday (&last_idle_time, NULL);
#endif

}
// **********************************************************************
//  void PosicUser()
// **********************************************************************
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,AspectRatio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsX, obsY, obsZ,
		      targetX,targetY,targetZ,
			  0.0f,1.0f,0.0f);

}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	AspectRatio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	PosicUser();

}
// **********************************************************************
//  void DesenhaCubo()
// **********************************************************************
void DesenhaCubo()
{
	glBegin ( GL_QUADS );
		// Front Face
		glNormal3f(0,0,1);
		glColor3f(0.0f,0.0f,1.0f); //Azul
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f(0,0,-1);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f(0,1,0);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f(0,-1,0);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f(1,0,0);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1,0,0);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

// **********************************************************************
//  void display( void )
// **********************************************************************
void display( void )
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DefineLuz();


    PosicUser();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glTranslatef ( 1.0f, 0.0f, 0.0f );
        glRotatef(AngY,0,1,0);
		glColor3f(0.5f,0.0f,0.0f); // Vermelho
		DesenhaCubo();
	glPopMatrix();

	Move();

    DrawGround();
    DrawWalls();
    DrawObjects();

	glPushMatrix();
        glTranslatef(0,0.1f,0);
		DrawAxis();
	glPopMatrix();



	glutSwapBuffers();
}

// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
// **********************************************************************
void animate()
{
    static float dt;
    static float AccumTime=0;

#ifdef _WIN32
    DWORD time_now;
    time_now = GetTickCount();
    dt = (float) (time_now - last_idle_time) / 1000.0;
#else
    // Figure out time elapsed since last call to idle function
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
    1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);
#endif
    AccumTime +=dt;
    if (AccumTime >=3) // imprime o FPS a cada 3 segundos
    {
        cout << 1.0/dt << " FPS"<< endl;
        AccumTime = 0;
    }
    //cout << "AccumTime: " << AccumTime << endl;
    // Anima cubos
    // Sa;va o tempo para o próximo ciclo de rendering
    last_idle_time = time_now;

        //if  (GetAsyncKeyState(32) & 0x8000) != 0)
          //  cout << "Espaco Pressionado" << endl;

    // Redesenha
    glutPostRedisplay();
}
// **********************************************************************
//  void DrawGround(void)
//  Desenha o ch„o no espaÁo (em verde)
// **********************************************************************
void DrawGround()
{
    float size = 100.0f;
    glPushMatrix();
    {
        glTranslatef(0,0,50);
        glBegin ( GL_QUADS );
            glNormal3f(0,1,0);
            glColor3f(0.0f,1.0f,0.0f); //Azul
            glVertex3f(-size, 0,  size);
            glVertex3f(size, 0,  size);
            glVertex3f(size, 0,  -size);
            glVertex3f(-size, 0,  -size);
        glEnd();
    }
    glPopMatrix();
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
    case 27:        // Termina o programa qdo
      exit ( 0 );   // a tecla ESC for pressionada
      break;

    default:
            cout << key;
      break;
  }
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{

		case GLUT_KEY_UP:       // When Up Arrow Is Pressed...
			//glutFullScreen ( ); // Go Into Full Screen Mode
			targetZ *= -1;
			obsZ *= -1;
			alfa *= -1;
			break;
	    case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...
			//glutInitWindowSize  ( 700, 500 );
			targetZ *= -1;
			obsZ *= -1;
			alfa *= -1;
			break;
        case GLUT_KEY_LEFT:
			break;
	    case GLUT_KEY_RIGHT:
			break;

		default:
            cout << a_keys << "\n";
			break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main ( int argc, char** argv )
{
	glutInit            ( &argc, argv );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	glutInitWindowPosition (0,0);
	glutInitWindowSize  ( 700, 500 );
	glutCreateWindow    ( "Computacao Grafica - Exemplo Basico 3D" );

	init ();
    //system("pwd");

	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutSpecialFunc ( arrow_keys );
	glutIdleFunc ( animate );

	glutMainLoop ( );
	return 0;
}



