#pragma once

#include "WASP.h"

class CSpriteChocolate : public CSprite
  {
  public:
    BOOL InitInstance(CImage* (*add)(UINT resID, LPCTSTR type))
      {
      mOffsetX = 121;
      mOffsetY = 117;

      mImages.push_back(add(IDB_PNG18, _T("PNG")));
      mImages.push_back(add(IDB_PNG19, _T("PNG")));
      mImages.push_back(add(IDB_PNG20, _T("PNG")));
      mImages.push_back(add(IDB_PNG21, _T("PNG")));
      mImages.push_back(add(IDB_PNG22, _T("PNG")));
      mImages.push_back(add(IDB_PNG23, _T("PNG")));
      mImages.push_back(add(IDB_PNG24, _T("PNG")));
      mImages.push_back(add(IDB_PNG25, _T("PNG")));
      mImages.push_back(add(IDB_PNG26, _T("PNG")));
      mImages.push_back(add(IDB_PNG27, _T("PNG")));
      mImages.push_back(add(IDB_PNG28, _T("PNG")));
      mImages.push_back(add(IDB_PNG29, _T("PNG")));
      mImages.push_back(add(IDB_PNG30, _T("PNG")));
      mImages.push_back(add(IDB_PNG31, _T("PNG")));
      mImages.push_back(add(IDB_PNG32, _T("PNG")));
      mImages.push_back(add(IDB_PNG33, _T("PNG")));
      mImages.push_back(add(IDB_PNG34, _T("PNG")));
      mImages.push_back(add(IDB_PNG35, _T("PNG")));
      mImages.push_back(add(IDB_PNG36, _T("PNG")));
      mImages.push_back(add(IDB_PNG37, _T("PNG")));
      mImages.push_back(add(IDB_PNG38, _T("PNG")));
      mImages.push_back(add(IDB_PNG39, _T("PNG")));
      mImages.push_back(add(IDB_PNG40, _T("PNG")));
      mImages.push_back(add(IDB_PNG41, _T("PNG")));
      mImages.push_back(add(IDB_PNG42, _T("PNG")));
      mImages.push_back(add(IDB_PNG43, _T("PNG")));
      mImages.push_back(add(IDB_PNG44, _T("PNG")));
      mImages.push_back(add(IDB_PNG45, _T("PNG")));
      mImages.push_back(add(IDB_PNG46, _T("PNG")));
      mImages.push_back(add(IDB_PNG47, _T("PNG")));

      return true;
      }
  };
