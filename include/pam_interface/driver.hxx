
template<int NB_DOFS>
Driver<NB_DOFS>::Driver(const Configuration<NB_DOFS>& config)
  : hw_interface_(nullptr),
    config_(config)
{}


template<int NB_DOFS>
Driver<NB_DOFS>::~Driver()
{
  hw_interface_->terminate();
}

template<int NB_DOFS>
void
Driver<NB_DOFS>::in(const PressureAction<2*NB_DOFS> &pressure_action)
{
  int dof;
  for(unsigned int actuator=0;actuator<2*NB_DOFS;actuator++)
    {
      dof = actuator/2;
      int pressure  = pressure_action.get(actuator);
      if(actuator%2==0)
	{
	  hw_interface_->set_pressure(dof,
				      Sign::AGONIST,
				      pressure);
	}
      else
	{
	  hw_interface_->set_pressure(dof,
				      Sign::ANTAGONIST,
				      pressure);
	}
    }
}


template<int NB_DOFS>
RobotState<NB_DOFS> Driver<NB_DOFS>::out()
{
  return hw_interface_->get_state();
}


