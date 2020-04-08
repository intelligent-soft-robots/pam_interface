#include "pam_robot/configuration.hpp"



namespace pam_robot {


  Configuration::Configuration(){}

  Configuration::Configuration(std::string segment_id)
  {
    shared_memory::deserialize(segment_id,
			       segment_id+"_configuration",
			       *this);

  }

  Configuration::~Configuration(){}

  void write(const std::string& segment_id)
  {
    shared_memory::serialize(segment_id,
			     segment_id+"_configuration",
			     *this);
  }

  void Configuration::print() const {

    std::cout << "\n";
    std::cout << "degrees of freedom: " << NB_DOFS << "\n";
    std::cout << "control period: " << control_period << "\n";
    std::cout << "sensor period: " << sensor_period << "\n";
    std::cout << "server frequency: " << server_frequency << "\n";
    std::cout << "minimum and maximum pressures for agonists(PLUS): \n";
    for(int i_dof=0;i_dof<NB_DOFS;i_dof++){
      std::cout << "\t"
		<< min_pressures_ago[i_dof]
		<< "\t" << max_pressures_ago[i_dof] << "\n";
    }
    std::cout << "minimum and maximum pressures for antagonists(MINUS): \n";
    for(int i_dof=0;i_dof<nb_dofs;i_dof++){
      std::cout << "\t"
		<< min_pressures_antago[i_dof] << "\t"
		<< max_pressures_antago[i_dof] << "\n";
    }
    std::cout << "print command history: " << print_command_history << "\n";
    std::cout << "\n";

  }

  template<typename T>
  T json_get(std::string file_path,
	     std::string key,
	     json_helper::Jsonhelper &jh){
    try {
      return jh.j[key].get<T>();
    } catch (...){
      std::stringstream ss;
      ss << "Failed to read key " << key << " from " << file_path << "\n";
      std::string error = ss.str();
      throw error;
    }
  }


  Json_configuration::Json_configuration(const std::string &file_path)
    : Configuration() {

      this->message = file_path;

      json_helper::Jsonhelper jh;
      try {
        jh.parse(file_path);
      } catch(...){
        std::stringstream ss;
        ss << "Failed to read JSON file " << file_path << "\n";
        std::string error = ss.str();
        throw error;
      }

      this->print_command_history = jh.j["print_command_history"].get<bool>();
      this->nb_dofs = jh.j["nb_dofs"].get<int>();
      this->control_period = jh.j["control_period"].get<int>();
      this->sensor_period = jh.j["sensor_period"].get<int>();
      this->server_frequency = jh.j["server_frequency"].get<int>();

      this->min_pressures_ago = new int[nb_dofs];
      this->max_pressures_ago = new int[nb_dofs];
      this->min_pressures_antago = new int[nb_dofs];
      this->max_pressures_antago = new int[nb_dofs];

      std::string items[4] = {"min_pressures_ago",
  			    "max_pressures_ago",
            "min_pressures_antago",
        		"max_pressures_antago"};

      int* arrays[4] = {this->min_pressures_ago,
  		      this->max_pressures_ago,
            this->min_pressures_antago,
        		this->max_pressures_antago};


      for(int i=0;i<4;i++){
        try {
          // std::cout << "TEST jh.j["<<items[i]<<"]= ";
  	       std::vector<int>  tmp;
           jh.json2vector(items[i],tmp);
           // std::cout<<tmp[0]<<std::endl;
           for (int i_dof=0;i_dof<this->nb_dofs;i_dof++){
          	  arrays[i][i_dof] = tmp[i_dof];
           }
        } catch(...) {
        	std::stringstream ss;
        	ss << "Failed to read key " << items[i] << " from " << file_path << "\n";
        	std::string error = ss.str();
        	throw error;
        }
      }
  }



  Default_configuration::Default_configuration()
    : Json_configuration(PAM_DEFAULT_CONFIG_FILE) {}

}
