
template<int NB_DOFS>
Driver<NB_DOFS>::Driver(const Configuration<NB_DOFS>& config)
  : robot_interfaces::RobotDriver< PressureAction<2*NB_DOFS>,
                                   RobotState<NB_DOFS> >(),
  hw_interface_(nullptr),
  config_(config)
{}


template<int NB_DOFS>
Driver<NB_DOFS>::~Driver()
{}

template<int NB_DOFS>
void Driver<NB_DOFS>::initialize(){}


template<int NB_DOFS>
PressureAction<2*NB_DOFS>
Driver<NB_DOFS>::apply_action(const PressureAction<2*NB_DOFS> &desired_action)
{
  PressureAction<2*NB_DOFS> applied;
  int dof,desired;
  for(unsigned int actuator=0;actuator<2*NB_DOFS;actuator++)
    {
      dof = actuator/2;
      int pressure  = desired_action.get(actuator);
      if(actuator%2==0)
	{
	  desired = hw_interface_->set_pressure(dof,
						Sign::AGONIST,
						pressure);
	}
      else
	{
	  desired = hw_interface_->set_pressure(dof,
						Sign::ANTAGONIST,
						pressure);
	}
      applied.set( actuator,
		   desired );
    }
  return applied;
}


template<int NB_DOFS>
RobotState<NB_DOFS> Driver<NB_DOFS>::get_latest_observation()
{
  return hw_interface_->get_state();
}


template<int NB_DOFS>
void Driver<NB_DOFS>::shutdown()
{
  hw_interface_->terminate();
}
