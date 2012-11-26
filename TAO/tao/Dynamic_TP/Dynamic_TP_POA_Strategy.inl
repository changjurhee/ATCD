// -*- C++ -*-
//
// $Id$

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
/// Constructor.
TAO_Dynamic_TP_POA_Strategy::TAO_Dynamic_TP_POA_Strategy(ACE_CString tp_config_name,
                                                         TAO_Dynamic_TP_POA_StrategyImpl * dynamic_strategy,
                                                         bool     /*serialize_servants */)
{
  this->dynamic_tp_config_name_ = tp_config_name;
  this->dtp_strategy_impl_ = dynamic_strategy;
}

ACE_INLINE
TAO_Dynamic_TP_POA_Strategy::TAO_Dynamic_TP_POA_Strategy(TAO_DTP_Definition * tp_config_name,
                                                         bool     serialize_servants)
{
  ACE_NEW(this->dtp_strategy_impl_,
          TAO_Dynamic_TP_POA_StrategyImpl(tp_config_name,serialize_servants));
}

ACE_INLINE
void
TAO_Dynamic_TP_POA_Strategy::set_num_threads(Thread_Counter num_threads)
{
  // Simple Mutator.  Assumes that num_threads > 0.
  this->num_threads_ = num_threads;
}

ACE_INLINE
ACE_CString
TAO_Dynamic_TP_POA_Strategy::get_tp_config()
{
  return this->dynamic_tp_config_name_;
}


ACE_INLINE
void
TAO_Dynamic_TP_POA_Strategy::set_servant_serialization(bool serialize_servants)
{
  // Simple Mutator.
  this->serialize_servants_ = serialize_servants;
}


TAO_END_VERSIONED_NAMESPACE_DECL