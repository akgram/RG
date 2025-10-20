#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	this->slika = 0;
	this->alfa = 1;
	this->beta = 1;
	this->rCam = 100;
	this->cam = 0;
	this->cam1 = 0;
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	slika = LoadTexture("slika.jpg");
	
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double xCam = rCam * sin(beta) * cos(alfa);
	double yCam = rCam * cos(beta);
	double zCam = rCam * sin(beta) * sin(alfa);

	gluLookAt(xCam, yCam, zCam, 0, 0, 0, 0, 1, 0);


	DrawAxes();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	SetLightingParams();

	SetLightParams(GL_LIGHT1);
	SetLightParams(GL_LIGHT2);

	glEnable(GL_CULL_FACE);
	float dif[] = {1, 1, 0, 1};
	SetMaterial(dif);
	DrawPrism(70, 42, 70, 10);
	glDisable(GL_CULL_FACE);

	glTranslated(0, 42 / 2 - 5, 0);
	float dif1[] = { 1, 1, 1, 1 };
	SetMaterial(dif1);
	DrawCameras(1, 5, 40, 110, 0, 4);


	
	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45, (double)w / (double)h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 

	glDeleteTextures(1, &slika);

	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::DrawAxes()
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(00, 50, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 50);
	glEnd();
	glPopMatrix();
}

UINT CGLRenderer::LoadTexture(char* fileName)
{
	UINT texID;
	DImage img;
	img.Load(CString(fileName));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), 
		GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return texID;
}

void CGLRenderer::SetLightingParams()
{
	GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLboolean localViewer = GL_TRUE;
	GLboolean twoSide = GL_TRUE;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, twoSide);

	glEnable(GL_LIGHTING);
}

