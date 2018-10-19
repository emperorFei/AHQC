#ifndef SHIFTSSCHEME_H
#define SHIFTSSCHEME_H
#include "focusscheme.h"

class ShiftsScheme : public FocusScheme
{
public:
    explicit ShiftsScheme(QTime shiftsTime);
    ~ShiftsScheme();
    TimeRange getFocusRange();
private:
    QTime shiftsTime;
};

#endif // SHIFTSSCHEME_H
