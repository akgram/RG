
// GLKView.cpp : implementation of the CGLKView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GLK.h"
#endif

#include "GLKDoc.h"
#include "GLKView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLKView

IMPLEMENT_DYNCREATE(CGLKView, CView)

BEGIN_MESSAGE_MAP(CGLKView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGLKView construction/destruction

CGLKView::CGLKView()
{
}

CGLKView::~CGLKView()
{
}

BOOL CGLKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGLKView drawing

void CGLKView::OnDraw(CDC* pDC)
{
	CGLKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// CGLKView printing

BOOL CGLKView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLKView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLKView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGLKView diagnostics

#ifdef _DEBUG
void CGLKView::AssertValid() const
{
	CView::AssertValid();
}

void CGLKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLKDoc* CGLKView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLKDoc)));
	return (CGLKDoc*)m_pDocument;
}
#endif //_DEBUG


// CGLKView message handlers


int CGLKView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CGLKView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CGLKView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);	
}


BOOL CGLKView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CGLKView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void CGLKView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_glRenderer.SetDragging(true);
	m_glRenderer.SetPoint(point);
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CGLKView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_glRenderer.SetDragging(false);
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


void CGLKView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_glRenderer.GetDragging()) {
		// Pomeranje miša po X i Y osi
		float deltaX = point.x - m_glRenderer.GetPoint().x;
		float deltaY = point.y - m_glRenderer.GetPoint().y;

		// Povećanje ili smanjenje ugla na osnovu promene pozicije miša
		m_glRenderer.SetAngleX(deltaX * 0.5f);  // Osetljivost 0.1
		m_glRenderer.SetAngleY(deltaY * 0.5f);  // Osetljivost 0.1

		// Ograničavanje vertikalnog ugla (da se ne okrene kamera previše)
		if (m_glRenderer.GetAngleX() > 360.0f) m_glRenderer.SetAngleX(-360.0f);
		if (m_glRenderer.GetAngleX() < -360.0f) m_glRenderer.SetAngleX(360.0f);
		if (m_glRenderer.GetAngleY() > 360.0f) m_glRenderer.SetAngleX(-360.0f);
		if (m_glRenderer.GetAngleY() < -360.0f) m_glRenderer.SetAngleX(360.0f);

		Invalidate();
	}
	m_glRenderer.SetPoint(point);

	CView::OnMouseMove(nFlags, point);
}


void CGLKView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q')
	{
		m_glRenderer.SetAngle(10);
	}
	else if (nChar == 'W')
	{
		m_glRenderer.SetAngle(-10);
	}
	else if (nChar == VK_LEFT)
	{
		m_glRenderer.SetAngleX(0.2f);
		m_glRenderer.SetAngleY(0.2f);
	}
	else if (nChar == VK_RIGHT)
	{
		m_glRenderer.SetAngleX(-0.2f);
		m_glRenderer.SetAngleY(-0.2f);
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
