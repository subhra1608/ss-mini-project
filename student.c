#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
bool login_student(int client_socket,int id,char* password)
{
    printf("%d",id);
    printf("%s",password);
    int file=open("Student.txt",O_RDONLY);
    struct StudentDetail student ;
    int found=0;

    //reading file and checking if id and passwords match
    while(read(file,&student,sizeof(struct StudentDetail)))
    {
        if(student.id==id)
        {
           if(strcmp(student.password,password)==0)
           {
            found=1;
            break;
           }
        }
    }
    close(file);
    return found;    
}
void enroll_course(int client_socket,int student_id,int course_id)
{
    //open faculty file 
   int fd=open("Faculty.txt",O_RDONLY);
    
   //open course file
   int fd2=open("course.txt",O_RDWR);

   //open enrolled courses file
   int fd3=open("enrolled_courses.txt",O_RDWR,0777);
   int flag=0;
   struct CourseDetail course;
   struct course_enrolled course_enr;  
 while(read(fd2,&course,sizeof(struct CourseDetail)))
 {
    if(course.id==course_id)
    {
      while(read(fd3,&course_enr,sizeof(course_enr)))
      {
        if(course_enr.student_id==student_id&&course_enr.course_id==course_id)
        {
           if(course.seat>0)
           {
            flag=1;
            lseek(fd2,-(sizeof(struct CourseDetail)),SEEK_CUR);
            struct CourseDetail course_copy;
            course_copy.id=course_id;
            course_copy.faculty_id=course.faculty_id;
            strcpy(course_copy.name,course.name);
            strcpy(course_copy.department,course.department);
            course_copy.seat=course.seat-1;
            course_copy.max_seats=course.max_seats;
            course_copy.credit=course.credit;
            write(fd2,&course_copy,sizeof(struct CourseDetail));
            send(client_socket,"Successfully Enrolled\n",sizeof("Successfully Enrolled"),0);
            lseek(fd3,-(sizeof(struct course_enrolled)),SEEK_CUR);
            struct course_enrolled course_en;
            course_en.student_id=student_id;
            course_en.course_id=course_id;
            course_en.enrolled=1;
            strcpy(course_en.course_name,course.name);
            course_en.faculty_id=course.faculty_id;     
            write(fd3,&course_en,sizeof(struct course_enrolled));           
           }
           else
           {
            send(client_socket,"Sorry No Seats Available.....\n",sizeof("Sorry No Seats Available...Try Later Sometime"),0);
           }
        }
        
      } 

      if(course.seat>0&&flag==0)
      {
        lseek(fd2,-(sizeof(struct CourseDetail)),SEEK_CUR);
        struct CourseDetail course_copy;
        course_copy.id=course_id;
        course_copy.faculty_id=course.faculty_id;
        strcpy(course_copy.name,course.name);
        strcpy(course_copy.department,course.department);
        course_copy.seat=course.seat-1;
        course_copy.max_seats=course.max_seats;
        course_copy.credit=course.credit;
        write(fd2,&course_copy,sizeof(struct CourseDetail));
        send(client_socket,"Successfully Enrolled\n",sizeof("Successfully Enrolled"),0);
        lseek(fd3,0,SEEK_END);
        struct course_enrolled course_en;
        course_en.student_id=student_id;
        course_en.course_id=course_id;
        course_en.enrolled=1;
        strcpy(course_en.course_name,course.name);
        course_en.faculty_id=course.faculty_id;
        write(fd3,&course_en,sizeof(struct course_enrolled));           
     }
     else
     {
        send(client_socket,"Sorry No Seats Available.....\n",sizeof("Sorry No Seats Available...Try Later Sometime"),0);
     }
    }      
 }
  close(fd);
  close(fd2);
  close(fd3);
}
void denroll_student(int client_socket,int student_id,int course_id)
{
    int fd=open("Faculty.txt",O_RDONLY);
    int fd2=open("course.txt",O_RDWR);
    int fd3=open("enrolled_courses.txt",O_RDWR);
    if(fd==-1||fd2==-1||fd3==-1)
    {
        perror("ERROR:");
    }
    struct CourseDetail course;
    struct course_enrolled course_enr;
    while((read(fd2,&course,sizeof(struct CourseDetail))))
    {        
     if(course.id==course_id)
     {
        while((read(fd3,&course_enr,sizeof(struct course_enrolled))))
        {
          if(course_enr.student_id==student_id&&course_enr.course_id==course_id)
          {
            if(course.seat<course.max_seats)
            {   
             lseek(fd2,-(sizeof(struct CourseDetail)),SEEK_CUR);
             struct CourseDetail course_copy;
             course_copy.id=course_id;
             course_copy.faculty_id=course.faculty_id;
             strcpy(course_copy.name,course.name);
             strcpy(course_copy.department,course.department);
             course_copy.seat=course.seat+1;
             course_copy.max_seats=course.max_seats;
             course_copy.credit=course.credit;
             write(fd2,&course_copy,sizeof(struct CourseDetail));
             lseek(fd3,-(sizeof(struct course_enrolled)),SEEK_CUR);
             struct course_enrolled course_en;
             course_en.student_id=student_id;
             course_en.course_id=course_id;
             strcpy(course_en.course_name,course.name);
             course_en.faculty_id=course.faculty_id;
             course_en.enrolled=0;
             write(fd3,&course_en,sizeof(struct course_enrolled));    
            }
            else
            {
            send(client_socket,"not allowed",sizeof("not allowed"),0);
            }
          }
        }   
    }  
  }    
}
void view_enrolled_course_details(int client_socket,int student_id)
{
    int fd=open("enrolled_courses.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct course_enrolled course;
    int ack=1;
    // printf("after 1\n");
    while(read(fd,&course,sizeof(course)))
    {
        if(course.student_id==student_id && course.enrolled==1)
        {
            send(client_socket,&ack,sizeof(ack),0);
            send(client_socket,&course,sizeof(course),0);
        }
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);
}
void view_offered_courses_to_student(int client_socket,int student_id)
{
    int fd=open("course.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct CourseDetail course_view;
    int ack=1;
    while(read(fd,&course_view,sizeof(course_view)))
    {
    
        send(client_socket,&ack,sizeof(ack),0);
        send(client_socket,&course_view,sizeof(course_view),0);
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);   
}
void change_password_s(int client_socket,int id,char* password)
{
    int fd=open("Student.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct StudentDetail student;
    while(read(fd,&student,sizeof(student)))
    {
        if(student.id==id)
        {
            strcpy(student.password,password);
            printf("%s",student.password);
            lseek(fd, -sizeof(student), SEEK_CUR); // Move the file pointer back to the beginning of the record
            write(fd, &student,sizeof(student)); 
            char password[30]="password change successfully..";
            send(client_socket,password,sizeof(password),0);
            break; 
        }   
    }
}