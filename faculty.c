#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
bool login_faculty(int client_socket,int id,char* password)
{
    printf("%d",id);
    printf("%s",password);
    int file=open("Faculty.txt",O_RDONLY);
    struct facultyDetail faculty;
    ssize_t read_result;
    int found=0;

    //reading file and checking if id and passwords match
    while(read(file,&faculty,sizeof(struct facultyDetail)))
    {
        if(faculty.id==id)
        {
           if(strcmp(faculty.password,password)==0)
           {
            found=1;
            break;
           }
        }
    }
    close(file);
    return found;    
}
void add_course(int client_socket,int id)
{
    int fd=open("course.txt",O_RDWR|O_CREAT,0777);
    struct CourseDetail course;
    memset(&course,0,sizeof(course));
    char buff[30];
   
    struct stat file_info;
    fstat(fd, &file_info);

    if(file_info.st_size != 0){
        lseek(fd,-(sizeof(struct CourseDetail)),SEEK_END);
        struct CourseDetail stucpy;
        read(fd,&stucpy,sizeof(struct CourseDetail));
        course.id = stucpy.id + 1;
    }
    else{
       course.id= 1;
    }

    //setting faculty id as the id of faculty logged in and adding the course
     course.faculty_id=id;

    char text1[]="enter course name:";
    send(client_socket,text1,strlen(text1),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(course.name,buff);
    memset(&buff,0,sizeof(buff));

    char text2[]="enter department name:";
    send(client_socket,text2,strlen(text2),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(course.department,buff);
    memset(&buff,0,sizeof(buff));

    char text3[]="enter available seats:";
    send(client_socket,text3,strlen(text3),0);
    recv(client_socket,&buff,sizeof(buff),0);
    course.seat=atoi(buff);
    course.max_seats=atoi(buff);
    // strcpy(course.seat,buff);
    memset(&buff,0,sizeof(buff));

    char text4[]="enter course credit:";
    send(client_socket,text4,strlen(text4),0);
    recv(client_socket,&buff,sizeof(buff),0);
    course.credit=atoi(buff);
    // strcpy(course.credit,buff);
    memset(&buff,0,sizeof(buff));

    lseek(fd,0,SEEK_END);
    write(fd,&course,sizeof(struct CourseDetail));

    printf("Id=%d\n",course.id);
    printf("name=%s\n",course.name);
    printf("department=%s\n",course.department);
    printf("seats=%d\n",course.seat);
    printf("credit=%d\n",course.credit);
    printf("faculty id=%d\n",course.faculty_id);
    printf("max seats=%d\n",course.max_seats);
    close(fd);
    char sentMsg[] = "Course added successfully.\n";
    send(client_socket, sentMsg, sizeof(sentMsg), 0);
}
void view_offered_course(int client_socket,int id)
{
    int fd=open("course.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct CourseDetail course;
    int ack=1;
    while(read(fd,&course,sizeof(course)))
    {
        if(course.faculty_id==id)
        {
            send(client_socket,&ack,sizeof(ack),0);
            send(client_socket,&course,sizeof(course),0);
            // send(client_socket,course.name,sizeof(course.name),0);
            // send(client_socket,&course.department,sizeof(course.department),0);
            // send(client_socket,&course.seat,sizeof(course.seat),0);
            // send(client_socket,&course.credit,sizeof(course.credit),0);
        }
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);
}
void delete_course_from_catalog(int client_socket,int id)
{
    int fd=open("course.txt",O_RDWR);
    struct CourseDetail course;
   
    int temp_fd = open("temp.txt", O_CREAT|O_RDWR|S_IRUSR|S_IWUSR,0777);
    
    //reading file and finding id to delete
    while(read(fd,&course,sizeof(course)))
    {
        if(course.id!=id)
        {
            write(temp_fd, &course,sizeof(struct CourseDetail));
        }
    }

    close(fd);
    close(temp_fd);

    remove("course.txt");
    rename("temp.txt", "course.txt");
}
void change_password(int client_socket,int id,char* password)
{
    int fd=open("Faculty.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct facultyDetail faculty;
    while(read(fd,&faculty,sizeof(faculty)))
    {
        if(faculty.id==id)
        {
            strcpy(faculty.password,password);
            printf("%s",faculty.password);
            lseek(fd, -sizeof(faculty), SEEK_CUR); // Move the file pointer back to the beginning of the record
            write(fd, &faculty, sizeof(faculty)); 
            char password[30]="password change successfully..";
            send(client_socket,password,sizeof(password),0);
            break; 
        }   
    }
}