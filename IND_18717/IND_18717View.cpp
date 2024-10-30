
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
	CBrush bgBrush(RGB(0, 255, 255));       // cyan background

	pDC->FillRect(CRect(0, 0, width, height), &bgBrush); // pozadina

	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->Ellipse(0.48 * width, 0.83 * height, 0.52 * width, 0.88 * height);

	CString EMFname = CString("C:\\Users\\krstic\\Desktop\\RG\\cactus_part_light.emf");
	HENHMETAFILE Meta = GetEnhMetaFile(EMFname);

	if (Meta == NULL) {
		AfxMessageBox(_T("Nije moguće učitati WMF fajl."));
		return;
	}

	pDC->PlayMetaFile(Meta, CRect(0.45 * width, 0.7 * height, 0.55 * width, 0.85 * height));
	//pDC->PlayEnhMetaFile(Meta, CRect(0, 0, 800, 600));
	//DeleteMetaFile(Meta);



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

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CIND18717View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{

}

void CIND18717View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{

}

void CIND18717View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{

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
