// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved

#ifndef CKS_EXPERIMENT_INC
#define CKS_EXPERIMENT_INC

#include "ck_export.h"

class CKPart;
class ck_experiment;

// @class (Optionally) Locks the database to prevent the user from calling any functions
// which aren't marked as "Safe", which means that they don't do anything
// that would cause undo states to be created in the model.  This also
// allows changes to be made to the data model which can then be undone if
// they don't work out properly.  When this object goes out of scope, any
// changes which haven't been accept()'ed are discarded, and the model is
// rolled back to the state it was in when the experiment was created, or
// last accept()'ed.  After an experiment has been accept()'ed or rejected,
// the undo part of the functionality is suspended.  It can be restarted
// by calling the resume() function.  The database lock portion is maintained
// until the object goes out of scope.
class SDK_EXPORT cks_experiment
    {
public:
    cks_experiment(CKPart &rPart, bool bLock=true);
    ~cks_experiment();

    // @cmember Accepts all changes made since the object was created,
    // or since the last resume().
    void accept();

    // @cmember Rejects all changes made since the object was created,
    // or since the last resume().
    void reject();

    // @cmember Restarts an experiment that has either been accept()'ed or
    // reject()'ed.
    void resume();

protected:
    std::unique_ptr<ck_experiment> m_pcksExperiment;

private:
    // Don't allow creating these objects with new.
    void *operator new(size_t);
    void *operator new(size_t, void *);
    void *operator new[](size_t);
    void *operator new[](size_t, void *);
    };

#endif
