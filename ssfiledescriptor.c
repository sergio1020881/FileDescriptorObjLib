#include "ssfiledescriptor.h"
//
struct filedescriptor* FileDescriptorCreate(const char* pathname, int flags, mode_t mode)
{
  //PROTOTIPOS
  const char* filedescriptorGetFDpath(struct filedescriptor* fd);
  ssize_t filedescriptorWrite(struct filedescriptor* fd, const void* buf, unsigned int count);
  int filedescriptorID(struct filedescriptor* fd);
  int filedescriptorClose(struct filedescriptor* fd);
  off_t filedescriptorSetoffset(struct filedescriptor* fd, off_t offset);
  off_t filedescriptorSetend(struct filedescriptor* fd);
  off_t filedescriptorSetendoffset(struct filedescriptor* fd, off_t offset);
  off_t filedescriptorGetpos(struct filedescriptor* fd);
  ssize_t filedescriptorRead(struct filedescriptor* fd, void* buf, unsigned int count);
  void filedescriptorSetDefault(struct filedescriptor* fd);
  void filedescriptorSetFLflags(struct filedescriptor* fd, int arg);
  void filedescriptorSetFDflags(struct filedescriptor* fd, int arg);
  int filedescriptorGetFLflags(struct filedescriptor* fd);
  int filedescriptorGetFDflags(struct filedescriptor* fd);
  mode_t filedescriptorGetFDmode(struct filedescriptor* fd);
  int filedescriptorRequest(struct filedescriptor* fd, int request, char* argp);
  off_t filedescriptorRewind(struct filedescriptor* fd);
  int filedescriptorSetOwner(struct filedescriptor* fd, pid_t owner);
  //ALLOCAÇÂO MEMORIA PARA Estrutura
  struct filedescriptor* fd;
  fd=(struct filedescriptor*)calloc(1,sizeof(struct filedescriptor));
  if(fd == NULL){
	perror("FileDescriptorCreate at calloc");
  }
  //Variables
  errno=0;
  fd->FDpathname=pathname;
  fd->FDflags=flags;
  fd->FDmode=mode;
  sprintf(fd->errcode,"None errno: %d\n", errno);
  //Direccionar apontadores para PROTOTIPOS
  fd->GetFDpath=filedescriptorGetFDpath;
  fd->Write=filedescriptorWrite;
  fd->ID=filedescriptorID;
  fd->Close=filedescriptorClose;
  fd->Setoffset=filedescriptorSetoffset;
  fd->Setend=filedescriptorSetend;
  fd->Setendoffset=filedescriptorSetendoffset;
  fd->Getpos=filedescriptorGetpos;
  fd->Read=filedescriptorRead;
  fd->SetDefault=filedescriptorSetDefault;
  fd->SetFLflags=filedescriptorSetFLflags;
  fd->SetFDflags=filedescriptorSetFDflags;
  fd->GetFLflags=filedescriptorGetFLflags;
  fd->GetFDflags=filedescriptorGetFDflags;
  fd->GetFDmode=filedescriptorGetFDmode;
  fd->Request=filedescriptorRequest;
  fd->Rewind=filedescriptorRewind;
  fd->SetOwner=filedescriptorSetOwner;
  //
  fd->id = open(fd->FDpathname, fd->FDflags, fd->FDmode);
  if(fd->id < 0){
	perror("FileDescriptorCreate at open");
	sprintf(fd->errcode,"FileDescriptorCreate at open errno: %d\n", errno);
	free(fd);
  }else if(fcntl(fd->id,F_SETFL,0)<0){
    perror("FileDescriptorCreate at fcntl");
	sprintf(fd->errcode,"FileDescriptorCreate at fcntl errno: %d\n", errno);
  }else
    fd->FLflags=0;
  return fd;
}
//
int filedescriptorID(struct filedescriptor* fd)
{ 
  int RETURN;
  RETURN=fd->id;
  return RETURN;
}
//
int filedescriptorClose(struct filedescriptor* fd)
{
  int RETURN = close(fd->id);
  free(fd);
  if(RETURN<0){
    perror("Close at close");
    sprintf(fd->errcode,"Close at close errno: %d\n", errno);
    RETURN = -1;
  }
  return RETURN;
}
//
const char* filedescriptorGetFDpath(struct filedescriptor* fd)
{ 
  const char* RETURN;
  RETURN=fd->FDpathname;
  return RETURN;
}
//
mode_t filedescriptorGetFDmode(struct filedescriptor* fd)
{
  mode_t RETURN;
  RETURN=fd->FDmode;
  return RETURN;
}
//
off_t filedescriptorSetoffset(struct filedescriptor* fd, off_t offset)
{
  off_t RETURN=lseek(fd->id,offset,SEEK_SET);
  if(RETURN<0){
	perror("Setoffset at lseek");
	sprintf(fd->errcode,"Setoffset at lseek errno: %d\n", errno);
    RETURN=-1;
  }
  return RETURN;
}
//
off_t filedescriptorRewind(struct filedescriptor* fd)
{
  off_t pos,rewind,RETURN;
  pos=lseek(fd->id,0,SEEK_CUR);
  if(pos<0){
	perror("Rewind at lseek");
	sprintf(fd->errcode,"Rewind at lseek errno: %d\n", errno);
    RETURN=-1;
  }else{
    rewind=lseek(fd->id,-pos,SEEK_CUR);
    if(rewind<0){
	  perror("Rewind at lseek");
	  sprintf(fd->errcode,"Rewind at lseek errno: %d\n", errno);
      RETURN=-1;
    }else
      RETURN=rewind;
  }
  return RETURN;
}
//
off_t filedescriptorSetend(struct filedescriptor* fd)
{
  off_t RETURN=lseek(fd->id,0,SEEK_END);
  if(RETURN<0){
	perror("Setend at lseek");
	sprintf(fd->errcode,"Setend at lseek errno: %d\n", errno);
    RETURN=-1;
  }
  return RETURN;
}
//
off_t filedescriptorSetendoffset(struct filedescriptor* fd, off_t offset)
{
  off_t RETURN=lseek(fd->id,offset,SEEK_END);
  if(RETURN<0){
	perror("Setendoffset at lseek");
	sprintf(fd->errcode,"Setendoffset at lseek errno: %d\n", errno);
    RETURN=-1;
  }
  return RETURN;
}
//
off_t filedescriptorGetpos(struct filedescriptor* fd)
{
  off_t RETURN=lseek(fd->id,0,SEEK_CUR);
  if(RETURN<0){
	perror("Getpos at lseek");
	sprintf(fd->errcode,"Getpos at lseek errno: %d\n", errno);
    RETURN=-1;
  }
  return RETURN;
}
//
ssize_t filedescriptorWrite(struct filedescriptor* fd,const void* buf, size_t count)
{
  ssize_t RETURN; 
  RETURN=write(fd->id,buf,count);
  if(RETURN<0){
    perror("Write at write");
    sprintf(fd->errcode,"Write at write errno: %d\n", errno);
    RETURN=-1;
  }	
  return RETURN;
}
//
ssize_t filedescriptorRead(struct filedescriptor* fd, void* buf, size_t count)
{
  ssize_t RETURN=0; 
  RETURN=read(fd->id,buf,count);
  if(RETURN<0){
    perror("Read at read");
    sprintf(fd->errcode,"Read at read errno: %d\n", errno);
    RETURN=-1;
  }	
  return RETURN;
}
//
void filedescriptorSetDefault(struct filedescriptor* fd)
{
  int var;
  var=O_RDWR | O_NOCTTY | O_NDELAY;
  if(fcntl(fd->id,F_SETFD,var)<0){
    perror("SetDefault at fcntl");
    sprintf(fd->errcode,"SetDefault at fcntl errno: %d\n", errno);
  }else
    fd->FDflags=var;
  var=FNDELAY;
  if(fcntl(fd->id,F_SETFL,var)<0){
    perror("SetDefault at fcntl");
    sprintf(fd->errcode,"SetDefault at fcntl errno: %d\n", errno);
  }else
    fd->FLflags=O_NONBLOCK;
}
//
void filedescriptorSetFLflags(struct filedescriptor* fd, int arg)
{
  if(fcntl(fd->id,F_SETFL,arg)<0){
    perror("SetFLflags at fcntl");
    sprintf(fd->errcode,"SetFLflags at fcntl errno: %d\n", errno);
  }else
    fd->FLflags=arg;
}
//
void filedescriptorSetFDflags(struct filedescriptor* fd, int arg)
{
  if(fcntl(fd->id,F_SETFD,arg)<0){
    perror("SetFDflags at fcntl");
    sprintf(fd->errcode,"SetFDflags at fcntl errno: %d\n", errno);
  }else
    fd->FDflags=arg;
}
//
int filedescriptorGetFLflags(struct filedescriptor* fd)
{
	int RETURN;
	RETURN=fd->FLflags;
    return RETURN;
}
//
int filedescriptorGetFDflags(struct filedescriptor* fd)
{
  int RETURN;
  RETURN=fd->FDflags;
  return RETURN;
}
//
int filedescriptorRequest(struct filedescriptor* fd, int request, char* argp)
{
  int RETURN;
  fd->argp=argp;
  RETURN=ioctl(fd->id,request,fd->argp);
  if(RETURN<0)
    perror("Request at ioctl");
    sprintf(fd->errcode,"Request at ioctl errno: %d\n", errno);
  return RETURN;
}

