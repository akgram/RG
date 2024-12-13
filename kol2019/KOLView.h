
// KOLView.h : interface of the CKOLView class
//

#pragma once

#include "DImage.h"

class CKOLView : public CView
{
protected: // create from serialization only
	CKOLView() noexcept;
	DECLARE_DYNCREATE(CKOLView)

// Attributes
public:
	CKOLDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawLeg2(CDC* pDC);
	void DrawBody1(CDC* pDC);
	void DrawTransformer(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	int arm1rot, arm2rot, leg1Prvirot, leg1Drugirot, leg2rot, bodyrot;

// Implementation
public:
	virtual ~CKOLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	DImage *body1, *arm1, *arm2, *leg1, *leg2, *back;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in KOLView.cpp
inline CKOLDoc* CKOLView::GetDocument() const
   { return reinterpret_cast<CKOLDoc*>(m_pDocument); }
#endif

