// $Id$

//#include "tao/CSD_Threadpool/CSD_TP_Strategy.h"
#include "tao/Dynamic_TP/Dynamic_TP_POA_StrategyImpl.h"
//#include "tao/CSD_ThreadPool/CSD_TP_Remote_Request.h"
//#include "tao/CSD_ThreadPool/CSD_TP_Collocated_Synch_Request.h"
//#include "tao/CSD_ThreadPool/CSD_TP_Collocated_Asynch_Request.h"
//
//#include "tao/CSD_ThreadPool/CSD_TP_Custom_Synch_Request.h"
//#include "tao/CSD_ThreadPool/CSD_TP_Custom_Asynch_Request.h"
//#include "tao/CSD_ThreadPool/CSD_TP_Collocated_Synch_With_Server_Request.h"
#include "ace/Trace.h"
#include "tao/ORB_Core.h"

#if !defined (__ACE_INLINE__)
#include "tao/Dynamic_TP/Dynamic_TP_POA_StrategyImpl.inl"
#endif /* ! __ACE_INLINE__ */

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

TAO_Dynamic_TP_POA_StrategyImpl::~TAO_Dynamic_TP_POA_StrategyImpl()
{
}

int
TAO_Dynamic_TP_POA_StrategyImpl::get_initial_pool_threads()
{
  return this->initial_pool_threads_;
}

int
TAO_Dynamic_TP_POA_StrategyImpl::get_max_pool_threads()
{
  return this->max_pool_threads_;
}

size_t
TAO_Dynamic_TP_POA_StrategyImpl::get_max_request_queue_depth()
{
  return this->max_request_queue_depth_;
}

int
TAO_Dynamic_TP_POA_StrategyImpl::get_min_pool_threads()
{
  return this->min_pool_threads_;
}

TAO::CSD::TP_Servant_State::HandleType
TAO_Dynamic_TP_POA_StrategyImpl::get_servant_state(PortableServer::Servant servant)
{
  TAO::CSD::TP_Servant_State::HandleType servant_state;

  if (this->serialize_servants_)
    {
      servant_state = this->servant_state_map_.find(servant);
    }

  return servant_state;
}

TAO_Dynamic_TP_Task &
  TAO_Dynamic_TP_POA_StrategyImpl::get_Task()
{
  return this->task_;
}

ACE_Time_Value
TAO_Dynamic_TP_POA_StrategyImpl::get_thread_idle_time()
{
  return this->thread_idle_time_;
}

size_t
TAO_Dynamic_TP_POA_StrategyImpl::get_thread_stack_size()
{
  return this->thread_stack_size_;
}

TAO_END_VERSIONED_NAMESPACE_DECL