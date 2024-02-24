#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include "structures.c"
void add_student(int client_socket) {

    int fd=open("Student.txt",O_RDWR);
    struct StudentDetail student;
    memset(&student,0,sizeof(student));
    char buff[30];

    struct stat file_info;
    fstat(fd, &file_info);

    if(file_info.st_size != 0){
        lseek(fd,-(sizeof(struct StudentDetail)),SEEK_END);
        struct StudentDetail stucpy;
        read(fd,&stucpy,sizeof(struct StudentDetail));
        student.id = stucpy.id + 1;
    }
    else{
        student.id= 1;
    }

    strcpy(student.password,"initial");
    student.active=1;
    char msg1[]="enter student name:";
    send(client_socket,&msg1,strlen(msg1),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.name,buff);
    memset(&buff,0,sizeof(buff));

    char msg2[]="enter student age:";
    send(client_socket,&msg2,strlen(msg2),0);
    recv(client_socket,&buff,sizeof(buff),0);
    student.age=atoi(buff);
    memset(&buff,0,sizeof(buff));

    char msg3[]="enter student email:";
    send(client_socket,&msg3,strlen(msg3),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.email,buff);
    memset(&buff,0,sizeof(buff));

    char msg4[]="enter student address:";
    send(client_socket,&msg4,strlen(msg4),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.address,buff);
    memset(&buff,0,sizeof(buff));

    lseek(fd,0,SEEK_END);
    write(fd,&student,sizeof(struct StudentDetail));

    printf("Id=%d\n",student.id);
    printf("name=%s\n",student.name);
    printf("password=%s\n",student.password);
    printf("email=%s\n",student.email);
    printf("address=%s\n",student.address);
    printf("active status=%d\n",student.active);

    close(fd);

    // Send success message back to the client
    char successMsg[] = "Student added successfully.\n";
    send(client_socket, successMsg, sizeof(successMsg), 0);
}
void viewStudentDetails(int client_socket)
{
    int file=open("Student.txt",O_RDONLY|O_CREAT,0744);
    
    //send idprompt
    char idprompt[]="enter student id:\n";
    send(client_socket,&idprompt,strlen(idprompt),0);
 
    //recieving id
    char idstr[10];
    int id;
    recv(client_socket,&idstr,sizeof(idstr),0);
    id=atoi(idstr);

    //reaching top of the id we want to access data of 
    int offset=(id-1)*sizeof(struct StudentDetail);
    struct StudentDetail student_detail;

    //using lseek and accessing that information by setting pointer to current offset
    int seekinfo=lseek(file,offset,SEEK_SET);
    int dataread=read(file,&student_detail,sizeof(struct StudentDetail));
    char tmp[10*sizeof(struct StudentDetail)];
    if(student_detail.active==1)
    {
        sprintf(tmp,"\nStudent Id:%d\nname:%s\nage:%d\nemail:%s\naddress:%s\nactive status%d\n",student_detail.id,student_detail.name,student_detail.age,student_detail.email,student_detail.address,student_detail.active);
        send(client_socket,&tmp,strlen(tmp),0);   
    }
    else
    {
        send(client_socket,"student blocked\n",sizeof("student blocked\n"),0);
    } 
}
void add_faculty(int client_socket)
{
   //opening a file and creating a stucture to store the data recieved from client
   int fd=open("Faculty.txt",O_RDWR);
   struct facultyDetail faculty;
   memset(&faculty,0,sizeof(faculty));
   char buff[30];

   struct stat file_info_faculty;
   fstat(fd, &file_info_faculty);

    if(file_info_faculty.st_size!=0){
        lseek(fd,-(sizeof(struct facultyDetail)),SEEK_END);
        struct facultyDetail faculty_cpy;
        read(fd,&faculty_cpy,sizeof(struct facultyDetail));
        faculty.id = faculty_cpy.id+1;
    }
    else{
        faculty.id= 1;
    }

   //setting initial password for now
   strcpy(faculty.password,"initial");

   //sending faculty name prompt
   char msg[]="enter faculty name:";
   send(client_socket,&msg,strlen(msg),0);

   //recieving faculty name and storing in structure
   recv(client_socket,&buff,sizeof(buff),0);
   strcpy(faculty.name,buff);
   memset(&buff,0,sizeof(buff));

   //repeating....

   char msg2[]="enter faculty designation:";
   send(client_socket,&msg2,strlen(msg2),0);

   recv(client_socket,&buff,sizeof(buff),0);
   strcpy(faculty.designation,buff);
   memset(&buff,0,sizeof(buff));

   char msg3[]="enter department name:";
   send(client_socket,&msg3,strlen(msg3),0);

   recv(client_socket,&buff,sizeof(buff),0);
   strcpy(faculty.department,buff);
   memset(&buff,0,sizeof(buff));

   char msg4[]="enter faculty email:";
   send(client_socket,&msg4,strlen(msg4),0);

   recv(client_socket,&buff,sizeof(buff),0);
   strcpy(faculty.email,buff);
   memset(&buff,0,sizeof(buff));

   char msg5[]="enter faculty address:";
   send(client_socket,&msg5,strlen(msg5),0);

   recv(client_socket,&buff,sizeof(buff),0);
   strcpy(faculty.address,buff);
   memset(&buff,0,sizeof(buff));

    lseek(fd,0,SEEK_END);
    write(fd,&faculty,sizeof(struct facultyDetail));

    printf("Id=%d\n",faculty.id);
    printf("name=%s\n",faculty.name);
    printf("password=%s\n",faculty.password);
    printf("designation=%s\n",faculty.designation);
    printf("department=%s\n",faculty.department);
    printf("email=%s\n",faculty.email);
    printf("address=%s\n",faculty.address);

    close(fd);

    // Send success message back to the client
    char successMsg[] = "faculty added successfully.\n";
    send(client_socket, successMsg, sizeof(successMsg), 0);
}
void view_faculty(int client_socket)
{
    int fd=open("Faculty.txt",O_RDONLY|O_CREAT,0744);
    
    //send idprompt
    char idprompt1[]="enter faculty id:\n";
    send(client_socket,&idprompt1,strlen(idprompt1),0);
 
    //recieving id
    char id_str[10];
    int id;
    recv(client_socket,&id_str,sizeof(id_str),0);
    id=atoi(id_str);

    //reaching top of the id we want to access data of 
    int offset=(id-1)*sizeof(struct facultyDetail);
    struct facultyDetail faculty_detail;

    //using lseek and accessing that information by setting pointer to current offset
    lseek(fd,offset,SEEK_SET);
    read(fd,&faculty_detail,sizeof(struct facultyDetail));
    char temp[10*sizeof(struct facultyDetail)];
    sprintf(temp,"\nFaculty id:%d\nname:%s\ndepartment:%s\nemail:%s\naddress:%s\ndesignation:%s\n",faculty_detail.id,faculty_detail.name,faculty_detail.department,faculty_detail.email,faculty_detail.address,faculty_detail.designation);

    send(client_socket,&temp,strlen(temp),0);
    close(fd); 
}
void modify_student(int client_socket)
{
    int file = open("Student.txt", O_RDWR);
    if (file == -1) {
        perror("Error opening file");
    }
    struct StudentDetail stu1;
    char buff1[30];
    char msg15[]="enter student id:";
    send(client_socket,msg15,strlen(msg15),0);
    recv(client_socket,&buff1,sizeof(buff1),0);
    int stu_id=atoi(buff1);
    printf("received id:%d\n",stu_id);
    
    //set the cursor to the end of the previous record
    int offset=(stu_id-1)*sizeof(struct StudentDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&stu1,sizeof(struct StudentDetail));
    printf("Id=%d\n",stu1.id);
    printf("name=%s\n",stu1.name);
    printf("password=%s\n",stu1.password);
    printf("age=%d\n",stu1.age);
    printf("email=%s\n",stu1.email);
    printf("address=%s\n",stu1.address);

    char field[30];
    memset(&field,0,sizeof(field));
    char msg16[]="enter field:";
    send(client_socket,msg16,strlen(msg16),0);
    recv(client_socket,&field,sizeof(field),0);
    printf("received field:%s\n",field);
    
    char value[30];
    memset(&value,0,sizeof(value));
    char msg17[]="enter value:";
    send(client_socket,msg17,strlen(msg17),0);
    recv(client_socket,&value,sizeof(value),0);
    printf("received value:%s\n",value);
    
    //compare each value with field
    if(strcmp(field,"name")==0)
    {
        memset(&stu1.name,0,sizeof(stu1.name));
        memcpy(&stu1.name,&value,strlen(value));
    }
    else if(strcmp(field,"age")==0)
    {
        stu1.age=atoi(value);
    }
    else if(strcmp(field,"email")==0)
    {
        memset(&stu1.email,0,sizeof(stu1.email));
        memcpy(&stu1.email,&value,strlen(value));
    }
    else if(strcmp(field,"address")==0)
    {
        memset(&stu1.address,0,sizeof(stu1.address));
        memcpy(&stu1.address,&value,strlen(value));
    }
    printf("Id=%d\n",stu1.id);
    printf("name=%s\n",stu1.name);
    printf("password=%s\n",stu1.password);
    printf("age=%d\n",stu1.age);
    printf("email=%s\n",stu1.email);
    printf("address=%s\n",stu1.address);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&stu1,sizeof(struct StudentDetail));
    
    char succ_send[]="successfully.\n";
    send(client_socket,succ_send,sizeof(succ_send),0);
    close(file);
    
}

