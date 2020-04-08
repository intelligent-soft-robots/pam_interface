
template<int NB_DOFS>
Interface<NB_DOFS>::Interface()
  : previous_state_(-1)
{
  desired_agonists_.fill(-1);
  desired_antagonists_.fill(-1);
}


template<int NB_DOFS>
RobotState<NB_DOFS> Interface<NB_DOFS>::get_state() 
{

  int sensor_iteration_ = read_sensor_iteration();
  if( sensor_iteration_==previous_state_.get_sensor_iteration() &&
      !previous_state_.get_id()<0 )
    {
      return previous_state_;
    }
  
  // interface is a friend of RobotState
  // so can directly write private members

  int control_iteration = read_control_iteration();
  int sensor_iteration = read_sensor_iteration();
  
  RobotState<NB_DOFS> state(control_iteration,sensor_iteration,time_now());

  int delta_time = sensor_iteration_-previous_state_.get_sensor_iteration();

  for(int dof=0;dof<NB_DOFS;dof++)
    {

      int encoder = read_encoder(dof);
      double angle = encoder_to_angle(dof,encoder);
      double velocity = ( angle-previous_state_.get_position(dof) )
	/ (static_cast<double>(delta_time)*10E-6);

      state.set_joint( dof,
		       read_pressure(dof,Sign::AGONIST),
		       read_pressure(dof,Sign::ANTAGONIST),
		       desired_agonists_[dof],
		       desired_antagonists_[dof],
		       angle,
		       velocity,
		       encoder,
		       is_reference_found(dof) );
	
    }


  previous_state_ = state;
  
  return state;
  
}
