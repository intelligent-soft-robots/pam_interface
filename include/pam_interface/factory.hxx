
template<int NB_DOFS>
std::map<int,typename Factory<NB_DOFS>::DummyRobotPtr> Factory<NB_DOFS>::dummy_robots;

template<int NB_DOFS>
std::map<int,typename Factory<NB_DOFS>::RealRobotPtr> Factory<NB_DOFS>::real_robots;


template <int NB_DOFS>
template<typename A, typename APtr>
APtr Factory<NB_DOFS>::create_robot(std::map<int,APtr> &robots,
				    int id,
				    const Configuration<NB_DOFS>& config)
{

  double max_action_duration_s =
    std::numeric_limits<double>::infinity();
  double max_inter_action_duration_s =
    std::numeric_limits<double>::infinity();
  
  // A in an instance if robot_interfaces::Robot<Action,Observation,Driver>
  // with Action = pam_interface::PressureAction
  //      Observation = pam_interface::RobotState
  //      Driver = pam_interface::DummyDriver or pam_interface::RealDriver
  APtr robot_ptr =
    std::make_shared<A>(max_action_duration_s,
			max_inter_action_duration_s,
			config);
  robot_ptr->initialize();
  
  robots.insert(std::make_pair(id, robot_ptr));
  
  return robot_ptr;
}

template <int NB_DOFS>
template<typename A, typename APtr>
bool Factory<NB_DOFS>::exists(std::map<int,APtr> &robots, int id)
{
  
  typename std::map<int,APtr>::iterator iter(robots.lower_bound(id));
  if (iter == robots.end() || id < iter->first)
    {
      return false;
    }
  return true;
}

template <int NB_DOFS>
template<typename A, typename APtr>
APtr Factory<NB_DOFS>::get_robot(std::map<int,APtr> &robots, int id)
{
  
  typename std::map<int,APtr>::iterator iter(robots.lower_bound(id));

  if (iter == robots.end() || id < iter->first)
    {
      return nullptr;
    }
  
  else
    {
      return iter->second;
    }
  
}

template <int NB_DOFS>
typename Factory<NB_DOFS>::DummyRobotPtr
Factory<NB_DOFS>::create_dummy(int id, const Configuration<NB_DOFS>& config)
{
  if(exists<Factory<NB_DOFS>::DummyRobot,
     Factory<NB_DOFS>::DummyRobotPtr>(Factory<NB_DOFS>::dummy_robots,
				      id))
    {
      throw std::runtime_error("pam_interface::Factory::get_dummy: robot of this id already exists");
    }
  
  return create_robot<Factory<NB_DOFS>::DummyRobot,
		      Factory<NB_DOFS>::DummyRobotPtr>(Factory<NB_DOFS>::dummy_robots,
						       id,
						       config);
}

template <int NB_DOFS>
typename Factory<NB_DOFS>::RealRobotPtr
Factory<NB_DOFS>::create_real(int id, const Configuration<NB_DOFS>& config)
{
  if(exists<Factory<NB_DOFS>::RealRobot,
     Factory<NB_DOFS>::RealRobotPtr>(Factory<NB_DOFS>::real_robots,
				     id))
    {
      throw std::runtime_error("pam_interface::Factory::get_real: robot of this id already exists");
    }

  return create_robot<Factory<NB_DOFS>::RealRobot,
		      Factory<NB_DOFS>::RealRobotPtr>(Factory<NB_DOFS>::real_robots,
						      id,
						      config);
}

template <int NB_DOFS>
typename Factory<NB_DOFS>::DummyRobotPtr
Factory<NB_DOFS>::get_dummy(int id)
{
  typename Factory<NB_DOFS>::DummyRobotPtr robot =
    get_robot<Factory<NB_DOFS>::DummyRobot,
	      Factory<NB_DOFS>::DummyRobotPtr>(Factory<NB_DOFS>::dummy_robots,
					       id);
  if(robot==nullptr)
    {
      throw std::runtime_error("pam_interface::Factory::get_dummy: no robot of this id has been created");
    }

  return robot;
}

template <int NB_DOFS>
typename Factory<NB_DOFS>::RealRobotPtr
Factory<NB_DOFS>::get_real(int id)
{
  typename Factory<NB_DOFS>::RealRobotPtr robot =
    get_robot<Factory<NB_DOFS>::RealRobot,
	      Factory<NB_DOFS>::RealRobotPtr>(Factory<NB_DOFS>::real_robots,
					       id);
  if(robot==nullptr)
    {
      throw std::runtime_error("pam_interface::Factory::get_real: no robot of this id has been created");
    }

  return robot;
}

