#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "structures.c"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // (error checking code...)

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // (error checking code...)

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    printf("Successfully created connection with server.\n");

    //recieving main menu prompt and writing to standard output
    char buf[200];
    int recvdata = recv(client_socket,&buf,sizeof(buf),0);
    int writedata = write(1,buf,recvdata);
    
    //taking user choice to login as
    char choiceprompt[] ="Enter your choice : ";
    writedata = write(1,choiceprompt,sizeof(choiceprompt));

    char readchoice;
    int choice = read(0,&readchoice,sizeof(readchoice));

    //sending choice to server
    int senddata = send(client_socket,&readchoice,sizeof(readchoice),0);

    if(readchoice=='1')
    {
     char server_response_admin[512];
     memset(server_response_admin,0,512*sizeof(char));
     //strcpy(server_response_admin,"");
     recv(client_socket, &server_response_admin, sizeof(server_response_admin), 0);
      while(1){
     //admin menu
     //getting the admin menu sent from server

     printf("%s",server_response_admin);

     //taking choice from that admin menu
     char choice_admin;
     printf("Enter your choice admin: ");
     scanf(" %c", &choice_admin);
     send(client_socket, &choice_admin, sizeof(choice_admin), 0);

     if(choice_admin=='q') break;

     //add student
     if(choice_admin=='1')
     {
            char buffer[512],ques[30];
            memset(ques,0,sizeof(ques));
            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s\n",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s\n",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s\n",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

        //printing student added successfully 
        char server_response[512];
        recv(client_socket, server_response, sizeof(server_response), 0);
        printf("%s", server_response);
     }

     if(choice_admin=='2')
     {
        //recieving idprompt
        char idprompt[50];
        memset(idprompt,0,sizeof(idprompt));
        recv(client_socket,idprompt,sizeof(idprompt),0);
        printf("%s",idprompt);

        //sending id
        char send_id[10];
        scanf("%s",send_id);
        send(client_socket,send_id,sizeof(send_id),0);

        //recieving the student data
        char studentData[300];
        recv(client_socket,&studentData,sizeof(studentData),0);
        printf("%s",studentData);        
     }
     if(choice_admin=='3')
     {
        char buffer[512],faculty_buff[30];
        memset(faculty_buff,0,sizeof(faculty_buff));

        //recieving faculty name prompt
        recv(client_socket,&faculty_buff,sizeof(faculty_buff),0);
        printf("%s\n",faculty_buff);
        memset(faculty_buff,0,sizeof(faculty_buff));

        //sending the faculty name
        scanf("%s",faculty_buff);
        send(client_socket,faculty_buff,sizeof(faculty_buff),0);
        memset(&faculty_buff,0,sizeof(faculty_buff));

        //repeating...

        recv(client_socket,&faculty_buff,sizeof(faculty_buff),0);
        printf("%s\n",faculty_buff);
        memset(faculty_buff,0,sizeof(faculty_buff));

        scanf("%s",faculty_buff);
        send(client_socket,faculty_buff,sizeof(faculty_buff),0);
        memset(&faculty_buff,0,sizeof(faculty_buff));

        recv(client_socket,&faculty_buff,sizeof(faculty_buff),0);
        printf("%s\n",faculty_buff);
        memset(faculty_buff,0,sizeof(faculty_buff));

        scanf("%s",faculty_buff);
        send(client_socket,faculty_buff,sizeof(faculty_buff),0);
        memset(&faculty_buff,0,sizeof(faculty_buff));

        recv(client_socket,&faculty_buff,sizeof(faculty_buff),0);
        printf("%s\n",faculty_buff);
        memset(faculty_buff,0,sizeof(faculty_buff));

        scanf("%s",faculty_buff);
        send(client_socket,faculty_buff,sizeof(faculty_buff),0);
        memset(&faculty_buff,0,sizeof(faculty_buff));

        recv(client_socket,&faculty_buff,sizeof(faculty_buff),0);
        printf("%s\n",faculty_buff);
        memset(faculty_buff,0,sizeof(faculty_buff));

        scanf("%s",faculty_buff);
        send(client_socket,faculty_buff,sizeof(faculty_buff),0);
        memset(&faculty_buff,0,sizeof(faculty_buff));

        //printing student added successfully 
        char server_response[512];
        recv(client_socket, server_response, sizeof(server_response), 0);
        printf("%s", server_response);
     }
     if(choice_admin=='4')
     {
        char id_prompt[50];
        memset(id_prompt,0,sizeof(id_prompt));
        recv(client_socket,id_prompt,sizeof(id_prompt),0);
        printf("%s",id_prompt);

        //sending id
        char send_id1[10];
        scanf("%s",send_id1);
        send(client_socket,send_id1,sizeof(send_id1),0);

        //recieving the student data
        char student_data[300];
        memset(student_data,0,sizeof(student_data));
        recv(client_socket,&student_data,sizeof(student_data),0);
        printf("%s",student_data); 
     }
     if(choice_admin=='5')
     {
        char get_sid[50];
        memset(get_sid,0,sizeof(get_sid));
        recv(client_socket,get_sid,sizeof(get_sid),0);
        printf("%s",get_sid);
        memset(get_sid,0,sizeof(get_sid));
        scanf("%s",get_sid);
        send(client_socket,get_sid,sizeof(get_sid),0);
        memset(get_sid,0,sizeof(get_sid));
        char s_response[400];
        memset(s_response,0,sizeof(s_response));
        recv(client_socket,s_response,sizeof(s_response),0);
        printf("%s",s_response);
     } 
     if(choice_admin=='6')
     {
        char get_sid[50];
        memset(get_sid,0,sizeof(get_sid));
        recv(client_socket,get_sid,sizeof(get_sid),0);
        printf("%s",get_sid);
        memset(get_sid,0,sizeof(get_sid));
        scanf("%s",get_sid);
        send(client_socket,get_sid,sizeof(get_sid),0);
        memset(get_sid,0,sizeof(get_sid));
        char s_response[400];
        memset(s_response,0,sizeof(s_response));
        recv(client_socket,s_response,sizeof(s_response),0);
        printf("%s",s_response);  
     }
     if(choice_admin=='7')
     {

        char get_id[30],set_id[30];
        // int set_id;
        memset(get_id,0,sizeof(get_id));
        recv(client_socket,get_id,sizeof(get_id),0);
        printf("%s",get_id);
        scanf("%s",set_id);
        send(client_socket,set_id,sizeof(int),0);

        char get_field[30],set_field[30];
        memset(get_field,0,sizeof(get_field));
        recv(client_socket,get_field,sizeof(get_field),0);
        printf("%s",get_field);
        scanf("%s",set_field);
        send(client_socket,set_field,sizeof(set_field),0);

        char get_value[30],set_value[30];
        memset(get_value,0,sizeof(get_value));
        recv(client_socket,get_value,sizeof(get_value),0);
        printf("%s",get_value);
        scanf("%s",set_value);
        send(client_socket,set_value,sizeof(set_value),0);

        char gotit[40];
        memset(gotit,0,sizeof(gotit));
        recv(client_socket,&gotit,sizeof(gotit),0);
        printf("%s",gotit);
     }
     if(choice_admin=='8')
     {

        char get_id[30],set_id[30];
        // int set_id;
        memset(get_id,0,sizeof(get_id));
        recv(client_socket,get_id,sizeof(get_id),0);
        printf("%s",get_id);
        scanf("%s",set_id);
        send(client_socket,set_id,sizeof(int),0);

        char get_field[30],set_field[30];
        memset(get_field,0,sizeof(get_field));
        recv(client_socket,get_field,sizeof(get_field),0);
        printf("%s",get_field);
        scanf("%s",set_field);
        send(client_socket,set_field,sizeof(set_field),0);

        char get_value[30],set_value[30];
        memset(get_value,0,sizeof(get_value));
        recv(client_socket,get_value,sizeof(get_value),0);
        printf("%s",get_value);
        scanf("%s",set_value);
        send(client_socket,set_value,sizeof(set_value),0);

        char gotit[40];
        memset(gotit,0,sizeof(gotit));
        recv(client_socket,&gotit,sizeof(gotit),0);
        printf("%s",gotit);
     }

    }
}

