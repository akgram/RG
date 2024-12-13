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
	void DrawCone(double h, double r, int nSeg);
	void DrawGrid(double width, double height, int nSegW, int nSegH);
	void DrawSphere(double r, int nSegAlpha, int nSegBeta);
	void DrawCylinder(double h, double r1, double r2, int nSeg);
	void DrawAxis(double width);
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	void SetAngle(int newAngle);
	void SetDragging(bool v);
	bool GetDragging();

	void SetAngleX(float add);
	bool GetAngleX();

	void SetAngleY(float add);
	bool GetAngleY();

	void SetPoint(CPoint p);
	CPoint GetPoint();


protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	int angle;

	bool isDragging;  //  mis pritisnut?
	CPoint lastMousePos;
	float angleX;  // Horizontalni ugao
	float angleY;  // Vertikalni ugao
	float cameraDist;
};
