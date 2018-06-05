/**********************************************************************

  Audacity: A Digital Audio Editor

  MadRuler.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __MADEDITMOD_RULER__
#define __MADEDITMOD_RULER__

#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/dcmemory.h>
#include <wx/event.h>
#include <wx/font.h>
#include <wx/window.h>
#include <algorithm>
#include <cmath>
#include <wx/defs.h>
#include <wx/debug.h>

enum NumberScaleType {
   nstLinear,
   nstLogarithmic,
   nstMel,
   nstBark,
   nstErb,
   nstPeriod,

   nstNumScaleTypes,
};


class NumberScale
{
public:
   NumberScale()
      : mType(nstLinear), mValue0(0), mValue1(1), mUnit(1)
   {}

   NumberScale(NumberScaleType type,
      float value0, float value1, float unit)
      : mType(type)
   {
      switch (mType) {
      case nstLinear:
      {
         mValue0 = value0 / unit;
         mValue1 = value1 / unit;
         mUnit = 1.0;
      }
      break;
      case nstLogarithmic:
      {
         mValue0 = logf(value0 / unit);
         mValue1 = logf(value1 / unit);
         mUnit = 1.0;
      }
      break;
      case nstMel:
      {
         mValue0 = hzToMel(value0);
         mValue1 = hzToMel(value1);
         mUnit = unit;
      }
      break;
      case nstBark:
      {
         mValue0 = hzToBark(value0);
         mValue1 = hzToBark(value1);
         mUnit = unit;
      }
      break;
      case nstErb:
      {
         mValue0 = hzToErb(value0);
         mValue1 = hzToErb(value1);
         mUnit = unit;
      }
      break;
      case nstPeriod:
      {
         mValue0 = hzToPeriod(value0);
         mValue1 = hzToPeriod(value1);
         mUnit = unit;
      }
      break;
      default:
         wxASSERT(false);
      }
   }

   NumberScale Reversal() const
   {
      NumberScale result(*this);
      std::swap(result.mValue0, result.mValue1);
      return result;
   }

   bool operator == (const NumberScale& other) const
   {
      return mType == other.mType
         && mValue0 == other.mValue0
         && mValue1 == other.mValue1
         && mUnit == other.mUnit;
   }

   bool operator != (const NumberScale &other) const
   {
      return !(*this == other);
   }

   static inline float hzToMel(float hz)
   {
      return 1127 * log(1 + hz / 700);
   }

   static inline float melToHz(float mel)
   {
      return 700 * (exp(mel / 1127) - 1);
   }

   static inline float hzToBark(float hz)
   {
      // Traunmueller's formula
      const float z1 = 26.81 * hz / (1960 + hz) - 0.53;
      if (z1 < 2.0)
         return z1 + 0.15 * (2.0 - z1);
      else if (z1 > 20.1)
         return z1 + 0.22 * (z1 - 20.1);
      else
         return z1;
   }

   static inline float barkToHz(float z1)
   {
      if (z1 < 2.0)
         z1 = 2.0 + (z1 - 2.0) / 0.85;
      else if (z1 > 20.1)
         z1 = 20.1 + (z1 - 20.1) / 1.22;
      return 1960 * (z1 + 0.53) / (26.28 - z1);
   }

   static inline float hzToErb(float hz)
   {
      return 11.17268 * log(1 + (46.06538 * hz) / (hz + 14678.49));
   }

   static inline float erbToHz(float erb)
   {
      return 676170.4 / (47.06538 - exp(0.08950404 * erb)) - 14678.49;
   }

   static inline float hzToPeriod(float hz)
   {
      return -1.0 / std::max (1.0f, hz);
   }

   static inline float periodToHz(float u)
   {
      return -1.0 / u;
   }

   // Random access
   float PositionToValue(float pp) const
   {
      switch (mType) {
      default:
         wxASSERT(false);
      case nstLinear:
         return mValue0 + pp * (mValue1 - mValue0);
      case nstLogarithmic:
         return exp(mValue0 + pp * (mValue1 - mValue0));
      case nstMel:
         return melToHz(mValue0 + pp * (mValue1 - mValue0)) / mUnit;
      case nstBark:
         return barkToHz(mValue0 + pp * (mValue1 - mValue0)) / mUnit;
      case nstErb:
         return erbToHz(mValue0 + pp * (mValue1 - mValue0)) / mUnit;
      case nstPeriod:
         return periodToHz(mValue0 + pp * (mValue1 - mValue0)) / mUnit;
      }
   }

   // STL-idiom iteration

   class Iterator
   {
   public:
      Iterator(NumberScaleType type, float step, float value, float unit)
         : mType(type), mStep(step), mValue(value), mUnit(unit)
      {
      }

      float operator * () const
      {
         switch (mType) {
         default:
            wxASSERT(false);
         case nstLinear:
         case nstLogarithmic:
            return mValue;
         case nstMel:
            return melToHz(mValue) / mUnit;
         case nstBark:
            return barkToHz(mValue) / mUnit;
         case nstErb:
            return erbToHz(mValue) / mUnit;
         case nstPeriod:
            return periodToHz(mValue) / mUnit;
         }
      }

      Iterator &operator ++()
      {
         switch (mType) {
         case nstLinear:
         case nstMel:
         case nstBark:
         case nstErb:
         case nstPeriod:
            mValue += mStep;
            break;
         case nstLogarithmic:
            mValue *= mStep;
            break;
         default:
            wxASSERT(false);
         }
         return *this;
      }

   private:
      const NumberScaleType mType;
      const float mStep;
      float mValue;
      float mUnit;
   };

   Iterator begin(float nPositions) const
   {
      switch (mType) {
      default:
         wxASSERT(false);
      case nstLinear:
      case nstMel:
      case nstBark:
      case nstErb:
      case nstPeriod:
         return Iterator
            (mType,
             nPositions == 1 ? 0 : (mValue1 - mValue0) / (nPositions - 1),
             mValue0, mUnit);
      case nstLogarithmic:
         return Iterator
            (mType,
             nPositions == 1 ? 1 : exp((mValue1 - mValue0) / (nPositions - 1)),
             exp(mValue0), mUnit);
      }
   }

   // Inverse
   float ValueToPosition(float val) const
   {
      switch (mType) {
      default:
         wxASSERT(false);
      case nstLinear:
         return ((val - mValue0) / (mValue1 - mValue0));
      case nstLogarithmic:
         return ((log(val) - mValue0) / (mValue1 - mValue0));
      case nstMel:
         return ((hzToMel(val * mUnit) - mValue0) / (mValue1 - mValue0));
      case nstBark:
         return ((hzToBark(val * mUnit) - mValue0) / (mValue1 - mValue0));
      case nstErb:
         return ((hzToErb(val * mUnit) - mValue0) / (mValue1 - mValue0));
      case nstPeriod:
         return ((hzToPeriod(val * mUnit) - mValue0) / (mValue1 - mValue0));
      }
   }

private:
   NumberScaleType mType;
   float mValue0;
   float mValue1;
   float mUnit;
};

class MadRuler {
 public:

   enum RulerFormat {
      IntFormat,
      RealFormat,
      RealLogFormat,
      TimeFormat,
      LinearDBFormat,
   };

   //
   // Constructor / Destructor
   //

   MadRuler();
   ~MadRuler();

   //
   // Required MadRuler Parameters
   //

   void SetBounds(int left, int top, int right, int bottom);

   // wxHORIZONTAL || wxVERTICAL
   void SetOrientation(int orient);

   // min is the value at (x, y)
   // max is the value at (x+width, y+height)
   // (at the center of the pixel, in both cases)
   void SetRange(double min, double max);

   // An overload needed for the special case of fisheye
   // min is the value at (x, y)
   // max is the value at (x+width, y+height)
   // hiddenMin, hiddenMax are the values that would be shown without the fisheye.
   // (at the center of the pixel, in both cases)
   void SetRange(double min, double max, double hiddenMin, double hiddenMax);

   //
   // Optional MadRuler Parameters
   //

   // If twoTone is true, cause zero and positive numbers to appear black, negative in another color.
   void SetTwoTone(bool twoTone);

   // IntFormat, RealFormat, or TimeFormat
   void SetFormat(RulerFormat format);

   // Specify the name of the units (like "dB") if you
   // want numbers like "1.6" formatted as "1.6 dB".
   void SetUnits(const wxString &units);

   // Logarithmic
   void SetLog(bool log);

   // Minimum number of pixels between labels
   void SetSpacing(int spacing);

   // If this is true, the edges of the ruler will always
   // receive a label.  If not, the nearest round number is
   // labeled (which may or may not be the edge).
   void SetLabelEdges(bool labelEdges);

   // Makes a vertical ruler hug the left side (instead of right)
   // and a horizontal ruler hug the top (instead of bottom)
   void SetFlip(bool flip);

   // Set it to false if you don't want minor labels.
   void SetMinor(bool value);

   // Good defaults are provided, but you can /*override*/ here
   void SetFonts(const wxFont &minorFont, const wxFont &majorFont, const wxFont &minorMinorFont);
   struct Fonts { wxFont *major, *minor, *minorMinor; };
   Fonts GetFonts() const
   {
	   Fonts font = { mMajorFont, mMinorFont, mMinorMinorFont };
	   return font; 
   }

      // Copies *pScale if it is not NULL
   void SetNumberScale(const NumberScale *pScale);

   // The ruler will not draw text within this (pixel) range.
   // Use this if you have another graphic object obscuring part
   // of the ruler's area.  The values start and end are interpreted
   // relative to the MadRuler's local coordinates.
   void OfflimitsPixels(int start, int end);

   //
   // Calculates and returns the maximum size required by the ruler
   //
   void GetMaxSize(wxCoord *width, wxCoord *height);


   // The following functions should allow a custom ruler setup:
   // autosize is a GREAT thing, but for some applications it's
   // useful the definition of a label array and label step by
   // the user.
   void SetCustomMode(bool value);
   // If this is the case, you should provide a wxString array of labels, start
   // label position, and labels step. The range eventually specified will be
   // ignored.
   void SetCustomMajorLabels(wxArrayString *label, int numLabel, int start, int step);
   void SetCustomMinorLabels(wxArrayString *label, int numLabel, int start, int step);


   //
   // Drawing
   //

   // Note that it will not erase for you...
   void Draw(wxDC& dc);
   // If length <> 0, draws lines perpendiculars to ruler corresponding
   // to selected ticks (major, minor, or both), in an adjacent window.
   // You may need to use the offsets if you are using part of the dc for rulers, borders etc.
   void DrawGrid(wxDC& dc, int length, bool minor = true, bool major = true, int xOffset = 0, int yOffset = 0);

   // So we can have white ticks on black...
   void SetTickColour( const wxColour & colour)
   { mTickColour = colour; mPen.SetColour( colour );}

   // Force regeneration of labels at next draw time
   void Invalidate();

 private:
   void Update();
   void FindTickSizes();
   void FindLinearTickSizes(double UPP);
   wxString LabelString(double d, bool major);

   void Tick(int pos, double d, bool major, bool minor);

   // Another tick generator for custom ruler case (noauto) .
   void TickCustom(int labelIdx, bool major, bool minor);

