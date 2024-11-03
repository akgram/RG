
// IND_18717View.cpp : implementation of the CIND18717View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IND_18717.h"
#endif

#include "IND_18717Doc.h"
#include "IND_18717View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIND18717View

IMPLEMENT_DYNCREATE(CIND18717View, CView)

BEGIN_MESSAGE_MAP(CIND18717View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CIND18717View construction/destruction

CIND18717View::CIND18717View() noexcept
{
	// TODO: add construction code here
	// Inicijalizacija u CIND18717View konstruktoru
	rotationAngle = 0;
	rotationAngle1 = 0;


}

CIND18717View::~CIND18717View()
{
}

BOOL CIND18717View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIND18717View drawing



void CIND18717View::OnDraw(CDC* pDC)
{
	CIND18717Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int width = 500;
	int height = 500;

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));  // black boja za konture
	CBrush bgBrush(RGB(0, 255, 255));       // cyan background
	CBrush green(RGB(0, 200, 0));       // green
	CBrush brown(RGB(210, 105, 30));       // brown

	pDC->FillRect(CRect(0, 0, width, height), &bgBrush); // pozadina

	CPen* pOldPen = pDC->SelectObject(&pen);


	CString EMFname = CString("C:\\Users\\krstic\\Desktop\\RG\\cactus_part_light.emf");
	HENHMETAFILE Meta = GetEnhMetaFile(EMFname);

	CString EMFname2 = CString("C:\\Users\\krstic\\Desktop\\RG\\cactus_part.emf");
	HENHMETAFILE Meta2 = GetEnhMetaFile(EMFname2);

	if (Meta == NULL && Meta2 == NULL) {
		AfxMessageBox(_T("Nije moguće učitati EMF fajl."));
		return;
	}

	int prevMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM xFormOld;
	bool b = pDC->GetWorldTransform(&xFormOld);

	//Translate(pDC, 0.5 * width, 0.85 * height, false);
	//Rotate(pDC, rotationAngle1, false); // Rotacija SVE
	//Translate(pDC, -0.5 * width, -0.775 * height, false);
	//Translate(pDC, 0.5 * width, 0.775 * height, false);
	//pDC->PlayMetaFile(Meta, CRect(-0.065 * width, -0.075 * height, 0.065 * width, 0.075 * height));
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta, CRect(0.435 * width, 0.7 * height, 0.565 * width, 0.85 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.55 * width, -0.65 * height, true); // crtanje
	Rotate(pDC, 45, true);
	Translate(pDC, 0.55 * width, 0.65 * height, true);
	//////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.525 * width, 0.57 * height, 0.575 * width, 0.73 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.45 * width, -0.65 * height, true); // crtanje
	Rotate(pDC, -45, true);
	Translate(pDC, 0.45 * width, 0.65 * height, true);
	/////////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.425 * width, 0.57 * height, 0.475 * width, 0.73 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.325 * width, -0.6 * height, true); // crtanje
	Rotate(pDC, 90, true);
	Translate(pDC, 0.32 * width, 0.595 * height, true);
	////////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.285 * width, 0.525 * height, 0.365 * width, 0.675 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.325 * width, -0.6 * height, true); // cratnje
	Rotate(pDC, 90, true);
	Translate(pDC, 0.68 * width, 0.595 * height, true);
	////////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.285 * width, 0.525 * height, 0.365 * width, 0.675 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.55 * width, -0.65 * height, true); // crtanje
	Rotate(pDC, 45, true);
	Translate(pDC, 0.798 * width, 0.551 * height, true);
	//////////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.51 * width, 0.56 * height, 0.59 * width, 0.71 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.55 * width, -0.65 * height, true); // crtanje
	Rotate(pDC, -45, true);
	Translate(pDC, 0.82 * width, 0.66 * height, true);
	//////////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.51 * width, 0.56 * height, 0.59 * width, 0.71 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.605 * width, -0.595 * height, true);
	Rotate(pDC, rotationAngle, true); // Rotacija sa dinamičkim uglom
	Translate(pDC, 0.605 * width, 0.595 * height, true);
	///////////////
	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta, CRect(0.565 * width, 0.445 * height, 0.645 * width, 0.595 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.475 * width, 0.55 * height, 0.525 * width, 0.7 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.355 * width, 0.445 * height, 0.435 * width, 0.595 * height));

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->PlayMetaFile(Meta2, CRect(0.335 * width, 0.295 * height, 0.455 * width, 0.445 * height));


	// krugovi
	pDC->SelectObject(&green);
	pDC->Ellipse(0.48 * width, 0.83 * height, 0.52 * width, 0.87 * height);

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->Ellipse(0.48 * width, 0.68 * height, 0.52 * width, 0.72 * height);

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->Ellipse(0.375 * width, 0.575 * height, 0.415 * width, 0.615 * height);

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->Ellipse(0.585 * width, 0.575 * height, 0.625 * width, 0.615 * height);

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	pDC->Ellipse(0.375 * width, 0.425 * height, 0.415 * width, 0.465 * height);

	b = pDC->SetWorldTransform(&xFormOld);

	Translate(pDC, -0.5 * width, -0.85 * height, true);
	Rotate(pDC, rotationAngle1, true); // Rotacija SVE
	Translate(pDC, 0.5 * width, 0.85 * height, true);
	//Scale(pDC, 1.3, 1.3, true);
	pDC->Ellipse(0.735 * width, 0.575 * height, 0.775 * width, 0.615 * height);

	b = pDC->SetWorldTransform(&xFormOld);
	pDC->SetGraphicsMode(prevMode);

	pDC->SelectObject(&brown);
	pDC->Rectangle(0.38 * width, 0.855 * height, 0.62 * width, 0.9 * height);
	CPoint cup[4] = { CPoint(0.4 * width, 0.9 * height), CPoint(0.6 * width, 0.9 * height), CPoint(0.58 * width, height), CPoint(0.42 * width, height) };
	pDC->Polygon(cup, 4);



	// Crtanje mreže (grid)
	CPen grids(TRANSPARENT, 2, RGB(240, 240, 240));
	pDC->SelectObject(&grids);
	if (showGrid) // showGrid je bool koji kontroliše da li se mreža iscrtava
	{
		int gridSpacing = 0.05 * width; // Razmak između linija mreže
		for (int x = 0; x <= width; x += gridSpacing)
			pDC->MoveTo(x, 0), pDC->LineTo(x, height);
		for (int y = 0; y <= height; y += gridSpacing)
			pDC->MoveTo(0, y), pDC->LineTo(width, y);
	}
}