void CGLRenderer::SetLightParams(int glLight)
{
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position0[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // pozicija OD
	GLfloat light_direction0[] = { 0.0f, 0.0f, -1.0f }; // ka poziciji

	glLightfv(glLight, GL_AMBIENT, light_ambient);
	glLightfv(glLight, GL_DIFFUSE, light_diffuse);
	glLightfv(glLight, GL_SPECULAR, light_specular);
	glLightfv(glLight, GL_POSITION, light_position0);
	glLightfv(glLight, GL_SPOT_DIRECTION, light_direction0);

	glLightf(glLight, GL_SPOT_CUTOFF, 45.0f);      // ugao konusa
	glLightf(glLight, GL_SPOT_EXPONENT, 10.0f);    // koncentracija

	// mala atenuacija (slabljenje sa rastojanjem)
	glLightf(glLight, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(glLight, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(glLight, GL_QUADRATIC_ATTENUATION, 0.0f);

	glEnable(glLight);
}

void CGLRenderer::SetMaterial(float diffuse[])
{
	GLfloat ambient[] = { diffuse[0] * 0.5f, 
				diffuse[1] * 0.5f, diffuse[2] * 0.5f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat shininess = 64.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void CGLRenderer::DrawRect(float a, float b, int n)
{
	glPushMatrix();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			float x = -a / 2 + i * a / n;
			float y = -b / 2 + j * b / n;

			glBegin(GL_QUADS);

			glTexCoord2f((float)i / n, (float)j / n);
			glNormal3f(0, 0, 1);
			glVertex3f(x, y, 0);

			glTexCoord2f((float)(i + 1) / n, (float)j / n);
			glNormal3f(0, 0, 1);
			glVertex3f(x + a / n, y, 0);

			glTexCoord2f((float)(i + 1) / n, (float)(j + 1) / n);
			glNormal3f(0, 0, 1);
			glVertex3f(x + a / n, y + b / n, 0);

			glTexCoord2f((float)i / n, (float)(j + 1) / n);
			glNormal3f(0, 0, 1);
			glVertex3f(x, y + b / n, 0);

			glEnd();
		}
	}

	glPopMatrix();
}

void CGLRenderer::DrawPrism(float a, float b, float c, int n)
{
	glPushMatrix(); // prednja
	glTranslated(0, 0, c / 2);
	glNormal3f(0, 0, 1);
	DrawRect(a, b, n);
	glPopMatrix();

	glPushMatrix(); // zadnja
	glTranslated(0, 0, -c / 2);
	glNormal3f(0, 0, 1);
	DrawRect(a, b, n);
	glPopMatrix();

	glPushMatrix(); // leva
	glTranslated(-a / 2, 0, 0);
	glRotated(90, 0, 1, 0);
	glNormal3f(0, 0, 1);
	DrawRect(c, b, n);
	glPopMatrix();

	glPushMatrix(); // desna
	glTranslated(a / 2, 0, 0);
	glRotated(90, 0, 1, 0);
	glNormal3f(0, 0, 1);
	DrawRect(c, b, n);
	glPopMatrix();

	glPushMatrix(); // gornja
	glTranslated(0, b / 2, 0);
	glRotated(90, 1, 0, 0);
	glNormal3f(0, 0, 1);
	DrawRect(a, c, n);
	glPopMatrix();

	glPushMatrix(); // donja
	glTranslated(0, -b / 2, 0);
	glRotated(90, 1, 0, 0);
	glNormal3f(0, 0, 1);
	DrawRect(a, c, n);
	glPopMatrix();
}

void CGLRenderer::DrawCylindar(float r, float b, int nR)
{
	glPushMatrix();

	double alfa = 2 * 3.14 / nR;

	glBegin(GL_TRIANGLE_FAN); // donja
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= nR; i++)
	{
		double step = alfa * i;
		float x = r * cos(step);
		float z = r * sin(step);

		glVertex3f(x, 0, z);
	}
	glEnd();

	glBegin(GL_QUADS); // omotac cylindar
	for (int i = 0; i < nR; i++)
	{
		//double step = alfa * i;
		float x1 = r * cos(alfa * i);
		float z1 = r * sin(alfa * i);

		float x2 = r * cos(alfa * i);
		float z2 = r * sin(alfa * i);

		float x12 = r * cos(alfa * (i + 1));
		float z12 = r * sin(alfa * (i + 1));

		float x22 = r * cos(alfa * (i + 1));
		float z22 = r * sin(alfa * (i + 1));

		glVertex3f(x1, b, z1);
		glVertex3f(x12, b, z12);
		glVertex3f(x22, 0, z22);
		glVertex3f(x2, 0, z2);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // gornja cylindar
	glVertex3f(0, b, 0);
	for (int i = 0; i <= nR; i++)
	{
		double step = alfa * i;
		float x = r * cos(step);
		float z = r * sin(step);

		glVertex3f(x, b, z);
	}
	glEnd();
	glPopMatrix();
}

void CGLRenderer::DrawCamera(float r, float h, int nR, float alfa, float beta)
{
	glPushMatrix();

	DrawCylindar(r, h, nR);
	glTranslated(0, r, -h / 2);
	glRotated(alfa + cam, 1, 0, 0);
	//glRotated(cam1, 0, 0, 1); // treba da rotira oko svoju tacku 8 * r????
	DrawCylindar(r, h, nR);
	glTranslated(0, h, 0);
	DrawCylindar(2 * r, 0.5 * h, nR);

	glPopMatrix();
}

void CGLRenderer::DrawCameras(float r, float h, int nR, float alfa, float beta, int nC)
{
	glPushMatrix();
	DrawCylindar(12 * r, 0.5 * h, nR);
	glColor3f(1, 0, 0);

	//glTranslated(0, -h / 2, 8 * r);
	for (int i = 0; i < nC; i++)
	{
		glPushMatrix();

		glRotated(360 / nC * i, 0, 1, 0);
		glTranslated(0, -h / 2, 8 * r);
		DrawCamera(r, h, nR, alfa, beta);

		glPopMatrix();
	}

	glPopMatrix();
}
