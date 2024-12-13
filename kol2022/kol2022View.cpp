
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
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CvezbaView construction/destruction

CvezbaView::CvezbaView() noexcept
{
	arm1Rot = 0;
	arm2Rot = 0;
	headRot = 0;

	base = new DImage();
	base->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\base.png"));

	arm1 = new DImage();
	arm1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\arm1.png"));

	arm2 = new DImage();
	arm2->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\arm2.png"));

	head = new DImage();
	head->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\head.png"));

	pozadina = new DImage();
	pozadina->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\pozadina.jpg"));

	base_shadow = new DImage();
	base_shadow->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\base_shadow.png"));

	arm1_shadow = new DImage();
	arm1_shadow->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\arm1_shadow.png"));

	arm2_shadow = new DImage();
	arm2_shadow->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\arm2_shadow.png"));

	head_shadow = new DImage();
	head_shadow->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2022\\head_shadow.png"));
}

CvezbaView::~CvezbaView()
{
	delete base;
	delete arm1;
	delete arm2;
	delete head;
	delete pozadina;
	delete base_shadow;
	delete arm1_shadow;
	delete arm2_shadow;
	delete head_shadow;
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
	GetClientRect(rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* old = memDC->SelectObject(&bm);

	int prevMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM xForm;
	memDC->GetWorldTransform(&xForm);
	//kod
	DrawBackground(memDC);
	DrawLamp(memDC, true);
	DrawLampShadow(memDC);


	memDC->SetWorldTransform(&xForm);
	memDC->SetGraphicsMode(prevMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	pDC->SelectObject(old);

	delete memDC;
}

void CvezbaView::DrawLamp(CDC* pDC, bool bIsShadow)
{
	DrawLampBase(pDC, bIsShadow);
	DrawLampArm1(pDC, bIsShadow);
	DrawLampArm2(pDC, bIsShadow);
	DrawLampHead(pDC, bIsShadow);
}

void CvezbaView::DrawLampShadow(CDC* pDC)
{
	Translate(pDC, 58, 61, false);
	Scale(pDC, 1.0, 0.25, false);
	//Rotate(pDC, -90, false);
	Translate(pDC, -58, -61, false);

	DrawLamp(pDC, false);
}

void CvezbaView::DrawLampBase(CDC* pDC, bool bIsShadow)
{
	CRect cli;
	GetClientRect(cli);
	Translate(pDC, cli.Width() * 0.5, cli.Height() * 0.7, false);

	if (bIsShadow)
	{
		DrawImgTransparent(pDC, base);
	}
	else
	{
		DrawImgTransparent(pDC, base_shadow);
	}
	Translate(pDC, 121, -40, false);
}

void CvezbaView::DrawLampArm1(CDC* pDC, bool bIsShadow)
{
	Translate(pDC, 58, 61, false);
	Rotate(pDC, -45 + arm1Rot, false);
	Translate(pDC, -58, -61, false);

	if (bIsShadow)
	{
		DrawImgTransparent(pDC, arm1);
	}
	else
	{
		DrawImgTransparent(pDC, arm1_shadow);
	}
	Translate(pDC, 309, 61, false);
}

void CvezbaView::DrawLampArm2(CDC* pDC, bool bIsShadow)
{
	Rotate(pDC, -90 + arm2Rot, false);
	Translate(pDC, -36, -40, false);

	Translate(pDC, 272, 40, false);
}

void CvezbaView::DrawLampHead(CDC* pDC, bool bIsShadow)
{
	XFORM f;
	pDC->GetWorldTransform(&f);
	Rotate(pDC, -180 + headRot, false);
	Translate(pDC, -178, -100, false);

	if (bIsShadow)
	{
		DrawImgTransparent(pDC, head);
	}
	else
	{
		DrawImgTransparent(pDC, head_shadow);
	}
	pDC->SetWorldTransform(&f);

	Translate(pDC, -272, -40, false); // namestili smo trans za head pa smo vratili za arm2
	if (bIsShadow)
	{
		DrawImgTransparent(pDC, arm2);
	}
	else
	{
		DrawImgTransparent(pDC, arm2_shadow);
	}
}

void CvezbaView::DrawBackground(CDC* pDC)
{
	CRect cli;
	GetClientRect(cli);

	int poX = (cli.Width() - pozadina->Width()) / 2;
	int poY = cli.Height() - pozadina->Height();

	CRect rect(0, 0, pozadina->Width(), pozadina->Height());
	CRect rect1(poX, poY, poX + pozadina->Width(), poY + pozadina->Height());

	pozadina->Draw(pDC, rect, rect1);
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

	xForm.eDx = 0.0f;
	xForm.eDy = 0.0f;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CvezbaView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xForm;
	xForm.eM11 = sX;
	xForm.eM12 = 0.0f;
	xForm.eM21 = 0.0f;
	xForm.eM22 = sY;

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


BOOL CvezbaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CvezbaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '1')
	{
		arm1Rot += 10;
	}
	else if (nChar == '2')
	{
		arm1Rot -= 10;
	}
	else if (nChar == '3')
	{
		arm2Rot += 10;
	}
	else if (nChar == '4')
	{
		arm2Rot -= 10;
	}
	else if (nChar == '5')
	{
		headRot += 10;
	}
	else if (nChar == '6')
	{
		headRot -= 10;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
