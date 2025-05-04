#ifndef CCPDFZOOMMANAGEPOLICY_H
#define CCPDFZOOMMANAGEPOLICY_H

class CCPdfZoomManagePolicy
{
public:

    struct Indicator {
        float   new_zoom;
        bool    req_follow_indicator;
    };

    CCPdfZoomManagePolicy();
};

#endif // CCPDFZOOMMANAGEPOLICY_H
