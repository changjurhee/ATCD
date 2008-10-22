// $Id$
//
// ****              Code generated by the                 ****
// ****  Component Integrated ACE ORB (CIAO) CIDL Compiler ****
// CIAO has been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// CIDL Compiler has been developed by:
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about CIAO is available at:
//    http://www.dre.vanderbilt.edu/CIAO

#ifndef CIAO_MESSENGER_EXEC_H
#define CIAO_MESSENGER_EXEC_H

#include /**/ "ace/pre.h"

#include "Messenger_svnt.h"
#include "Messenger_exec_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/LocalObject.h"

// MY CODE
#include <string>
#include "ace/Task.h"

namespace CIDL_Messenger_Impl
{
  class Runnable_exec_i;
  class Publication_exec_i;
  class History_exec_i;

  class MESSENGER_EXEC_Export Messenger_exec_i
  : public virtual Messenger_Exec,
    public virtual TAO_Local_RefCounted_Object,
    public virtual ACE_Task_Base
  {
    public:
    Messenger_exec_i (void);
    virtual ~Messenger_exec_i (void);

    // Supported or inherited operations.

    // Operations from ::Runnable

    // Attribute operations.

    virtual char * subject ();

    virtual void subject (const char* subject);

    // Port operations.

    virtual ::CCM_Publication_ptr
    get_content ();

    virtual ::CCM_Runnable_ptr
    get_control ();

    virtual ::CCM_History_ptr
    get_message_history ();

    // Operations from Components::SessionComponent

    virtual void
    set_session_context (
    ::Components::SessionContext_ptr ctx);

    virtual void
    ciao_preactivate ();

    virtual void
    ciao_postactivate ();

    virtual void
    ccm_activate ();

    virtual void
    ccm_passivate ();

    virtual void
    ccm_remove ();

    // MY CODE
    virtual int svc();

    protected:
    Messenger_Context *context_;

    // MY CODE
    private:
      Runnable_exec_i* control_;
      Publication_exec_i* content_;
      History_exec_i* history_;

      std::string subject_;
      const std::string user_;
  };

  class MESSENGER_EXEC_Export MessengerHome_exec_i
  : public virtual MessengerHome_Exec,
  public virtual TAO_Local_RefCounted_Object
  {
    public:
    MessengerHome_exec_i (void);
    virtual ~MessengerHome_exec_i (void);

    // Supported or inherited operations.

    // Home operations.

    // Factory and finder operations.

    // Attribute operations.

    // Implicit operations.

    virtual ::Components::EnterpriseComponent_ptr
    create ();
  };

  extern "C" MESSENGER_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_MessengerHome_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* CIAO_MESSENGER_EXEC_H */