public:
   bool mbTicksOnly; // true => no line the length of the ruler
   bool mbTicksAtExtremes;
   wxRect mRect;

private:
   static wxColour mTickColour;
   wxPen mPen;

   int          mMaxWidth, mMaxHeight;
   int          mLeft, mTop, mRight, mBottom, mLead;
   int          mLength;
   int          mLengthOld;
   wxDC        *mDC;

   wxFont      *mMinorFont, *mMajorFont;
   wxFont      *mMinorMinorFont;
   bool         mUserFonts;

   double       mMin, mMax;
   double       mHiddenMin, mHiddenMax;

   double       mMajor;
   double       mMinor;

   int          mDigits;

   int         *mUserBits;
   int         *mBits;
   int          mUserBitLen;

   bool         mValid;

   class Label {
    public:
      double value;
      int pos;
      int lx, ly;
      wxString text;

      void Draw(wxDC &dc, bool twoTone) const;
   };

   int          mNumMajor;
   Label       *mMajorLabels;
   int          mNumMinor;
   Label       *mMinorLabels;
   int          mNumMinorMinor;
   Label       *mMinorMinorLabels;

   // Returns 'zero' label coordinate (for grid drawing)
   int FindZero(Label * label, int len);

   public:
   int GetZeroPosition();

   private:
   int          mOrientation;
   int          mSpacing;
   bool         mHasSetSpacing;
   bool         mLabelEdges;
   RulerFormat  mFormat;
   bool         mLog;
   bool         mFlip;
   bool         mCustom;
   bool         mbMinor;
   bool         mMajorGrid;      //  for grid drawing
   bool         mMinorGrid;      //         .
   int          mGridLineLength; //        end
   wxString     mUnits;
   bool         mTwoTone;
   int          mLeftOffset;

   NumberScale *mpNumberScale;
};

class RulerPanel /*final*/ : public wxPanel {
   DECLARE_DYNAMIC_CLASS(RulerPanel)

 public:
   RulerPanel(wxWindow* parent, wxWindowID id,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize);

   ~RulerPanel();

   void DoSetSize(int x, int y,
                  int width, int height,
                  int sizeFlags = wxSIZE_AUTO) /*override*/;

   void OnErase(wxEraseEvent &evt);
   void OnPaint(wxPaintEvent &evt);
   void OnSize(wxSizeEvent &evt);

   // We don't need or want to accept focus.
   bool AcceptsFocus() const { return false; }
   // So that wxPanel is not included in Tab traversal - see wxWidgets bug 15581
   bool AcceptsFocusFromKeyboard() const { return false; }

 public:

   MadRuler  ruler;

private:
    DECLARE_EVENT_TABLE()
};

class QuickPlayIndicatorOverlay;
class QuickPlayRulerOverlay;

#endif //define __MADEDITMOD_RULER__
