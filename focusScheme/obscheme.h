#ifndef OBSCHEME_H
#define OBSCHEME_H
#include "focusscheme.h"

class OBScheme : public FocusScheme
{
public:
    OBScheme();
    ~OBScheme();
    TimeRange getFocusRange() override;
};

#endif // OBSCHEME_H