int filedescriptorSetOwner(struct filedescriptor* fd, pid_t owner){
  int RETURN;
  RETURN=fcntl(fd->id, F_SETOWN, owner);
  if (RETURN < 0){
    perror("Owner at Unable to set process to owner");
  }
  return RETURN;
}
/***ftos***/
char* ftos(FILE* stream)
{
  int i, NBytes;
  char caracter;
  char* value=NULL;
  for(i=0, NBytes=4; (caracter=getc(stream)) != EOF; i++){
    if((i==0) | (i==NBytes)){
      NBytes=2*NBytes;
      value=(char*)realloc(value, NBytes*sizeof(char));
      if(value==NULL){
        perror("ReadConsole at calloc");
        break;
      }
    }
    *(value+i)=caracter;
  }
  return value;
}
//fltos
char* fltos(FILE* stream)
{
  int i, NBytes;
  char caracter;
  char* value=NULL;
  for(i=0, NBytes=4; (caracter=getc(stream)) != EOF; i++){
    if((i==0) | (i==NBytes)){
      NBytes=2*NBytes;
      value=(char*)realloc(value, NBytes*sizeof(char));
      if(value==NULL){
        perror("ReadConsole at calloc");
        break;
      }
    }
    *(value+i)=caracter;
    if(caracter=='\n'){
      *(value+i)='\0';
      break;
    }
  }
  return value;
}
/***getnum***/
unsigned int getnum(char* x)
{
  unsigned int RETURN;
  unsigned int value;
  unsigned int n;
  errno=0;
  n=sscanf(x,"%d",&value);
  if(n==1){
    RETURN=value;
  }else if(errno != 0){
    perror("getnum at sscanf");
    RETURN=0;
  }else{
    RETURN=0;
  }
  return RETURN;
}
/**/
int strtotok(char* line,char* token[],const char* parser)
{
  int i;
  char* str;
  str=calloc(strlen(line),sizeof(char));
  for (i = 0, strcpy(str,line); ; i++, str = NULL) {
    token[i] = strtok(str, parser);
    if (token[i] == NULL)
      break;
    printf("%d: %s\n", i, token[i]);
  }
  free(str);
  return i;
}
/**/
