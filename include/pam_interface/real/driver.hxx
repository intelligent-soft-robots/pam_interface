
template<int NB_DOFS>
RealRobotDriver<NB_DOFS>::RealRobotDriver(const Configuration<NB_DOFS>& config)
  : Driver<NB_DOFS>(config)
{

  if(NB_DOFS!=4)
    {
      throw std::runtime_error("RealRobotDriver: only 4 dof PAM robots supported");
    }

}


template<int NB_DOFS>
std::string RealRobotDriver<NB_DOFS>::get_error()
{
  std::string s;
  return s;
}

template<int NB_DOFS>
void
RealRobotDriver<NB_DOFS>::initialize()
{
  // see pam_interface/real/factory.hpp
  this->hw_interface_ =
    four_dofs::get_interface<NB_DOFS>(this->config_);
  this->hw_interface_->init();
}
