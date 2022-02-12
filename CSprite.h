#pragma once

#include "WASP.h"

class CSprite
  {
  public:
    virtual BOOL InitInstance(CImage* (*add)(UINT resID, LPCTSTR type)) = 0;

    bool Draw(size_t frame, HDC hDC, HDC hDCMem, float ratio, CRect* pRect)
      {
      // IF "mStartFrame == -1" THEN ANIMATON HASN'T STARTED. SO START IT
      if (mStartFrame < 0)
        mStartFrame = frame;

      bool   stillAnimating = true;
      size_t currentFrame   = frame - mStartFrame;

      if (currentFrame >= mImages.size())
        {
        // IF PAST THE END, HOLD ON LAST FRAME
        mStartFrame = -1;
        currentFrame = mImages.size() - 1;
        stillAnimating = false;
        }

      // DRAW FRAME
      CRect frameRect(0, 0, (int) (ratio * mImages.at(currentFrame)->GetWidth()), (int) (ratio * mImages.at(currentFrame)->GetHeight()));

      frameRect.OffsetRect(pRect->left, pRect->top);
      frameRect.OffsetRect((int) (ratio * mOffsetX), (int) (ratio * mOffsetY));

      SelectObject(hDCMem, *mImages.at(currentFrame));
      TransparentBlt(hDC, frameRect.left, frameRect.top, frameRect.Width(), frameRect.Height(), hDCMem,
                          0, 0, mImages.at(currentFrame)->GetWidth(), mImages.at(currentFrame)->GetHeight(),
                          RGB(255,0,255));

      return stillAnimating;
      }

    std::vector<CImage*> mImages;
    int mOffsetX = 0;
    int mOffsetY = 0;

  protected:
    LONGLONG mStartFrame = -1;
  };
