
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
#include "../DImage/DImage.h"


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
	//bmpImage.Load(L"C:\\Users\\krstic\\Desktop\\RG\\bitmap_lab3\\download.bmp");


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


void CIND18717View::Photo(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	transDeo(pDC, -centerX, centerY - 143, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img1.dib"), 166);
	transDeo(pDC, -centerX + 6, centerY - 7.5, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img2.dib"), 14);
	transDeo(pDC, -centerX + 150, centerY + 157, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img3.dib"), 156);
	transDeo(pDC, -centerX - 141, centerY + 149, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img4.dib"), 60);
	transDeo(pDC, -centerX - 150, centerY + 8, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img5.dib"), 169.5);
	transDeo(pDC, -centerX + 158, centerY - 148, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img6.dib"), 87);
	transDeo(pDC, -centerX - 7, centerY + 149, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img7.dib"), -102.5); // CRVENA
	transDeo(pDC, -centerX - 156, centerY - 148, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img8.dib"), -135);
	transDeo(pDC, -centerX + 158, centerY + 2, CString(L"C:\\Users\\krstic\\Desktop\\RG\\dib_zad\\img9.dib"), 82);
}


void CIND18717View::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC* MemDC = new CDC();
	MemDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	MemDC->SelectObject(&bmp);
	CBrush brush(RGB(255, 255, 255));
	CBrush* pOldBrush = MemDC->SelectObject(&brush);
	MemDC->Rectangle(0, 0, rect.Width(), rect.Height());

	Grid(MemDC, width, height, showGrid);

	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	MemDC->SetGraphicsMode(GM_ADVANCED);

	XFORM old;
	MemDC->GetWorldTransform(&old);
	//AntiFlicker(pDC);
	Photo(MemDC);
	MemDC->SetWorldTransform(&old);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), MemDC, 0, 0, SRCCOPY);
	MemDC->DeleteDC();
	delete MemDC;
}

CPoint CIND18717View::drawDeo(int x, int y, CString nameOfFile, CDC* pDC) {
	DImage* slika = new DImage();
	slika->Load(nameOfFile);

	CBitmap* bmpSlika = slika->m_pBmp;
	CBitmap bmpMask;
	BITMAP bm;

	bmpSlika->GetBitmap(&bm);
	bmpMask.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	CDC* SrcDC = new CDC();
	SrcDC->CreateCompatibleDC(pDC);
	CDC* DstDC = new CDC();
	DstDC->CreateCompatibleDC(pDC);

	CBitmap* pOldSrcBmp = SrcDC->SelectObject(bmpSlika);
	CBitmap* pOldDstBmp = DstDC->SelectObject(&bmpMask);

	COLORREF clrTopLeft = SrcDC->GetPixel(0, 0);
	COLORREF clrSaveBk = SrcDC->SetBkColor(clrTopLeft);
	DstDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, SrcDC, 0, 0, SRCCOPY); // copy sve iz scrDC u dstDC

	// Ako je ime fajla d6.bmp, primeni plavi filter
	if (nameOfFile.Find(L"img7.dib") != -1) {
		BITMAP bmBlue;
		bmpSlika->GetBitmap(&bmBlue);
		Red(bmpSlika, bmBlue);
	}
	Gray(bmpSlika, bm);

	COLORREF clrSaveDstText = SrcDC->SetTextColor(RGB(255, 255, 255));
	SrcDC->SetBkColor(RGB(0, 0, 0));
	SrcDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, DstDC, 0, 0, SRCAND); // vraca iz dstDC u srcDC ali sa AND i pravi transparent


	pDC->BitBlt(-bm.bmWidth / 2, -bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, DstDC, 0, 0, SRCAND);
	pDC->BitBlt(-bm.bmWidth / 2, -bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, SrcDC, 0, 0, SRCPAINT);

	SrcDC->DeleteDC();
	delete SrcDC;
	DstDC->DeleteDC();
	delete DstDC;

	return{ bm.bmWidth, bm.bmHeight };
}

void CIND18717View::transDeo(CDC* pDC, int x, int y, CString fileName, double alpha) {
	this->Mirror(pDC, true, false, true);
	this->Scale(pDC, 0, 0, true);
	this->Translate(pDC, x, y, false);
	this->Rotate(pDC, alpha, false);
	CString nameOfFile1(fileName);
	CPoint imageWidthHeight1 = drawDeo(0, 0, nameOfFile1, pDC);

	XFORM Xform;
	ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_IDENTITY);
}

void CIND18717View::Grid(CDC* pDC, int width, int height, bool showGrid)
{
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

		CRect rect;
		GetClientRect(&rect);
		InvalidateRect(&rect);

	}

	// Pozovi osnovnu klasu da obradi ostale tastere
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CIND18717View::Gray(CBitmap* bmpImage, BITMAP bm)
{

	long dwCount = bm.bmWidthBytes * bm.bmHeight;
	BYTE* lpBits = new BYTE[dwCount];
	ZeroMemory(lpBits, dwCount);
	bmpImage->GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, lpBits);

	for (long i = 0; i < dwCount - 3; i += 3)
	{
		BYTE b = BYTE(lpBits[i]);
		BYTE g = BYTE(lpBits[i + 1]);
		BYTE r = BYTE(lpBits[i + 2]);
		BYTE gray = 64 + (b + g + r) / 3; if (gray > 255) gray = 255; // 0.299 * r + 0.587 * g + 0.114 * b;
		lpBits[i] = gray;
		lpBits[i + 1] = gray;
		lpBits[i + 2] = gray;
	}

	bmpImage->SetBitmapBits(dwCount, lpBits);
	delete[] lpBits;
}

void CIND18717View::Red(CBitmap* bmpImage, BITMAP bm)
{

	long dwCount = bm.bmWidthBytes * bm.bmHeight;
	BYTE* lpBits = new BYTE[dwCount];
	ZeroMemory(lpBits, dwCount);
	bmpImage->GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, lpBits); // kopira sve piksele iz bmpImage u lpBits

	for (long i = 0; i < dwCount - 3; i += 3)
	{
		lpBits[i] = lpBits[i];      // R ostavlja
		lpBits[i + 1] = 0;  // G na 0
		lpBits[i + 2] = 0;  // B na 0
	}

	bmpImage->SetBitmapBits(dwCount, lpBits);
	delete[] lpBits;
}

void CIND18717View::AntiFlicker(CDC* dc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(dc);

	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(dc, 500, 500);
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	Photo(&memDC);

	dc->BitBlt(0, 0, 500, 500, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
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

void CIND18717View::Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply) {
	XFORM transform;
	transform.eM11 = mx ? -1.0f : 1.0f;
	transform.eM12 = 0.0f;
	transform.eM21 = 0.0f;
	transform.eM22 = my ? -1.0f : 1.0f;
	transform.eDx = 0.0f;
	transform.eDy = 0.0f;
	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
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
