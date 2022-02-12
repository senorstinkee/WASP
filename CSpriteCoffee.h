#pragma once

#include "WASP.h"

class CSpriteCoffee : public CSprite
  {
  public:
    BOOL InitInstance(CImage* (*add)(UINT resID, LPCTSTR type))
      {
      mOffsetX = 252;
      mOffsetY = 115;

      mImages.push_back(add(IDB_PNG48, _T("PNG")));
      mImages.push_back(add(IDB_PNG49, _T("PNG")));
      mImages.push_back(add(IDB_PNG50, _T("PNG")));
      mImages.push_back(add(IDB_PNG51, _T("PNG")));
      mImages.push_back(add(IDB_PNG52, _T("PNG")));
      mImages.push_back(add(IDB_PNG53, _T("PNG")));
      mImages.push_back(add(IDB_PNG54, _T("PNG")));
      mImages.push_back(add(IDB_PNG55, _T("PNG")));
      mImages.push_back(add(IDB_PNG56, _T("PNG")));
      mImages.push_back(add(IDB_PNG57, _T("PNG")));
      mImages.push_back(add(IDB_PNG58, _T("PNG")));
      mImages.push_back(add(IDB_PNG59, _T("PNG")));
      mImages.push_back(add(IDB_PNG60, _T("PNG")));
      mImages.push_back(add(IDB_PNG61, _T("PNG")));
      mImages.push_back(add(IDB_PNG62, _T("PNG")));
      mImages.push_back(add(IDB_PNG63, _T("PNG")));
      mImages.push_back(add(IDB_PNG64, _T("PNG")));
      mImages.push_back(add(IDB_PNG65, _T("PNG")));
      mImages.push_back(add(IDB_PNG66, _T("PNG")));
      mImages.push_back(add(IDB_PNG67, _T("PNG")));

      return true;
      }
  };
