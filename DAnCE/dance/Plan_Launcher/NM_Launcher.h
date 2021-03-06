/**
 * @file NM_Launcher.h
 * @author William R. Otte <wotte@dre.vanderbilt.edu>
 *
 * Plan Launcher bridge for the Node Manager.
 */

#ifndef DANCE_PLAN_LAUNCHER_NM
#define DANCE_PLAN_LAUNCHER_NM

#include "Plan_Launcher_Base_Impl_T.h"

#include "dance/Deployment/Deployment_NodeApplicationC.h"
#include "dance/Deployment/Deployment_NodeApplicationManagerC.h"
#include "dance/Deployment/Deployment_NodeManagerC.h"
#include "dance/Plan_Launcher/Plan_Launcher_Export.h"

namespace DAnCE
{
  class DAnCE_Plan_Launcher_Export NM_Launcher :
    public virtual Plan_Launcher_Base_Impl< ::Deployment::NodeManager,
                                            ::Deployment::NodeApplicationManager,
                                            ::Deployment::NodeApplication >
  {
    typedef Plan_Launcher_Base_Impl< ::Deployment::NodeManager,
                                     ::Deployment::NodeApplicationManager,
                                     ::Deployment::NodeApplication > __Base;

  public:
    NM_Launcher (CORBA::ORB_ptr orb,
                      __Base::Manager_ptr managerw);

    ~NM_Launcher (void);


  };
}

#endif
