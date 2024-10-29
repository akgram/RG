
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
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

	void DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle);
	bool showGrid = false; // Da li je mreža uključena
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


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

