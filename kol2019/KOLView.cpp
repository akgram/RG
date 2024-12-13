
// KOLView.cpp : implementation of the CKOLView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KOL.h"
#endif

#include "KOLDoc.h"
#include "KOLView.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKOLView

IMPLEMENT_DYNCREATE(CKOLView, CView)

BEGIN_MESSAGE_MAP(CKOLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKOLView construction/destruction

CKOLView::CKOLView() noexcept
{
	// TODO: add construction code here
	arm1rot = 0;
	arm2rot = 0;
	leg1Prvirot = 0;
	leg1Drugirot = 0;
	leg2rot = 0;
	bodyrot = 0;

	body1 = new DImage();
	body1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\body1.png"));

	arm1 = new DImage();
	arm1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\arm1.png"));

	arm2 = new DImage();
	arm2->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\arm2.png"));

	leg1 = new DImage();
	leg1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\leg1.png"));

	leg2 = new DImage();
	leg2->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\leg2.png"));

	back = new DImage();
	back->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2019\\background.jpg"));

}

CKOLView::~CKOLView()
{
	delete body1;
	delete arm1;
	delete arm2;
	delete leg1;
	delete leg2;
	delete back;
}

BOOL CKOLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKOLView drawing

void CKOLView::OnDraw(CDC* pDC)
{
	CKOLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// flicker
	CRect rect;
	GetClientRect(&rect);
	CDC* mem = new CDC();
	mem->CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* old = mem->SelectObject(&bitmap);

	int prevMode = mem->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	mem->GetWorldTransform(&oldForm);
	// tijana gas

	DrawBackground(mem, rect);
	DrawTransformer(mem);

	mem->SetWorldTransform(&oldForm);
	mem->SetGraphicsMode(prevMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), mem, 0, 0, SRCCOPY);
	pDC->SelectObject(&old);

	//mem->DeleteDC();
	delete mem;

	// flicker kraj





}

void CKOLView::DrawBackground(CDC* pDC, CRect rc)
{
	back->Draw(pDC, CRect(0, 0, back->Width(), back->Height()), rc);
}

void CKOLView::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	BYTE* bytes = pImage->GetDIBBits();
	COLORREF color = RGB(bytes[2], bytes[1], bytes[0]);

	CRect rect1 = CRect(0, 0, pImage->Width(), pImage->Height());
	CRect rect2 = CRect(0, 0, pImage->Width(), pImage->Height());
	pImage->DrawTransparent(pDC, rect1, rect2, color);
}

void CKOLView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xForm;
	xForm.eM11 = 1.0f;
	xForm.eM12 = 0.0f;
	xForm.eM21 = 0.0f;
	xForm.eM22 = 1.0f;
	xForm.eDx = dX;
	xForm.eDy = dY;

	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
	}
}

void CKOLView::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xForm;
	float rad = angle * 3.1415f / 180.0f;
	xForm.eM11 = cos(rad);
	xForm.eM12 = sin(rad);
	xForm.eM21 = -sin(rad);
	xForm.eM22 = cos(rad);
	xForm.eDx = 0.0f;
	xForm.eDy = 0.0f;

	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
	}
}

void CKOLView::DrawArm1(CDC* pDC)
{
	Translate(pDC, 34, 31, false);
	Rotate(pDC, arm1rot, false);
	Translate(pDC, -34, -31, false);

	Translate(pDC, 480, 267, true);
	DrawImgTransparent(pDC, arm1);
}

void CKOLView::DrawArm2(CDC* pDC)
{
	Translate(pDC, 23, 61, false);
	Rotate(pDC, 180 + arm2rot, false);
	Translate(pDC, -23, -61, false);

	Translate(pDC, 667, 308, true);
	DrawImgTransparent(pDC, arm2);
}

void CKOLView::DrawLeg1(CDC* pDC)
{
	Translate(pDC, 30, 125, false);
	Rotate(pDC, leg1Prvirot, false);
	Translate(pDC, -30, -125, false);

	Translate(pDC, 90, 219, true);
	DrawImgTransparent(pDC, leg1);
}

void CKOLView::DrawLeg2(CDC* pDC)
{
	Translate(pDC, 35, 60, false);
	Rotate(pDC, leg2rot, false);
	Translate(pDC, -35, -60, false);

	Translate(pDC, 85, 285, true);
	DrawImgTransparent(pDC, leg2);
}

void CKOLView::DrawBody1(CDC* pDC)
{
	Translate(pDC, 26, 133, false);
	Rotate(pDC, bodyrot, false);
	Translate(pDC, -26, -133, false);

	Translate(pDC, 303, 214, true);
	DrawImgTransparent(pDC, body1);
}

void CKOLView::DrawTransformer(CDC* mem)
{
	XFORM oldForm;
	mem->GetWorldTransform(&oldForm);

	DrawBody1(mem);
	mem->SetWorldTransform(&oldForm);
	DrawArm2(mem);
	mem->SetWorldTransform(&oldForm);
	DrawLeg2(mem);
	mem->SetWorldTransform(&oldForm);
	DrawLeg1(mem);
	mem->SetWorldTransform(&oldForm);
	DrawArm1(mem);
	mem->SetWorldTransform(&oldForm);
}


// CKOLView printing

BOOL CKOLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKOLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKOLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKOLView diagnostics

#ifdef _DEBUG
void CKOLView::AssertValid() const
{
	CView::AssertValid();
}

void CKOLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKOLDoc* CKOLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKOLDoc)));
	return (CKOLDoc*)m_pDocument;
}
#endif //_DEBUG


// CKOLView message handlers


BOOL CKOLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CKOLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 'Q')
	{
		arm1rot += 10;
		leg1Prvirot -= 10;
		Invalidate();
	}
	else if (nChar == 'A')
	{
		arm1rot -= 10;
		leg1Drugirot += 10;
		Invalidate();
	}
	else if (nChar == 'T')
	{
		arm2rot += 10;
		Invalidate();
	}
	else if (nChar == 'G')
	{
		arm2rot -= 10;
		Invalidate();
	}
	else if (nChar == 'R')
	{
		leg2rot += 10;
		Invalidate();
	}
	else if (nChar == 'F')
	{
		leg2rot -= 10;
		Invalidate();
	}
	else if (nChar == 'W')
	{
		bodyrot += 10;
		Invalidate();
	}
	else if (nChar == 'S')
	{
		bodyrot -= 10;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
