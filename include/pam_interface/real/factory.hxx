

template<int NB_DOFS>
std::shared_ptr<Interface<NB_DOFS>>
get_interface(const Configuration<NB_DOFS>& config)
{

  static_assert(NB_DOFS==4,
		"pam_interface.real.factory: only 4 dofs robots supported");
  
  interface_4dofs_g =
    std::make_shared<pam_interface::RealRobotInterface<NB_DOFS>>(config);
      
  return interface_4dofs_g;
  
}
