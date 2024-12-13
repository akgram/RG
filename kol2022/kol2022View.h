
// kol2022View.h : interface of the Ckol2022View class
//

#pragma once
#include "DImage.h"

class Ckol2022View : public CView
{
protected: // create from serialization only
	Ckol2022View() noexcept;
	DECLARE_DYNCREATE(Ckol2022View)

// Attributes
public:
	Ckol2022Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawLampBase(CDC* pDC, bool bIsShadow);
	void DrawLampArm1(CDC* pDC, bool bIsShadow);
	void DrawLampArm2(CDC* pDC, bool bIsShadow);
	void DrawLampHead(CDC* pDC, bool bIsShadow);
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawLamp(CDC* pDC, bool bIsShadow);
	void DrawLampShadow(CDC* pDC);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ckol2022View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	DImage *base, *arm1, *arm2, *head, *pozadina, *base_shadow, *arm1_shadow, *arm2_shadow, *head_shadow;
	int arm1Prvirot, arm1Drugirot, arm2Prvirot, arm2Drugirot, headrot;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in kol2022View.cpp
inline Ckol2022Doc* Ckol2022View::GetDocument() const
   { return reinterpret_cast<Ckol2022Doc*>(m_pDocument); }
#endif

