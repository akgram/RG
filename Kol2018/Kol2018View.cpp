
// Kol2018View.cpp : implementation of the CKol2018View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kol2018.h"
#endif

#include "Kol2018Doc.h"
#include "Kol2018View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKol2018View

IMPLEMENT_DYNCREATE(CKol2018View, CView)

BEGIN_MESSAGE_MAP(CKol2018View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKol2018View construction/destruction

CKol2018View::CKol2018View() noexcept
{
	arm1Rot = 0;
	arm2Rot = 0;
	viljuskaRot = 0;
	bagerTrans = 0;

	bager = new DImage();
	bager->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2018\\bager.png"));

	arm1 = new DImage();
	arm1->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2018\\arm1.png"));

	arm2 = new DImage();
	arm2->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2018\\arm2.png"));

	pozadina = new DImage();
	pozadina->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2018\\pozadina.png"));

	viljuska = GetEnhMetaFile(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2018\\viljuska.emf"));

}

CKol2018View::~CKol2018View()
{
	delete bager;
	delete arm1;
	delete arm2;
	delete pozadina;
	//delete viljuska;

}

BOOL CKol2018View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKol2018View drawing

void CKol2018View::OnDraw(CDC* pDC)
{
	CKol2018Doc* pDoc = GetDocument();
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
	XFORM oldForm;
	memDC->GetWorldTransform(&oldForm);
	//kod
	DrawBackground(memDC);
	DrawExcavator(memDC);

	memDC->SetWorldTransform(&oldForm);
	memDC->SetGraphicsMode(prevMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	pDC->SelectObject(&old);
	delete memDC;
}

void CKol2018View::DrawFork(CDC* memDC)
{
	ENHMETAHEADER header;
	GetEnhMetaFileHeader(viljuska, sizeof(ENHMETAHEADER), &header); //??

	Rotate(memDC, -90 + viljuskaRot, false);
	Scale(memDC, 2.5, 2.5, false);
	Translate(memDC, -14, -20, false);

	Translate(memDC, 15, 13, false);
	memDC->PlayMetaFile(viljuska, 
		CRect(header.rclBounds.left, header.rclBounds.top, header.rclBounds.right, header.rclBounds.bottom)); //??
}

void CKol2018View::DrawExcavator(CDC* memDC)
{
	DrawBody(memDC);
	DrawArm1(memDC);
	DrawArm2(memDC);
	DrawFork(memDC);
}

void CKol2018View::DrawBackground(CDC* pDC)
{
	CRect cli;
	GetClientRect(cli);

	int xPos = (cli.Width() - pozadina->Width()) / 2;

	CRect rect(0, 0, xPos + pozadina->Width(), cli.bottom);

	pozadina->Draw(pDC, rect, cli);
}

void CKol2018View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	BYTE* bytes = pImage->GetDIBBits();
	COLORREF color = RGB(bytes[2], bytes[1], bytes[0]);

	CRect rect(0, 0, pImage->Width(), pImage->Height());
	CRect rect1(0, 0, pImage->Width(), pImage->Height());
	pImage->DrawTransparent(pDC, rect, rect1, color);
}

void CKol2018View::DrawBody(CDC* pDC)
{
	CRect cli;
	GetClientRect(cli);
	Translate(pDC, cli.Width() - 800 + bagerTrans, cli.Height() - 300, false);
	DrawImgTransparent(pDC, bager);
	Translate(pDC, 5, 105, false);
}

void CKol2018View::DrawArm1(CDC* pDC)
{
	Translate(pDC, 58, 61, false);
	Rotate(pDC, -90 + arm1Rot, false);
	Translate(pDC, -58, -61, false);

	DrawImgTransparent(pDC, arm1);

	Translate(pDC, 309, 61, false);
}

void CKol2018View::DrawArm2(CDC* pDC)
{
	//Translate(pDC, 36, 40, false); ne trebaaa aloooo
	Rotate(pDC, -90 + arm2Rot, false);
	Translate(pDC, -36, -40, false);

	DrawImgTransparent(pDC, arm2);

	Translate(pDC, 272, 40, false);
}

void CKol2018View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
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

void CKol2018View::Rotate(CDC* pDC, float angle, bool rightMultiply)
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

void CKol2018View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
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


// CKol2018View printing

BOOL CKol2018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKol2018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKol2018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKol2018View diagnostics

#ifdef _DEBUG
void CKol2018View::AssertValid() const
{
	CView::AssertValid();
}

void CKol2018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKol2018Doc* CKol2018View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKol2018Doc)));
	return (CKol2018Doc*)m_pDocument;
}
#endif //_DEBUG


// CKol2018View message handlers


BOOL CKol2018View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CKol2018View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '1')
	{
		arm1Rot += 10;
		Invalidate();
	}
	else if (nChar == '2')
	{
		arm1Rot -= 10;
		Invalidate();
	}
	else if (nChar == '3')
	{
		arm2Rot += 10;
		Invalidate();
	}
	else if (nChar == '4')
	{
		arm2Rot -= 10;
		Invalidate();
	}
	else if (nChar == '5')
	{
		viljuskaRot += 10;
		Invalidate();
	}
	else if (nChar == '6')
	{
		viljuskaRot -= 10;
		Invalidate();
	}
	else if (nChar == VK_LEFT)
	{
		bagerTrans -= 10;
		Invalidate();
	}
	else if (nChar == VK_RIGHT)
	{
		bagerTrans += 10;
		Invalidate();
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
