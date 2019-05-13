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
#include <Camera.h>
#include <Position.h>
#include <Vector3.h>
#define DEG 0.01745329251
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

#define LIMIT_Y = 0.5

void Move();
void DrawScenario();
void DrawRetangle();

GLfloat AspectRatio, AngY=0;
Camera* mainCamera = new Camera(new Position(new Vector3(0,10,0),0.0f));
Position* pos = new Position(new Vector3(0,1,0), 0);
float alfa = 0.01f;
float limit_y = 0.5;

// **********************************************************************
//  void DrawRetangle(float _size) (EM IMPLEMENTACAO)
//  Desenha um retangulo de area=2_size*2_size. PIVO NO CENTRO!!!
// **********************************************************************
void DrawRetangle(float _size)
{
    glBegin(GL_QUADS);
		glVertex3f(-_size, 0,  _size);
		glVertex3f( _size, 0,  _size);
		glVertex3f( _size, 0, -_size);
		glVertex3f(-_size, 0, -_size);
    glEnd();
}

// **********************************************************************
//  void DrawScenario()
//  Desenha todos os objetos presentes no cenario
// **********************************************************************
void DrawScenario()
{
    //Desenha chao
    glPushMatrix();

    glPopMatrix();
}

void MoveCube()
{
    if(GetKeyState('W') & 0x8000)
    {
        pos->coord->z += cos(pos->angle*DEG) * alfa;
        pos->coord->x += sin(pos->angle*DEG) * alfa;
    }

    if(GetKeyState('S') & 0x8000)
    {
        pos->coord->z -= cos(pos->angle*DEG) * alfa;
        pos->coord->x -= sin(pos->angle*DEG) * alfa;
    }

    if(GetKeyState('D') & 0x8000)
    {
        pos->angle -= alfa*15;
    }

    if(GetKeyState('A') & 0x8000)
    {
        pos->angle += alfa*15;
    }
}

// **********************************************************************
//  void Move()
//  Movimenta o observador e o target
// **********************************************************************
void Move()
{
    if(GetKeyState('W') & 0x8000)
    {
        mainCamera->Move(alfa);
    }

    if(GetKeyState('S') & 0x8000)
    {
        mainCamera->Move(alfa);
    }

    if(GetKeyState('A') & 0x8000)
    {
        mainCamera->position->coord->x += alfa;
        mainCamera->target->x += alfa;
    }

    if(GetKeyState('D') & 0x8000)
    {
        mainCamera->position->coord->x -= alfa;
        mainCamera->target->x -= alfa;
    }

    if(GetKeyState('Q') & 0x8000)
    {
        mainCamera->position->coord->y += alfa;
        mainCamera->target->y += alfa;

        if(mainCamera->position->coord->y < limit_y || mainCamera->target->y < limit_y)
        {
            mainCamera->position->coord->y = limit_y;
            mainCamera->target->y = limit_y;
        }
    }

    if(GetKeyState('E') & 0x8000)
    {
        mainCamera->position->coord->y -= alfa;
        mainCamera->target->y -= alfa;

        if(mainCamera->position->coord->y < limit_y || mainCamera->target->y < limit_y)
        {
            mainCamera->position->coord->y = limit_y;
            mainCamera->target->y = limit_y;
        }
    }

    if(GetKeyState('I') & 0x8000)
    {
        mainCamera->target->y += abs(alfa);
    }

    if(GetKeyState('K') & 0x8000)
    {
        mainCamera->target->y -= abs(alfa);
    }

    if(GetKeyState('J') & 0x8000)
    {
        mainCamera->position->angle -= alfa*5;
    }

    if(GetKeyState('L') & 0x8000)
    {
        mainCamera->position->angle += alfa*5;
    }
}

// **********************************************************************
//  void DefineLuz(void)
//
//
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
//
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
//
//
// **********************************************************************
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,AspectRatio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(mainCamera->position->angle,0,1,0);
	gluLookAt(mainCamera->position->coord->x, mainCamera->position->coord->y, mainCamera->position->coord->z,
		      mainCamera->target->x,mainCamera->target->y,mainCamera->target->z,
			  mainCamera->direction->x,mainCamera->direction->y,mainCamera->direction->z);

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
//
//
// **********************************************************************
void DesenhaCubo()
{
	glBegin ( GL_QUADS );
		// Front Face
		glNormal3f(0,0,1);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f(0,0,-1);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f(0,1,0);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f(0,-1,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f(1,0,0);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1,0,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

void DrawExample()
{

}

// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display( void )
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DefineLuz();

	PosicUser();

	//Move();
    MoveCube();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glTranslatef ( pos->coord->x, pos->coord->y, pos->coord->z );
        glRotatef(pos->angle,0,1,0);
		glColor3f(0.5f,0.0f,0.0f); // Vermelho
		DesenhaCubo();
	glPopMatrix();

    /*
	glPushMatrix();
		glTranslatef ( -1.0f, 4.0f, 8.0f );
		glRotatef(AngY,0,1,0);
		glColor3f(0.0f,0.6f,0.0f); // Verde
		DesenhaCubo();
	glPopMatrix();
	*/

	glColor3f(0.0f, 1.0f, 0.0f);
	DrawRetangle(25);


	glutSwapBuffers();
}

// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
//
//
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
        alfa = dt*2;
    }
    //cout << "AccumTime: " << AccumTime << endl;
    // Anima cubos
    AngY += alfa;
    // Sa;va o tempo para o próximo ciclo de rendering
    last_idle_time = time_now;

        //if  (GetAsyncKeyState(32) & 0x8000) != 0)
          //  cout << "Espaco Pressionado" << endl;

    // Redesenha
    glutPostRedisplay();
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
      /*
    case 'w':
        mainCamera->Move(alfa);
        cout << mainCamera->position->coord->x << " " << mainCamera->position->coord->y << " " << mainCamera->position->coord->z << "\n";
        break;
    case 's':
        mainCamera->Move(-alfa);
        cout << mainCamera->position->coord->x << " " << mainCamera->position->coord->y << " " << mainCamera->position->coord->z << "\n";
        break;

    case 'i':
        mainCamera->target->y += abs(alfa);
        break;
    case 'k':
        mainCamera->target->y -= abs(alfa);
        break;
    case 'j':
        mainCamera->position->angle -= alfa*5;
        break;
    case 'l':
        mainCamera->position->angle += alfa*5;
        break;
        */
    case 'i':
        mainCamera->target->y += abs(alfa);
        break;
    case 'k':
        mainCamera->target->y -= abs(alfa);
        break;
    default:
            cout << key;
      break;
  }

    cout << "Angle = " << mainCamera->position->angle << "\n";
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
			glutFullScreen ( ); // Go Into Full Screen Mode
			break;
	    case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...
			glutInitWindowSize  ( 700, 500 );
			break;
		default:
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


