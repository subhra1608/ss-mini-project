#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "admin.c"
#include "student.c"
#include "faculty.c"

void handle_client(int client_socket) {

    char string[20];
    char buff[] = "----------Welcome to Academia ----------\n"
    "Choose login type \n"
    "1. Admin\t 2. Faculty\t 3. Student\n";

    //sending menu to client
    int bytesSend = send(client_socket,&buff,sizeof(buff),0);

    //recieving choice from client
    int recvBytes = recv(client_socket,&string,sizeof(string),0);
    string[recvBytes] = '\0';
    int choice = atoi(string);

    switch(choice) {
    case 1:
        char menu_admin[] = "Choose from the following options\n 1) Add Student \n 2) View Student Details \n 3) Add Faculty\n 4) View Faculty Details\n 5) Activate Student\n 6) Block Student\n 7) Modify Student Details\n 8) Modify Faculty Details\n 9) Logout and Exit\n ";
        send(client_socket,menu_admin,strlen(menu_admin), 0);
     while(1){
      //if choice is 1 send admin menu
     char admin_choice;
     recv(client_socket, &admin_choice,sizeof(admin_choice), 0);
     //call to respective c functions
     if(admin_choice=='1')
     {
        //add student
       add_student(client_socket);
     }
     if(admin_choice=='2')
     {
        //view student
        viewStudentDetails(client_socket);
     }
     if(admin_choice=='3')
     {
        //add faculty
        add_faculty(client_socket);
     }
     if(admin_choice =='4')
     {
        //view faculty
        view_faculty(client_socket);
     }
     if(admin_choice=='5')
     {
        //activate student
        activate_student(client_socket);
     }
     if(admin_choice=='6')
     {
        //block student
        block_student(client_socket);
     }
     if(admin_choice=='7')
     {
        //modify student details
        modify_student(client_socket);
     }
     if(admin_choice=='8')
     {
        //modify faculty details
        modify_faculty(client_socket);
     }
     if(admin_choice=='q') break;
    }
     break;
    case 2:
      char login_prompt[]="enter login id:";
      char password_prompt[]="enter password:";
      char recv_login_id[30];
      char recv_password[30];
      //sending login prompt
      send(client_socket,login_prompt,strlen(login_prompt),0);

      //recieving login id
      recv(client_socket,&recv_login_id,sizeof(recv_login_id),0);
      int id=atoi(recv_login_id);
      printf("%d\n",id);

      //sending password prompt
      send(client_socket,password_prompt,strlen(password_prompt),0);

      //recieving password
      recv(client_socket,&recv_password,sizeof(recv_password),0);
      printf("%s\n",recv_password);
      
      //sending valid value to check if user is found or not
      int valid = login_faculty(client_socket,id,recv_password);
      send(client_socket,&valid,sizeof(valid),0);

      if(valid==1)
      {
        char result[]="login successfull....welcome faculty\n";
        send(client_socket,result,strlen(result),0);

        //if login is successfull send faculty menu
        char menu_faculty[] = "Choose from the following options\n 1) Add Course \n 2) View Offering Courses\n 3)Remove Course From Catalog\n 4)Update Course Details\n 5)Change Password\n 6)Logout and Exit\n";
        send(client_socket,menu_faculty,strlen(menu_faculty),0);

        //recieve choice of faculty
        int faculty_choice;
        recv(client_socket,&faculty_choice,sizeof(faculty_choice),0);
        printf("%d",faculty_choice); 

        if(faculty_choice==1)
        {
            add_course(client_socket,id);
        }
        if(faculty_choice==2)
        {
            view_offered_course(client_socket,id);
        }
        if(faculty_choice==3)
        {
            //sending delete prompt 
            char delete_prompt[]="select course id you want to delete:";
            send(client_socket,delete_prompt,strlen(delete_prompt),0);

            //recieving course id to delete
            int c_id;
            recv(client_socket,&c_id,sizeof(c_id),0);

            delete_course_from_catalog(client_socket,c_id);
        }
        if(faculty_choice==5)
        {
            //asking password of user
            char old_password[]="enter password:";
            send(client_socket,old_password,strlen(old_password),0);
            
            //recieving password of user
            char password[20];
            recv(client_socket,&password,sizeof(password),0);
            
            change_password(client_socket,id,password);
            
        }
      }
      else
      {
        char result[]="invalid credentials...try again\n";
        send(client_socket,result,strlen(result),0);
      } 
     break;
     case 3:
      char login_prompt_s[]="enter login id:";
      char password_prompt_s[]="enter password:";
      char recv_login_id_s[30];
      char recv_password_s[30];

      //sending login prompt
      send(client_socket,login_prompt_s,strlen(login_prompt_s),0);

      //recieving login id
      recv(client_socket,&recv_login_id_s,sizeof(recv_login_id_s),0);
      int id_s=atoi(recv_login_id_s);
      printf("%d\n",id_s);

      //sending password prompt
      send(client_socket,password_prompt_s,strlen(password_prompt_s),0);

      //recieving password
      recv(client_socket,&recv_password_s,sizeof(recv_password_s),0);
      printf("%s\n",recv_password_s);
      
      //sending valid value to check if user is found or not
      int valid_s = login_student(client_socket,id_s,recv_password_s);
      send(client_socket,&valid_s,sizeof(valid_s),0);

      if(valid_s==1)
      {
        char result[]="login successful....welcome student\n";
        send(client_socket,result,strlen(result),0);

        //if login is successfull send faculty menu
        char menu_student[] = "Choose from the following options\n 1) View Courses \n 2) Enroll(Pick) New Course \n 3) Drop Course\n 4) View Enrolled Course Details\n 5) Change Password\n 6) Logout And Exit\n";
        send(client_socket,menu_student,strlen(menu_student),0);
        
        //recieve choice of student
        int student_choice;
        recv(client_socket,&student_choice,sizeof(student_choice),0);
        if(student_choice==1)
        {
            view_offered_courses_to_student(client_socket,id_s);
        }
        if(student_choice==2)
        {
            //courseid prompt
            send(client_socket,"which course id you want to register?",sizeof("which course id you want to register?"),0);

            //recieve courseid
            int course_id;
            recv(client_socket,&course_id,sizeof(course_id),0);

            enroll_course(client_socket,id_s,course_id);
        }
        if(student_choice==3)
        {
            //asking the user which course they want to denroll
            send(client_socket,"Enter the course id you want to denroll for: ",sizeof("Enter the course id you want to denroll for: "),0);

            //recieving course id
            int course_id;
            recv(client_socket,&course_id,sizeof(course_id),0);

            //calling de-enroll function
            denroll_student(client_socket,id_s,course_id);
        }
        if(student_choice==4)
        {
            view_enrolled_course_details(client_socket,id_s);
        }
        if(student_choice==5)
        {
            //asking password of user
            char old_password_s[]="enter password:";
            send(client_socket,old_password_s,strlen(old_password_s),0);
            
            //recieving password of user
            char password_s[20];
            recv(client_socket,&password_s,sizeof(password_s),0);
            
            change_password_s(client_socket,id_s,password_s);
        }
      }
      else
      {
        char result[]="invalid credentials...try again\n";
        send(client_socket,result,strlen(result),0);
      } 
    default:
        close(client_socket);
    }
        printf("\n");
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    if (listen(server_socket, 10) == 0) {
        printf("Server listening on port %d...\n", ntohs(server_addr.sin_port));
    } else {
        perror("Error listening");
        exit(1);
    }

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

        if (client_socket < 0) {
            perror("Error accepting client");
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Error forking");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else {
            // Parent process
            close(client_socket);
        }
    }
    return 0;
}