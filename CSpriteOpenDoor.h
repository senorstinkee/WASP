#pragma once

#include "WASP.h"

class CSpriteOpenDoor : public CSprite
  {
  public:
    BOOL InitInstance(CImage* (*add)(UINT resID, LPCTSTR type))
      {
      mOffsetX = 256;
      mOffsetY = 115;

      mImages.push_back(add(IDB_PNG0, _T("PNG")));
      mImages.push_back(add(IDB_PNG1, _T("PNG")));
      mImages.push_back(add(IDB_PNG2, _T("PNG")));
      mImages.push_back(add(IDB_PNG3, _T("PNG")));
      mImages.push_back(add(IDB_PNG4, _T("PNG")));
      mImages.push_back(add(IDB_PNG5, _T("PNG")));
      mImages.push_back(add(IDB_PNG6, _T("PNG")));
      mImages.push_back(add(IDB_PNG7, _T("PNG")));
      mImages.push_back(add(IDB_PNG8, _T("PNG")));
      mImages.push_back(add(IDB_PNG9, _T("PNG")));

      return true;
      }
  };
