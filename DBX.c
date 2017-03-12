#include "DBX.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// From Jason
char * Load_Read_Data(HITS_DB *db) {
  FILE   *bases  = (FILE *) db->bases;
  struct stat sbuf;
  char *data;

  bases = fopen(Catenate(db->path,"","",".bps"),"r");
  if (bases == NULL) EXIT(1);
  stat(Catenate(db->path,"","",".bps"), &sbuf);
  data = (char *) malloc(sbuf.st_size);
  if (data == NULL) EXIT(1);
  fread(data, sbuf.st_size, 1, bases);
  fclose(bases);
  return(data);
}

// From Jason
int Load_Read_From_RAM(HITS_DB *db, char *data, int i, char *read, int ascii) {
  int64      off;
  int        len, clen;
  HITS_READ *r = db->reads;

  if (i >= db->nreads) { EXIT(1); }

  off = r[i].boff;
  len = r[i].rlen;
  clen = COMPRESSED_LEN(len);
  if (clen > 0) { memcpy(read, data + off, clen); } //fread(read,clen,1,bases)
  Uncompress_Read(len, read);
  if (ascii == 1)
    { Lower_Read(read);
      read[-1] = '\0';
    }
  else if (ascii == 2)
    { Upper_Read(read);
      read[-1] = '\0';
    }
  else
    read[-1] = 4;
  return (0);
}
