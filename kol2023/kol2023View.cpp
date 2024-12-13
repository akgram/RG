
// kol2023View.cpp : implementation of the Ckol2023View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kol2023.h"
#endif

#include "kol2023Doc.h"
#include "kol2023View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ckol2023View

IMPLEMENT_DYNCREATE(Ckol2023View, CView)

BEGIN_MESSAGE_MAP(Ckol2023View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Ckol2023View construction/destruction

Ckol2023View::Ckol2023View() noexcept
{
	nadlakticaRot = 0;
	podlakticaRot = 0;
	sakaRot = 0;
	ceoRot = 0;
	ceoScale = 1.0f;


	glava = new DImage();
	glava->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\glava.png"));

	nadkolenica = new DImage();
	nadkolenica->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\nadkolenica.png"));

	nadlaktica = new DImage();
	nadlaktica->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\nadlaktica.png"));

	podkolenica = new DImage();
	podkolenica->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\podkolenica.png"));

	podlaktica = new DImage();
	podlaktica->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\podlaktica.png"));

	saka = new DImage();
	saka->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\saka.png"));

	stopalo = new DImage();
	stopalo->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\stopalo.png"));

	telo = new DImage();
	telo->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\telo.png"));

	pozadina = new DImage();
	pozadina->Load(CString("C:\\Users\\krstic\\Desktop\\RG\\rgKol2023\\pozadina.jpg"));

}

Ckol2023View::~Ckol2023View()
{
	delete glava;
	delete nadkolenica;
	delete nadlaktica;
	delete podkolenica;
	delete podlaktica;
	delete saka;
	delete stopalo;
	delete telo;
	delete pozadina;
}

BOOL Ckol2023View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ckol2023View drawing

void Ckol2023View::OnDraw(CDC* pDC)
{
	Ckol2023Doc* pDoc = GetDocument();
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
	memDC->GetWorldTransform(&oldForm);
	//kod
	DrawBackground(memDC);
	DrawRobot(memDC);

	memDC->SetWorldTransform(&oldForm);
	memDC->SetGraphicsMode(prevMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	pDC->SelectObject(old);

	delete memDC;
}

void Ckol2023View::DrawBackground(CDC* pDC)
{
	CRect cli;
	GetClientRect(&cli);

	CRect rect(0, 0, pozadina->Width(), pozadina->Height());

	pozadina->Draw(pDC, rect, rect);
}

void Ckol2023View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	BYTE* bytes = pImage->GetDIBBits();
	COLORREF color = RGB(bytes[2], bytes[1], bytes[0]);

	CRect rect1(0, 0, pImage->Width(), pImage->Height());
	CRect rect2(0, 0, pImage->Width(), pImage->Height());
	pImage->DrawTransparent(pDC, rect1, rect2, color);
}

void Ckol2023View::DrawHalf(CDC* pDC)
{

	Translate(pDC, pozadina->Width() / 2, 0, false);
	Translate(pDC, -106, 170, false);
	DrawImgTransparent(pDC, telo);
	int a = pDC->SaveDC();

	Translate(pDC, 61 - 29, 262 - 20, false);
	DrawImgTransparent(pDC, nadkolenica);

	Translate(pDC, 30 - 25, 184 - 37, false); // oduzima se jer ne rotira
	DrawImgTransparent(pDC, podkolenica);

	Translate(pDC, 25 - 20, 248 - 16, false); // oduzima se jer ne rotira
	DrawImgTransparent(pDC, stopalo);

	pDC->RestoreDC(a);
	int bezRotacije = pDC->SaveDC();
	Translate(pDC, 25, 65, false);

	Rotate(pDC, nadlakticaRot, false);
	Translate(pDC, -35, -35, false);
	DrawImgTransparent(pDC, nadlaktica);

	Translate(pDC, 22, 167, false);

	Rotate(pDC, podlakticaRot, false);
	Translate(pDC, -30, -33, false);
	DrawImgTransparent(pDC, podlaktica);

	Translate(pDC, 30, 140, false);

	Rotate(pDC, sakaRot, false);
	Translate(pDC, -25, -3, false);
	DrawImgTransparent(pDC, saka);
	pDC->RestoreDC(bezRotacije);
}

void Ckol2023View::DrawHead(CDC* pDC)
{
	int bezHead = pDC->SaveDC();
	Translate(pDC, 60, -99, false);
	DrawImgTransparent(pDC, glava);
	pDC->RestoreDC(bezHead);
}

void Ckol2023View::DrawRobot(CDC* memDC)
{
	Translate(memDC, pozadina->Width() / 2, pozadina->Height() / 2, false);
	Rotate(memDC, ceoRot, false);
	Scale(memDC, ceoScale, ceoScale, false);
	Translate(memDC, -pozadina->Width() / 2, -pozadina->Height() / 2, false);

	DrawHalf(memDC);
	DrawHead(memDC);

	Translate(memDC, pozadina->Width() / 2, 0, false);
	Translate(memDC, 106, -170, false);
	Scale(memDC, -1, 1, false);
	DrawHalf(memDC);
}

void Ckol2023View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
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

void Ckol2023View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xForm;
	float rad = angle * 3.1415f / 180.0;
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

void Ckol2023View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xForm;
	xForm.eM11 = sX;
	xForm.eM12 = 0.0f;
	xForm.eM21 = 0.0f;
	xForm.eM22 = sY;

	xForm.eDx = 0.0f;
	xForm.eDy = 0.0f;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&xForm, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}


// Ckol2023View printing

BOOL Ckol2023View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ckol2023View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ckol2023View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ckol2023View diagnostics

#ifdef _DEBUG
void Ckol2023View::AssertValid() const
{
	CView::AssertValid();
}

void Ckol2023View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ckol2023Doc* Ckol2023View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ckol2023Doc)));
	return (Ckol2023Doc*)m_pDocument;
}
#endif //_DEBUG


// Ckol2023View message handlers


BOOL Ckol2023View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void Ckol2023View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'A' && sakaRot < 30)
	{
		sakaRot += 10;
		Invalidate();
	}
	else if (nChar == 'S' && sakaRot > -10)
	{
		sakaRot -= 10;
		Invalidate();
	}
	else if (nChar == 'D' && podlakticaRot < 80)
	{
		podlakticaRot += 10;
		Invalidate();
	}
	else if (nChar == 'F' && podlakticaRot > -10)
	{
		podlakticaRot -= 10;
		Invalidate();
	}
	else if (nChar == 'G' && nadlakticaRot < 90)
	{
		nadlakticaRot += 10;
		Invalidate();
	}
	else if (nChar == 'H' && nadlakticaRot > -10)
	{
		nadlakticaRot -= 10;
		Invalidate();
	}
	else if (nChar == '1' && ceoScale < 1.5f)
	{
		ceoRot += 10;
		ceoScale += 0.1f;
		Invalidate();
	}
	else if (nChar == '2' && ceoScale > 0.1f)
	{
		ceoRot -= 10;
		ceoScale -= 0.1f;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
