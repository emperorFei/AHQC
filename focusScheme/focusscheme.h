#ifndef FOCUSSCHEME_H
#define FOCUSSCHEME_H
#include "../simpleobject.h"

class FocusScheme{
public:
   FocusScheme(){}
   virtual ~FocusScheme(){}
   virtual TimeRange getFocusRange() = 0;
};
#endif // FOCUSSCHEME_H
