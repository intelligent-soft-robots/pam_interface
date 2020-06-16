
template<int NB_DOFS>
RealRobotDriver<NB_DOFS>::RealRobotDriver(const Configuration<NB_DOFS>& config)
  : Driver<NB_DOFS>(config)
{

  if(NB_DOFS!=4)
    {
      throw std::runtime_error("RealRobotDriver: only 4 dof PAM robots supported");
    }

  // see pam_interface/real/factory.hpp
  this->hw_interface_ =
    four_dofs::get_interface<NB_DOFS>(this->config_);
  this->hw_interface_->init();

}

