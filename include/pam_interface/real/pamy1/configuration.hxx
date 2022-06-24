
template <int NB_DOFS>
Pamy1DefaultConfiguration<NB_DOFS>::Pamy1DefaultConfiguration(bool simulation)
    : JsonConfiguration<NB_DOFS>(get_default_configuration_path(simulation))
{
}

template <int NB_DOFS>
std::string Pamy1DefaultConfiguration<NB_DOFS>::get_default_configuration_path(
    bool simulation)
{
    if (simulation)
    {
        return (pam_configuration::get_path() /
                std::string(PAMY1_SIM_JSON_RELATIVE_PATH))
            .string();
    }
    else
    {
        return (pam_configuration::get_path() /
                std::string(PAMY1_REAL_JSON_RELATIVE_PATH))
            .string();
    }
}
