#include<stdio.h>

/* Function to decrypt the size of the text hidden in the image */
void size_decryption(FILE *pf1, int *size_txt)         //.........................................................
{
//pf1 represent img file and other representing the int where size will be stored

    int file_buff = 0, i;  //reconstruct size of the hidden text;;counter hai agla
    int ch; //Represents the current character read from the image file
    int bit_msg; //  Stores the least significant bit of the current character

    // Loop through the first 8 bytes to extract the size information
    for (i = 0; i < 8; i++)
    {
        ch = fgetc(pf1);
        bit_msg = (ch & 1); //it is lsb .fuction reads it to re-construct the size

        // Extract the bit and reconstruct the size
        if (bit_msg) // Reconstruct the size by shifting the bits and adding the extracted bit
        {
            file_buff = (file_buff << 1) | 1; // sets the bit('bit_msg') tp 1
        }
        else 
        {
            file_buff = file_buff << 1; //shift file buff to 1
        }
    }
    *size_txt = file_buff;
}

/* Function to decrypt a string hidden in the image */
void string_decryption(FILE *pf1, char *strng, int size)//.......................................................................
  {              //file*pf1 use ho rha img file ke liye (as above)..
                //char points to where decrypted string will be stored
                // int size mein size of hidden string hai

    int file_buff = 0;//reconstruct eacn character of hidden msg
     int i; // loop counter ke liye used hoga
     int j = 0; //counter to track no of bits processed in each byte
     int k = 0; //store char in output string 
    int ch;// represent the curret character read from the img file
    int bit_msg; //stores the LSB of current character


    // Loop through each byte in the hidden string 8 bits in total
    for (i = 0; i < (size * 8); i++)
    {
        j++;    //Bit counter ka increment
        ch = fgetc(pf1);    //har character ko read krta hai so that LSB can be found out from bit_msg
        bit_msg = (ch & 1);  //stores the LSB(As done before)
             
        // Extract the bit and reconstruct the character
        if (bit_msg) //LSB storage true it sets this bit in file_buff to 1.
        {
            file_buff = (file_buff << 1) | 1;      //   | is a bitwise operator.
        }
        else  //agr false to left pe shift kr dega
        {
            file_buff = file_buff << 1;
        }

        // When 8 bits are accumulated, store the character in the output string
        if (j == 8)
        {
            strng[k] = (char)file_buff;      // explicit typecasting
            j = 0;   //reset ho jaega to 0
            k++; // k mein increment ho jae ga
            file_buff = 0;  //file buff to 0 for next iteration.
        }
    }
    // Null-terminate the output string
    strng[k] = '\0'; // "\0" in strings represents end as well 
}

/* Function to decrypt the secret message hidden in the image */
void secret_decryption(int size_txt, FILE *pf1, FILE *pf2)            //.............................................................
 {     //size_txt is size of previous decrypted string
       //pf1 for -i
       // pf2 for -o upcomng decrypted text


    int file_buff = 0;  //reconstruct each char of secret msg
    int i; //loop counter
    int j = 0;  //track of no of bits processed in each byte
    int k = 0;  //store char in output array
    int ch;  //tell about the current char read by the img
    int bit_msg;  //store LSB of each char
    char output[250] = {0};  //stores decrypted msg

    // Loop through each byte in the secret message (size_txt*8 bits in total)
    for (i = 0; i < (size_txt * 8); i++)
    {
        j++;   //counter++
        ch = fgetc(pf1); //reads the char
        bit_msg = (ch & 1);   ///extracting the LSB

        // reconstruct the character by adding extracted bit.
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1; //If LSB is 1 set file_buff to 1
        }
        else
        {
            file_buff = file_buff << 1; // If LSB 0, file_buff shift to left
        }

        // When 8 bits are accumulated, write the character to the output file
        if (j == 8)
        {
            putc(file_buff, pf2);     //reconstruction ocurs here
            output[k++] = file_buff;   //output mein sotrage ho rhi(Array)
            j = 0;  // to start next iteration from 0
            file_buff = 0;    //to reconstruct 
        }

        //Next Iteration.
    }
}

/* Main decoding function */
int Decode(char *argv_2, char *argv_4)      //........................................................................
{     //argv_2 for input img file name       
      //argv_4 file name of output txt file


    FILE *pf1, *pf2;       //pointers for the input output file
    int size1, size_txt;   //will store decrypted size info

    // Opening the image file for reading....Agr nhi khulti to error de ga
    if ((pf1 = fopen(argv_2, "r")) == NULL)
    {
        printf("Could not open file %s.\nAborting\n", argv_2);
        return 1; //error
    }

    // Move the file cursor to (offset 54) where the size information is stored in the image
    fseek(pf1, 54, SEEK_SET);

    // Opening a new file for writing the decoded message
    if ((pf2 = fopen(argv_4, "w+")) == NULL)
    {
        printf("Could not open file %s.\nAborting\n", argv_4);
        return 1;
    }

    // Password verification
    char passwd[20], passwd_str[20];
    size_decryption(pf1, &size1);
    string_decryption(pf1, passwd_str, size1);

    printf("Enter The Password: ");
    scanf("%s", passwd);

    int temp = strcmp(passwd, passwd_str);
    if (temp)
    {
        printf("\n*** Entered Wrong Password ***\n");
        return 0;
    }
    else
        printf("*** Password Accepted ***\n");

    // Decrypting the size of the hidden text and the secret message
    size_decryption(pf1, &size_txt);

    // Decrypting the secret message and writing it to the output file
    secret_decryption(size_txt, pf1, pf2);

    printf("The Secret Text is copied to: %s\n\n", argv_4);

    // Close the files
    fclose(pf1);
    fclose(pf2);
    return 0;
}
