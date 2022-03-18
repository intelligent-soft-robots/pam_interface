
template <int NB_DOFS>
Pamy1DefaultConfiguration<NB_DOFS>::Pamy1DefaultConfiguration()
    : JsonConfiguration<NB_DOFS>(get_default_configuration_path())
{
}

template <int NB_DOFS>
std::string Pamy1DefaultConfiguration<NB_DOFS>::get_default_configuration_path()
{
  return ( pam_configuration::get_path() / std::string(PAMY1_JSON_RELATIVE_PATH) ).string();
}
