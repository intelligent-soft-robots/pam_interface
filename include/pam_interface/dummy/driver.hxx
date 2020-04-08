
template<int NB_DOFS>
DummyRobotDriver<NB_DOFS>::DummyRobotDriver(const Configuration<NB_DOFS>& config)
  : Driver<NB_DOFS>(config)
{}

template<int NB_DOFS>
std::string DummyRobotDriver<NB_DOFS>::get_error()
{
  std::string s;
  return s;
}


template<int NB_DOFS>
void DummyRobotDriver<NB_DOFS>::initialize()
{
  this->hw_interface_ =
    std::make_shared<DummyInterface<NB_DOFS>>(this->config_);
}
