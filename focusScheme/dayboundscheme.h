#ifndef DAYBOUNDSCHEME_H
#define DAYBOUNDSCHEME_H
#include "focusscheme.h"

class DayBoundScheme : public FocusScheme
{
public:
    DayBoundScheme();
    ~DayBoundScheme() override;
    TimeRange getFocusRange() override;
};

#endif // DAYBOUNDSCHEME_H