void modify_faculty(int client_socket)
{
    int file = open("Faculty.txt", O_RDWR);
    if (file == -1) {
        perror("Error opening file");
    }
    struct facultyDetail fac1;
    char buff2[30];
    char msg18[]="enter faculty id:";
    send(client_socket,msg18,strlen(msg18),0);
    recv(client_socket,&buff2,sizeof(buff2),0);
    int fac_id=atoi(buff2);
    printf("received id:%d\n",fac_id);
    
    //set the cursor to the end of the previous record
    int offset=(fac_id-1)*sizeof(struct facultyDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&fac1,sizeof(struct facultyDetail));
    printf("Id=%d\n",fac1.id);
    printf("name=%s\n",fac1.name);
    printf("password=%s\n",fac1.password);
    printf("department=%s\n",fac1.department);
    printf("email=%s\n",fac1.email);
    printf("address=%s\n",fac1.address);
    printf("designation=%s\n",fac1.designation);

    char fac_field[30];
    memset(&fac_field,0,sizeof(fac_field));
    char msg19[]="enter field:";
    send(client_socket,msg19,strlen(msg19),0);
    recv(client_socket,&fac_field,sizeof(fac_field),0);
    printf("received field:%s\n",fac_field);
    
    char fac_value[30];
    memset(&fac_value,0,sizeof(fac_value));
    char msg20[]="enter value:";
    send(client_socket,msg20,strlen(msg20),0);
    recv(client_socket,&fac_value,sizeof(fac_value),0);
    printf("received value:%s\n",fac_value);
    
    //compare each value with field
    if(strcmp(fac_field,"name")==0)
    {
        memset(&fac1.name,0,sizeof(fac1.name));
        memcpy(&fac1.name,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"department")==0)
    {
        memset(&fac1.department,0,sizeof(fac1.department));
        memcpy(&fac1.department,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"email")==0)
    {
        memset(&fac1.email,0,sizeof(fac1.email));
        memcpy(&fac1.email,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"address")==0)
    {
        memset(&fac1.address,0,sizeof(fac1.address));
        memcpy(&fac1.address,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"designation")==0)
    {
        memset(&fac1.designation,0,sizeof(fac1.designation));
        memcpy(&fac1.designation,&fac_value,strlen(fac_value));
    }
    printf("Id=%d\n",fac1.id);
    printf("name=%s\n",fac1.name);
    printf("password=%s\n",fac1.password);
    printf("department=%s\n",fac1.designation);
    printf("email=%s\n",fac1.department);
    printf("address=%s\n",fac1.email);
    printf("designation=%s\n",fac1.address);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&fac1,sizeof(struct facultyDetail));
    
    char fac_send[]="successfully.\n";
    send(client_socket,fac_send,sizeof(fac_send),0);
    close(file);
    
}
void activate_student(int client_socket)
{
    char student_id_str[10];
    int student_id;
    char prompt[] = "Enter the ID of the student to activate: ";
    send(client_socket, prompt, strlen(prompt), 0);
    recv(client_socket, student_id_str, sizeof(student_id_str), 0);
    student_id = atoi(student_id_str);

    
    int student_file = open("Student.txt", O_RDWR);

    //at the end of the previous record
    int offset = (student_id - 1) * sizeof(struct StudentDetail);
    int seek_result = lseek(student_file, offset, SEEK_SET);

    struct StudentDetail student;
    read(student_file, &student, sizeof(struct StudentDetail));

    // Activate the student
    student.active = 1;

    //set the cursor to the start of that record
    lseek(student_file, offset, SEEK_SET);
    write(student_file, &student, sizeof(struct StudentDetail));


    close(student_file);

    char success_txt[] = "Student activated successfully.\n";
    send(client_socket, success_txt, sizeof(success_txt), 0);
}
void block_student(int client_socket)
{
    char student_id_str1[10];
    int student_id1;

    // Prompt the admin to enter the student's ID
    char prompt1[] = "Enter the ID of the student to block: ";
    send(client_socket, prompt1, strlen(prompt1), 0);
    recv(client_socket, student_id_str1, sizeof(student_id_str1), 0);
    student_id1 = atoi(student_id_str1);

    // Open the student data file (Student.txt) for reading and writing
    int student_file = open("Student.txt", O_RDWR);

    // Calculate the offset to the student's data
    int offset = (student_id1 - 1) * sizeof(struct StudentDetail);

    // Seek to the student's data in the file
    int seek_result = lseek(student_file, offset, SEEK_SET);

    // Read the student's data
    struct StudentDetail student;
    int read_result = read(student_file, &student, sizeof(struct StudentDetail));

    // Activate the student
    student.active = 0;

    // Seek back to the student's data and write the updated information
    int write_result = lseek(student_file, offset, SEEK_SET);

    int write_result2 = write(student_file, &student, sizeof(struct StudentDetail));

    // Close the student data file
    close(student_file);

    // Send a success message to the admin
    char success_msg[] = "Student blocked successfully.\n";
    send(client_socket, success_msg, sizeof(success_msg), 0);
}