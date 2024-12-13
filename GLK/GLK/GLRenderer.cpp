#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "GLKView.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	angle = 0;

	isDragging = false;
	angleX = 0.0f;
	angleY = 0.0f;
	cameraDist = 20.0f;
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
	 
	// Boja pozadine
	glClearColor(0.47f, 0.0f, 0.0f, 1.0f);

	// Omogući dubinsko testiranje
	glEnable(GL_DEPTH_TEST);


	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Postavi kameru
	gluLookAt(cameraDist * cos(angleY + 20) * sin(angleX) + 20.0f, 5.0f, cameraDist * sin(angleY) - 2.0f,   // Kamera pozicija
			0.0, 4.0, 0.0,   // Gledna tačka
			0.0, 2.0, 0.0);  // Gore vektor

	// Omogući dubinski test (važan za 3D objekte)
	glEnable(GL_DEPTH_TEST);

	// Postavljanje boje za mrežu (crna) i debljinu linije (1 piksel)
	pDC->SetDCPenColor(RGB(0, 0, 0)); // Crna boja
	pDC->SetBkMode(TRANSPARENT); // Bez pozadinske boje
	pDC->SetROP2(R2_COPYPEN); // Koristi direktno boju penke (bez efekta)

	// 5x5 sa po 5 koraka
	glColor3f(1.0f, 0.6f, 0.0f);
	DrawGrid(5.0, 5.0, 5, 5);

	glColor3f(0.0f, 0.8f, 0.0f);

	DrawCylinder(1.5, 1, 1.2, 8); // saksija 1/2

	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	DrawCylinder(0.7, 1.5, 1.5, 8); // saksija 2/2
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 2.2f, 0.0f);
	//DrawCylinder(1.4, 0.5, 0.5, 8); // prvi cilindar
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // prva kupa
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 4.0f, 0.0f);
	DrawSphere(0.4, 10, 10); // prva sfera
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 4.4f, 0.0f);
	//DrawCylinder(1.4, 0.4, 0.4, 8); // drugi cilindar, sredina
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // druga kupa, sredina
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.8f, 0.0f);
	DrawSphere(0.4, 10, 10);//
	glTranslatef(0.0f, 0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // druga kupa, sredina 2
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.8f, 0.0f);
	DrawSphere(0.4, 10, 10);//
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 4.3f, -0.2f);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	//DrawCylinder(1.4, 0.4, 0.4, 8); // treci cilindar, desni
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // treca kupa, desna
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.8f, 0.0f);
	DrawSphere(0.4, 10, 10);//
	//glTranslatef(0.0f, 1.1f, 0.0f);
	//DrawCone(1.4, 0.4, 20);//
	//glColor3f(0.0f, 0.5f, 0.0f);
	//glTranslatef(0.0f, 1.1f, 0.0f);
	//DrawSphere(0.4, 10, 10);//
	//glTranslatef(0.0f, 1.1f, 0.0f);
	//DrawCone(1.4, 0.4, 20);//
	//glColor3f(0.0f, 0.5f, 0.0f);
	//glTranslatef(0.0f, 1.1f, 0.0f);
	//DrawSphere(0.4, 10, 10);//
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -4.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 4.3f, 0.2f);


	glPushMatrix();
	glRotatef(45.0, 1.0, 0.0, 0.0);
	//DrawCylinder(1.4, 0.4, 0.4, 8); // cetvrti cilindar, levi
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawCone(1.5, 0.5, 8); // cetvrta kupa, leva
	glPopMatrix();

	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.3f, 1.2f);
	DrawSphere(0.4, 10, 10);//

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.4f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.4, 0.4, 20);//
	glPopMatrix();

	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 0.0f, 2.2f);
	DrawSphere(0.4, 10, 10);//
	glTranslatef(0.0f, 0.4f, -2.2f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCylinder(1.4, 0.4, 0.4, 8);
	glTranslatef(0.0f, 1.8f, 0.0f);
	glColor3f(0.5f, 0.75f, 1.0f);
	DrawSphere(0.4, 10, 10);//
	glTranslatef(0.0f, 0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.4, 0.4, 20);//
	glTranslatef(0.0f, 1.8f, 0.0f);
	glColor3f(0.5f, 0.75f, 1.0f);
	DrawSphere(0.4, 10, 10);//


	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 6.5f, -0.3f);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	//DrawCylinder(1.4, 0.4, 0.4, 8); // peti cilindar, desno 2
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // peta kupa, desna 2
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.8f, 0.0f);
	DrawSphere(0.4, 10, 10);//
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glTranslatef(0.0f, 0.4f, 0.0f);
	//DrawCylinder(1.4, 0.4, 0.4, 8); // sesti cilindar, desno 2 nastavak
	//glColor3f(0.0f, 0.5f, 0.0f);
	//glTranslatef(0.0f, 1.8f, 0.0f);
	//DrawSphere(0.4, 10, 10);//
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(0.0f, 6.2f, 0.0f);
	//glRotatef(angle, 1.0f, 0.0f, 0.0f); // ROTATE
	//glTranslatef(0.0f, -6.2f, 0.0f);
	//glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 6.5f, 0.3f);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	//DrawCylinder(1.4, 0.4, 0.4, 8); // sedmi cilindar, levi 2 rotira se
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // sedma kupa, leva 2
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.8f, 0.0f);
	DrawSphere(0.4, 10, 10);//
	glTranslatef(0.0f, 0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCone(1.5, 0.5, 8); // sedma kupa, leva 2 nastavak
	glColor3f(0.5f, 0.75f, 1.0f);
	glTranslatef(0.0f, 1.8f, 0.0f);
	DrawSphere(0.4, 10, 10);//
	//glTranslatef(0.0f, 1.1f, 0.0f);
	//DrawCone(1.4, 0.4, 20);//
	//glColor3f(0.0f, 0.5f, 0.0f);
	//glTranslatef(0.0f, 1.1f, 0.0f);
	//DrawSphere(0.4, 10, 10);//
	glPopMatrix();


	// Iscrtavanje koordinatnih osa dužine 10, crne boje i debljine 3 piksela
	pDC->SetDCPenColor(RGB(0, 0, 0)); // Crna boja za ose
	//pDC->SetLineWidth(3); // Debljina linije 3 piksela
	DrawAxis(10.0);

	// Onemogući dubinski test ako je potrebno
	glDisable(GL_DEPTH_TEST);

	SwapBuffers(pDC->m_hDC);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::SetAngle(int add) { angle += add; }

void CGLRenderer::SetDragging(bool v) { isDragging = v; }

bool CGLRenderer::GetDragging() { return isDragging; }

void CGLRenderer::SetAngleX(float add) { angleX += add; }

bool CGLRenderer::GetAngleX() { return angleX; }

void CGLRenderer::SetAngleY(float add) { angleY += add; }

bool CGLRenderer::GetAngleY() { return angleY; }

void CGLRenderer::SetPoint(CPoint p) { lastMousePos = p; }

CPoint CGLRenderer::GetPoint() { return lastMousePos; }


void CGLRenderer::DrawCone(double h, double r, int nSeg)
{
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	//glTranslatef(0.0f, 0.0f, -h / 2);
	glBegin(GL_POLYGON);
	for (int i = 0; i < nSeg; i++)
	{
		float angle = 2.0f * 3.1415 * i / nSeg;
		float x = r * cos(angle);
		float y = r * sin(angle);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
	glPopMatrix();

	// bocne strane
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	//glTranslatef(0.0f, 0.0f, -h / 2);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= nSeg; i++)
	{
		float angle = 2.0f * 3.1415 * i / nSeg;
		float x = r * cos(angle);
		float y = r * sin(angle);

		// Bočne strane
		glVertex3f(x, y, 0.0f);
		glVertex3f(0.0f, 0.0f, h); // vrh
	}
	glEnd();
	glPopMatrix();
}

void CGLRenderer::DrawGrid(double width, double height, int nSegW, int nSegH) {

	glBegin(GL_LINES);
	for (int i = -nSegW; i <= nSegW; ++i) {
		// horizontalne
		glVertex3d(i, 0.0, -width);
		glVertex3d(i, 0.0, width);
	}

	for (int i = -nSegH; i <= nSegH; ++i) {
		// vertikalne
		glVertex3d(-height, 0.0, i);
		glVertex3d(height, 0.0, i);
	}

	glEnd();
}

void CGLRenderer::DrawSphere(double r, int nSegAlpha, int nSegBeta)
{
	double dAlpha = 3.1415 / nSegAlpha;
	double dBeta = 2 * 3.1415 / nSegBeta;

	for (int i = 0; i < nSegAlpha; ++i)
	{
		double alpha1 = i * dAlpha;
		double alpha2 = (i + 1) * dAlpha;

		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= nSegBeta; ++j)
		{
			double beta = j * dBeta; // trenutni ugao

			// tacka na prvoj paraleli
			double x1 = r * sin(alpha1) * cos(beta);
			double y1 = r * cos(alpha1);
			double z1 = r * sin(alpha1) * sin(beta);
			glVertex3d(x1, y1, z1);

			// tacka na drugoj paraleli
			double x2 = r * sin(alpha2) * cos(beta);
			double y2 = r * cos(alpha2);
			double z2 = r * sin(alpha2) * sin(beta);
			glVertex3d(x2, y2, z2);
		}
		glEnd();
	}
}

void CGLRenderer::DrawCylinder(double h, double r1, double r2, int nSeg)
{
	double angleStep = 2.0 * 3.14159 / nSeg;
	double angle = 0.0;

	glBegin(GL_POLYGON); // donja
	for (int i = 1; i <= nSeg; i++)
	{
		glVertex3d(r1 * cos(angle), 0.0, r1 * sin(angle));
		angle += angleStep;
	}
	glEnd();

	angle = 0.0;
	glBegin(GL_POLYGON); // gornja
	for (int i = 1; i <= nSeg; i++)
	{
		glVertex3d(r2 * cos(angle), h, r2 * sin(angle));
		angle += angleStep;
	}
	glEnd();

	angle = 0.0;
	glBegin(GL_QUAD_STRIP);
	for (int i = 1; i <= nSeg; i++)
	{
		glVertex3d(r1 * cos(angle), 0.0, r1 * sin(angle));

		glVertex3d(r2 * cos(angle), h, r2 * sin(angle));

		angle += angleStep;
	}

	glVertex3d(r1 * cos(0.0), 0.0, r1 * sin(0.0));
	glVertex3d(r2 * cos(0.0), h, r2 * sin(0.0));
	glEnd();
}

void CGLRenderer::DrawAxis(double width) {

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // crvena
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(width, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0); // zelena
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, width, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0); // plava
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, width);
	glEnd();
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	
	glViewport(0, 0, w, h); // Postavi viewport

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / h, 1.0, 100.0); // Perspektivna projekcija

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}
