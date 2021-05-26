
template <int NB_DOFS>
Configuration<NB_DOFS>::Configuration()
{
}

template <int NB_DOFS>
Configuration<NB_DOFS>::~Configuration()
{
}

template <int NB_DOFS>
void Configuration<NB_DOFS>::print() const
{
    std::cout << "\tdegrees of freedom: " << NB_DOFS << "\n";
    std::cout << "\tcontrol period: " << control_period << "\n";
    std::cout << "\tsensor period: " << sensor_period << "\n";
    std::cout << "\tserver frequency: " << server_frequency << "\n";
    std::cout << "\tminimum and maximum pressures for agonists: \n";
    for (int i_dof = 0; i_dof < NB_DOFS; i_dof++)
    {
        std::cout << "\t\t" << min_pressures_ago[i_dof] << "\t"
                  << max_pressures_ago[i_dof] << "\n";
    }
    std::cout << "\tminimum and maximum pressures for antagonists: \n";
    for (int i_dof = 0; i_dof < NB_DOFS; i_dof++)
    {
        std::cout << "\t\t" << min_pressures_antago[i_dof] << "\t"
                  << max_pressures_antago[i_dof] << "\n";
    }
    std::cout << "\n";
}

template <int NB_DOFS>
int Configuration<NB_DOFS>::min_pressure(int dof, Sign sign)
{
    if (sign == Sign::AGONIST)
    {
        return min_pressures_ago[dof];
    }
    return min_pressures_antago[dof];
}

template <int NB_DOFS>
int Configuration<NB_DOFS>::max_pressure(int dof, Sign sign)
{
    if (sign == Sign::AGONIST)
    {
        return max_pressures_ago[dof];
    }
    return max_pressures_antago[dof];
}

template <int NB_DOFS>
int Configuration<NB_DOFS>::min_pressure()
{
    int min = std::numeric_limits<int>::max();
    for (Sign sign : signs)
    {
        for (int dof = 0; dof < NB_DOFS; dof++)
        {
            int min_ = min_pressure(dof, sign);
            if (min_ < min)
            {
                min = min_;
            }
        }
    }
    return min;
}

template <int NB_DOFS>
int Configuration<NB_DOFS>::max_pressure()
{
    int max = std::numeric_limits<int>::max();
    for (Sign sign : signs)
    {
        for (int dof = 0; dof < NB_DOFS; dof++)
        {
            int max_ = max_pressure(dof, sign);
            if (max_ < max)
            {
                max = max_;
            }
        }
    }
    return max;
}

template <typename T>
T json_get(std::string file_path, std::string key, json_helper::Jsonhelper &jh)
{
    try
    {
        return jh.j[key].get<T>();
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "Failed to read key " << key << " from " << file_path << "\n";
        std::string error = ss.str();
        throw error;
    }
}

template <int NB_DOFS>
JsonConfiguration<NB_DOFS>::JsonConfiguration(const std::string &file_path)
    : Configuration<NB_DOFS>()
{
    json_helper::Jsonhelper jh;
    try
    {
        jh.parse(file_path);
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "Failed to read JSON file " << file_path << "\n";
        std::string error = ss.str();
        throw error;
    }

    int nb_dofs = jh.j["nb_dofs"].get<int>();

    if (nb_dofs != NB_DOFS)
    {
        std::stringstream ss;
        ss << "fail to construct " << NB_DOFS << " dofs robot"
           << " from " << file_path << " which specifies " << NB_DOFS
           << " dofs";
        std::string error = ss.str();
        throw std::runtime_error(error);
    }

    this->control_period = jh.j["control_period"].get<int>();
    this->sensor_period = jh.j["sensor_period"].get<int>();
    this->server_frequency = jh.j["server_frequency"].get<int>();

    std::string items[4] = {"min_pressures_ago",
                            "max_pressures_ago",
                            "min_pressures_antago",
                            "max_pressures_antago"};

    std::array<int, NB_DOFS> *arrays[4] = {&(this->min_pressures_ago),
                                           &(this->max_pressures_ago),
                                           &(this->min_pressures_antago),
                                           &(this->max_pressures_antago)};

    for (int i = 0; i < 4; i++)
    {
        try
        {
            std::vector<int> tmp;
            jh.json2vector(items[i], tmp);
            for (int i_dof = 0; i_dof < NB_DOFS; i_dof++)
            {
                (*arrays[i])[i_dof] = tmp[i_dof];
            }
        }
        catch (...)
        {
            std::stringstream ss;
            ss << "Failed to read key " << items[i] << " from " << file_path
               << "\n";
            std::string error = ss.str();
            throw error;
        }
    }
}

template <int NB_DOFS>
DefaultConfiguration<NB_DOFS>::DefaultConfiguration()
    : JsonConfiguration<NB_DOFS>(PAM_DEFAULT_CONFIG_FILE_PATH)
{
}

template <int NB_DOFS>
std::string DefaultConfiguration<NB_DOFS>::get_default_configuration_path()
{
    return std::string(PAM_DEFAULT_CONFIG_FILE_PATH);
}
