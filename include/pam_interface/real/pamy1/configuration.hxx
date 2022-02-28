
template <int NB_DOFS>
Pamy1DefaultConfiguration<NB_DOFS>::Pamy1DefaultConfiguration()
    : JsonConfiguration<NB_DOFS>(PAMY1_DEFAULT_CONFIG_FILE_PATH)
{
}

template <int NB_DOFS>
std::string Pamy1DefaultConfiguration<NB_DOFS>::get_default_configuration_path()
{
    return std::string(PAMY1_DEFAULT_CONFIG_FILE_PATH);
}
