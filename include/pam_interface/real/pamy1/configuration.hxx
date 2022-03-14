
template <int NB_DOFS>
Pamy1DefaultConfiguration<NB_DOFS>::Pamy1DefaultConfiguration()
    : JsonConfiguration<NB_DOFS>(get_default_configuration_path())
{
}

template <int NB_DOFS>
std::string Pamy1DefaultConfiguration<NB_DOFS>::get_default_configuration_path()
{
  std::string parent_folder = pam_configuration::get_path().string();
  return parent_folder+std::string(PAMY1_JSON_RELATIVE_PATH);
}
