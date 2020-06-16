
template<int NB_DOFS>
DummyRobotDriver<NB_DOFS>::DummyRobotDriver(const Configuration<NB_DOFS>& config)
  : Driver<NB_DOFS>(config)
{
  this->hw_interface_ =
    std::make_shared<DummyInterface<NB_DOFS>>(this->config_);
}
