
// vezbaView.cpp : implementation of the CvezbaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "vezba.h"
#endif

#include "vezbaDoc.h"
#include "vezbaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvezbaView

IMPLEMENT_DYNCREATE(CvezbaView, CView)

BEGIN_MESSAGE_MAP(CvezbaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CvezbaView construction/destruction

CvezbaView::CvezbaView() noexcept
{
	arm1Rot = 0;
	arm2Rot = 0;
	leg1Rot = 0;
	leg2Rot = 0;
	bodyRot = 0;

	body = new DImage();
	body->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\body1.png"));

	arm1 = new DImage();
	arm1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\arm1.png"));

	arm2 = new DImage();
	arm2->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\arm2.png"));

	leg1 = new DImage();
	leg1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\leg1.png"));

	leg2 = new DImage();
	leg2->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\leg2.png"));

	backgr = new DImage();
	backgr->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\background.jpg"));
}

CvezbaView::~CvezbaView()
{
	delete body;
	delete arm1;
	delete arm2;
	delete leg1;
	delete leg2;
	delete backgr;
}

BOOL CvezbaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CvezbaView drawing

void CvezbaView::OnDraw(CDC* pDC)
{
	CvezbaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* old = memDC->SelectObject(&bm);

	int prevMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	memDC->SetWorldTransform(&oldForm);
	//kod
	DrawBackground(memDC, rect);
	DrawTransformer(memDC);

	memDC->GetWorldTransform(&oldForm);
	memDC->SetGraphicsMode(prevMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	pDC->SelectObject(old);

	delete memDC;
}

void CvezbaView::DrawTransformer(CDC* pDC)
{
	int a = pDC->SaveDC();
	DrawLeg2(pDC);
	DrawLeg1(pDC);
	DrawBody1(pDC);
	DrawArm1(pDC);
	DrawArm2(pDC);

	pDC->RestoreDC(a);
}

void CvezbaView::DrawBody1(CDC* pDC)
{
	//Translate(pDC, 26, 133, false);
	Rotate(pDC, bodyRot, false);
	Translate(pDC, -26, -133, false);

	DrawImgTransparent(pDC, body);
}


void CvezbaView::DrawLeg1(CDC* pDC)
{
	Translate(pDC, 30, 125, false);
	Rotate(pDC, leg1Rot, false);
	Translate(pDC, -30, -125, false);

	DrawImgTransparent(pDC, leg1);

	Translate(pDC, 237, 125, false);
}

void CvezbaView::DrawLeg2(CDC* pDC)
{
	CRect cli;
	GetClientRect(cli);
	Translate(pDC, cli.Width() * 0.1, cli.Height() * 0.6, false);

	Translate(pDC, 35, 60, false);
	Rotate(pDC, leg2Rot, false);
	Translate(pDC, -35, -60, false);

	DrawImgTransparent(pDC, leg2);

	Translate(pDC, 6, -64, false);
}

void CvezbaView::DrawArm1(CDC* pDC)
{
	Translate(pDC, 178, 55, false);

	Translate(pDC, 34, 31, false);
	Rotate(pDC, arm1Rot, false);
	Translate(pDC, -34, -31, false);

	//DrawImgTransparent(pDC, arm1); crtamo u arm2

	Translate(pDC, 210, 102, false);
}

void CvezbaView::DrawArm2(CDC* pDC)
{
	//Translate(pDC, 23, 61, false);  ne treba jer ima od arm1
	int a = pDC->SaveDC();
	Rotate(pDC, -180 + arm2Rot, false);
	Translate(pDC, -23, -61, false);

	DrawImgTransparent(pDC, arm2);
	pDC->RestoreDC(a);

	Translate(pDC, -210, -102, false);
	DrawImgTransparent(pDC, arm1);
}


void CvezbaView::DrawBackground(CDC* pDC, CRect rc)
{
	CRect rect(0, 0, backgr->Width(), backgr->Height()); // pozadina

	backgr->Draw(pDC, rect, rc);
}

void CvezbaView::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	BYTE* bytes = pImage->GetDIBBits();
	COLORREF color = RGB(bytes[2], bytes[1], bytes[0]);

	CRect rect(0, 0, pImage->Width(), pImage->Height());
	pImage->DrawTransparent(pDC, rect, rect, color);
}

void CvezbaView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xForm;
	xForm.eM11 = 1.0f;
	xForm.eM12 = 0.0f;
	xForm.eM21 = 0.0f;
	xForm.eM22 = 1.0f;

	xForm.eDx = dX;
	xForm.eDy = dY;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CvezbaView::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xForm;
	float rad = angle * 3.14159f / 180.0;
	xForm.eM11 = cos(rad);
	xForm.eM12 = sin(rad);
	xForm.eM21 = -sin(rad);
	xForm.eM22 = cos(rad);

	xForm.eDx = 0;
	xForm.eDy = 0;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}


// CvezbaView printing

BOOL CvezbaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CvezbaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CvezbaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CvezbaView diagnostics

#ifdef _DEBUG
void CvezbaView::AssertValid() const
{
	CView::AssertValid();
}

void CvezbaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvezbaDoc* CvezbaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvezbaDoc)));
	return (CvezbaDoc*)m_pDocument;
}
#endif //_DEBUG


// CvezbaView message handlers


void CvezbaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q')
	{
		arm1Rot += 6;
		leg1Rot += 10;
	}
	else if (nChar == 'A')
	{
		arm1Rot -= 6;
		leg1Rot -= 10;
	}
	else if (nChar == 'T')
	{
		arm2Rot += 10;
	}
	else if (nChar == 'G')
	{
		arm2Rot -= 10;
	}
	else if (nChar == 'R')
	{
		leg2Rot += 10;
	}
	else if (nChar == 'F')
	{
		leg2Rot -= 10;
	}
	else if (nChar == 'W')
	{
		bodyRot += 10;
	}
	else if (nChar == 'S')
	{
		bodyRot -= 10;
	}
	else if (nChar == VK_LEFT)
	{

	}
	else if (nChar == VK_RIGHT)
	{

	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CvezbaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}