void CIND18717View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q') // na Q ukljuci/iskljuci
	{
		showGrid = !showGrid;
		Invalidate();         // refresh
	}

	else if (nChar == 'R') // Na "r" rotiraj za 10 stepeni JEDAN
	{
		rotationAngle += 10; // Povećaj ugao rotacije za 10 stepeni
		Invalidate(); // refresh
	}

	else if (nChar == 'M') // Na "R" rotiraj za 10 stepeni SVE
	{
		rotationAngle1 += 10; // Povećaj ugao rotacije za 10 stepeni
		Invalidate(); // refresh
	}

	else if (nChar == 'L') // Na "l" rotiraj za -10 stepeni JEDAN
	{
		rotationAngle -= 10;
		Invalidate();
	}

	else if (nChar == 'N') // Na "L" rotiraj za 10 stepeni SVE
	{
		rotationAngle1 -= 10;
		Invalidate();
	}

	// Pozovi osnovnu klasu da obradi ostale tastere
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CIND18717View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xForm;
	xForm.eM11 = 1.0f; 
	xForm.eM12 = 0.0f;
	xForm.eM21 = 0.0f; 
	xForm.eM22 = 1.0f;
	xForm.eDx = dX;    
	xForm.eDy = dY;

	if (rightMultiply) {
		// Desno množenje (T * M)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	}
	else {
		// Levo množenje (M * T)
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
	}
}

void CIND18717View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xForm;
	xForm.eM11 = sX;   
	xForm.eM12 = 0.0f;
	xForm.eM21 = 0.0f; 
	xForm.eM22 = sY;
	xForm.eDx = 0.0f;  
	xForm.eDy = 0.0f;

	if (rightMultiply) {
		// Desno množenje (S * M)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	}
	else {
		// Levo množenje (M * S)
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
	}
}

void CIND18717View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xForm;
	float radians = angle * 3.14159f / 180.0f; // Konverzija stepeni u radijane
	xForm.eM11 = cos(radians);
	xForm.eM12 = sin(radians);
	xForm.eM21 = -sin(radians);
	xForm.eM22 = cos(radians);
	xForm.eDx = 0.0f;
	xForm.eDy = 0.0f;

	if (rightMultiply) {
		// Desno množenje (R * M)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	}
	else {
		// Levo množenje (M * R)
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
	}
}



// CIND18717View printing

BOOL CIND18717View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIND18717View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIND18717View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIND18717View diagnostics

#ifdef _DEBUG
void CIND18717View::AssertValid() const
{
	CView::AssertValid();
}

void CIND18717View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIND18717Doc* CIND18717View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIND18717Doc)));
	return (CIND18717Doc*)m_pDocument;
}
#endif //_DEBUG


// CIND18717View message handlers
