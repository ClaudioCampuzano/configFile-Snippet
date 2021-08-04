#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <string.h>

/* This example reads the configuration file 'example.cfg' and displays
 * some of its contents.
 */

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char **argv)
{
  config_t cfg;
  config_setting_t *setting;
  const char *str;
  char *camara_id;
  int periodoMuestreo;
  

  config_init(&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "config_cameras.cfg"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
  /* -------------------------------------------------------------------*/
  if(config_lookup_int(&cfg, "periodoMuestreo", &periodoMuestreo))
    printf("Periodo: %d\n", periodoMuestreo);
  else
     fprintf(stderr, "No 'periodoMuestreo' setting in configuration file.\n");


  /* Obteniendo lista de camaras activas */
  if(config_lookup_string(&cfg, "camarasActivas", &str))
  {
    //printf("Camaras activas: %s\n\n", str);
    camara_id = strtok(strdup(str), ",");
    while(camara_id != NULL)
    {
      char * nombre_cam =  concat("camaras.cam_",camara_id);
      //printf( "cam_%s \n", camara_id);

      setting = config_lookup(&cfg, nombre_cam);
      if(setting != NULL)
      {
        int count = config_setting_length(setting);
        int i;
        for(i = 0; i < count; ++i)
        {
           config_setting_t *info_camara = config_setting_get_elem(setting, i);
           const char *lc, *aforo;

           if(!(config_setting_lookup_string(info_camara, "lc", &lc)
             && config_setting_lookup_string(info_camara, "aforo", &aforo)))
           continue;
           printf("%s -> %-30s  %-30s", nombre_cam,lc, aforo);
        }
        putchar('\n');
      }
      camara_id = strtok(NULL, ",");
    }
  }else
    fprintf(stderr, "No 'camarasActivas' setting in configuration file.\n");

  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}

/* eof */
