
// IND_18717View.h : interface of the CIND18717View class
//

#pragma once


class CIND18717View : public CView
{
protected: // create from serialization only
	CIND18717View() noexcept;
	DECLARE_DYNCREATE(CIND18717View)

// Attributes
public:
	CIND18717Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void Photo(CDC* pDC);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	CPoint drawDeo(int x, int y, CString nameOfFile, CDC* pDC);
	void transDeo(CDC* pDC, int x, int y, CString fileName, double alpha);
	void Grid(CDC* pDC, int width, int height, bool showGrid);
	bool showGrid = false; // Da li je mreža uključena
	int width = 500;
	int height = 500;

	double alpha = 0;
	int kvadrat = 25;
	int centerX = 250;
	int centerY = 250;
	int baseX = 0;
	int baseY = 0;
	bool stanje = 1;
	//CIND18717Doc* GetDocument() const;

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void Gray(CBitmap* bmpImage, BITMAP bm);

	void Blue(CBitmap* bmpImage, BITMAP bm);

	void AntiFlicker(CDC& dc);

	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply);

	CImage bmpImage;


	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CIND18717View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IND_18717View.cpp
inline CIND18717Doc* CIND18717View::GetDocument() const
   { return reinterpret_cast<CIND18717Doc*>(m_pDocument); }
#endif

