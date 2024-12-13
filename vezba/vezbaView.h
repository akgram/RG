
// vezbaView.h : interface of the CvezbaView class
//

#pragma once
#include "DImage.h"


class CvezbaView : public CView
{
protected: // create from serialization only
	CvezbaView() noexcept;
	DECLARE_DYNCREATE(CvezbaView)

// Attributes
public:
	CvezbaDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawTransformer(CDC* pDC);
	void DrawBody1(CDC* pDC);
	void DrawLeg2(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawArm1(CDC* pDC);
	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CvezbaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DImage* body, * arm1, * arm2, * leg1, * leg2, * backgr;
	int arm1Rot, arm2Rot, leg1Rot, leg2Rot, bodyRot;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in vezbaView.cpp
inline CvezbaDoc* CvezbaView::GetDocument() const
   { return reinterpret_cast<CvezbaDoc*>(m_pDocument); }
#endif