if(readchoice=='2')
{
        //faculty module
        char login_prompt[30];
        char send_login_id[30];
        char password_prompt[30];
        char send_password[30];

        //recieving login prompt
        recv(client_socket,&login_prompt,sizeof(login_prompt),0);
        printf("%s",login_prompt);
  
        //sending login id
        scanf("%s",send_login_id);
        send(client_socket,send_login_id,sizeof(send_login_id),0);

        //recieving password prompt
        recv(client_socket,&password_prompt,sizeof(password_prompt),0);
        printf("%s",password_prompt);

        //sending password
        scanf("%s",send_password);
        send(client_socket,send_password,sizeof(send_password),0);

       //recieving valid value
       int valid;
       recv(client_socket,&valid,sizeof(valid),0);
       if(valid==1)
       {
        char result[37];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
        
        //if login is successfull recieve faculty menu
        char server_response_faculty[512];
        memset(server_response_faculty,0,512*sizeof(char));
        recv(client_socket, &server_response_faculty, sizeof(server_response_faculty),0);
        printf("%s",server_response_faculty);

        //take choice of function to execute
        int choice;
        scanf("%d",&choice);
        send(client_socket,&choice,sizeof(choice),0);
        
        if(choice==1)
        {
            // struct StudentDetail newStudent;
           char buffer[512],fac_ques[30];
            memset(&fac_ques,0,sizeof(fac_ques));
            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            char fac_rec_msg[512];
            recv(client_socket, &fac_rec_msg, sizeof(fac_rec_msg), 0);
            printf("%s\n", fac_rec_msg);
        }

        if(choice==2)
        {
            int ack;
            while(1)
            {
              recv(client_socket,&ack,sizeof(ack),0);
              if(ack==0)break;
              struct CourseDetail course;
              recv(client_socket,&course,sizeof(course),0);
              printf("Course Id=%d\n",course.id);
              printf("Course Name=%s\n",course.name);
              printf("Department offering course=%s\n",course.department);
              printf("Number of Seats=%d\n",course.seat);
              printf("course credit=%d\n",course.credit);
            }       
        }
        if(choice==3)
        {
            //recieving delete prompt
            char delete_propmt[40];
            recv(client_socket,&delete_propmt,sizeof(delete_propmt),0);
            printf("%s",delete_propmt);

            //sending id to delete
            int sendId;
            scanf("%d",&sendId);
            send(client_socket,&sendId,sizeof(sendId),0);
        }
        if(choice==5)
        {
            //recieving password prompt
            char recv_pasword[30];
            recv(client_socket,&recv_pasword,sizeof(recv_pasword),0);
            printf("%s",recv_pasword);

            //sending password of user
            char password[20];
            scanf("%s",password);
            send(client_socket,password,sizeof(password),0);

            char result[30];
            recv(client_socket,&result,sizeof(result),0);
            printf("%s",result);
        }
     }
 
     else
       {
        char result[32];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
       }
}
    if(readchoice=='3')
    {
        //student module
        char login_prompt[30];
        char send_login_id[30];
        char password_prompt[30];
        char send_password[30];

        //recieving login prompt
        recv(client_socket,&login_prompt,sizeof(login_prompt),0);
        printf("%s",login_prompt);
  
        //sending login id
        scanf("%s",send_login_id);
        send(client_socket,send_login_id,sizeof(send_login_id),0);

        //recieving password prompt
        recv(client_socket,&password_prompt,sizeof(password_prompt),0);
        printf("%s",password_prompt);

        //sending password
        scanf("%s",send_password);
        send(client_socket,send_password,sizeof(send_password),0);

       //recieving valid value
       int valid;
       recv(client_socket,&valid,sizeof(valid),0);
       if(valid==1)
       {
        char result[35];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
        
        //if login is successfull recieve student menu
        char server_response_student[512];
        memset(server_response_student,0,512*sizeof(char));
        recv(client_socket, &server_response_student, sizeof(server_response_student),0);
        printf("%s",server_response_student);

        //take choice of function to execute
        int choice;
        scanf("%d",&choice);
        send(client_socket,&choice,sizeof(choice),0);
        if(choice==1)
        {
            int ack;
            while(1)
            {
              recv(client_socket,&ack,sizeof(ack),0);
              if(ack==0)break;
              struct CourseDetail course;
              recv(client_socket,&course,sizeof(course),0);
              printf("Course id=%d\n",course.id);
              printf("Course Name=%s\n",course.name);
              printf("Department offering course=%s\n",course.department);
              printf("Number of Seats=%d\n",course.seat);
              printf("course credit=%d\n",course.credit);
            }    
        }
        if(choice==2)
        {
            //recieve choice of course
            char course_id_prompt[40];
            recv(client_socket,&course_id_prompt,sizeof(course_id_prompt),0);
            printf("%s",course_id_prompt);

            //send courseid
            int course_id;
            scanf("%d",&course_id);
            send(client_socket,&course_id,sizeof(course_id),0); 

            char buff[30];
            recv(client_socket,&buff,sizeof(buff),0);
            printf("%s",buff);
        }
        if(choice==3)
        {
            //recieving course id prompt
            char denroll[45];
            recv(client_socket,&denroll,sizeof(denroll),0);
            printf("%s",denroll);

            //taking user choice for course id
            int course_id;
            scanf("%d",&course_id);
            send(client_socket,&course_id,sizeof(course_id),0);
        }
        if(choice==4)
        {
            int stu_ack;
            while(1)
            {
              recv(client_socket,&stu_ack,sizeof(stu_ack),0);
              if(stu_ack==0)break;
              struct course_enrolled stu_course;
              recv(client_socket,&stu_course,sizeof(stu_course),0);
              printf("Course id=%d\n",stu_course.course_id);
              printf("Course Name=%s\n",stu_course.course_name);
              printf("student id=%d\n",stu_course.student_id);
              printf("faculty id=%d\n",stu_course.faculty_id);        
            }    
        }
        if(choice==5)
        {
            //recieving password prompt
            char recv_pasword_s[30];
            recv(client_socket,&recv_pasword_s,sizeof(recv_pasword_s),0);
            printf("%s",recv_pasword_s);

            //sending password of user
            char password_s[20];
            scanf("%s",password_s);
            send(client_socket,password_s,sizeof(password_s),0);

            char result_s[30];
            recv(client_socket,&result_s,sizeof(result_s),0);
            printf("%s",result_s);
        }
     }
       else
       {
        char result[32];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
       }
    }  
    close(client_socket);
    return 0;
}