#pragma once

#include "WASP.h"

class CSpritePantsFallDown : public CSprite
  {
  public:
    BOOL InitInstance(CImage* (*add)(UINT resID, LPCTSTR type))
      {
      mOffsetX = 253;
      mOffsetY = 115;

      mImages.push_back(add(IDB_PNG10, _T("PNG")));
      mImages.push_back(add(IDB_PNG11, _T("PNG")));
      mImages.push_back(add(IDB_PNG12, _T("PNG")));
      mImages.push_back(add(IDB_PNG13, _T("PNG")));
      mImages.push_back(add(IDB_PNG14, _T("PNG")));
      mImages.push_back(add(IDB_PNG15, _T("PNG")));
      mImages.push_back(add(IDB_PNG16, _T("PNG")));
      mImages.push_back(add(IDB_PNG17, _T("PNG")));

      return true;
      }
  };
