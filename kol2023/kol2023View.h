
// kol2023View.h : interface of the Ckol2023View class
//

#pragma once
#include "DImage.h"


class Ckol2023View : public CView
{
protected: // create from serialization only
	Ckol2023View() noexcept;
	DECLARE_DYNCREATE(Ckol2023View)

// Attributes
public:
	Ckol2023Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawHalf(CDC* pDC);
	void DrawHead(CDC* pDC);
	void DrawRobot(CDC* pDC);
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
	virtual ~Ckol2023View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DImage* glava, * nadkolenica, * nadlaktica, * podkolenica, * podlaktica, * saka, * stopalo, * telo, * pozadina;
	int nadlakticaRot, podlakticaRot, sakaRot, ceoRot;
	float ceoScale;


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in kol2023View.cpp
inline Ckol2023Doc* Ckol2023View::GetDocument() const
   { return reinterpret_cast<Ckol2023Doc*>(m_pDocument); }
#endif

