#ifndef _SSFILEDESCRIPTOR_H
#define _SSFILEDESCRIPTOR_H

// fopen perror fread fwrite feof fseek ferror fclose rewind scanf sscanf getchar scanf fscanf
#include <stdio.h>
// calloc free realloc malloc
#include <stdlib.h>
// strcpy strcmp strcat memcmp
#include <string.h>
// termios tcflush
#include <termios.h>
// nanosleep sleep
#include <time.h>
// tcflsuh read write close
#include <unistd.h>
// perror
#include <errno.h>
// open
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio_ext.h>
#include <math.h>

struct filedescriptor{
  int id;
  const char* FDpathname;
  int FDflags;
  mode_t FDmode;
  int FLflags;//access mode
  char* argp;
  char errcode[64];
  //Apontador de tipo funcao
  const char* (*GetFDpath)(struct filedescriptor* fd);
  ssize_t (*Write)(struct filedescriptor* fd, const void* buf, unsigned int count);
  int (*ID)(struct filedescriptor* fd);
  int (*Close)(struct filedescriptor* fd);
  off_t (*Setoffset)(struct filedescriptor* fd, off_t offset);
  off_t (*Setend)(struct filedescriptor* fd);
  off_t (*Setendoffset)(struct filedescriptor* fd, off_t offset);
  off_t (*Getpos)(struct filedescriptor* fd);
  ssize_t (*Read)(struct filedescriptor* fd, void* buf, unsigned int count);
  void (*SetDefault)(struct filedescriptor* fd);
  void (*SetFLflags)(struct filedescriptor* fd, int arg);
  void (*SetFDflags)(struct filedescriptor* fd, int arg);
  int (*GetFLflags)(struct filedescriptor* fd);
  int (*GetFDflags)(struct filedescriptor* fd);
  mode_t (*GetFDmode)(struct filedescriptor* fd);
  int (*Request)(struct filedescriptor* fd, int request, char* argp);
  off_t (*Rewind)(struct filedescriptor* fd);
  int (*SetOwner)(struct filedescriptor* fd, pid_t owner);
};

typedef struct filedescriptor filedescriptor;

struct filedescriptor* FileDescriptorCreate(const char* pathname, int flags, mode_t mode);

char* ReadConsole(FILE* stream);

unsigned int getnum(char* x);

#endif
