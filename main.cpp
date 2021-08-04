#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include <cstring>  
#include <vector>
#include <sstream>
#include <map>
#include <string> 

using namespace std;
using namespace libconfig;

vector<int> ids;
int periodo = 0;
map <int, vector<string>>  lcs;
map <int, vector<string>> rois;

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int main(int argc, char **argv)
{
  Config cfg;

  try
  {
    cfg.readFile("config_cameras.cfg");
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file." << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return(EXIT_FAILURE);
  }

  /* -------------------------------------------------------------------*/

  vector<string> v, aux;
  try
  {
    string periodoMuestreo = cfg.lookup("periodoMuestreo");
    string camarasActivas = cfg.lookup("camarasActivas");

    //cout << "Periodo: " << periodoMuestreo << endl <<"Camaras " << camarasActivas << endl;
    v = split (camarasActivas, ',');
    //////Insercion en periodo//////
    periodo = stoi(periodoMuestreo);
    ////////////////////////////////
  }
  catch(const SettingNotFoundException &nfex)
  {
    cerr << "No 'periodoMuestreo' setting in configuration file." << endl;
  }

  const Setting& root = cfg.getRoot();
  for (auto camara_id : v){
    //////Insercion en ids[100]//////
    ids.push_back(stoi(camara_id));
    ////////////////////////////////
    try {
      const Setting &camaras = root["camaras"]["cam_"+camara_id];
      int count = camaras.getLength();
      for(int i = 0; i < count; ++i)
      {
        const Setting &camara = camaras[i];
        string lc, aforo;
        if(!(camara.lookupValue("lc", lc)
           && camara.lookupValue("aforo", aforo)))
        continue;
        //cout << setw(30) << lc << "  " << aforo << "  " << endl;
      
        //////Insercion maps//////
        aux = split (lc, ',');
        lcs.insert(pair<int, vector<string>>(stoi(camara_id), aux ));

        aux = split (aforo, ',');
        rois.insert(pair<int, vector<string>>(stoi(camara_id), aux));
        ////////////////////////////////
      }
      cout << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
      cerr << "No 'camaras' setting in configuration file." << endl;
    }
  }
  return(EXIT_SUCCESS);
}

// eof
