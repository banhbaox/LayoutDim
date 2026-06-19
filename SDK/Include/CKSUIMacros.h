// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef CKS_UIMACROS_INC
#define CKS_UIMACROS_INC

// @doc EXTERNAL SDK

// @func | CKS_BEGIN_UI_LOOP_FIRST_STEP | This macro sets up a while()-switch()
// loop for walking through the steps of a function that returns <t Events>.
// This must have a matching <f CKS_END_UI_LOOP> closing macro.  The number
// of this first step is 1.  The macro still has a parameter so that it is
// identified as step 1.  The macro will ASSERT if the parameter is not 1.
#define CKS_BEGIN_UI_LOOP_FIRST_STEP(nFirstStep)  \
    ASSERT(nFirstStep == 1);                      \
    int eUIStandardHandler = CKEscape;            \
    int nUICurrentStep = 1;                       \
    while(1)                                      \
        {                                         \
        switch(nUICurrentStep)                    \
            {                                     \
            case (0):                             \
                return(eUIStandardHandler);       \
            case (1):

#ifdef _DEBUG
#define DEBUGMSG(x) AfxMessageBox((x), MB_ICONERROR);
#else
#define DEBUGMSG(x)
#endif

// @func | CKS_END_UI_LOOP | Ends the user interface while()-switch() loop that
// was started with the <f CKS_BEGIN_UI_LOOP_FIRST_STEP> macro.
#define CKS_END_UI_LOOP()                                                \
/*              DEBUGMSG(_T("CKS_END_UI_LOOP: Last step unterminated."));\
                return(CKEscape);                                        \
*/                                                                       \
            default:                                                     \
                DEBUGMSG(_T("CKS_END_UI_LOOP: current step is invalid"));\
                return(CKEscape);                                        \
            }                                                            \
        }                                         

// @func | CKS_BEGIN_UI_LOOP_STEP | Starts another step in the user interface 
// loop
// @parm int | n | The number of the step being started
#define CKS_BEGIN_UI_LOOP_STEP(n)                     \
            case (n):

// @func | CKS_BEGIN_UI_LOOP_OPTIONAL_STEP | This is used to define a step
// that is only executed under certain circumstances.
//
// @parm int    | n | The number of the step being started
// @parm bool   | b | If this is true, the step is executed, if not, it is
//                    skipped.
// @parm Events | e | Event returned from UI that is used to determine the
//                    skip direction.  If e == CKBackup, control passes to
//                    the previous step, otherwise it passes to the next step.
#define CKS_BEGIN_UI_LOOP_OPTIONAL_STEP(n, b, e)             \
            case (n):                                        \
                if(!(b))                                     \
                    {                                        \
                    if((e) == CKBackup)                      \
                        {                                    \
                        CKS_UI_LOOP_RESTART_PREVIOUS_STEP(); \
                        }                                    \
                    else                                     \
                        {                                    \
                        CKS_UI_LOOP_RESTART_NEXT_STEP();     \
                        }                                    \
                    }                                        \
                else                                         \
                    {                                        \
                    }

// @func | CKS_UI_LOOP_RESTART_AT_STEP | Restarts the UI loop going to the
//  specified step.
// @parm int | n | The number of the step to restart at
#define CKS_UI_LOOP_RESTART_AT_STEP(n)            \
            {                                     \
            nUICurrentStep = (n);                 \
            continue;                             \
            }

// @func | CKS_UI_LOOP_RESTART_PREVIOUS_STEP | Restarts the UI loop with the 
//  step just prior to the current step.  This skips the remainder of the 
//  current step.  If currently executing step 1, the function is exited 
//  instead. This is the same behavior as 
//  CKS_UI_LOOP_STANDARD_HANDLER(CKBackup);
#define CKS_UI_LOOP_RESTART_PREVIOUS_STEP()       \
            {                                     \
            --nUICurrentStep;                     \
            continue;                             \
            }

// @func | CKS_UI_LOOP_RESTART_CURRENT_STEP | Restarts the current UI loop 
//  step.  This skips the remainder of the current step before restarting.
#define CKS_UI_LOOP_RESTART_CURRENT_STEP()            \
            continue;

// @func | CKS_UI_LOOP_RESTART_NEXT_STEP | Restarts the UI loop at the next 
//  step.  This skips the remainder of the current step.
#define CKS_UI_LOOP_RESTART_NEXT_STEP()           \
            {                                     \
            ++nUICurrentStep;                     \
            continue;                             \
            }

// @func | CKS_UI_LOOP_FALL_THROUGH | Allows processing to fall into the next
//  step of the UI loop.  When used within a <f CKS_BEGIN_UI_LOOP_STEP> block,
//  the fall through macro should always be at the end of the block.  The
//  next block in the code must be numbered one more than the current
//  block for proper flow, as flow proceeds directly into the next block
//  without restarting the loop.  If the next step isn't located directly
//  after the current step, use <f CKS_UI_LOOP_RESTART_NEXT_STEP> instead.
#define CKS_UI_LOOP_FALL_THROUGH()                    \
            ++nUICurrentStep;

// @func | CKS_UI_LOOP_STANDARD_HANDLER | Macro to handle typical loop 
//  navigation for <t Events> returned by calls to the User Interface. 
//  Events handled are:
// @flag <e Events.CKBackup>    | moves loop processing to the previous step.
//                                If currently executing step 1, the function
//                                is exited instead.
// @flag <e Events.CKEscape>    |
// @flag <e Events.CKRoot>      |
// @flag <e Events.CKExiting>   | 
// @flag <e Events.CKDocChange> | Exits the function, returning the event.
//
// @parm Events | x | Event returned from UI that is to be handled.
#define CKS_UI_LOOP_STANDARD_HANDLER(x)           \
    switch(eUIStandardHandler = (x))              \
        {                                         \
        case CKBackup:                            \
            CKS_UI_LOOP_RESTART_PREVIOUS_STEP();  \
                                                  \
        case CKEscape:                            \
        case CKRoot:                              \
        case CKExiting:                           \
        case CKDocChange:                         \
            CKS_UI_LOOP_RESTART_AT_STEP(0);       \
        }

// @func | CKS_MAINTAIN_UPM | This macro declares an integer variable to hold
// a default UPM item.  It also adds code to switch from Polar or Delta
// to the system default when entering the function containing this macro.
// This should be placed outside of any loops, or it will be reset from
// polar or delta every time through the loop.
//
// @parm | nDefault | The name of the variable which will be used in a call
// to <mf CKMainFrame::GetPos>.
//
// @ex An example of multiple GetPos calls in the same function |
// MAINTAIN_UPM(nFirstDefault);
// MAINTAIN_UPM(nSecondDefault);
//
// GetPos(csFirstPrompt, nFirstDefault, ckcFirst);
// GetPos(csSecondPrompt, nSecondDefault, ckcSecond);
#define CKS_MAINTAIN_UPM(nDefault)           \
    static int nDefault;                     \
    if((7 == nDefault) || (8 == nDefault))   \
        {                                    \
        nDefault = 0;                        \
        }

#endif
