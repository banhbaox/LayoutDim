// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef CK_PROGRESS_CTRL_INC
#define CK_PROGRESS_CTRL_INC

#if defined(KCMATH_MAIN) || defined(SDK_MAIN)
#define PROGRESS_EXPORT __declspec(dllexport)
#else
#define PROGRESS_EXPORT __declspec(dllimport)
#endif

// @doc Internal EXTERNAL SDK

// @class The purpose of this class is to provide uniform progress
// control functionality within KeyCreator.  Implementing methods that set
// the progress text on the fly could vary so it is done here for you.
// Additionally this progress control can be pushed meaning you can
// instantiate one while another is active.  Use the default arguments
// of the constructor to take the current range and position from the parent.
class PROGRESS_EXPORT CKProgressCtrl
    {
    static int s_nMaxSteps;

// @Access Public Functions
public:
    static bool s_bSuppressCtrl;

    // @cmember Constructor
    CKProgressCtrl(LPCTSTR lpszText, size_t nTotalNumSteps=100,
                   bool bAllowNesting=false, size_t nStart=0, size_t nPos=0,
                   size_t nStep=1);

    CKProgressCtrl(UINT unText, size_t nTotalNumSteps = 100,
                   bool bAllowNesting = false, size_t nStart = 0,
                   size_t nPos = 0, size_t nStep = 1);

    void Init();

    ~CKProgressCtrl();

    // @cmember Set the start and end values for the progress control,
    // and the step size.
    void SetRange(size_t nStart, size_t nTotalNumSteps, size_t nStep);

    // @cmember Set the text displayed on the progress control
    void SetText(LPCTSTR lpszText);

    // @cmember Advance the progress control
    void Step();

    // @cmember Set the current location of the progress control
    void Set(size_t pos);

    // @cmember Get the data from the progress control.
    void GetData(size_t &nStart, size_t &nTotalNumSteps, bool &bAllowNesting,
                 size_t &nStep, size_t &nPos, std::wstring &csText)
        {
        nStart = m_nStart;
        nTotalNumSteps = m_nTotalNumSteps;
        bAllowNesting = m_bAllowNesting;
        nStep = m_nStep;
        nPos = m_nPos;
        csText = m_csText;
        }

// @Access Protected Functions
protected:
    // @cmember Updates the display of the status bar
    void Display();

    // @cmember Sets the pushed flag
    void Push() { m_bPushed = true; }

// @Access Protected Data
protected:
    // @cmember The progress control that was active when this one was created
    CKProgressCtrl *m_pParentProgressCtrl;

    // @cmember The current start value of the progress control.
    size_t m_nStart;

    // @cmember The current end value of the progress control.
    size_t m_nTotalNumSteps;

    // @cmember The current step value of the progress control.
    size_t m_nStep;

    // @cmember The current position of the progress control.
    size_t m_nPos;

    // @cmember The number of times Step must be called to update the
    // progress control
    size_t m_nStepsPerUpdate;

    // @cmember The number of times Step has been called since last update
    size_t m_nStepsSinceUpdate;

    // @cmember The time that the last update was done.
    clock_t m_nLastUpdateClock;

    // @cmember Was this control pushed out by another one?  This requires
    // the display to be refreshed.
    bool m_bPushed;

    // @cmember Should we allow nested progress controls
    bool m_bAllowNesting;

    // @cmember The displayed text.
    std::wstring m_csText;
    };

#undef PROGRESS_EXPORT

#endif
