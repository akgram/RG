
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

	int radius = 0.07 * width; // poluprecnik

	CPen pen(PS_SOLID, 5, RGB(255, 255, 0));  // Cyan boja za konture
	CBrush orangeBrush(RGB(255, 165, 0));     // orange
	CBrush purpleBrush(RGB(128, 0, 128));     // purple
	CBrush pinkBrush(RGB(255, 182, 193));     // pink
	CBrush bgBrush(RGB(192, 192, 192));       // gray background
	CBrush red(RGB(255, 0, 0));				  // red
	CBrush yellow(RGB(255, 255, 0));          // yellow
	CBrush green(RGB(0, 255, 0));			  // green

	CBrush hatchBrush(HS_DIAGCROSS , RGB(0, 0, 255)); // sara sa kosim linijama

	pDC->FillRect(CRect(0, 0, width, height), &bgBrush); // pozadina

	CPen* pOldPen = pDC->SelectObject(&pen);

	// Crtanje gornjeg dela
	pDC->SelectObject(&orangeBrush);
	CPoint leftHalf[3] = { {int(0.5 * width), int(0.35 * height)}, {int(0.5 * width), int(0.54 * height)}, {int(0.7 * width), int(0.35 * height)} };
	pDC->Polygon(leftHalf, 3);

	// Crtanje donjeg dela
	pDC->SelectObject(&pinkBrush);
	CPoint top[3] = { {int(0.7 * width), int(0.54 * height)}, {int(0.3 * width), int(0.95 * height)}, {int(0.7 * width), int(0.95 * height)} };
	pDC->Polygon(top, 3);

	pDC->SelectObject(&yellow);
	CPoint right[3] = { {int(0.3 * width), int(0.54 * height)}, {int(0.5 * width), int(0.54 * height)}, {int(0.5 * width), int(0.75 * height)} };
	pDC->Polygon(right, 3);

	pDC->SelectObject(&purpleBrush);
	RECT rectangle1 = { int(0.3 * width), int(0.35 * height), int(0.5 * width), int(0.54 * height) };
	pDC->Rectangle(&rectangle1);

	pDC->SelectObject(&red);
	CPoint left[3] = { {int(0.5 * width) , int(0.05 * height)}, {int(0.2 * width), int(0.35 * height)}, {int(0.8 * width), int(0.35 * height)} };
	pDC->Polygon(left, 3);

	pDC->SelectObject(&green);
	CPoint rect[4] = { {int(0.7 * width), int(0.35 * height)}, {int(0.5 * width), int(0.54 * height)}, {int(0.5 * width), int(0.75 * height)}, {int(0.7 * width), int(0.54 * height)} };
	pDC->Polygon(rect, 4);

	pDC->SelectObject(&hatchBrush);
	CPoint shrafura[3] = { {int(0.3 * width), int(0.54 * height)}, {int(0.5 * width), int(0.75 * height)}, {int(0.3 * width), int(0.95 * height)} };
	pDC->Polygon(shrafura, 3);

	//int Mx = (int(0.55 * width)) / 2;
	//int My = (int(0.55 * height)) / 2;

	//int Mx_norm = (Mx + int(0.5 * width)) / 2;
	//int My_norm = (My + int(0.5 * height)) / 2;


	//Mnogouglovi
	CPen pen1(PS_SOLID, 3, RGB(255, 255, 0));
	pDC->SelectObject(&pen1);
	pDC->SelectStockObject(NULL_BRUSH);
	DrawRegularPolygon(pDC, 0.38 * width, 0.75 * height, radius * 0.6, 6, 0); // srafura
	DrawRegularPolygon(pDC, 0.58 * width, 0.82 * height, radius, 4, 0); // pink
	//DrawRegularPolygon(pDC, 0.5 * width, 0.125 * height * 5, radius * 0.71, 7, 0); // pink
	DrawRegularPolygon(pDC, 0.50 * width, 0.22 * height, radius * 0.8, 5, 0); // red
	DrawRegularPolygon(pDC, 0.56 * width, 0.4 * height, radius * 0.4, 8, 0); // orange

	// Crtanje mreže (grid)
	CPen pen2(TRANSPARENT, 2, RGB(220, 220, 220));
	pDC->SelectObject(&pen2);
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

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CIND18717View::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle)
{
	if (n < 3) return;

	CPoint* points = new CPoint[n];

	float angleStep = 2 * 3.14159265359f / n; // ugao izmedju susednih temena
	for (int i = 0; i < n; ++i)
	{
		float angle = i * angleStep + rotAngle; // trenutni ugao uz rotaciju
		points[i].x = cx + r * cos(angle);
		points[i].y = cy + r * sin(angle);
	}

	pDC->Polygon(points, n);
	delete[] points;
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
