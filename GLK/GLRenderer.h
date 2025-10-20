#pragma once

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	void DrawAxes();

	UINT LoadTexture(char* fileName);

	void SetLightingParams();

	void SetLightParams(int glLight);

	void SetMaterial(float diffuse[]);

	void DrawRect(float a, float b, int n);

	void DrawPrism(float a, float b, float c, int n);

	void DrawCylindar(float r, float b, int nR);

	void DrawCamera(float r, float h, int nR, float alfa, float beta);

	void DrawCameras(float r, float h, int nR, float alfa, float beta, int nC);


	double rCam, beta, alfa, cam, cam1;
	UINT slika;

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

};
